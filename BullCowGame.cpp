#pragma once

#include "BullCowGame.h"
#include <map>

// Unreal coding standards require int32 instead of int, etc.
#define TMap std::map
using int32 = int;

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 }, { 4, 7 }, { 5, 10 }, {6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const 
{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() 
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if(!IsIsogram(Guess)) // If guess isn't isogram 
	{
		return EGuessStatus::Not_Isogram; // Return error
	}
	else if(!IsLowerCase(Guess))// If guess isn't all lowercase // TODO write function
	{
		return EGuessStatus::Not_Lowercase; // Return error
	}
	else if(GetHiddenWordLength()!=Guess.length())// If guess has wrong length
	{
		return EGuessStatus::Wrong_Length;// Return error
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter string as isograms
	if(Word.length() <= 1) return true;
	
	//setup map
	TMap<char, bool> LetterSeen; // Using maps instead of sorting algo reduces the efficiency from O(n^2) to O(n)

	// Loop/traverse through the string letter by letter
	for(auto Letter : Word)
	{
		Letter = tolower(Letter); // Handle mixed cases
		
		// Check if the letter exists in the map
		if(LetterSeen[Letter]) return false; // If yes, return false. NOT an isogram
		else LetterSeen[Letter] = true; // If no, insert character in the string in the TMap
		
	}
	// When loop ends if no letter is repeated, return true	
	return true; // For example in cases where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	// Handle \0, space and zero length strings
	if((Guess.length()==0) || (Guess==" ") || (Guess=="")) return false;
	for(auto Letter : Guess)
	{
		if(!islower(Letter)) // Check if uppercase is found return false
		{
			return false; 
		}
		
	}
	return true;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

// Recieves valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	BullCowCount = FBullCowCount();
	int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess

	// Loop through all letters in the hidden word
	for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
	    // Compare letters against the guess word
		for(int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if(Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if(MHWChar == GChar)
				{
					BullCowCount.Bulls++; // Increment bulls if they are in the same place
				}
				else BullCowCount.Cows++; // Else increment cows
			}
		}
	}

	if(BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

FBullCowGame::FBullCowGame() 
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; // ! This MUST be an ISOGRAM
	BullCowCount = FBullCowCount();
	bGameIsWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

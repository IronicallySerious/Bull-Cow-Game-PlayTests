#pragma once

#include "stdafx.h"
#include "FBUllCowGame.h"
#include <map>

//Unreal coding standards require int32 instead of int, etc.
#define TMap std::map
using int32 = int;

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 }, { 4, 7 }, { 5, 10 }, {6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

bool FBullCowGame::IsGameWon() 
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if(!IsIsogram(Guess))//if guess isn't isogram 
	{
		return EGuessStatus::Not_Isogram;// return error
	}
	else if(!IsLowerCase(Guess))//if guess isn't all lowercase // TODO write function
	{
		return EGuessStatus::Not_Lowercase;//return error
	}
	else if(GetHiddenWordLength()!=Guess.length())// if guess has wrong length
	{
		return EGuessStatus::Wrong_Length;//return error
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter string as isograms
	if(Word.length() <= 1) return true;
	
	//setup map
	TMap<char, bool> LetterSeen; // Using maps instead of sorting algo reduces the efficiency from O(n^2) to O(n)

	// loop/traverse through the string letter by letter
	for(auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed cases
		
		// Check if the letter exists in the map
		if(LetterSeen[Letter]) return false; // if yes, return false. NOT an isogram
		else LetterSeen[Letter] = true; // if no, insert character in the string in the TMap
		
	}
	// When loop ends if no letter is repeated, return true	
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	//handle \0, space and zero length strings
	if((Guess.length()==0) || (Guess==" ") || (Guess=="")) return false;
	for(auto Letter : Guess)
	{
		if(!islower(Letter)) // check if uppercase is found return false
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

//recieves valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	BullCowCount = FBullCowCount();
	int32 WordLength = MyHiddenWord.length(); //Assuming same length as guess

	//loop through all letters in the hidden word
	for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
	    //compare letters against the guess word
		for(int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if(Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if(MHWChar == GChar)
				{
					BullCowCount.Bulls++; //increment bulls if they are in the same place
				}
				else BullCowCount.Cows++; //else   //increment cows
			}
			
		}
 
	}
	if(BullCowCount.Bulls == WordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	return BullCowCount;
}

FBullCowGame::FBullCowGame() {Reset();}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; //This MUST be an ISOGRAM
	BullCowCount = FBullCowCount();
	bGameIsWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

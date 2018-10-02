/* This is the console executable that makes use of the BullCow Class
	Acts as a view in MVC pattern and int32is responsible for all user interaction
	For game logic see the FBullCowGame Class.
*/

#pragma once

#include <iostream>
#include <string>
#include "BullCowGame.h"
#include <map>
#define TMap std::map

// Unreal coding standards require int32 instead of int, etc.
using FText = std::string; 
using int32 = int;
FBullCowGame BCGame; // Instantiate a game object

// Prototypes________________________Begin
void PrintIntro();
void PrintGameSummary();
FString SelectWordLength();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
// Prototypes________________________End

 // Entry Point 
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} while(bPlayAgain);

	return 0; // Exit the application
}

void PrintIntro()
{
	// Introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

// Loop continually until valid guess is put
FText GetValidGuess()
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// Get a guess from player
		int CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry<< " of "<< BCGame.GetMaxTries();

		std::cout << ". Enter a guess : ";
		std::getline(std::cin, Guess);

		// Check if the Guess is a valid one. Run tests and report back any errors
		Status = BCGame.CheckGuessValidity(Guess);
		switch(Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter your guess in lowercase.\n";
				break;
			default:
				// Asssuming the guess is valid as all checks have been exhausted
				return Guess;
		}
	} while(Status != EGuessStatus::OK);   // Keep looping till no error comes
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// Plays a single game session to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// Loop asking for guesses while game is NOT won
	// And there are tries remaining
	// Loop for the number of turns asking for guesses
	while((!BCGame.IsGameWon()) && (BCGame.GetCurrentTry() <= MaxTries))
	{
		FText Guess = GetValidGuess(); 
		
		// Submit valid guess to the game and receives number of bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n";
	}
	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if(BCGame.IsGameWon() == true)
	{
		std::cout << "CONGRTULATIONS! YOU WON THE GAME!\n";
	}
	else if(BCGame.GetCurrentTry() == BCGame.GetMaxTries()+1) // Plus 1 because the current try # is incremented after it reaches max value in SubmitValidGuess()
	{
		std::cout << "You exhausted your number of tries! Try again!\n";
	}
	
}

/*
	Below you will find provisional code that never made the cut.
	The function SelectWordLength() was made to let the user select the difficulty
	However, implementing this function resulted in some errors in the object code 
	of the program. Thus any changes done then were reverted but the function 
	definition was preserved
*/
FString SelectWordLength()
{
	std::cout << "Select a word length/difficulty level : \t3 for Easy\t4 for Medium\t5 for Intermediate\t6 for Legendary\nYour option: ";
	int32 Select;
	std::cin >> Select;
	TMap<int32, FString> WordMap{ { 3, "mud" }, { 4, "sour" }, { 5, "pines" }, {6,"planet"} };
	return WordMap[Select];
}

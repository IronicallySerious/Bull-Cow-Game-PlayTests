/*
	The game logic (no view code or direct user interaction)
	The game is a simple guess word game based on mastermind
*/

#pragma once

#include <string>

// Unreal coding standards require int32 instead of int, etc.
using FString = std::string;
using int32 = int;

// Data type for bulls and cows container
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// Defines error messages
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

/*
	This is the game instance.
	All helper functions have been declared inside this class.
	The main function instantiates this class by the
	object name "BCGame".
*/
class FBullCowGame
{
public:
	FBullCowGame(); // Constructor
	void Reset();
	// Counts bulls and cows and increments try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);
	int32 GetHiddenWordLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon();
	EGuessStatus CheckGuessValidity(FString) const;



// ^^^^^^^^^^^^^ LOOK UP ^^^^^^^^^^^^^
private: // See constructor for instantiation details
	FBullCowCount BullCowCount;
	bool bGameIsWon;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};

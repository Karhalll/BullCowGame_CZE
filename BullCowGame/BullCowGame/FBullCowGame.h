#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Word_lenght,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitGuess(FString);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWinStatus;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
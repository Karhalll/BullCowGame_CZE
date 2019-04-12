#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#define TMap std::map

using int32 = int;

void FBullCowGame::Reset()
{
	std::vector <FString> DatabazeSlov5 { "cikán", "èolek", "skaut", "golem", "akcie", "akryl", "albín", "album", "andìl", "ampér", "apríl", "areál", "aspik", "bìlmo", "bøímì", "cévka", "cysta", "dabér", "dìkan", "drbna", "forma", "fošna", "guláš", "grázl", "hùlka", "holiè", "jabko", "jehla", "kùzle", "kužel", "mlíko", "odliv", "puška", "rodiè", "tábor", "tukan", "zvrat"};

	int rndnum = 0;
	srand(time(NULL));
	rndnum = rand() % DatabazeSlov5.size();

	FString  HIDDEN_WORD = DatabazeSlov5.at(rndnum);

	//pøekladaè hodnot char pri zadání ve zdrojáku na stejnou hodnotu jako pøi zadání v pøíkazové øádce (aby se vyøešil zkurvenej problém, že zadání pøes konzoli má prdelní hodnotu)
	const int InRadek[] = { -40, -25, -97, -3, -89, -20, -96, -95, -126, -93, -123, -44, -27, -94, -100, -73, -26, -84, -4, -90, -19, -75, -42, -112, -23, -34, -46, -43, -32, -101 };
	const int InZdrojak[] = { -20, -102, -24, -8, -98, -3, -31, -19, -23, -6, -7, -17, -14, -13, -99, -52, -118, -56, -40, -114, -35, -63, -51, -55, -38, -39, -49, -46, -45, -115 };

	for (int i = 0; i < HIDDEN_WORD.length(); i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (HIDDEN_WORD.at(i) == InZdrojak[j])
			{
				HIDDEN_WORD.at(i) = InRadek[j];
				break;
			}
		}
	}
	//konec pøekladaèe

	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	constexpr int32 MAX_TRIES = 8;
	bWinStatus = false;

	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,10}, {5,15}, {6,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bWinStatus;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Word_lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 i = 0; i < WordLength; i++)
	{
		//copare letters againts the hidden word
		for (int32 j = 0; j < WordLength; j++)
		{
			//if they match then
			if (Guess[i] == MyHiddenWord[j])
			{
				//if they're in the same place
				if (i == j)
				{
					//incriment bulls 
					BullCowCount.Bulls++;
				}
				//else
				else
				{
					//incriment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bWinStatus++;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])//if the letter is in the map
		{
			return false;// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is enterd
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		const int VD[] = { -73, -26, -84, -4, -90, -19, -75, -42, -112, -23, -34, -46, -43, -32, -101 };
		
		for (int i = 1; i < 15; i++)
		{

			if (int(Letter) == VD[i])// if not a lowercase letter 
			{
				return false;
			}
		}
	}
	return true;
}

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <locale.h>
#include <clocale>
#include <cstdio>
#include <windows.h>


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //insantiet a new game

int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; 
}

void PrintIntro()
{	
	// introduce the game
	setlocale(LC_ALL, "");

	std::cout << "V�tej ve h�e B�ci a Kr�vy (v origin�le: Bulls and Cows).\n\n";
	std::cout << std::endl;
	std::cout << "          }   {              ___ " << std::endl;
	std::cout << "          (o o)             (o o)" << std::endl;
	std::cout << "   /-------\\ /               \\ /------\\" << std::endl;
	std::cout << "  / | BULL |O                 O| COW | \\" << std::endl;
	std::cout << " *  |-,--- |                   |-----|  *" << std::endl;
	std::cout << "    ^      ^                   ^     ^" << std::endl;
	std::cout << "Jde o slovn� puzzle h���ku, kde p�i omezen�m po�tu pokus� se sna�� uh�dnout tajn� slovo o p�edem zn�m�m po�tu p�smen.\n";
	std::cout << "P�i h�d�n� ti pom�haj� pr�v� b�ci a kr�vy.\n";
	std::cout << "B�ci: po�et uhodnut�ch a spr�vn� za�azen�ch p�smen ve slov�\n";
	std::cout << "Kr�vy: po�et uhodnut�ch p�smen, kter� jsou ale na jin�m m�st� ne� jsi tipoval/a\n\n";
	std::cout << "JO! A je��e jedno pravidlo. Tajn� slovo je isogram. Tj. slovo ve kter�m se p�smeno m��e vyskytovat jen jednou. Nap��klad kostra.";
	std::cout << std::endl;
	
	std::cout << "TAK�E JDEME NA TO! Uhodne� tajn� slovo kter� m� ";
	std::cout << BCGame.GetHiddenWordLength();
	std::cout << " p�smen?\n";
	std::cout << std::endl;

	setlocale(LC_ALL, "C");

	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		setlocale(LC_ALL, "");
		std::cout << "B�ci = " << BullCowCount.Bulls;
		std::cout << ". Kr�vy = " << BullCowCount.Cows << "\n\n";
		setlocale(LC_ALL, "C");
	}
	PrintGameSummary();
}

// loop continually until user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTries = BCGame.GetCurrentTry();

		// get a guess from the player
		setlocale(LC_ALL, "");
		std::cout << CurrentTries << ". pokus z " << BCGame.GetMaxTries() << ". Zadej sv�j pokus: ";
		setlocale(LC_ALL, "C");

		std::getline(std::cin, Guess);

		setlocale(LC_ALL, "");
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Word_lenght:
			std::cout << "Slovo mus� m�t " << BCGame.GetHiddenWordLength() << " p�smen!\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Zadej isogram! ��dn� p�smeno ve slov� se nesm� opakovat.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Zad�vej slovo jen s mal�my p�smeny pros�m.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		setlocale(LC_ALL, "C");
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	setlocale(LC_ALL, "");
	std::cout << "Chce� to zkusit znovu (a/n)? ";
	setlocale(LC_ALL, "C");
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'a') || (Response[0] == 'A');
}

void PrintGameSummary()
{
	setlocale(LC_ALL, "");
	if (BCGame.IsGameWon() == 1)
	{
		std::cout << "ANO! Vyhr�l jsi! Gratuluji.\n\n";
	}
	else
	{
		std::cout << "�KODA! Zkus to znovu.\n\n";
	}
	setlocale(LC_ALL, "C");
}
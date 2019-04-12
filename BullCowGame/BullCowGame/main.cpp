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

	std::cout << "Vítej ve høe Býci a Krávy (v originále: Bulls and Cows).\n\n";
	std::cout << std::endl;
	std::cout << "          }   {              ___ " << std::endl;
	std::cout << "          (o o)             (o o)" << std::endl;
	std::cout << "   /-------\\ /               \\ /------\\" << std::endl;
	std::cout << "  / | BULL |O                 O| COW | \\" << std::endl;
	std::cout << " *  |-,--- |                   |-----|  *" << std::endl;
	std::cout << "    ^      ^                   ^     ^" << std::endl;
	std::cout << "Jde o slovní puzzle høíèku, kde pøi omezeném poètu pokusù se snažíš uhádnout tajné slovo o pøedem známém poètu písmen.\n";
	std::cout << "Pøi hádání ti pomáhají právì býci a krávy.\n";
	std::cout << "Býci: poèet uhodnutých a správnì zaøazených písmen ve slovì\n";
	std::cout << "Krávy: poèet uhodnutých písmen, která jsou ale na jiném místì než jsi tipoval/a\n\n";
	std::cout << "JO! A ješe jedno pravidlo. Tajné slovo je isogram. Tj. slovo ve kterém se písmeno mùže vyskytovat jen jednou. Napøíklad kostra.";
	std::cout << std::endl;
	
	std::cout << "TAKŽE JDEME NA TO! Uhodneš tajné slovo které má ";
	std::cout << BCGame.GetHiddenWordLength();
	std::cout << " písmen?\n";
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
		std::cout << "Býci = " << BullCowCount.Bulls;
		std::cout << ". Krávy = " << BullCowCount.Cows << "\n\n";
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
		std::cout << CurrentTries << ". pokus z " << BCGame.GetMaxTries() << ". Zadej svùj pokus: ";
		setlocale(LC_ALL, "C");

		std::getline(std::cin, Guess);

		setlocale(LC_ALL, "");
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Word_lenght:
			std::cout << "Slovo musí mít " << BCGame.GetHiddenWordLength() << " písmen!\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Zadej isogram! Žádné písmeno ve slovì se nesmí opakovat.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Zadávej slovo jen s malýmy písmeny prosím.\n\n";
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
	std::cout << "Chceš to zkusit znovu (a/n)? ";
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
		std::cout << "ANO! Vyhrál jsi! Gratuluji.\n\n";
	}
	else
	{
		std::cout << "ŠKODA! Zkus to znovu.\n\n";
	}
	setlocale(LC_ALL, "C");
}
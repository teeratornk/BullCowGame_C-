/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/
#include<iostream>
#include<string>
#include<boost/algorithm/string.hpp>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//using namespace std;

// function headers

int main();

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText &Guess);
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main() {

	bool bPlayAgain = false;

    // do while for play game
	do {

		// introduce the game
		PrintIntro();

		// get a guess from the player
		PlayGame();

		// ask the play to play again
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	

	return 0;
}

// function bodies

void PrintIntro() {
	// introduce the game
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking of? \n";
	std::cout << std::endl;
	return;
}

void PlayGame() {
	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//  loop for the number of terns asking for guesses
	//TODO change from FOR to WHILE loop, validating a try
	for (int32 i = 0; i < MaxTries; i++) {

		FText Guess = GetValidGuess(); // TODO make loop checking valid guess

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);
		
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		PrintBack(Guess);
	}

	// TODO add a game summary
}

// loop continually until the user gives the valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		// get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry();
		std::cout << " Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;

} 

void PrintBack(FText &Guess) {
	// repeat the guess back to them
	std::cout << "Your guess was: " << Guess << std::endl;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	//std::cout << char(::toupper(Response[0]));
	return (Response[0] == 'y' or Response[0] == 'y');
}


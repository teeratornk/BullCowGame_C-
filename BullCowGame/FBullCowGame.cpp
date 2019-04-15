#include "FBullCowGame.h"
#include <map>
#include<iostream>
#include<boost/algorithm/string.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define TMap std::map // using and define are not the same

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default con

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

bool FBullCowGame::IsIsogram(FString Word) const {

	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; // we do not have an isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) {
		if (! islower(Letter)) {
			return false;
		}
	}
	return true;
}

int32 FBullCowGame::GetMaxTries() const { 
	//TMap<int32, int32> WordLengthToMaxtries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
	//return WordLengthToMaxtries[MyHiddenWord.length()];
	return MyHiddenWord.length() * 2 + 2;
}

void FBullCowGame::Reset() {
	//constexpr int32 MAX_TRIES = 8;
	//MyMaxTries = MAX_TRIES;

	FMyHiddenWordUse RandomHiddenWord;
	srand(time(NULL));
	int iSecret = rand() % RandomHiddenWord.FWordList.size();

	//std::cout << RandomHiddenWord.FWordList[iSecret] << std::endl;

	const FString HIDDEN_WORD = RandomHiddenWord.FWordList[iSecret];
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a valid guess, increment turn, count Bull and Cow
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length is the same

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letter against the guess word
		for (int32 GWChar = 0; GWChar < WordLength; GWChar++) {
			// if they match then
			if (MyHiddenWord[MHWChar] == Guess[GWChar]) {
				// if they are in the same place
				if (MHWChar == GWChar) {
					// increment bulls
					BullCowCount.Bulls++;
				}
				// if not
				else {
					//increment cows
					BullCowCount.Cows++;
				}		
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	// TODO QUIT program
	if (Guess == "QUIT:(") {
		return EGuessStatus::QUIT;
	}
	
	if (! IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}// if the guess is not an isogram 
	else if (! IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}// if the guess is not all lowercase
	else if (GetHiddenWordLength()!= Guess.length()) {
		return EGuessStatus::Wrong_Length;
	}// if the guess length is wrong
	else {
		return EGuessStatus::OK;
	} 
		
	
	
	//
	return EGuessStatus::OK; // TODO make actual value
}

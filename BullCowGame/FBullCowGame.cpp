#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

// receives a valid guess, increment turn, count Bull and Cow
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;
	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		// compare letter against the hidden word
		for (int32 GWChar = 0; GWChar < HiddenWordLength; GWChar++) {
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
	return BullCowCount;
}

bool FBullCowGame::IsGameWon() const {
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (false) {
		return EGuessStatus::Not_Isogram;
	}// if the guess is not an isogram 
	else if (false) {
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
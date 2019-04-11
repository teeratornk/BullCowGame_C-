#pragma once
#include<string>
// no namespace in the header file

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus {
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.
	
	void Reset(); // TODO make a more rich return value.
	// provide a method for counting bulls and cows and increasing turn number #assuming valid guess
	FBullCowCount SubmitValidGuess(FString Guess);

// ^^ forcus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};
// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(HiddenWordsArray);

    SetUpGame();
    WelcomePlayer();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    // Check if game is over
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
        WelcomePlayer();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess.Equals(HiddenWord))
    {
        PrintLine(TEXT("You are correct!"));
        PrintLine(TEXT("You win the level!"));
        EndGame();
        return;
    }

    // Check if there is the correct number of characters
    // Guess again
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Wrong number of letters.\nTry a word of length %i"), HiddenWord.Len());
        return;
    }

    // Check if isogram
    // Guess again
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("The guess is not an isogram.\nTry again."));
        return;
    }

    // Decrement life count
    --NumberLives;

    if (NumberLives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You are out of lives"));
        PrintLine(TEXT("The HiddenWord was %s\n"), *HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Your guess was incorrect!"));
    PrintLine(TEXT("You now have %i lives left."), NumberLives);

    FBullCowCount BullCowCount = GetBullCows(Guess);
    
    PrintLine(TEXT("Your current Bulls: %i, Cows %i."), BullCowCount.Bulls, BullCowCount.Cows);
    PrintLine(TEXT("Guess again."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for(int i = 0; i < Word.Len(); i++)
    {
        for(int j = i + 1; j < Word.Len(); j++)
        {
            if(Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount BCCount;

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BCCount.Bulls++;
            continue; //We can continue since the word is an isogram
        }

        for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                BCCount.Cows++;
                break; //We can break since the word is an isogram
            }
        }
    }
    
    return BCCount;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordArray) const
{
    TArray<FString> ValidArray;

    for(FString TempWord : WordArray)
    {
        if(TempWord.Len() >= 4 && TempWord.Len() <= 8 && IsIsogram(TempWord))
        {
            ValidArray.Emplace(TempWord.ToLower());
        }
    }
    return ValidArray;
}

void UBullCowCartridge::SetUpGame()
{
    int32 RandNum = FMath::RandRange(0, Isograms.Num() - 1);
    HiddenWord = Isograms[RandNum];
    NumberLives = HiddenWord.Len();
    bGameOver = false;

    // DEBUG code
    PrintLine(TEXT("DEBUG -- Isograms list length %i"), Isograms.Num());
    PrintLine(TEXT("DEBUG -- HiddenWord: %s"), *HiddenWord);
}

void UBullCowCartridge::WelcomePlayer()
{
    PrintLine(TEXT("MOOOO!! Welcome to Bull Cows!"));
    PrintLine(TEXT("Your goal is to guess the isogram."));
    PrintLine(TEXT("The word is of length %i"), HiddenWord.Len());
    PrintLine(TEXT("You now have %i lives. Don't screw up."), NumberLives);
    PrintLine(TEXT("Please enter your guess."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press enter to play again."));
}
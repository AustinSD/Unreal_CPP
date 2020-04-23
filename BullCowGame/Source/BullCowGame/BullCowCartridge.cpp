// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    ValidWords = GetValidWords(HiddenWordsArray);

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

    // Need to display bulls and cows
    PrintLine(TEXT("Your guess was incorrect!"));
    PrintLine(TEXT("You now have %i lives left."), NumberLives);
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
    int32 RandNum = FMath::RandRange(0, ValidWords.Num() - 1);
    HiddenWord = ValidWords[RandNum];//TEXT("john");
    NumberLives = HiddenWord.Len();
    bGameOver = false;

    // DEBUG code
    PrintLine(TEXT("DEBUG -- ValidWords length %i"), ValidWords.Num());
    PrintLine(TEXT("DEBUG -- HiddenWord: %s"), *HiddenWord);
}

void UBullCowCartridge::WelcomePlayer()
{
    PrintLine(TEXT("MOOOO!! Welcome to Bull Cows!"));
    PrintLine(TEXT("Your goal is to guess the isogram."));
    PrintLine(TEXT("The word is of length %i"), HiddenWord.Len());
    PrintLine(TEXT("You now have %i lives. Don't screw up."), NumberLives);

    // Prompt for guess
    PrintLine(TEXT("Please enter your guess."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press enter to play again."));
}
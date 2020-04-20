// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("MOOOO!! Welcome to Bull Cow!"));
    HiddenWord = TEXT("austin");
    PrintLine(TEXT("Please enter your guess."));
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    PrintLine(TEXT("You've entered:"));
    PrintLine(Input);

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You are correct!"));
    }
    else
    {
        PrintLine(TEXT("You where wrong. The HiddenWord is ") + HiddenWord);
    }
}
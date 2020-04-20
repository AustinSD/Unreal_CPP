// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("MOOOO!! Welcome to Bull Cow!"));
    PrintLine(TEXT("Please enter yout name."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString HiddenWord = TEXT("austin");

    ClearScreen();
    PrintLine(TEXT("You've entered:"));
    PrintLine(Input);
    PrintLine(TEXT("The HiddenWord is ") + HiddenWord);
    
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreboardRow.h"

#include "Components/TextBlock.h"

void UScoreboardRow::SetPlayerName(const FString& PlayerName) const
{
	PlayerNameText->SetText(FText::FromString(PlayerName));
}

void UScoreboardRow::SetScore(const int32 Score) const
{
	ScoreText->SetText(FText::AsNumber(Score));
}

void UScoreboardRow::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetPlayerName(FString{ "Player Name" });
	SetScore(0);
}

void UScoreboardRow::NativeConstruct()
{
	Super::NativeConstruct();
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Scoreboard.h"

#include "Components/VerticalBox.h"
#include "GameFramework/PlayerState.h"
#include "UI/ScoreboardRow.h"

void UScoreboard::AddScoreboardRow(const FString& PlayerName, const int32 Score) const
{
	if(ScoreboardRowWidgetClass)
	{
		UScoreboardRow* ScoreboardRow = CreateWidget<UScoreboardRow>(GetOwningLocalPlayer()->PlayerController, ScoreboardRowWidgetClass);
		PlayerScoreContainer->AddChild(ScoreboardRow);
		ScoreboardRow->SetPlayerName(PlayerName);
		ScoreboardRow->SetScore(Score);
	}
}

void UScoreboard::InitScoreBoard(const TArray<TObjectPtr<APlayerState>>& PlayerArray) const
{
	for (auto PS : PlayerArray)
	{
		const APlayerState* PlayerState = PS.Get();
		const FString PlayerName = PlayerState->GetPlayerName();
		const int32 Score = PlayerState->GetScore();
		bool PlayerFound = false;

		const TArray<UWidget*> Rows = PlayerScoreContainer->GetAllChildren();

		// Try to update the player score if player is already in the list
		for(const UWidget* RowWidget : Rows)
		{
			if(const UScoreboardRow* ScoreboardRow = Cast<UScoreboardRow>(RowWidget))
			{
				if (ScoreboardRow->GetPlayerName() == PlayerName)
				{
					PlayerFound = true;
					ScoreboardRow->SetScore(Score);
					break;
				}
			}
		}

		// Add player to the list if not found
		if(!PlayerFound)
			AddScoreboardRow(PlayerName, Score);
	}
}

void UScoreboard::UpdatePlayerScore(const FString& PlayerName, const float Score) const
{
	const TArray<UWidget*> Rows = PlayerScoreContainer->GetAllChildren();

	bool PlayerFound = false;

	// Try to update the player score if player is already in the list
	for(const UWidget* RowWidget : Rows)
	{
		if(const UScoreboardRow* ScoreboardRow = Cast<UScoreboardRow>(RowWidget))
		{
			if (ScoreboardRow->GetPlayerName() == PlayerName)
			{
				PlayerFound = true;
				ScoreboardRow->SetScore(Score);
				break;
			}
		}
	}

	// Add player to the list if not found
	if(!PlayerFound)
		AddScoreboardRow(PlayerName, Score);
}

void UScoreboard::NativeConstruct()
{
	Super::NativeConstruct();

	// Set Hidden by default
	SetVisibility(ESlateVisibility::Collapsed);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Scoreboard.h"

#include "Components/VerticalBox.h"
#include "GameFramework/PlayerState.h"
#include "UI/ScoreboardRow.h"

void UScoreboard::AddScoreboardRow(const FString& PlayerName, const int32 Score)
{
	if(ScoreboardRowWidgetClass)
	{
		const UScoreboardRow* ScoreboardRow = CreateWidget<UScoreboardRow>(this, ScoreboardRowWidgetClass);
		ScoreboardRow->SetPlayerName(PlayerName);
		ScoreboardRow->SetScore(Score);
		PlayerScoreContainer->AddChildToVerticalBox(ScoreboardRow->GetRootWidget());
	}
}

void UScoreboard::InitScoreBoard(const TArray<TObjectPtr<APlayerState>>& PlayerArray)
{
	for (auto PS : PlayerArray)
	{
		const APlayerState* PlayerState = PS.Get();
		const FString PlayerName = PlayerState->GetPlayerName();
		const int32 Score = PlayerState->GetScore();
		bool PlayerFound = false;

		const auto Rows = PlayerScoreContainer->GetAllChildren();
		
		for(const auto RowWidget : Rows)
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

		if(!PlayerFound)
			AddScoreboardRow(PlayerName, Score);
	}
}

void UScoreboard::NativeConstruct()
{
	Super::NativeConstruct();

}

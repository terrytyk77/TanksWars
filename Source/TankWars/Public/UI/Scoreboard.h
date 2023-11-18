// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scoreboard.generated.h"

class UVerticalBox;
class UScoreboardRow;

UCLASS()
class TANKWARS_API UScoreboard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddScoreboardRow(const FString& PlayerName, const int32 Score) const;
	void InitScoreBoard(const TArray<TObjectPtr<APlayerState>>& PlayerArray) const;
	void UpdatePlayerScore(const FString& PlayerName, const float Score) const;

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UVerticalBox* PlayerScoreContainer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UScoreboardRow> ScoreboardRowWidgetClass;
};

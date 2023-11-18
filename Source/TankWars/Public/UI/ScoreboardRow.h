// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreboardRow.generated.h"

class UTextBlock;

UCLASS()
class TANKWARS_API UScoreboardRow : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FString& PlayerName) const;
	void SetScore(const int32 Score) const;
	
	FORCEINLINE FString GetPlayerName() const { return PlayerNameText->GetText().ToString(); }
	FORCEINLINE int32 GetPlayerScore() const { return FCString::Atoi(*ScoreText->GetText().ToString()); }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
private:
	// Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* PlayerNameText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* ScoreText;
};

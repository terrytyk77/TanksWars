// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

class ATankPlayerController;

UCLASS()
class TANKWARS_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void OnRep_Score() override;
	void AddToScore(const float ScoreAmount);

private:
	UPROPERTY()
	 ATankPlayerController* TankPlayerController;
};

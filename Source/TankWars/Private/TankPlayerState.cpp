// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerState.h"

#include "TankPlayerController.h"

void ATankPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATankPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
}

void ATankPlayerState::AddToScore(const float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);

	if(!TankPlayerController)
	{
		if (APlayerController* PlayerController = GetPlayerController())
		{
			TankPlayerController = Cast<ATankPlayerController>(PlayerController);
		}
	}

	if(TankPlayerController)
	{
		
	}
}

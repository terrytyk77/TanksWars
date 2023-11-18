// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerState.h"

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
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMatchGameMode.h"

void ADeathMatchGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("%s"), *NewPlayer->GetName()));
}

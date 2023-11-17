// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DeathMatchGameMode.generated.h"

class ATankCharacter;
class ATankPlayerController;

UCLASS()
class TANKWARS_API ADeathMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(ATankCharacter* EliminatedCharacter, ATankPlayerController* VictimController, ATankPlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* EliminatedCharacter, AController* EliminatedController);
	
protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMatchGameMode.h"

#include "DeathMatchGameState.h"
#include "TankCharacter.h"
#include "TankPlayerController.h"
#include "TankPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ADeathMatchGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if(const ATankPlayerState* PlayerState = NewPlayer->GetPlayerState<ATankPlayerState>())
	{
		UpdatePlayerScore(PlayerState->GetPlayerName(), PlayerState->GetScore());
	}
}

void ADeathMatchGameMode::PlayerEliminated(ATankCharacter* EliminatedCharacter, ATankPlayerController* VictimController, ATankPlayerController* AttackerController)
{
	if(AttackerController)
	{
		if (ATankPlayerState* TankPlayerState = AttackerController->GetPlayerState<ATankPlayerState>())
		{
			TankPlayerState->AddToScore(1);
			UpdatePlayerScore(TankPlayerState->GetPlayerName(), TankPlayerState->GetScore());
		}
	}
	
	if (EliminatedCharacter)
	{
		EliminatedCharacter->Eliminate();
	}
}

void ADeathMatchGameMode::RequestRespawn(ACharacter* EliminatedCharacter, AController* EliminatedController)
{
	if(EliminatedCharacter) // Free the controller and destroy the character 
	{
		EliminatedCharacter->Reset();
		EliminatedCharacter->Destroy();
	}
	if(EliminatedController) // Respawn the controller in a new character
	{
		// Find all the player starts actor in the level
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
		// Get random player start index to spawn the character
		const int32 RandomPlayerStartIndex = FMath::RandHelper(PlayerStarts.Num());
		RestartPlayerAtPlayerStart(EliminatedController, PlayerStarts[RandomPlayerStartIndex]);
	}
}

void ADeathMatchGameMode::UpdatePlayerScore(const FString& PlayerName, const float Score) const
{
	for (auto PS : GameState->PlayerArray)
	{
		const APlayerState* PlayerState = PS.Get();
		if (!PlayerState || !PlayerState->GetPlayerController())
		{
			return;
		}
		
		if(ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerState->GetPlayerController()))
		{
			TankPlayerController->ClientUpdatePlayerScore(PlayerName, Score);
		}
	}
}

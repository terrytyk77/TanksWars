// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMatchGameMode.h"

#include "TankCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ADeathMatchGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Connected: %s"), *NewPlayer->GetName()));
}

void ADeathMatchGameMode::PlayerEliminated(ATankCharacter* EliminatedCharacter, ATankPlayerController* VictimController, ATankPlayerController* AttackerController)
{
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

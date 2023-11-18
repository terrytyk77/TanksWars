// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class TANKWARS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATankPlayerController();
	// Used to replicate variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(Client, Reliable)
	void ClientUpdatePlayerScore(const FString& PlayerName, const float Score);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UNiagaraSystem* FXCursor;
	UPROPERTY(ReplicatedUsing="OnRep_PossessedPawn")
	APawn* PossessedPawn;
	
	UFUNCTION()
	void MoveToMouseLocation();
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void ToggleScoreboard();
	UFUNCTION()
	void OnRep_PossessedPawn();
};

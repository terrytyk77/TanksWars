// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "NiagaraFunctionLibrary.h"
#include "TankCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/Scoreboard.h"
#include "UI/TankHUD.h"

// Sets default values
ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}

void ATankPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATankPlayerController, PossessedPawn);
}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName("Click"), EInputEvent::IE_Released, this, &ThisClass::MoveToMouseLocation);
	InputComponent->BindAction(FName("Fire"),  EInputEvent::IE_Pressed, this, &ThisClass::Fire);
	InputComponent->BindAction(FName("Scoreboard"), EInputEvent::IE_Pressed, this, &ThisClass::ToggleScoreboard);
}

void ATankPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = InPawn;
}

void ATankPlayerController::MoveToMouseLocation()
{
	FHitResult MouseHitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, MouseHitResult);
	
	if(MouseHitResult.bBlockingHit)
	{
		const FVector LocationToMoveTo = MouseHitResult.Location;
		// Move to the mouse location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, LocationToMoveTo);
		// Spawn mouse move-to particle effect
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, LocationToMoveTo);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ATankPlayerController::Fire()
{
	if(APawn* PlayerPawn = GetPawn())
	{
		if(ATankCharacter* TankCharacter = Cast<ATankCharacter>(PlayerPawn))
		{
			TankCharacter->ServerFire();
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ATankPlayerController::ToggleScoreboard()
{
	if(const ATankHUD* HUD = GetHUD<ATankHUD>())
	{
		HUD->ToggleScoreboardVisibility(GetWorld()->GetGameState()->PlayerArray);
	}
}

void ATankPlayerController::OnRep_PossessedPawn()
{
	// A fix to solve an engine bug which made the function SimpleMoveToLocation not work after repossession of a new pawn
	// After a client respawn we need to reinitialize the path following component
	// The default code path that sorts this out only fires on the server after a Possess so we have to replicate it on the client as well
	
	UPathFollowingComponent* PathFollowingComp = FindComponentByClass<UPathFollowingComponent>();
	if (PathFollowingComp == nullptr)
	{
		PathFollowingComp = NewObject<UPathFollowingComponent>(this);
		PathFollowingComp->RegisterComponentWithWorld(GetWorld());
		PathFollowingComp->Initialize();
	}

	if (!PathFollowingComp->IsPathFollowingAllowed())
	{
		PathFollowingComp->Initialize();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "DeathMatchGameMode.h"
#include "TankCharacter.h"
#include "TankPlayerController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Create the collision sphere with it's collision presets
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->SetSphereRadius(16.f);
	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	// Creat the mesh for the projectile
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	// Create the projectile movement component and give it some default values
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		CollisionSphere->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnHit);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!OtherActor)
		return;
	
	if(ATankCharacter* TankCharacter = Cast<ATankCharacter>(OtherActor);
		TankCharacter && TankCharacter != GetOwner())
	{
		if(const UWorld* World = GetWorld())
		{
			if(ADeathMatchGameMode* GameMode = World->GetAuthGameMode<ADeathMatchGameMode>())
			{
				ATankPlayerController* AttackerPlayerController = Cast<ATankPlayerController>(GetOwner()->GetInstigatorController());
				ATankPlayerController* VictimPlayerController = Cast<ATankPlayerController>(TankCharacter);
				GameMode->PlayerEliminated(TankCharacter, VictimPlayerController, AttackerPlayerController);
			}
		}
	}

	if(IsValid(this))
		Destroy();
}


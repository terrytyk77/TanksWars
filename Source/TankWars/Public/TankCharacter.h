// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

class AProjectile;
class UCameraComponent;
class USpringArmComponent;
class UPathFollowingComponent;

UCLASS()
class TANKWARS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();
	// Used to replicate variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Returns CameraBoom sub-object */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera sub-object */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	/** To Eliminate and play any effect when player dies */
	void Eliminate();

	UFUNCTION(Server, Reliable)
	void ServerFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Camera boom positioning the camera on top of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;
	/** Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Components", meta=(AllowPrivateAccess="true"))
	UPathFollowingComponent* PathFollowingComponent;
	/** The distance from the camera to the focus point */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess="true"))
	float CameraArmLength;
	/** Projectile to spawn when the tank fires */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(Transient, ReplicatedUsing = "OnRep_PlayerColor")
	FColor PlayerColor;

	UFUNCTION()
	void OnRep_PlayerColor() const;
};

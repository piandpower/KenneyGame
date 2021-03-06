// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "KenneyCommons.h"

#include "PaperHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KENNEYGAME_API APaperHeroCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	APaperHeroCharacter(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void MoveRight(float Value);
	void MoveUp(float Value);
	void StartJump();
	void StopJump();

	UFUNCTION()
	void DoCharMoveUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

	void SetMoveDirection(EPaperHeroCharacterMoveDirection NewDir);

protected:
	UFUNCTION()
	void OnRep_HeroMoveDirection(EPaperHeroCharacterMoveDirection LastDir);

	UFUNCTION(Reliable, server, WithValidation)
	void ServerSetMoveDirection(EPaperHeroCharacterMoveDirection NewDir);
	virtual bool ServerSetMoveDirection_Validate(EPaperHeroCharacterMoveDirection NewDir);
	virtual void ServerSetMoveDirection_Implementation(EPaperHeroCharacterMoveDirection NewDir);

	virtual bool CanJumpInternal_Implementation() const override;

	virtual bool CanCrouch() override;

	void UpdateSpriteDir(EPaperHeroCharacterMoveDirection NewDir);

protected:
	UPROPERTY(Transient, ReplicatedUsing = OnRep_HeroMoveDirection)
	EPaperHeroCharacterMoveDirection HeroMoveDirection;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	UCameraComponent* SideViewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* WalkFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* JumpFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* DuckFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float NormalSpriteZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float CrouchedSprizteZ;

};

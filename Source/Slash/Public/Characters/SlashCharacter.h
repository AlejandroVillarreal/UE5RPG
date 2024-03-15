// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "BaseCharacter.h"
#include "SlashCharacter.generated.h"


class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AItem;
class ASoul;
class UAnimMontage;
class USlashOverlay;
class ATreasure;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	/* Callbacks for input*/
	virtual void Jump() override;
	void Equip();


	/*Play montage functions*/

	

	bool CanDisarm();
	bool CanArm();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPlayerEnhancedInput(APlayerController* PlayerController);
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SlashContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* DodgeAction;

	virtual void Attack() override;
	void Dodge();
	/**
	* Play montage functions
	*/
	
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	//void SetPlayerEnhacedInput(APlayerController* PlayerController);
	void EquipWeapon(AWeapon* Weapon);
	/*Called for movement input*/
	void Move(const FInputActionValue& Value);
	/*Called for look input*/
	void Look(const FInputActionValue& Value);
	void Disarm();
	void Arm();
	void PlayEquipMontage(const FName& SectionName);

	virtual void Die_Implementation() override;
	bool HasEnoughStamina();
	bool IsOccupied();
	UFUNCTION(BlueprintCallable)
		void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
		void AttachWeaponToHand();

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	
public:	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;

	UFUNCTION(BlueprintCallable)
		void FinishEquipping();

	UFUNCTION(BlueprintCallable)
		void HitReactEnd();
	
	
private: 
	bool IsUnoccupied();
	void SetHUDHealth();
	void InitializeSlashOverlay(class APlayerController* PlayerController);
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;



	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	UPROPERTY()
	USlashOverlay* SlashOverlay;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EActionState ActionState = EActionState::EAS_Unoccupied;
};

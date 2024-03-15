// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Soul.h"
#include "Interfaces/PickupInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"


void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PickSouls(OtherActor);
	//FTimerDelegate Delegate;
	//Delegate.BindUFunction(this, FName("PickSouls"), OtherActor);
	//GetWorldTimerManager().SetTimer(TimerHandle, Delegate, 5.0f, false);
}
void ASoul::PickSouls(AActor* OtherActor)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);

		SpawnPickupSystem();
		SpawnPickupSound();

		Destroy();
	}
}






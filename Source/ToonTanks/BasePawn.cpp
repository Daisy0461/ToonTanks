// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;		//CapsuleComp를 RootComponent로 명시적으로 지정

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget){
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); //봐라봐야할 FVector를 구함
	FRotator LookAtRotation = ToTarget.Rotation();		//봐라봐야할 Vector로 향하는 Rotation을 구함.
	LookAtRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);		//Turret이 바닥을 향하거나 하늘을 향하면 안되기 때문에 Pitch, Roll 고정
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			10.f));
}

void ABasePawn::Fire(){
	DrawDebugSphere(GetWorld(), 
	ProjectileSpawnPoint->GetComponentLocation(), 
	15.f, 
	15, 
	FColor::Blue, 
	false, 
	3.f);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = StaticMesh;
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComponent"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		//delegate이며 AddDynamic으로 함수를 추가한다.
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

//HitComp = 때린 Compoent, OtherActor = 맞은 Actor, OtherComp = 맞은 MeshComponent
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	UE_LOG(LogTemp, Warning, TEXT("On Hit"));

	UE_LOG(LogTemp, Display, TEXT("HitComponent: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Display, TEXT("Hitted Actor Name: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Display, TEXT("Hitted Component: %s"), *OtherComp->GetName());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = StaticMesh;
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComponent"));
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		//delegate이며 AddDynamic으로 함수를 추가한다.
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 1.0, 0.5);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

//HitComp = 때린 Compoent, OtherActor = 맞은 Actor, OtherComp = 맞은 MeshComponent
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	auto MyOwner = GetOwner();		//Tank가 쐈으면 Tank가 들어온다. Turret이 쏘면 Turret이 들어온다.
									//이유는 Tank에서 나온 Projectile의 Owner는 Tank이기 떄문이다.	
	if(MyOwner == nullptr) {
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner){
		//아래 ApplyDamage를 Call하면 Damage Event가 발생한다. -> DamageTaken이 Call 된다.
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles && HitSound){
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
	}
	Destroy();
}

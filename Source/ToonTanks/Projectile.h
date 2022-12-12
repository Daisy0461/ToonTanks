// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Combat")
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* MoveComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;		//한번 class로 Forward declare를 하면 뒤에는 하지 않아도 괜찮다.


	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;		//이 변수에 대해서 BP를 만들었기 때문에 다른 일반적인 변수들과 다르게 TSubclassOf를 앞에 붙이고 사용이 가능하다.
};

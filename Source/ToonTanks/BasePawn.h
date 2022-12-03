// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()		//이유는 모르겠지만 12번째 줄에 있어야하고 이게 붉은 줄이 생긴다고 해도 크게 신경안써도 괜찮다.

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void RotateTurret(FVector LookAtTarget);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Component")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Component")
	USceneComponent* ProjectileSpawnPoint;		//위치만 있으면 되니까 USceneComponent를 사용한다./

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Component")
	UStaticMeshComponent* BaseMesh;			//UStatic은 모든 Actor에 Default로 들어가 있어서 Forward Declaration이 필요없다.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Component")
	UStaticMeshComponent* TurretMesh;
};

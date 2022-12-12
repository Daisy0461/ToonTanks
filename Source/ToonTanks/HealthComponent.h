// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )//UClass에 meta에 다음과 같이 있으면 Blueprint에서 생성해서 사용할 수 있다.
class TOONTANKS_API UHealthComponent : public UActorComponent			
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;
	float Health = 0.f;

	//Unreal Engine은 Damage Type에 대한 개념이 있다. 이 Type은 User가 Custom도 가능하다.
	//이 Type들은 Type에 따라 추가적인 data를 준다. 예를 들어 Fire, Poision, Explosive 등이 있다.
	//Instigator는 Player가 컨트롤하는 Pawn에 의해 데미지가 발생하였을 때, Pawn을 소유하고 있는 Controller를 의미한다. 필요없으면 Null을 넣으면 된다.
	//간단하게 Instigator는 데미지를 준 Pawn을 조종하는 Controller이다.
	//DamageCauser는 데미지를 주는 Actor를 의미한다. 총알이나 포탄 같은 것이다.
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	class AToonTankGameMode* ToonTankGameMode;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};

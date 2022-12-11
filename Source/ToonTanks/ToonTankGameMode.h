// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	//BlueprintImplementableEvent를 적으면 body를 만들 필요 없이 BP에서 기능적인것을 생성하면 된다.
	//물론 C++에서도 부를 수 있다.
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class Turret* Turret;
	class AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay = 3.f;
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();			//남아있는 Tower의 갯수를 구함

	void HandleGameStart();
};

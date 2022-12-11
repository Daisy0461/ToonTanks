// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor){
    if(DeadActor == Tank && ToonTankPlayerController){      //여기서 Tank가 null이라면 false를 출력한다.
        Tank->HandleDestruction();
        ToonTankPlayerController->SetPlayerEnabledState(false);
        GameOver(false);

    }else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){       //DeadActor를 Tower로 Cast했을 때 된다면 그것은 Tower가 되기 때문에 이렇게 작성
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0){
            GameOver(true);
        }
    }
}

void AToonTankGameMode::BeginPlay(){
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTankGameMode::HandleGameStart(){
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));       //player가 사용하는 Tank를 나타낸다.
    ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTankPlayerController){
        ToonTankPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        //첫번째 파라미터는 사용할 함수가 있는 *를 전달한다. 여기에 존재하면 this를 넘기면 된다.
        //두번째는 특이하게 함수를 적는데 파라미터는 안에 넣지 않는다. 사용하는 함수의 파라미터를 CreateUObject의 다음 파라미터로 넣으면 된다.
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTankPlayerController, 
            &AToonTankPlayerController::SetPlayerEnabledState, 
            true
        );

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false
        );
    }
}

int32 AToonTankGameMode::GetTargetTowerCount(){
    TSubclassOf<class ATower> TowerClass = ATower::StaticClass();
    TArray<AActor*> Towers;   
    UGameplayStatics::GetAllActorsOfClass(this, TowerClass, Towers);
    
    return Towers.Num();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor){
    if(DeadActor == Tank){      //여기서 Tank가 null이라면 false를 출력한다.
        Tank->HandleDestruction();
        APlayerController* TankController = Tank->GetTankPlayerController();
        if(TankController)
            Tank->DisableInput(TankController);
            TankController->bShowMouseCursor = false;
    }else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){       //DeadActor를 Tower로 Cast했을 때 된다면 그것은 Tower가 되기 때문에 이렇게 작성
        DestroyedTower->HandleDestruction();
    }
}

void AToonTankGameMode::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));       //player가 사용하는 Tank를 나타낸다.
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(CheckTankDistance()){
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction(){
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition(){
    if(CheckTankDistance()){
        Fire();
    }
}

bool ATower::CheckTankDistance(){
    if(Tank){
        FVector TankLoaction = Tank->GetActorLocation();
        
        float Distance = FVector::Dist(GetActorLocation(), TankLoaction);

        if(Distance <= FireRange){
            return true;
        }else{
            return false;
        }
    }else{
        UE_LOG(LogTemp, Warning, TEXT("Player Tank is missing"));
        return false;
    }
}


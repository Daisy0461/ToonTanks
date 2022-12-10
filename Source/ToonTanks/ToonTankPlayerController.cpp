// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool bPlayerEnable){
    if(bPlayerEnable){
        GetPawn()->EnableInput(this);
    }else{
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bPlayerEnable;
}

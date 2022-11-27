// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	RootComponent->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
}

//이 자체로 Tick에 넣지 않아도 매 프래임마다 호출이 된다.
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //TEXT에는 Input에서 이름으로 확인할 수 있는 것으로 넣고 두번째 파라미터는 이 BindAxis를 어디에 적용을 할건지
    //세번째는 어떤 함수에 Input으로 들어온 값을 넣을 것인지를 정하는 것이다.
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value){

}
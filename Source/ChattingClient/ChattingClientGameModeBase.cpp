// Copyright Epic Games, Inc. All Rights Reserved.

#include "User.h"
#include "Kismet/GameplayStatics.h"
#include "ChattingClientGameModeBase.h"

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<AActor> UserActor = AUser::StaticClass();
	TArray<AActor*>actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), UserActor, actors);
	User = Cast<AUser>(actors[0]);
}
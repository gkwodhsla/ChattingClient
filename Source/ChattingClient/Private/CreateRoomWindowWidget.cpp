// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateRoomWindowWidget.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"
#include "../ChattingClientGameModeBase.h"

void UCreateRoomWindowWidget::CreateButtonClickedCallback()
{
	auto user = Cast<AChattingClientGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->User;
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "CreateButtonClicked");
}

void UCreateRoomWindowWidget::CancelButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "CancelButtonClicked");

}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomListWidget.generated.h"

/**
 * 
 */
class UScrollBox;
class UButton;
UCLASS()
class CHATTINGCLIENT_API URoomListWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ChattingRoomScrollBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* RoomJoinButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* RoomCreateButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton = nullptr;

};

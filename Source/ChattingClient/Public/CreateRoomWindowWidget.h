// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateRoomWindowWidget.generated.h"

class UEditableTextBox;
class UButton;

UCLASS()
class CHATTINGCLIENT_API UCreateRoomWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ParticipantsTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RoomNameTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CreateButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton = nullptr;
};

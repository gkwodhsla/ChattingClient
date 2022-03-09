// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateRoomWindowWidget.generated.h"

class AUser;
class UEditableTextBox;
class UButton;

const std::string ROOM_OPEN_REQ_COMMAND = "o ";

UCLASS()
class CHATTINGCLIENT_API UCreateRoomWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

public:
	UFUNCTION()
	void CreateButtonClickedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ParticipantsTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RoomNameTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CreateButton = nullptr;
	UPROPERTY()
	AUser* User = nullptr;
};

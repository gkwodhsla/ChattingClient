// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

const int BACKGROUND_IMG_INDEX = 0;
const int USER_LIST_INDEX = 1;
const int ROOM_LIST_INDEX = 2;
const int CREATE_ROOM_INDEX = 3;
const int SEND_MAIL_INDEX = 4;

class UButton;
class UWidgetSwitcher;
class UUserListWidget;
class UCreateRoomWindowWidget;
class USendMailWindowWidget;

UCLASS()
class CHATTINGCLIENT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UserListButtonClickedCallback();
	UFUNCTION()
	void RoomListButtonClickedCallback();
	UFUNCTION()
	void CreateRoomButtonClickedCallback();
	UFUNCTION()
	void SendMailButtonClickedCallback();
	UFUNCTION()
	void ExitButtonClickedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* LobbyWidgetSwitcher = nullptr;
	UPROPERTY(meta = (BindWidget))
	UUserListWidget* UserListScroll = nullptr;
	UPROPERTY(meta = (BindWidget))
	UUserListWidget* RoomListScroll = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCreateRoomWindowWidget* CreateRoomWindow = nullptr;
	UPROPERTY(meta = (BindWidget))
	USendMailWindowWidget* SendMailWindow = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UButton* UserListButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* RoomListButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CreateRoomButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* SendMailButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton = nullptr;

};

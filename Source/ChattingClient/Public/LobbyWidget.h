// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <string>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

const FString USER_LIST_REQ_COMMAND = "us";
const FString ROOM_LIST_REQ_COMMAND = "lt";
const FString END_PROGRAM_REQ_COMMAND = "x";

const int LOBBY_INDEX = 0;
const int USER_LIST_INDEX = 1;
const int ROOM_LIST_INDEX = 2;
const int CREATE_ROOM_INDEX = 3;
const int SEND_MAIL_INDEX = 4;
const int CHATTING_WINDOW_INDEX = 5;

class AUser;

class UButton;
class UWidgetSwitcher;
class UUserListWidget;
class UCreateRoomWindowWidget;
class USendMailWindowWidget;
class UChattingWindowWidget;
class UUserInfoWidget;
class UWarningMsgWidget;

UCLASS()
class CHATTINGCLIENT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

	UFUNCTION()
	void UserListButtonClickedCallback();
	UFUNCTION()
	void RoomListButtonClickedCallback();
	UFUNCTION()
	void CreateRoomButtonClickedCallback();
	UFUNCTION()
	void SendMailButtonClickedCallback();
	UFUNCTION()
	void ChattingWindowButtonClickedCallback();
	UFUNCTION()
	void ExitButtonClickedCallback();
	UFUNCTION()
	void AnimationFinishedCallback();

public:
	void ShowUserInfoList(const std::vector<std::string>& UserList);
	void ShowUserSpecificInfo(const std::vector<std::string>& UserList);
	void ShowRoomList(const std::vector<std::string>& RoomList);
	void ShowRoomSpecificInfo(const std::vector<std::string>& RoomList);
	void AddChattingMsgToChattingWindow(const std::vector<std::string>& Chatting);
	void EraseAllChatting();
	void GoToLobby();
	void ShowExitButton();
	void HideExitButton();
	void ShowWarningMsg(const FString& Msg);

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
	UChattingWindowWidget* ChattingWindow = nullptr;

	
	UPROPERTY(meta = (BindWidget))
	UButton* UserListButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* RoomListButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CreateRoomButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* SendMailButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ChattingWindowButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UWarningMsgWidget* WarningMsg = nullptr;

	UPROPERTY()
	AUser* User = nullptr;

	TArray<UUserWidget*> UserListWidgets;
	TArray<UUserWidget*> RoomListWidgets;

private:
	FWidgetAnimationDynamicEvent EndDelegate;
};

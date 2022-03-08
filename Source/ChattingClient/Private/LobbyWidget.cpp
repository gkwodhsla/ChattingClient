// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/WidgetSwitcher.h"

void ULobbyWidget::UserListButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(USER_LIST_INDEX);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "UserListButtonClicked");
}
void ULobbyWidget::RoomListButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(ROOM_LIST_INDEX);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "RoomListButtonClicked");
}
void ULobbyWidget::CreateRoomButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(CREATE_ROOM_INDEX);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "CreateRoomButtonClicked");
}
void ULobbyWidget::SendMailButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(SEND_MAIL_INDEX);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "SendMailButtonClicked");
}
void ULobbyWidget::ExitButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "ExitButtonClicked");
}
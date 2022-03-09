// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ChattingWindowWidget.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"
#include "UserListWidget.h"
#include "UserInfoWidget.h"
#include "UserSpecificInfoWindowWidget.h"
#include "RoomInfoWidget.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	UserListButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::UserListButtonClickedCallback);
	RoomListButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::RoomListButtonClickedCallback);
	CreateRoomButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::CreateRoomButtonClickedCallback);
	SendMailButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::SendMailButtonClickedCallback);
	ChattingWindowButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::ChattingWindowButtonClickedCallback);
	ExitButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::ExitButtonClickedCallback);
}

void ULobbyWidget::UserListButtonClickedCallback()
{
	if (User)
	{
		LobbyWidgetSwitcher->SetActiveWidgetIndex(USER_LIST_INDEX);

		User->SendMsg(USER_LIST_REQ_COMMAND);
		//유저 정보를 달라고 서버에 요청합니다.
	}
}

void ULobbyWidget::RoomListButtonClickedCallback()
{
	if (User)
	{
		LobbyWidgetSwitcher->SetActiveWidgetIndex(ROOM_LIST_INDEX);

		User->SendMsg(ROOM_LIST_REQ_COMMAND);
		//방 정보를 달라고 서버에 요청합니다.
	}
}

void ULobbyWidget::CreateRoomButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(CREATE_ROOM_INDEX);
}

void ULobbyWidget::SendMailButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(SEND_MAIL_INDEX);
}

void ULobbyWidget::ExitButtonClickedCallback()
{
	if (User)
	{
		User->SendMsg(END_PROGRAM_REQ_COMMAND);
	}
}

void ULobbyWidget::ChattingWindowButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(CHATTING_WINDOW_INDEX);
}


void ULobbyWidget::ShowUserInfoList(const std::vector<std::string>& UserList)
{
	if (User)
	{
		for (int i = 0; i < UserListWidgets.Num(); ++i)
		{
			UserListScroll->UserScrollBox->RemoveChild(UserListWidgets[i]);
		}
		UserListWidgets.Reset();
		//새로운 정보를 붙이기 전에 기존 정보를 전부 제거합니다.

		for (int i = 1; i < UserList.size(); ++i)
		{
			UserListWidgets.Add(CreateWidget(GetWorld(), User->UserInfoWidgetClass));
			auto newUserInfo = Cast<UUserInfoWidget>(UserListWidgets.Top());
			if (newUserInfo)
			{
				newUserInfo->UserInfoText->SetText(FText::FromString(UserList[i].c_str()));
				UserListScroll->UserScrollBox->AddChild(newUserInfo);
			}
		}
		//0번 인덱스는 ------UserList------라는 텔넷에서 보여주는 용도로 사용되는 문자열이라 여기선 포함하지않습니다
	}
}

void ULobbyWidget::ShowUserSpecificInfo(const std::vector<std::string>& UserList)
{
	if (User && UserList.size() > 1)
	{
		auto specificInfoWidget = Cast<UUserSpecificInfoWindowWidget>
			(CreateWidget(GetWorld(), User->UserSpecificInfoWindowWidgetClass));
		specificInfoWidget->InfoText->SetText(FText::FromString(UserList[1].c_str()));
		specificInfoWidget->AddToViewport();
	}
}

void ULobbyWidget::ShowRoomList(const std::vector<std::string>& RoomList)
{
	if (User)
	{
		for (int i = 0; i < RoomListWidgets.Num(); ++i)
		{
			RoomListScroll->UserScrollBox->RemoveChild(RoomListWidgets[i]);
		}
		RoomListWidgets.Reset();
		//새로운 정보를 붙이기 전에 기존 정보를 전부 제거합니다.

		for (int i = 1; i < RoomList.size(); ++i)
		{
			RoomListWidgets.Add(CreateWidget(GetWorld(), User->RoomInfoWidgetClass));
			auto newRoomInfo = Cast<URoomInfoWidget>(RoomListWidgets.Top());
			if (newRoomInfo)
			{
				newRoomInfo->RoomInfoText->SetText(FText::FromString(RoomList[i].c_str()));
				RoomListScroll->UserScrollBox->AddChild(newRoomInfo);
			}
		}
		//0번 인덱스는 ------RoomList------라는 텔넷에서 보여주는 용도로 사용되는 문자열이라 여기선 포함하지않습니다
	}
}

void ULobbyWidget::ShowRoomSpecificInfo(const std::vector<std::string>& RoomList)
{
	if (User && RoomList.size() > 1)
	{
		UE_LOG(LogTemp, Log, TEXT("Call Show Room Specific Info!"));
		std::string temp = "";
		for (int i = 1; i < RoomList.size(); ++i)
		{
			temp = temp + RoomList[i] + "\n";
		}
		auto specificInfoWidget = Cast<UUserSpecificInfoWindowWidget>
			(CreateWidget(GetWorld(), User->UserSpecificInfoWindowWidgetClass, TEXT("RoomSpecificInfo")));
		specificInfoWidget->InfoText->SetText(FText::FromString(temp.c_str()));
		specificInfoWidget->AddToViewport();
	}
}

void ULobbyWidget::AddChattingMsgToChattingWindow(const std::vector<std::string>& Chatting)
{
	ChattingWindow->AddNewChatting(Chatting.at(0));
}

void ULobbyWidget::EraseAllChatting()
{
	ChattingWindow->EraseAllChatting();
}

void ULobbyWidget::GoToLobby()
{
	LobbyWidgetSwitcher->SetActiveWidget(LOBBY_INDEX);
}
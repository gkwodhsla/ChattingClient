// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ChattingWindowWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SendMailWindowWidget.h"
#include "User.h"
#include "UserListWidget.h"
#include "UserInfoWidget.h"
#include "UserSpecificInfoWindowWidget.h"
#include "RoomInfoWidget.h"
#include "WarningMsgWidget.h"


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
	InviteButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::InviteButtonClickedCallback);
	ExitButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::ExitButtonClickedCallback);
	EndDelegate.BindDynamic(this, &ULobbyWidget::AnimationFinishedCallback);

	WarningMsg->BindToAnimationFinished(WarningMsg->FadeOut, EndDelegate);
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
	if (!LobbyWidgetSwitcher || !SendMailWindow)
	{
		return;
	}
	LobbyWidgetSwitcher->SetActiveWidgetIndex(SEND_MAIL_INDEX);
	SendMailWindow->ChangeSendMailMode();
}

void ULobbyWidget::ExitButtonClickedCallback()
{
	if (User)
	{
		User->SendMsg(END_PROGRAM_REQ_COMMAND);
	}
}

void ULobbyWidget::InviteButtonClickedCallback()
{
	if (!LobbyWidgetSwitcher || !SendMailWindow)
	{
		return;
	}

	if (User && User->IsJoinRoom)
	{
		LobbyWidgetSwitcher->SetActiveWidgetIndex(SEND_MAIL_INDEX);
		SendMailWindow->ChangeInviteMode();
	}
	if (!User->IsJoinRoom)
	{
		User->ShowWarningMsg("Before sending Invite Message join chatting room first");
	}
}

void ULobbyWidget::ChattingWindowButtonClickedCallback()
{
	if (LobbyWidgetSwitcher)
	{
		LobbyWidgetSwitcher->SetActiveWidgetIndex(CHATTING_WINDOW_INDEX);
	}
}

void ULobbyWidget::AnimationFinishedCallback()
{
	if (WarningMsg)
	{
		WarningMsg->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULobbyWidget::ShowUserInfoList(const std::vector<std::string>& UserList)
{
	if (!User || !UserListScroll)
	{
		return;
	}
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

void ULobbyWidget::ShowUserSpecificInfo(const std::vector<std::string>& UserList)
{
	if (User && UserList.size() > 1)
	{
		auto specificInfoWidget = Cast<UUserSpecificInfoWindowWidget>
			(CreateWidget(GetWorld(), User->UserSpecificInfoWindowWidgetClass));
		if (specificInfoWidget)
		{
			specificInfoWidget->InfoText->SetText(FText::FromString(UserList[1].c_str()));
			specificInfoWidget->AddToViewport();
		}
	}
}

void ULobbyWidget::ShowRoomList(const std::vector<std::string>& RoomList)
{
	if (!User || !RoomListScroll)
	{
		return;
	}
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
		if (specificInfoWidget)
		{
			specificInfoWidget->InfoText->SetText(FText::FromString(temp.c_str()));
			specificInfoWidget->AddToViewport();
		}
	}
}

void ULobbyWidget::AddChattingMsgToChattingWindow(const std::vector<std::string>& Chatting)
{
	if (ChattingWindow)
	{
		ChattingWindow->AddNewChatting(Chatting.at(0));
	}
}

void ULobbyWidget::EraseAllChatting()
{
	if(ChattingWindow)
	{
		ChattingWindow->EraseAllChatting();
	}
}

void ULobbyWidget::GoToLobby()
{
	if (LobbyWidgetSwitcher)
	{
		LobbyWidgetSwitcher->SetActiveWidget(LOBBY_INDEX);
	}
}

void ULobbyWidget::ShowExitButton()
{
	if (ExitButton)
	{
		ExitButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULobbyWidget::HideExitButton()
{
	if (ExitButton)
	{
		ExitButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULobbyWidget::ShowWarningMsg(const FString& Msg)
{
	if (WarningMsg)
	{
		WarningMsg->SetVisibility(ESlateVisibility::Visible);
		WarningMsg->Msg->SetText(FText::FromString(Msg));
		WarningMsg->PlayAnimation(WarningMsg->FadeOut);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "../ChattingClientGameModeBase.h"
#include "User.h"
#include "UserListWidget.h"
#include "UserInfoWidget.h"
#include "UserSpecificInfoWindowWidget.h"

void ULobbyWidget::NativeConstruct()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	UserListButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::UserListButtonClickedCallback);
	RoomListButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::RoomListButtonClickedCallback);
	CreateRoomButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::CreateRoomButtonClickedCallback);
	SendMailButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::SendMailButtonClickedCallback);
	ExitButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::ExitButtonClickedCallback);
}

void ULobbyWidget::UserListButtonClickedCallback()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(USER_LIST_INDEX);

	User->SendMsg("us");
	//유저 정보를 달라고 서버에 요청합니다.
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
//소켓쪽에서 로비위젯의 함수를 호출해준다!
//로비위젯 함수에선 파싱된 메시지를 받아서
//WBP_UserInfo클래스를 만들고 유저 정보 내용을 채워 로비의 유저리스트에 붙여준다.

void ULobbyWidget::ShowUserInfoList(const std::vector<std::string>& UserList)
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

void ULobbyWidget::ShowUserSpecificInfo(const std::vector<std::string>& UserList)
{
	if (UserList.size() > 1)
	{
		auto specificInfoWidget = Cast<UUserSpecificInfoWindowWidget>
			(CreateWidget(GetWorld(), User->UserSpecificInfoWindowWidgetClass));
		specificInfoWidget->InfoText->SetText(FText::FromString(UserList[1].c_str()));
		specificInfoWidget->AddToViewport();
	}
}
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
	//���� ������ �޶�� ������ ��û�մϴ�.
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
//�����ʿ��� �κ������� �Լ��� ȣ�����ش�!
//�κ����� �Լ����� �Ľ̵� �޽����� �޾Ƽ�
//WBP_UserInfoŬ������ ����� ���� ���� ������ ä�� �κ��� ��������Ʈ�� �ٿ��ش�.

void ULobbyWidget::ShowUserInfoList(const std::vector<std::string>& UserList)
{
	for (int i = 0; i < UserListWidgets.Num(); ++i)
	{
		UserListScroll->UserScrollBox->RemoveChild(UserListWidgets[i]);
	}
	UserListWidgets.Reset();
	//���ο� ������ ���̱� ���� ���� ������ ���� �����մϴ�.

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
	//0�� �ε����� ------UserList------��� �ڳݿ��� �����ִ� �뵵�� ���Ǵ� ���ڿ��̶� ���⼱ ���������ʽ��ϴ�
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
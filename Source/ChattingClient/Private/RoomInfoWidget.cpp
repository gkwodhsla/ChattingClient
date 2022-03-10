// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomInfoWidget.h"
#include "User.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SocketComponent.h"

void URoomInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	SpecificInfoButton->OnClicked.AddUniqueDynamic(this, &URoomInfoWidget::SpecificInfoButtonClickedCallback);

	JoinButton->OnClicked.AddUniqueDynamic(this, &URoomInfoWidget::JoinButtonClickedCallback);
}

void URoomInfoWidget::SpecificInfoButtonClickedCallback()
{
	if (!User)
	{
		return;
	}
	FText roomInfo = RoomInfoText->GetText();

	auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
	if (tokens.size() > 0)
	{
		FString msgToSend = ROOM_SPECIFIC_INFO_REQ_COMMAND;
		msgToSend.AppendChar(tokens[0][1]); //->�� �ε��� ��ȣ�Դϴ�. tokens[0]�� [�� ��ȣ]<-�̷��� �����Ǿ��ֽ��ϴ�.
		msgToSend.AppendChar('\0');
		//��Ʈ������ ��ȯ�ϰ� �Ľ��� ������ �� �ε��� ��ȣ�� �ٿ��ݴϴ�.
		User->SendMsg(msgToSend);
	}
}

void URoomInfoWidget::JoinButtonClickedCallback()
{
	if (User && !User->IsJoinRoom)
	{
		FText roomInfo = RoomInfoText->GetText();

		auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
		//��Ʈ������ ��ȯ�ϰ� �Ľ��� ������ �� �ε��� ��ȣ�� �ٿ��ݴϴ�.
		FString msgToSend = ROOM_JOIN_REQ_COMMAND;
		if (tokens.size() > 1)
		{
			msgToSend.AppendChar(tokens[0][1]);
			msgToSend.AppendChar('\0');
			User->SendMsg(msgToSend);
			User->JoiningRoom();
			User->RoomName = FText::FromString(tokens[1].c_str());
		}
	}
	if (User->IsJoinRoom)
	{
		User->ShowWarningMsg("Before join another room please <quit room first>");
	}
}
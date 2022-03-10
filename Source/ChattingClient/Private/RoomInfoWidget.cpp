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
		msgToSend.AppendChar(tokens[0][1]); //->방 인덱스 번호입니다. tokens[0]은 [방 번호]<-이렇게 구성되어있습니다.
		msgToSend.AppendChar('\0');
		//스트링으로 변환하고 파싱한 다음에 방 인덱스 번호를 붙여줍니다.
		User->SendMsg(msgToSend);
	}
}

void URoomInfoWidget::JoinButtonClickedCallback()
{
	if (User && !User->IsJoinRoom)
	{
		FText roomInfo = RoomInfoText->GetText();

		auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
		//스트링으로 변환하고 파싱한 다음에 방 인덱스 번호를 붙여줍니다.
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
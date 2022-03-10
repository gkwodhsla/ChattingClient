// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateRoomWindowWidget.h"
#include "../ChattingClientGameModeBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"


void UCreateRoomWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	CreateButton->OnClicked.AddUniqueDynamic(this, &UCreateRoomWindowWidget::CreateButtonClickedCallback);
}

void UCreateRoomWindowWidget::CreateButtonClickedCallback()
{
	if (User->IsJoinRoom)
	{
		User->ShowWarningMsg("Before Creating new room first <quit room>");
		return;
	}

	if (User && !User->IsJoinRoom)
	{
		std::string msgToSend = ROOM_OPEN_REQ_COMMAND;

		FText maxParticipants = ParticipantsTextBox->GetText();
		if (FCString::Atoi(*maxParticipants.ToString()) < MIN_ROOM_PARTICIPANTS)
		{
			User->ShowWarningMsg("Participants must over 2");
			return;
		}
		FText roomName = RoomNameTextBox->GetText();

		msgToSend = msgToSend + std::string(TCHAR_TO_UTF8(*maxParticipants.ToString())) + " ";
		msgToSend += std::string(TCHAR_TO_UTF8(*roomName.ToString()));

		User->SendMsg(msgToSend.c_str());

		User->JoiningRoom();
		//채팅윈도우로 이동합니다.
		User->RoomName = roomName;
	}
	

	if (ParticipantsTextBox)
	{
		ParticipantsTextBox->SetText(FText::FromString(""));
	}
	if (RoomNameTextBox)
	{
		RoomNameTextBox->SetText(FText::FromString(""));
	}
}

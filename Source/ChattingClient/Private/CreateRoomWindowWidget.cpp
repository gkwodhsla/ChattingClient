// Fill out your copyright notice in the Description page of Project Settings.


#include "../ChattingClientGameModeBase.h"
#include "Components/Button.h"
#include "CreateRoomWindowWidget.h"
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
	if (User)
	{
		std::string msgToSend = ROOM_OPEN_REQ_COMMAND;

		FText maxParticipants = ParticipantsTextBox->GetText();
		FText roomName = RoomNameTextBox->GetText();

		msgToSend = msgToSend + std::string(TCHAR_TO_UTF8(*maxParticipants.ToString())) + " ";
		msgToSend += std::string(TCHAR_TO_UTF8(*roomName.ToString()));

		User->SendMsg(msgToSend.c_str());

		User->JoiningRoom();
		//채팅윈도우로 이동합니다.
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateRoomWindowWidget.h"
#include "../ChattingClientGameModeBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"


void UCreateRoomWindowWidget::NativeConstruct()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	CreateButton->OnClicked.AddUniqueDynamic(this, &UCreateRoomWindowWidget::CreateButtonClickedCallback);
}

void UCreateRoomWindowWidget::CreateButtonClickedCallback()
{
	std::string msgToSend = "o ";

	FText maxParticipants = ParticipantsTextBox->GetText();
	FText roomName = RoomNameTextBox->GetText();

	msgToSend = msgToSend + std::string(TCHAR_TO_UTF8(*maxParticipants.ToString())) + " ";
	msgToSend += std::string(TCHAR_TO_UTF8(*roomName.ToString()));

	User->SendMsg(msgToSend.c_str());
	
	User->JoiningRoom();
	//채팅윈도우로 이동합니다.
}

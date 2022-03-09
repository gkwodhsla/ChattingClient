// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomInfoWidget.h"
#include "User.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SocketComponent.h"

void URoomInfoWidget::NativeConstruct()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	SpecificInfoButton->OnClicked.AddUniqueDynamic(this, &URoomInfoWidget::SpecificInfoButtonClickedCallback);

	JoinButton->OnClicked.AddUniqueDynamic(this, &URoomInfoWidget::JoinButtonClickedCallback);
}

void URoomInfoWidget::SpecificInfoButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Specific button clicked");
	FText roomInfo = RoomInfoText->GetText();
	
	auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
	//스트링으로 변환하고 파싱한 다음에 방 인덱스 번호를 붙여줍니다.
	std::string msgToSend = "st ";
	msgToSend.push_back(tokens[0][1]);
	msgToSend.push_back('\0');
	User->SendMsg(msgToSend.c_str());
}

void URoomInfoWidget::JoinButtonClickedCallback()
{
	FText roomInfo = RoomInfoText->GetText();
	
	auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
	//스트링으로 변환하고 파싱한 다음에 방 인덱스 번호를 붙여줍니다.
	std::string msgToSend = "j ";
	msgToSend.push_back(tokens[0][1]);
	msgToSend.push_back('\0');
	User->SendMsg(msgToSend.c_str());
	User->JoiningRoom();

}
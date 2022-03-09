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
	//��Ʈ������ ��ȯ�ϰ� �Ľ��� ������ �� �ε��� ��ȣ�� �ٿ��ݴϴ�.
	std::string msgToSend = "st ";
	msgToSend.push_back(tokens[0][1]);
	msgToSend.push_back('\0');
	User->SendMsg(msgToSend.c_str());
}

void URoomInfoWidget::JoinButtonClickedCallback()
{
	FText roomInfo = RoomInfoText->GetText();
	
	auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*roomInfo.ToString()), ' ');
	//��Ʈ������ ��ȯ�ϰ� �Ľ��� ������ �� �ε��� ��ȣ�� �ٿ��ݴϴ�.
	std::string msgToSend = "j ";
	msgToSend.push_back(tokens[0][1]);
	msgToSend.push_back('\0');
	User->SendMsg(msgToSend.c_str());
	User->JoiningRoom();

}
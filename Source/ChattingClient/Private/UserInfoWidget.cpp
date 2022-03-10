// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInfoWidget.h"
#include "User.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SocketComponent.h"

void UUserInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}
	SpecificInfoButton->OnClicked.AddUniqueDynamic(this, &UUserInfoWidget::SpecificInfoButtonClickedCallback);
}

void UUserInfoWidget::SpecificInfoButtonClickedCallback()
{
	if (!User || !UserInfoText)
	{
		return;
	}
	FText userInfo = UserInfoText->GetText();
	auto tokens = USocketComponent::Tokenizing(TCHAR_TO_UTF8(*userInfo.ToString()), ' ');
	std::string msgToSend = "pf " + tokens[0];
	User->SendMsg(msgToSend.c_str());
}
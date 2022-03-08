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
	//User->SendMsg("lt");
}

void URoomInfoWidget::JoinButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Join Button Clicked");
}
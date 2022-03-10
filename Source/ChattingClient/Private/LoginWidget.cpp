// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "SocketComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ChattingClientGameModeBase.h"
#include "User.h"
#include "WarningMsgWidget.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	LoginButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::LoginButtonClickedCallback);
	EndDelegate.BindDynamic(this, &ULoginWidget::AnimationFinishedCallback);

	WarningMsg->BindToAnimationFinished(WarningMsg->FadeOut, EndDelegate);
}

void ULoginWidget::AnimationFinishedCallback()
{
	if (WarningMsg)
	{
		WarningMsg->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULoginWidget::LoginButtonClickedCallback()
{
	if (!User || !LoginTextBox || !WarningMsg)
	{
		return;
	}
	FText text = LoginTextBox->GetText();
	if (text.ToString().Len() > 0)
	{
		FString msg = LOGIN_REQ_COMMAND + text.ToString();

		User->SendMsg(msg);

		User->LoginWidget->RemoveFromViewport();
		User->LobbyWidget->AddToViewport();
		User->UserName = text;
	}
	else
	{
		WarningMsg->SetVisibility(ESlateVisibility::Visible);
		WarningMsg->Msg->SetText(FText::FromString(TEXT("Name must be at least one letters")));
		WarningMsg->PlayAnimation(WarningMsg->FadeOut);
	}
}

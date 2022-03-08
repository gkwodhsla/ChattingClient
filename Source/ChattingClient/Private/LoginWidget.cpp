// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "SocketComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ChattingClientGameModeBase.h"
#include "User.h"

void ULoginWidget::NativeConstruct()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	LoginButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::LoginButtonClickedCallback);
}

void ULoginWidget::LoginButtonClickedCallback()
{
	FText text = LoginTextBox->GetText();
	FString msg = "login " + text.ToString();
	
	User->SendMsg(msg);

	User->LoginWidget->RemoveFromViewport();
	User->LobbyWidget->AddToViewport();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, text.ToString());
}

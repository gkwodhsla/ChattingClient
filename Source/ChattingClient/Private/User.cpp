// Fill out your copyright notice in the Description page of Project Settings.


#include "User.h"
#include "LoginWidget.h"
#include "LobbyWidget.h"
#include "SendMailWindowWidget.h"
#include "CreateRoomWindowWidget.h"
#include "SocketComponent.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUser::AUser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> loginWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Login.WBP_Login_C'"));
	if (loginWidgetBP.Succeeded())
	{
		LoginWidgetClass = loginWidgetBP.Class;
		LoginWidget = CreateWidget(GetWorld(), LoginWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> lobbyWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Lobby.WBP_Lobby_C'"));
	if (lobbyWidgetBP.Succeeded())
	{
		LobbyWidgetClass = lobbyWidgetBP.Class;
		LobbyWidget = CreateWidget(GetWorld(), LobbyWidgetClass);
	}

	SockComp = CreateDefaultSubobject<USocketComponent>(TEXT("SockComp"));
}

// Called when the game starts or when spawned
void AUser::BeginPlay()
{
	Super::BeginPlay();
	if (LoginWidget)
	{
		auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(playerController))
		{
			FInputModeUIOnly mode;
			playerController->SetInputMode(mode);
			playerController->SetShowMouseCursor(true);
		}
		Cast<ULoginWidget>(LoginWidget)->LoginButton->OnClicked.AddDynamic(this, &AUser::LoginButtonClickedCallback);
		
		AddLobbyCallbackFunction();
		LoginWidget->AddToViewport();
		//LobbyWidget->AddToViewport();
	}
}

// Called every frame
void AUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUser::LoginButtonClickedCallback()
{
	FText text = Cast<ULoginWidget>(LoginWidget)->LoginTextBox->GetText();
	FString msg = "login " + text.ToString();
	SockComp->SendMsg(msg);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, text.ToString());
}

void AUser::AddLobbyCallbackFunction()
{
	ULobbyWidget* lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	lobbyWidget->UserListButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::UserListButtonClickedCallback);
	lobbyWidget->RoomListButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::RoomListButtonClickedCallback);
	lobbyWidget->CreateRoomButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::CreateRoomButtonClickedCallback);
	lobbyWidget->SendMailButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::SendMailButtonClickedCallback);
	lobbyWidget->ExitButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::ExitButtonClickedCallback);

	lobbyWidget->SendMailWindow->SendButton->OnClicked.
		AddDynamic(lobbyWidget->SendMailWindow, &USendMailWindowWidget::SendButtonClickedCallback);
	lobbyWidget->SendMailWindow->CancelButton->OnClicked.
		AddDynamic(lobbyWidget->SendMailWindow, &USendMailWindowWidget::CancelButtonClickedCallback);

	lobbyWidget->CreateRoomWindow->CreateButton->OnClicked.
		AddDynamic(lobbyWidget->CreateRoomWindow, &UCreateRoomWindowWidget::CreateButtonClickedCallback);
	lobbyWidget->CreateRoomWindow->CancelButton->OnClicked.
		AddDynamic(lobbyWidget->CreateRoomWindow, &UCreateRoomWindowWidget::CancelButtonClickedCallback);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "User.h"
#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUser::AUser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> LoginWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Login.WBP_Login_C'"));
	if (LoginWidgetBP.Succeeded())
	{
		LoginWidgetClass = LoginWidgetBP.Class;

		LoginWidget = CreateWidget(GetWorld(), LoginWidgetClass);
	}
	else
	{
		
	}
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

		LoginWidget->AddToViewport();
	}
}

// Called every frame
void AUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUser::LoginButtonClickedCallback()
{
	auto text = Cast<ULoginWidget>(LoginWidget)->LoginTextBox->GetText();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, text.ToString());
}
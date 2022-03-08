// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChattingClientGameModeBase.generated.h"

class AUser;

UCLASS()
class CHATTINGCLIENT_API AChattingClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	AUser* User;
};

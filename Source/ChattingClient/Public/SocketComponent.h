#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SocketComponent.generated.h"

class FSocket;

const size_t MAX_BUFFER_SIZE = 1024;

USTRUCT(BlueprintType)
struct FSendBuffer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint32 LeftPos;
	UPROPERTY()
	uint32 RightPos;
	TStaticArray<char, MAX_BUFFER_SIZE> Buffer;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHATTINGCLIENT_API USocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USocketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SendMsg(const FString& Msg);
	void ProcessingRecv();
	void ProcessingSend();

private:
	FSocket* Socket = nullptr;
	TStaticArray<char, MAX_BUFFER_SIZE> ReadBuffer;
	TQueue<FSendBuffer, EQueueMode::Spsc> SendQ; //Single Producer, Single Consumer
	//������ ������ �Լ����� SendQ�� �����͸� �־���ٰ�
	//���߿� Tick���� �� �濡 �����͸� �۽Ź��ۿ� �����մϴ�.
};

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <string>
#include <vector>
#include "SocketComponent.generated.h"

class FSocket;

const int32 MAX_BUFFER_SIZE = 1024;
const int32 ADDITIONAL_PACKET_SIZE = 2;
//�ڳ� Ŭ���̾�Ʈ�� �޽��� ����� �����ϱ� ���ؼ�
//��û�� �޽����� �߰������� \r\n���ڸ� �ٿ��ݴϴ�.

const char END_SIGN = '\f';
//����->Ŭ���̾�Ʈ ���� �������� \f�� ����մϴ�.

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
	void EndGame();
	void ProcessingPacket(const std::string& Packet);
	std::vector<std::string> Tokenizing(const std::string& Str, const char Delimiter);

private:
	FSocket* Socket = nullptr;
	TStaticArray<char, MAX_BUFFER_SIZE> RecvBuffer;
	int32 RecvRightPos;
	TQueue<FSendBuffer, EQueueMode::Spsc> SendQ; //Single Producer, Single Consumer
	//������ ������ �Լ����� SendQ�� �����͸� �־���ٰ�
	//���߿� Tick���� �� �濡 �����͸� �۽Ź��ۿ� �����մϴ�.
};

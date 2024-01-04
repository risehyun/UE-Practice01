// USMyGameInstance.cpp


#include "Game/SMyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

USMyGameInstance::USMyGameInstance()
{

}

void USMyGameInstance::Init()
{
	// �����Լ��� �������̵��� �Լ��� �ۼ��� ���� �׻� Super Ű������ Init�� ����� �𸮾� ����� ���� �����ϵ��� �Ѵ�.
	Super::Init();

    // �� �����͸� ���� �̸��� ���̵� �ִ´�.
    FBirdData SrcRawData(TEXT("Pigeon17"), 17);
    UE_LOG(LogTemp, Log, TEXT("[SrcRawData] Name: %s, ID: %d"), *SrcRawData.Name, SrcRawData.ID);

    // ������Ʈ ���͸� ��ο� saved ������ �߰��ؼ� ���� ��θ� �ϼ��Ѵ�. 
    // ������� ��ΰ� �ùٸ��� Ȯ���ϱ� ���� �α׸� ����Ѵ�.
    const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
    UE_LOG(LogTemp, Log, TEXT("SavedDir: %s"), *SavedDir);

    // ����ȭ�ؼ� ������ ������ ������ �̸��� �������ְ�
    const FString RawDataFileName(TEXT("RawData.bin"));
    // ��û ������� �����θ� ���� �� ���� save dir�� ���ؼ� ������ ������ �̸��� ���̴� combine�� ���ش�.
    FString AbsolutePathForRawData = FPaths::Combine(*SavedDir, *RawDataFileName);
    UE_LOG(LogTemp, Log, TEXT("Relative path for saved file: %s"), *AbsolutePathForRawData);
    // �� �ڵ忡�� ������� ���� ��ü ��θ� �״�� ���� �ʰ� �𸮾� �°� �������� ���ش�.
    FPaths::MakeStandardFilename(AbsolutePathForRawData);
    UE_LOG(LogTemp, Log, TEXT("Absolute path for saved file: %s"), *AbsolutePathForRawData);

    // ������� ��ο� ������ �� FileWriterArchive�� ����� ���� �Լ��� ����Ѵ�.
    // ���ڷ� path�� �Ѱ��ش�.
    FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*AbsolutePathForRawData);
    if (nullptr != RawFileWriterAr)
    {
        // ���ڷ� �ѱ� ��ġ�� �� �ο� �����͸� �Ѱ��ش�.
        *RawFileWriterAr << SrcRawData;
        // �޸� ������ ���� ���� �����͸� �ѱ�� �۾��� ������ 
        // �ӽ÷� ������� ��ī�̺긦 �ݰ� �ٷ� �����ش�.
        RawFileWriterAr->Close();
        delete RawFileWriterAr;
        // ���� ��ī�̺�� nullptr�� ����� ���� ���� ���ش�. 
        // �̷��� �ϸ� ���� � �������� �� �����Ϳ� �����ϴ��� 
        // nullptr���� �ƴ��� üũ�ϴ� ���� ���������Ƿ� ��۸� �����͸� �������ش�.
        RawFileWriterAr = nullptr;
    }

    // ����� ������ �ٽ� �ѹ� �о� �� �� �� �����Ϳ� ������ �Ѵ�.
    FBirdData DstRawData;
    FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*AbsolutePathForRawData);
    if (nullptr != RawFileReaderAr)
    {
        // RawFileReaderAr�� ���� DstRawData��� ������ �����. 
        // �����ڰ� << ���������� ��ǻ� ������ ������ >> �� �ȴٰ� �����ϸ� ���ϴ�.
        *RawFileReaderAr << DstRawData;
        // �о�� �۾��� �������Ƿ� ��ī�̺긦 �ݰ�, �������ش�.
        RawFileReaderAr->Close();
        delete RawFileReaderAr;
        // ��۸� ������ ������ ���� ���� ���� ó���� ���� nullptr ó���� ���ش�.
        RawFileReaderAr = nullptr;

        // ���������� �о �����͸� Ȯ���ϱ� ���� �α׸� ������ش�.
        UE_LOG(LogTemp, Log, TEXT("[DstRawData] Name: %s, ID: %d"), *DstRawData.Name, DstRawData.ID);
    }

    // �ø��������� ������ ������ ���ο� ������Ʈ�� ���� ���ش�. 
    SerializedPigeon = NewObject<USPigeon>();
    SerializedPigeon->SetName(TEXT("Pigeon76"));
    SerializedPigeon->SetID(76);
    UE_LOG(LogTemp, Log, TEXT("[SerializedPigeon] Name: %s, ID: %d"), *SerializedPigeon->GetName(), SerializedPigeon->GetID());

    // ���ݺ��ʹ� ������Ʈ ������ ���� ��ü�� ���� ������ �غ���.
    // ������ �̸��� �����ϰ� ��θ� ����
    const FString ObjectDataFileName(TEXT("ObjectData.bin"));
    FString AbsolutePathForObjectData = FPaths::Combine(*SavedDir, *ObjectDataFileName);
    //  ������� ��θ� �𸮾� ���˿� �°� ���� ���ش�.
    FPaths::MakeStandardFilename(AbsolutePathForObjectData);

    // �̹����� �𸮾� ������Ʈ�� �޸𸮿� �����ϱ� ���� ������ ������ �� ������ ������ش�.
    // Array�� �ڷ����� Uint8�̴�. ��, �� ĭ �� 1����Ʈ�̱� ������ �ۼ��ϱⰡ ����.
    // ���� �� 1����Ʈ ¥�� TArray�� ������ش�.
    TArray<uint8> BufferArray;
    // �޸� �����Ϳ� �� TArray�� �������ش�.
    FMemoryWriter MemoryWriterAr(BufferArray);
    // �Ʊ� ���� ���´� ������ �������� ���� �𸮾� ������Ʈ�� 
    // �ٽ� �޸� �����Ϳ� �ø�������� ���ش�.
    SerializedPigeon->Serialize(MemoryWriterAr);

    // ������ �ϱ� ���� Writer�� ��ī�̺긦 �����´�.
    TUniquePtr<FArchive> ObjectDataFileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*AbsolutePathForObjectData));
    if (nullptr != ObjectDataFileWriterAr)
    {
        // ���ۿ� ������ �ִ� ������ ��ī�̺꿡 �������ش���
        *ObjectDataFileWriterAr << BufferArray;
        // ������ �������Ƿ� ��ī�̺긦 �ݴ´�.
        ObjectDataFileWriterAr->Close();

        ObjectDataFileWriterAr = nullptr; //delete ObjectDataFileWriterAr; �� ���� ȿ��.
    }

    // �̹����� ���ۿ� ����� �𸮾� ������Ʈ �����͸� �о�´�.
    // �Ȱ��� �о�� ���۸� ����� �� ����
    TArray<uint8> BufferArrayFromObjectDataFile;
    TUniquePtr<FArchive> ObjectDataFileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*AbsolutePathForObjectData));
    if (nullptr != ObjectDataFileReaderAr)
    {
        // ��ī�̺긦 ���ؼ� �Ȱ��� �о�´�.
        *ObjectDataFileReaderAr << BufferArrayFromObjectDataFile;
        // �б� �۾��� �������Ƿ� ��ī�̺긦 �ݰ� nullptr ó�����ش�.
        ObjectDataFileReaderAr->Close();

        ObjectDataFileReaderAr = nullptr;
    }

    // �о�� ������Ʈ �����͸� �α׷� ����� Ȯ���Ѵ�.
    FMemoryReader MemoryReaderAr(BufferArrayFromObjectDataFile);
    USPigeon* Pigeon77 = NewObject<USPigeon>();
    Pigeon77->Serialize(MemoryReaderAr);
    UE_LOG(LogTemp, Log, TEXT("[Pigeon77] Name: %s, ID: %d"), *Pigeon77->GetName(), Pigeon77->GetID());


    // JSON ��� �ǽ�
    // Json ������ ����� ��ġ ��θ� �����ش�.
    const FString JsonDataFileName(TEXT("StudyJsonFile.txt"));
    FString AbsolutePathForJsonData = FPaths::Combine(*SavedDir, *JsonDataFileName);
    FPaths::MakeStandardFilename(AbsolutePathForJsonData);

    /*
        json ���� ���˿� ������ ������ �� 
        json object�� json value�� ����� �� �ִ�.

        json object�� ��� new object�� ���� �����ϰų� ���� �� ���� ����ü�̴�.

        �ݸ� ������Ʈ ������ �ƴ� �ܼ� ���� �����ϰų� �а� ���� ���� 
        json value�� ����ϸ� �ȴ�.
    
    */

    // json ������Ʈ�� �ϳ� ������� ����
    TSharedRef<FJsonObject> SrcJsonObject = MakeShared<FJsonObject>();
    FJsonObjectConverter::UStructToJsonObject(SerializedPigeon->GetClass(), SerializedPigeon, SrcJsonObject);

    // json ������Ʈ�� ��� ������ �� �� �����ϰ� ������ �ʿ䰡 �ִ�.
    // ���� TShared ���۷����� ����Ѵ�.
    // ���� TObject�� ����ص� ������ ���� �̷��� �� ������ 
    // ���۷����� ����ϸ� nullptr�� �ʱ�ȭ�� ���� �ʴ� ���� ������ �����Ƿ� 
    // ���� �� �����ϰ� �ڵ带 ¥�� �����̴�.

    // json�� �����ϱ� ���� ��ī�̺긦 ����ؼ� ���̺긦 �Ѵ�.
    FString JsonOutString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
    if (true == FJsonSerializer::Serialize(SrcJsonObject, JsonWriterAr))
    {
        // ������ ��ο� ������ �ش޶�� ��û�Ѵ�.
        FFileHelper::SaveStringToFile(JsonOutString, *AbsolutePathForJsonData);
    }

    // ���� �ٷ� ������ ����� ������ �о� �´�.
    // ������ ���� �о�� ��ī�̺긦 ������ �����͸� �ε带 �� ����
    FString JsonInString;
    FFileHelper::LoadFileToString(JsonInString, *AbsolutePathForJsonData);
    TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

    // �о�� ����Ǿ� �ִ� �����͸� ��ø�������� ���� �غ� �Ѵ�.
    TSharedPtr<FJsonObject> DstJsonObject;
    // ���� ������ ��ø������� �����ߴٸ�
    if (true == FJsonSerializer::Deserialize(JsonReaderAr, DstJsonObject))
    {
        // �о�� �����͸� ����ؼ� ��ü�� �����.
        USPigeon* Pigeon78 = NewObject<USPigeon>();
        if (true == FJsonObjectConverter::JsonObjectToUStruct(DstJsonObject.ToSharedRef(), Pigeon78->GetClass(), Pigeon78))
        {
            UE_LOG(LogTemp, Log, TEXT("[Pigeon78] Name: %s, ID: %d"), *Pigeon78->GetName(), Pigeon78->GetID());
        }
    }
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}
// USMyGameInstance.cpp


#include "Game/SMyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"

USMyGameInstance::USMyGameInstance()
{

}

void USMyGameInstance::Init()
{
	// 가상함수를 오버라이드한 함수를 작성할 때는 항상 Super 키워드의 Init을 사용해 언리얼 기능을 먼저 실행하도록 한다.
	Super::Init();

    // 새 데이터를 만들어서 이름과 아이디를 넣는다.
    FBirdData SrcRawData(TEXT("Pigeon17"), 17);
    UE_LOG(LogTemp, Log, TEXT("[SrcRawData] Name: %s, ID: %d"), *SrcRawData.Name, SrcRawData.ID);

    // 프로젝트 디렉터리 경로에 saved 폴더를 추가해서 최종 경로를 완성한다. 
    // 만들어진 경로가 올바른지 확인하기 위해 로그를 출력한다.
    const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
    UE_LOG(LogTemp, Log, TEXT("SavedDir: %s"), *SavedDir);

    // 직렬화해서 저장할 데이터 파일의 이름을 지정해주고
    const FString RawDataFileName(TEXT("RawData.bin"));
    // 엄청 길어지는 절대경로를 제거 한 다음 save dir을 통해서 저장할 데이터 이름을 붙이는 combine을 해준다.
    FString AbsolutePathForRawData = FPaths::Combine(*SavedDir, *RawDataFileName);
    UE_LOG(LogTemp, Log, TEXT("Relative path for saved file: %s"), *AbsolutePathForRawData);
    // 위 코드에서 만들어진 파일 전체 경로를 그대로 쓰지 않고 언리얼에 맞게 재조정을 해준다.
    FPaths::MakeStandardFilename(AbsolutePathForRawData);
    UE_LOG(LogTemp, Log, TEXT("Absolute path for saved file: %s"), *AbsolutePathForRawData);

    // 만들어진 경로에 저장을 할 FileWriterArchive를 만들기 위해 함수를 사용한다.
    // 인자로 path를 넘겨준다.
    FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*AbsolutePathForRawData);
    if (nullptr != RawFileWriterAr)
    {
        // 인자로 넘긴 위치에 새 로우 데이터를 넘겨준다.
        *RawFileWriterAr << SrcRawData;
        // 메모리 누수를 막기 위해 데이터를 넘기는 작업이 끝나면 
        // 임시로 만들어진 아카이브를 닫고 바로 지워준다.
        RawFileWriterAr->Close();
        delete RawFileWriterAr;
        // 지운 아카이브는 nullptr로 만들어 완전 삭제 해준다. 
        // 이렇게 하면 추후 어떤 시점에서 이 포인터에 접근하더라도 
        // nullptr인지 아닌지 체크하는 것이 가능해지므로 댕글링 포인터를 방지해준다.
        RawFileWriterAr = nullptr;
    }

    // 저장된 파일을 다시 한번 읽어 낸 뒤 새 데이터에 저장을 한다.
    FBirdData DstRawData;
    FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*AbsolutePathForRawData);
    if (nullptr != RawFileReaderAr)
    {
        // RawFileReaderAr로 부터 DstRawData라는 정보를 끌어낸다. 
        // 연산자가 << 방향이지만 사실상 관념적 방향은 >> 가 된다고 생각하면 편하다.
        *RawFileReaderAr << DstRawData;
        // 읽어내는 작업이 끝났으므로 아카이브를 닫고, 삭제해준다.
        RawFileReaderAr->Close();
        delete RawFileReaderAr;
        // 댕글링 포인터 방지를 위해 완전 삭제 처리를 위한 nullptr 처리를 해준다.
        RawFileReaderAr = nullptr;

        // 최종적으로 읽어낸 데이터를 확인하기 위해 로그를 출력해준다.
        UE_LOG(LogTemp, Log, TEXT("[DstRawData] Name: %s, ID: %d"), *DstRawData.Name, DstRawData.ID);
    }

    // 시리얼라이즈된 정보를 가지고 새로운 오브젝트를 생성 해준다. 
    SerializedPigeon = NewObject<USPigeon>();
    SerializedPigeon->SetName(TEXT("Pigeon76"));
    SerializedPigeon->SetID(76);
    UE_LOG(LogTemp, Log, TEXT("[SerializedPigeon] Name: %s, ID: %d"), *SerializedPigeon->GetName(), SerializedPigeon->GetID());

    // 지금부터는 오브젝트 데이터 파일 전체에 대한 저장을 해본다.
    // 저장할 이름을 지정하고 경로를 만들어서
    const FString ObjectDataFileName(TEXT("ObjectData.bin"));
    FString AbsolutePathForObjectData = FPaths::Combine(*SavedDir, *ObjectDataFileName);
    //  만들어진 경로를 언리얼 포맷에 맞게 수정 해준다.
    FPaths::MakeStandardFilename(AbsolutePathForObjectData);

    // 이번에는 언리얼 오브젝트를 메모리에 저장하기 위해 데이터 전달을 할 공간을 만들어준다.
    // Array는 자료형이 Uint8이다. 즉, 한 칸 당 1바이트이기 때문에 작성하기가 쉽다.
    // 따라서 이 1바이트 짜리 TArray를 만들어준다.
    TArray<uint8> BufferArray;
    // 메모리 라이터에 이 TArray를 전달해준다.
    FMemoryWriter MemoryWriterAr(BufferArray);
    // 아까 전에 꺼냈던 정보를 바탕으로 만들어낸 언리얼 오브젝트를 
    // 다시 메모리 라이터에 시리얼라이즈 해준다.
    SerializedPigeon->Serialize(MemoryWriterAr);

    // 저장을 하기 위해 Writer용 아카이브를 가져온다.
    TUniquePtr<FArchive> ObjectDataFileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*AbsolutePathForObjectData));
    if (nullptr != ObjectDataFileWriterAr)
    {
        // 버퍼에 적혀져 있는 내용을 아카이브에 전달해준다음
        *ObjectDataFileWriterAr << BufferArray;
        // 전달이 끝났으므로 아카이브를 닫는다.
        ObjectDataFileWriterAr->Close();

        ObjectDataFileWriterAr = nullptr; //delete ObjectDataFileWriterAr; 와 같은 효과.
    }

    // 이번에는 버퍼에 저장된 언리얼 오브젝트 데이터를 읽어온다.
    // 똑같이 읽어올 버퍼를 만들어 준 다음
    TArray<uint8> BufferArrayFromObjectDataFile;
    TUniquePtr<FArchive> ObjectDataFileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*AbsolutePathForObjectData));
    if (nullptr != ObjectDataFileReaderAr)
    {
        // 아카이브를 통해서 똑같이 읽어온다.
        *ObjectDataFileReaderAr << BufferArrayFromObjectDataFile;
        // 읽기 작업이 끝났으므로 아카이브를 닫고 nullptr 처리해준다.
        ObjectDataFileReaderAr->Close();

        ObjectDataFileReaderAr = nullptr;
    }

    // 읽어온 오브젝트 데이터를 로그로 출력해 확인한다.
    FMemoryReader MemoryReaderAr(BufferArrayFromObjectDataFile);
    USPigeon* Pigeon77 = NewObject<USPigeon>();
    Pigeon77->Serialize(MemoryReaderAr);
    UE_LOG(LogTemp, Log, TEXT("[Pigeon77] Name: %s, ID: %d"), *Pigeon77->GetName(), Pigeon77->GetID());
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}
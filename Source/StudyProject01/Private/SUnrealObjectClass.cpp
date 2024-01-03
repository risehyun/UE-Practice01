// SUnrealObjectClass.h

#include "SUnrealObjectClass.h"

USUnrealObjectClass::USUnrealObjectClass()
{
	Name = TEXT("USUnrealObejctClass CDO");
}

void USUnrealObjectClass::HelloUnreal()
{
	UE_LOG(LogTemp, Log, TEXT("USUnrealObjectClass::HelloUnreal() has been called."));
}

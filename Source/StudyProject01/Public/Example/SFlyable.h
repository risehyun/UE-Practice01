// SFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SFlyable.generated.h"

// This class does not need to be modified.
// Ŭ���� ������ ������ �� ����ϰ� �Ǵ� U Ŭ�����̴�.
UINTERFACE(MinimalAPI)
class USFlyable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
// ��κ��� ���Ǵ� �Ʒ��� I Ŭ�������� �ϰ� �ȴ�.
class STUDYPROJECT01_API ISFlyable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Fly() = 0;
};

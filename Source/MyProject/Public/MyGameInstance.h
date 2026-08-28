
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UMySaveGame;

UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	virtual void Init() override;

	const FString SaveSlotName = TEXT("SaveSlot");

	UPROPERTY()
		UMySaveGame* CurrentSave;

	UFUNCTION()
		void SaveGame(int32 NewRecord);

	UFUNCTION()
		void LoadSave();

	UFUNCTION()
		void ReturnPlayerToMenu();
	
};

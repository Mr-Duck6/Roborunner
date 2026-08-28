

#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"

void UMyGameInstance::Init()
{
	Super::Init();
	LoadSave();
}

void UMyGameInstance::SaveGame(int32 NewRecord)
{
	if (CurrentSave)
	{
		CurrentSave->PlayerRecord = NewRecord;

		UGameplayStatics::SaveGameToSlot(CurrentSave, SaveSlotName,0);
	}
}

void UMyGameInstance::LoadSave()
{

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName,0))
	{
		CurrentSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName,0));
	}
	else
	{
		CurrentSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
}

void UMyGameInstance::ReturnPlayerToMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenuLevel"));
}


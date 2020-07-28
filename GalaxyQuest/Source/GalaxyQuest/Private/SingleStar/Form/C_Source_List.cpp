
#include "../Public/SingleStar/Form/C_Source_List.h"
#include "../Public/SingleStar/Form/C_Source_Form.h"

bool UC_Source_List::Initialize() 
{
	sourceData = LoadObject<UDataTable>(nullptr, TEXT("/Game/Form/SourceForm.SourceForm"));
	UE_LOG(LogTemp, Warning, TEXT("LoadingData"));
	return sourceData != nullptr;
}

UC_Source_List* UC_Source_List::GetList()
{
	return GetMutableDefault<UC_Source_List>();
}

void UC_Source_List::GetAllItem(TArray<FSourceData*>& outItems)
{
	if (sourceData == nullptr)
	{
		if (Initialize() == false)
		{
			return;
		}
	}
	static const FString contexString(TEXT("General"));
	sourceData->GetAllRows(contexString, outItems);
}

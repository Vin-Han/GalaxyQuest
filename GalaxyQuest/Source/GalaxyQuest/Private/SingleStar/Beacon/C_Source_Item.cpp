
#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "Kismet/KismetMathLibrary.h"

void FSourceBase::UpdateState()
{
	if (targetItem && 
		UKismetMathLibrary::RandomFloatInRange(0.0f,1.0f) > targetItem->OccurPercent
		)
	{
		totalCount = UKismetMathLibrary::RandomIntegerInRange(
			targetItem->MinCount, targetItem->MaxCount);
		singlePrice = UKismetMathLibrary::RandomIntegerInRange(
			targetItem->MinPrice, targetItem->MaxPrice);
	}
	else
	{
		totalCount = 0;
		singlePrice = 0;
	}
}

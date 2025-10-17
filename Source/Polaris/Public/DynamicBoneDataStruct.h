#pragma once
#include "CoreMinimal.h"
#include "DynamicBoneBoneOverrideDataStruct.h"
#include "DynamicBoneVariationStruct.h"
#include "DynamicBoneDataStruct.generated.h"

class UPhoenixDynamicBoneBinary;

USTRUCT(BlueprintType)
struct POLARIS_API FDynamicBoneDataStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UPhoenixDynamicBoneBinary* Data;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UPhoenixDynamicBoneBinary* Data_Collision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FDynamicBoneVariationStruct> Data_Variations;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ResetDeltaTimeMul;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    bool IsDontScaleBoneLocalTranslate;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    TArray<FDynamicBoneBoneOverrideDataStruct> DynamicBoneBoneOverrideData;
    
    FDynamicBoneDataStruct();
};


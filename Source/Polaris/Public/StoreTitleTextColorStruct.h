#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoreTitleTextColorStruct.generated.h"

USTRUCT(BlueprintType)
struct POLARIS_API FStoreTitleTextColorStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateColor title_main_color;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor title_outline_color;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 title_outline_size;
    
    FStoreTitleTextColorStruct();
};


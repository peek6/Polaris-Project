#pragma once
#include "CoreMinimal.h"
#include "EStoreItemType.h"
#include "PolarisTextBlock.h"
#include "StoreTitleTextColorStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PolarisStoreFunctionLibrary.generated.h"

UCLASS(Blueprintable)
class POLARIS_API UPolarisStoreFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UPolarisStoreFunctionLibrary();

    UFUNCTION(BlueprintCallable)
    static void SettingStoreTitleColor(UPolarisTextBlock* tb_title, FStoreTitleTextColorStruct color_data, bool enable_outline);

    UFUNCTION(BlueprintCallable)
    static void RecordShortcutKeyPress();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsSpecificLogoDisplayRequiredInStore();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsItemSalesMaintenanceStatus();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInExtraStageBlackPen();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInExtraStage(int32 current_lv, int32 max_level, int32 add_max_level);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsEnableStoreTestSetting();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsEnableLimitedOwnedButton();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDisablePF();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDisableOtherMenu();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCoinSalesMaintenanceStatus();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCoinConsumptionMaintenanceStatus();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsArabic();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsAlertNeededInStore();

    UFUNCTION(BlueprintCallable)
    static void IngameStoreViewerDestroyAllNiagaraEffects();

    UFUNCTION(BlueprintCallable)
    static void IngameStoreViewerDestroyAllDecals();

    UFUNCTION(BlueprintCallable)
    static void IngameStoreClickCharaIcon(int32 button_index);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool HasItemTypeInStore(EStoreItemType target_type);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetUpdateVcNoInStore();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetStoreIconIdFromSetId(const FName& item_id);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FText GetStoreCategoryTitleRawText(EStoreItemType Type);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetLatestBalloonRemainingTimeString();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetLatestBalloonInfo(FString& _out_raw_text, int32& _out_color_idx);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCurrentVerNo();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCurrentVcNumInStore();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool EnableBlackPenScene();

    UFUNCTION(BlueprintCallable)
    static FString ConvertStoreItemRemainingTimeText(int32 remaining_sec);

    UFUNCTION(BlueprintCallable)
    static void ConfigureInfomationID(const FName& info_id);
};


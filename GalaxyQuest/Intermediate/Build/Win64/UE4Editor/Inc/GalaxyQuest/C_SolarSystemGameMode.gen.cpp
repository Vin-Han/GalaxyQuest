// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GalaxyQuest/Public/GameMode/C_SolarSystemGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeC_SolarSystemGameMode() {}
// Cross Module References
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_SolarSystemGameMode_NoRegister();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_SolarSystemGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_GalaxyQuest();
// End Cross Module References
	void AC_SolarSystemGameMode::StaticRegisterNativesAC_SolarSystemGameMode()
	{
	}
	UClass* Z_Construct_UClass_AC_SolarSystemGameMode_NoRegister()
	{
		return AC_SolarSystemGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AC_SolarSystemGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RadiusLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_RadiusLimit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HeightLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_HeightLimit;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AC_SolarSystemGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_GalaxyQuest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_SolarSystemGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameMode/C_SolarSystemGameMode.h" },
		{ "ModuleRelativePath", "Public/GameMode/C_SolarSystemGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_RadiusLimit_MetaData[] = {
		{ "Category", "C_SolarSystemGameMode" },
		{ "ModuleRelativePath", "Public/GameMode/C_SolarSystemGameMode.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_RadiusLimit = { "RadiusLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_SolarSystemGameMode, RadiusLimit), METADATA_PARAMS(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_RadiusLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_RadiusLimit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_HeightLimit_MetaData[] = {
		{ "Category", "C_SolarSystemGameMode" },
		{ "ModuleRelativePath", "Public/GameMode/C_SolarSystemGameMode.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_HeightLimit = { "HeightLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_SolarSystemGameMode, HeightLimit), METADATA_PARAMS(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_HeightLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_HeightLimit_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AC_SolarSystemGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_RadiusLimit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_SolarSystemGameMode_Statics::NewProp_HeightLimit,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AC_SolarSystemGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AC_SolarSystemGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AC_SolarSystemGameMode_Statics::ClassParams = {
		&AC_SolarSystemGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AC_SolarSystemGameMode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AC_SolarSystemGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AC_SolarSystemGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AC_SolarSystemGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AC_SolarSystemGameMode, 854452564);
	template<> GALAXYQUEST_API UClass* StaticClass<AC_SolarSystemGameMode>()
	{
		return AC_SolarSystemGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AC_SolarSystemGameMode(Z_Construct_UClass_AC_SolarSystemGameMode, &AC_SolarSystemGameMode::StaticClass, TEXT("/Script/GalaxyQuest"), TEXT("AC_SolarSystemGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AC_SolarSystemGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

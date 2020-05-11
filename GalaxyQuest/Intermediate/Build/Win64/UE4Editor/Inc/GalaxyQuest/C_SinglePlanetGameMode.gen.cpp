// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GalaxyQuest/Public/GameMode/C_SinglePlanetGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeC_SinglePlanetGameMode() {}
// Cross Module References
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_SinglePlanetGameMode_NoRegister();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_SinglePlanetGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_GalaxyQuest();
// End Cross Module References
	void AC_SinglePlanetGameMode::StaticRegisterNativesAC_SinglePlanetGameMode()
	{
	}
	UClass* Z_Construct_UClass_AC_SinglePlanetGameMode_NoRegister()
	{
		return AC_SinglePlanetGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AC_SinglePlanetGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_GalaxyQuest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameMode/C_SinglePlanetGameMode.h" },
		{ "ModuleRelativePath", "Public/GameMode/C_SinglePlanetGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AC_SinglePlanetGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::ClassParams = {
		&AC_SinglePlanetGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AC_SinglePlanetGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AC_SinglePlanetGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AC_SinglePlanetGameMode, 3562973489);
	template<> GALAXYQUEST_API UClass* StaticClass<AC_SinglePlanetGameMode>()
	{
		return AC_SinglePlanetGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AC_SinglePlanetGameMode(Z_Construct_UClass_AC_SinglePlanetGameMode, &AC_SinglePlanetGameMode::StaticClass, TEXT("/Script/GalaxyQuest"), TEXT("AC_SinglePlanetGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AC_SinglePlanetGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

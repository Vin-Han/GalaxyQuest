// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GalaxyQuest/Public/Planet/C_PlanetController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeC_PlanetController() {}
// Cross Module References
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_PlanetController_NoRegister();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_PlanetController();
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	UPackage* Z_Construct_UPackage__Script_GalaxyQuest();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_NormalPlanetPawn_NoRegister();
// End Cross Module References
	void AC_PlanetController::StaticRegisterNativesAC_PlanetController()
	{
	}
	UClass* Z_Construct_UClass_AC_PlanetController_NoRegister()
	{
		return AC_PlanetController::StaticClass();
	}
	struct Z_Construct_UClass_AC_PlanetController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Planet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Planet;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AC_PlanetController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_GalaxyQuest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_PlanetController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Planet/C_PlanetController.h" },
		{ "ModuleRelativePath", "Public/Planet/C_PlanetController.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_PlanetController_Statics::NewProp_Planet_MetaData[] = {
		{ "ModuleRelativePath", "Public/Planet/C_PlanetController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_PlanetController_Statics::NewProp_Planet = { "Planet", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_PlanetController, Planet), Z_Construct_UClass_AC_NormalPlanetPawn_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_PlanetController_Statics::NewProp_Planet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_PlanetController_Statics::NewProp_Planet_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AC_PlanetController_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_PlanetController_Statics::NewProp_Planet,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AC_PlanetController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AC_PlanetController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AC_PlanetController_Statics::ClassParams = {
		&AC_PlanetController::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AC_PlanetController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AC_PlanetController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AC_PlanetController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AC_PlanetController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AC_PlanetController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AC_PlanetController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AC_PlanetController, 1022459814);
	template<> GALAXYQUEST_API UClass* StaticClass<AC_PlanetController>()
	{
		return AC_PlanetController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AC_PlanetController(Z_Construct_UClass_AC_PlanetController, &AC_PlanetController::StaticClass, TEXT("/Script/GalaxyQuest"), TEXT("AC_PlanetController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AC_PlanetController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

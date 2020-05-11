// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GalaxyQuest/Public/Planet/C_NormalPlanetPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeC_NormalPlanetPawn() {}
// Cross Module References
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_NormalPlanetPawn_NoRegister();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_NormalPlanetPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_GalaxyQuest();
	ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
// End Cross Module References
	void AC_NormalPlanetPawn::StaticRegisterNativesAC_NormalPlanetPawn()
	{
	}
	UClass* Z_Construct_UClass_AC_NormalPlanetPawn_NoRegister()
	{
		return AC_NormalPlanetPawn::StaticClass();
	}
	struct Z_Construct_UClass_AC_NormalPlanetPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SelfRotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SelfRotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SplineCom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SplineCom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SceneCom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SceneCom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlanetMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PlanetMesh;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CollisionCom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CollisionCom;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AC_NormalPlanetPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_GalaxyQuest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Planet/C_NormalPlanetPawn.h" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SelfRotation_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SelfRotation = { "SelfRotation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, SelfRotation), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SelfRotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SelfRotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SplineCom_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SplineCom = { "SplineCom", nullptr, (EPropertyFlags)0x00100000000a000d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, SplineCom), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SplineCom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SplineCom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SceneCom_MetaData[] = {
		{ "Category", "C_NormalPlanetPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SceneCom = { "SceneCom", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, SceneCom), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SceneCom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SceneCom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_PlanetMesh_MetaData[] = {
		{ "Category", "C_NormalPlanetPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_PlanetMesh = { "PlanetMesh", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, PlanetMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_PlanetMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_PlanetMesh_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom_MetaData[] = {
		{ "Category", "C_NormalPlanetPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom = { "CollisionCom", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, CollisionCom), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AC_NormalPlanetPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SelfRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SplineCom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SceneCom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_PlanetMesh,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AC_NormalPlanetPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AC_NormalPlanetPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::ClassParams = {
		&AC_NormalPlanetPawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AC_NormalPlanetPawn_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AC_NormalPlanetPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AC_NormalPlanetPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AC_NormalPlanetPawn, 1327112550);
	template<> GALAXYQUEST_API UClass* StaticClass<AC_NormalPlanetPawn>()
	{
		return AC_NormalPlanetPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AC_NormalPlanetPawn(Z_Construct_UClass_AC_NormalPlanetPawn, &AC_NormalPlanetPawn::StaticClass, TEXT("/Script/GalaxyQuest"), TEXT("AC_NormalPlanetPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AC_NormalPlanetPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

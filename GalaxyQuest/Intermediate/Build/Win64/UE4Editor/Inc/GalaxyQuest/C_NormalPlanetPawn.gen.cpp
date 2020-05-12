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
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GALAXYQUEST_API UClass* Z_Construct_UClass_AC_TrackPlanetPawn_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SunTilt_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SunTilt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurDegree_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurDegree;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FarDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FarDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CloseDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CloseDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OrbitType_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_OrbitType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Target;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsTiltClockWise_MetaData[];
#endif
		static void NewProp_bIsTiltClockWise_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsTiltClockWise;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurTilt_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurTilt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Tilt_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Tilt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RevolutionDay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_RevolutionDay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RotationHour_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_RotationHour;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SunTilt_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SunTilt = { "SunTilt", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, SunTilt), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SunTilt_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SunTilt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurDegree_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurDegree = { "CurDegree", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, CurDegree), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurDegree_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurDegree_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_FarDistance_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_FarDistance = { "FarDistance", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, FarDistance), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_FarDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_FarDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CloseDistance_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CloseDistance = { "CloseDistance", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, CloseDistance), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CloseDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CloseDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_OrbitType_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_OrbitType = { "OrbitType", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, OrbitType), Z_Construct_UClass_AC_TrackPlanetPawn_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_OrbitType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_OrbitType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Target_MetaData[] = {
		{ "Category", "Revolution" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, Target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Target_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Target_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	void Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise_SetBit(void* Obj)
	{
		((AC_NormalPlanetPawn*)Obj)->bIsTiltClockWise = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise = { "bIsTiltClockWise", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AC_NormalPlanetPawn), &Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise_SetBit, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurTilt_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurTilt = { "CurTilt", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, CurTilt), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurTilt_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurTilt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Tilt_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Tilt = { "Tilt", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, Tilt), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Tilt_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Tilt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RevolutionDay_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RevolutionDay = { "RevolutionDay", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, RevolutionDay), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RevolutionDay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RevolutionDay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RotationHour_MetaData[] = {
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RotationHour = { "RotationHour", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, RotationHour), METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RotationHour_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RotationHour_MetaData)) };
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
		{ "Comment", "/*\n\x09""CollisionCom is for gameplay\n\x09SceneCom is for the changeable tilt of itself\n\x09PlanetMesh is for self rotation\n\x09*/" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Planet/C_NormalPlanetPawn.h" },
		{ "ToolTip", "CollisionCom is for gameplay\nSceneCom is for the changeable tilt of itself\nPlanetMesh is for self rotation" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom = { "CollisionCom", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AC_NormalPlanetPawn, CollisionCom), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CollisionCom_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AC_NormalPlanetPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_SunTilt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurDegree,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_FarDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CloseDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_OrbitType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Target,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_bIsTiltClockWise,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_CurTilt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_Tilt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RevolutionDay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AC_NormalPlanetPawn_Statics::NewProp_RotationHour,
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
	IMPLEMENT_CLASS(AC_NormalPlanetPawn, 3029210136);
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

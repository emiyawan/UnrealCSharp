﻿#pragma once

#include "Domain/FDomain.h"
#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Container/FContainerHelper.h"
#include "Reflection/Function/FFunctionDescriptor.h"

class FCSharpBind
{
public:
	static MonoObject* Bind(FDomain* InDomain, UObject* InObject);

	static bool Bind(FDomain* InDomain, UObject* InObject, bool bNeedMonoClass);

	static bool Bind(FDomain* InDomain, UStruct* InStruct, bool bNeedMonoClass);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                 MonoReflectionType* InValueReflectionType);

	static bool Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject);

private:
	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

private:
	static bool BindImplementation(FDomain* InDomain, UObject* InObject, bool bNeedMonoClass);

	static bool BindImplementation(FDomain* InDomain, UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                               MonoReflectionType* InValueReflectionType);

	static bool BindImplementation(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject);

private:
	static bool CanBind(const FDomain* InDomain, UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(const UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

	static void UpdateCallCSharpFunction(UFunction* InFunction);

	static void UpdateCallCSharpFunctionFlags(UFunction* InFunctionCallLua);

private:
	static bool IsOverrideType(const FDomain* InDomain, MonoReflectionType* InMonoReflectionType);

	static bool IsOverrideMethod(const FDomain* InDomain, MonoReflectionMethod* InMonoReflectionMethod);

#if !WITH_EDITOR
private:
	static TSet<TWeakObjectPtr<UStruct>> NotOverrideTypes;
#endif
};

#include "FCSharpBind.inl"

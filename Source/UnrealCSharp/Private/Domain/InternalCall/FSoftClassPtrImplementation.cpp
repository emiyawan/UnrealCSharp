﻿#include "Domain/InternalCall/FSoftClassPtrImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterSoftClassPtr
{
	FRegisterSoftClassPtr()
	{
		FClassBuilder(TEXT("SoftClassPtr"), NAMESPACE_LIBRARY)
			.Function("Register", FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation)
			.Function("UnRegister", FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation)
			.Function("Get", FSoftClassPtrImplementation::SoftClassPtr_GetImplementation)
			.Register();
	}
};

static FRegisterSoftClassPtr RegisterSoftClassPtr;

void FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                      const MonoObject* InClass)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

	const auto SoftClassPtr = new TSoftClassPtr<UObject>(FoundClass);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>>(InMonoObject, SoftClassPtr);
}

void FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftClassPtr<UObject>>(
			InGarbageCollectionHandle);
	});
}

void FSoftClassPtrImplementation::SoftClassPtr_GetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InGarbageCollectionHandle);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
}

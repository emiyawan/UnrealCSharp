﻿#include "Domain/InternalCall/FSubclassOfImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterSubclassOf
{
	FRegisterSubclassOf()
	{
		FClassBuilder(TEXT("SubclassOf"), NAMESPACE_LIBRARY)
			.Function("Register", FSubclassOfImplementation::SubclassOf_RegisterImplementation)
			.Function("UnRegister", FSubclassOfImplementation::SubclassOf_UnRegisterImplementation)
			.Function("Get", FSubclassOfImplementation::SubclassOf_GetImplementation)
			.Register();
	}
};

static FRegisterSubclassOf RegisterSubclassOf;

void FSubclassOfImplementation::SubclassOf_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

	const auto SubclassOf = new TSubclassOf<UObject>(FoundClass);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(InMonoObject, SubclassOf);
}

void FSubclassOfImplementation::SubclassOf_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSubclassOf<
			UObject>>(InGarbageCollectionHandle);
	});
}

void FSubclassOfImplementation::SubclassOf_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InGarbageCollectionHandle);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
}

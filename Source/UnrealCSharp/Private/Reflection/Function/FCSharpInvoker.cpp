#include "Reflection/Function/FCSharpInvoker.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FFunctionDescriptor.h"

DEFINE_FUNCTION(FCSharpInvoker::execCallCSharp)
{
	auto Function = Stack.Node;

	FFunctionDescriptor* FunctionDescriptor = nullptr;

	if (Stack.CurrentNativeFunction != nullptr)
	{
		if (Function != Stack.CurrentNativeFunction)
		{
			Function = Stack.CurrentNativeFunction;

			FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(
				Cast<UClass>(Function->GetOuter()), Function->GetFName());
		}
	}

	if (FunctionDescriptor == nullptr)
	{
		FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(
			Cast<UClass>(Function->GetOuter()), Function->GetFName());
	}

	if (FunctionDescriptor != nullptr)
	{
		FunctionDescriptor->CallCSharp(Stack, RESULT_PARAM);
	}
}

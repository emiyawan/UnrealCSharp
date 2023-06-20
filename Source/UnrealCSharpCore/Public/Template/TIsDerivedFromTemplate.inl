#pragma once

template <typename DerivedType, template <typename> class BaseType>
struct TIsDerivedFromTemplate
{
	template <typename T>
	static std::true_type Test(const BaseType<T>*);

	static std::false_type Test(...);

	enum { Value = std::is_same_v<decltype(Test(std::declval<DerivedType*>())), std::true_type> };
};

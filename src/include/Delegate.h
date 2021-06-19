#pragma once

#include <functional>
#include <vector>

template<typename TReturnType, typename... TArgs>
class Delegate;

//Delegate for any return type (returns a vector of TReturnType in the order of function call)
template<typename TReturnType, typename... TArgs>
class Delegate<TReturnType(TArgs...)>
{
public:
	using Function = std::function<TReturnType(TArgs...)>;
	using ActualReturnType = std::vector<TReturnType>;

	Delegate() = default;
	virtual ~Delegate() = default;

	ActualReturnType operator()(TArgs... args)
	{
		return Invoke(args...);
	}

	ActualReturnType Invoke(TArgs... args)
	{
		ActualReturnType ReturnValues;
		ReturnValues.reserve(functions.size());

		for (auto& function : functions)
		{
			ReturnValues.emplace_back(function(args...));
		}

		return ReturnValues;
	}

	Delegate& operator+=(Function&& function)
	{
		Add(std::move(function));
		return *this;
	}

	void Add(Function&& function)
	{
		functions.emplace_back(std::move(function));
	}

private:
	std::vector<Function> functions;
};

//Delegate overload for void functions
template<typename... TArgs>
class Delegate<void(TArgs...)>
{
public:
	using Function = std::function<void(TArgs...)>;
	using ActualReturnType = void;

	Delegate() = default;
	virtual ~Delegate() = default;

	ActualReturnType operator()(TArgs... args)
	{
		return Invoke(args...);
	}

	ActualReturnType Invoke(TArgs... args)
	{
		for (auto& function : functions)
		{
			function(args...);
		}
	}

	Delegate& operator+=(Function&& function)
	{
		Add(std::move(function));
		return *this;
	}

	void Add(Function&& function)
	{
		functions.emplace_back(std::move(function));
	}

private:
	std::vector<Function> functions;
};
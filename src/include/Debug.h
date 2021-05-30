#pragma once

#include <iostream>

//namespace with utility functions such as Print and Println for easy debugging
namespace Debug
{
	template<typename Arg>
	void Print(Arg arg)
	{
#ifdef DEBUG
		std::cout << arg << " ";
#endif
	}

	template<typename Arg, typename... Args>
	void Print(Arg arg, Args... args)
	{
#ifdef DEBUG
		std::cout << arg << " ";
		Print(args...);
#endif
	}

	template<typename Arg>
	void Println(Arg arg)
	{
#ifdef DEBUG
		std::cout << arg << "\n";
#endif
	}

	template<typename Arg, typename... Args>
	void Println(Arg arg, Args... args)
	{
#ifdef DEBUG
		std::cout << arg << " ";
		Println(args...);
#endif
	}
}
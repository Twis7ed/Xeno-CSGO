#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#ifdef _WIN32
#pragma once
#endif

inline struct Miscellaneous
{
	struct Movement
	{
		bool bunnyhop{ false };
	} mvmnt;
} misc;

#endif // STRUCTS_HPP
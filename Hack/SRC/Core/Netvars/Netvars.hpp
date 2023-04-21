#ifndef NETVARS_HPP
#define NETVARS_HPP
#ifdef _WIN32
#pragma once
#endif

#include <type_traits>
#include <unordered_map>

#include "../../Util/Hash.hpp"

class CRecvTable;
namespace Netvars
{
	void Init() noexcept;

	void Dump(const std::string_view base, const CRecvTable* table, const uint32_t offset = 0) noexcept;

	inline std::unordered_map<uint32_t, uint32_t> data{};
}

#define NETVAR(func, var, ...) \
inline std::add_lvalue_reference_t<__VA_ARGS__> func() noexcept \
{ \
	static const uint32_t offset = Netvars::data[Hash::CompileTime(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(uint32_t(this) + offset); \
}

#endif // NETVARS_HPP
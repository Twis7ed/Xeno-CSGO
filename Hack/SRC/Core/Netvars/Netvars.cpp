#include <format>

#define DONT_INCLUDE_WINDOWS
#include "../Interfaces.hpp"

void Netvars::Init() noexcept
{
	for (const CClientClass* client{ Interfaces::client->GetAllClasses() }; client; client = client->next)
		if (const CRecvTable * table{ client->table })
			Dump(client->networkName, table, 0);
}

void Netvars::Dump(const std::string_view base, const CRecvTable* table, const uint32_t offset) noexcept
{
	for (int i{}; i < table->count; ++i)
	{
		const CRecvProp* prop{ &table->props[i] };
		if (!prop)
			continue;

		if (std::isdigit(prop->name[0]))
			continue;

		if (Hash::RunTime(prop->name) == Hash::CompileTime("baseclass"))
			continue;

		if (prop->type == ESendPropType::DATATABLE && prop->table && prop->table->name[0] == 'D')
			Dump(base, prop->table, offset + prop->offset);

		data[Hash::RunTime(std::format("{}->{}", base, prop->name).c_str())] = offset + prop->offset;
	}
}
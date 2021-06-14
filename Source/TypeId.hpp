#pragma once

#include <cstdint>

inline std::uint32_t GenerateTypeId()
{
	static std::uint32_t id = 0;
	return id++;
}

template<typename>
class Type final
{
public:
	static std::uint32_t Id()
	{
		static std::uint32_t typeId = GenerateTypeId();
		return typeId;
	}
};
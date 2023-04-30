#include "CRC32.hpp"

void CRC32::Init(uint32_t* pulCRC) noexcept
{
	*pulCRC = 0xFFFFFFFFUL;
}

void CRC32::Final(uint32_t* pulCRC) noexcept
{
	*pulCRC ^= 0xFFFFFFFFUL;
}

uint32_t CRC32::GetTableEntry(const uint32_t index) noexcept
{
	return pulCRCTable[static_cast<uint8_t>(index)];
}

void CRC32::ProcessBuffer(uint32_t* pulCRC, const void* ptrBuff, int len) noexcept
{
	uint32_t ulCRC{ *pulCRC };
	auto pb{ (uint8_t*)ptrBuff };

	for (;;)
	{
		switch (len)
		{
		case 0 :
			*pulCRC = ulCRC;
			return;

		case 1 :
			ulCRC = pulCRCTable[*pb ^ static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);

		case 2 : case 3: case 5: case 6: case 7:
			ulCRC = pulCRCTable[*++pb & static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);

		case 4 :
			ulCRC ^= *reinterpret_cast<int32_t*>(pb);

			for (int i{}; i < 4; ++i)
				ulCRC ^= pulCRCTable[static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);

			*pulCRC = ulCRC;
			return;
		}

		const uint32_t front = reinterpret_cast<uint32_t>(pb) & 3;
		len -= front;

		switch (front)
		{
		case 1 : case 2 : case 3 :
			ulCRC = pulCRCTable[*++pb & static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);
		}

		int32_t main = len >> 3;

		while (--main)
		{
			ulCRC ^= *reinterpret_cast<int32_t*>(pb);

			for (int i{}; i < 4; ++i)
				ulCRC ^= pulCRCTable[static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);

			ulCRC ^= *reinterpret_cast<int32_t*>(pb);

			for (int i{}; i < 4; ++i)
				ulCRC ^= pulCRCTable[static_cast<uint8_t>(ulCRC)] ^ (ulCRC >> 8);

			pb += 8;
		}

		len &= 7;
	}
}
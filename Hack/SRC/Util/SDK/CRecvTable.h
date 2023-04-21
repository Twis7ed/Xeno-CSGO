#ifndef CRECVTABLE_H
#define CRECVTABLE_H
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>

enum class ESendPropType : int32_t
{
	INT = 0,
	FLOAT,
	VECTOR,
	VECTOR2D,
	STRING,
	ARRAY,
	DATATABLE,
	INT64,
	SENDPROPTYPEMAX
};

class CDataVariant
{
	union
	{
		float Float;
		int32_t Int;
		char* String;
		void* Data;
		float Vector[3];
		int64_t Int64;
	};

	ESendPropType type;
};

class CRecvProp;
class CRecvProxyData
{
public:
	CRecvProp* prop;
	CDataVariant value;
	int32_t element;
	int32_t objectID;
};

class CRecvTable
{
public:
	CRecvProp* props;
	int32_t count;
	void* decoder;
	char* name;
	bool isInitialized;
	bool inMainList;
};

class CRecvProp
{
public:
	char* name;
	ESendPropType type;
	int32_t flags;
	int32_t stringBufferSize;
	bool isInsideArray;
	const void* extraData;
	CRecvProp* prop;
	void* arrayLengthProxyFn;
	void* proxyFn;
	void* dataTableProxyFn;
	CRecvTable* table;
	unsigned int offset;
	int32_t stride;
	int32_t element;
	const char* parentPropName;
};

#endif // CRECVTABLE_H
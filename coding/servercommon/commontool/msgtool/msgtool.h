#ifndef __MSG_TOOL_H__
#define __MSG_TOOL_H__

#include "commontool/commontool.h"
#include "basedef.h"

#include<algorithm>

namespace CommonTool 
{
namespace MsgTool
{
/*
	��С�˵�һЩ���ߺ���(big endian and little endian)
*/

// ��ǰ������Ƿ��ǵ��ֽڴ洢
bool isLittleEndian();

/*
	Ŀǰֻ֧�ֵ��ֽڴ洢�ķ���������,�ߵ��ֽ��ֽڴ洢����ת��
*/
// ���ֽ� -> ���ֽ� ��Ŀǰֻ֧�� ���ֽں����ֽڡ�
template<class InputNumType, class ByteArrayType>
bool littleEndian2Big(InputNumType num, ByteArrayType& outByte)
{
	int len = getArraySize(outByte);

	if (sizeof(outByte[0]) != sizeof(byte))
	{
		return false;
	}
	if (len != sizeof(InputNumType))
	{
		return false;
	}

	if(!isLittleEndian()) // ���ϵͳ�Ǵ�˴洢,����ת��
	{
		byte* arr = (byte*)&num;
		memmove(outByte, arr, len);
		return true;
	}

	if (len == sizeof(ushort))
	{
		outByte[0] = (num >> 8) & 0xffff;
		outByte[1] = (num) & 0xffff;
	}
	else if (len == sizeof(uint))
	{
		outByte[0] = (num >> 24) & 0xFFFFFFFF;
		outByte[1] = (num >> 16) & 0xFFFFFFFF;
		outByte[2] = (num >> 8) & 0xFFFFFFFF;
		outByte[3] = (num) & 0xFFFFFFFF;
	}

	return true;
}

// ���ֽ� -> ���ֽ� ��Ŀǰֻ֧�� ���ֽں����ֽڡ�
template<class ByteArrayType, class OutputNumType>
bool bigEndian2Little(ByteArrayType& inputBytes, OutputNumType& outNum)
{
	int len = getArraySize(inputBytes);

	if(sizeof(inputBytes[0]) != sizeof(byte))
	{
		return false;
	}
	if(len != sizeof(OutputNumType))
	{
		return false;
	}

	if(!isLittleEndian()) // ���ϵͳ�Ǵ�˴洢,����ת��
	{
		outNum = *(OutputNumType*)inputBytes;
		return true;
	}

	if(len == sizeof(ushort))
	{
		ushort tmp = *(ushort*)inputBytes;
		outNum = ((tmp >> 8) &0x00FF) | 
				((tmp << 8) & 0xFF00);
	}
	else if(len == sizeof(uint))
	{
		uint tmp = *(uint*)inputBytes;
		outNum = (tmp >> 24 & 0x000000FF) | 
				((tmp >> 8) & 0x0000FF00) | 
				((tmp << 8) & 0x00FF0000) | 
				((tmp << 24) & 0xFF000000);
	}
	return true;
}

}}

#endif // !__MSG_TOOL_H__

#ifndef __MSG_TOOL_H__
#define __MSG_TOOL_H__

#include "commontool/commontool.h"

namespace CommonTool 
{
namespace MsgTool
{
/*
	��С�˵�һЩ���ߺ���(big endian and little endian)
*/

// ��ǰ������Ƿ��ǵ��ֽڴ洢
bool isLittleEndian();

// ���ֽ� -> ���ֽ� ��Ŀǰֻ֧�� ���ֽں����ֽڡ�
template<class InputNumType, class ByteArrayType>
bool Little2Big(InputNumType num, ByteArrayType& outByte)
{
	int len = getArraySize(outByte);
	if (sizeof(outByte[0]) != 1)
	{
		return false;
	}
	if (len != sizeof(InputNumType))
	{
		return false;
	}

	if (!isLittleEndian()) // ���ǵ��ֽڴ洢�ģ��Ͳ���ת��
	{
		char* arr = (char*)&num;
		memmove(outByte, arr, len);
		return true;
	}

	if (len == 2)
	{
		outByte[0] = (num >> 8) & 0xffff;
		outByte[1] = (num) & 0xffff;
	}
	else if (len == 4)
	{
		outByte[0] = (num >> 24) & 0xffffffff;
		outByte[1] = (num >> 16) & 0xffffffff;
		outByte[2] = (num >> 8) & 0xffffffff;
		outByte[3] = (num) & 0xffffffff;
	}

	return true;
}

}}

#endif // !__MSG_TOOL_H__

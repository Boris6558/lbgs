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

	if(!isLittleEndian()) // ���ǵ��ֽڴ洢�ģ��Ͳ���ת��
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
		outByte[0] = (num >> 24) & 0xffffffff;
		outByte[1] = (num >> 16) & 0xffffffff;
		outByte[2] = (num >> 8) & 0xffffffff;
		outByte[3] = (num) & 0xffffffff;
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

	if(isLittleEndian()) // ���Ǹ��ֽڴ洢�ģ��Ͳ���ת��
	{
		outNum = *(OutputNumType*)inputBytes;
		return true;
	}

	DEFINE_BYTE_ARRAY(byteArray, sizeof(OutputNumType));
	memmove(byteArray, inputBytes, sizeof(OutputNumType));
	std::reverse(byteArray, byteArray + sizeof(OutputNumType) - 1);
	outNum = *(OutputNumType*)byteArray;

	return true;
}

}}

#endif // !__MSG_TOOL_H__

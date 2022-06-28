#include "util.h"

//bool IsStrUTF8(const char * pBuffer, int size)
//{
//	if (size < 0)
//	{
//		return false;
//	}
//
//	bool IsUTF8 = true;
//	unsigned char* start = (unsigned char*)pBuffer;
//	unsigned char* end = (unsigned char*)pBuffer + size;
//	if (NULL == start ||
//		NULL == end)
//	{
//		return false;
//	}
//	while (start < end)
//	{
//		if (*start < 0x80) // ch:(10000000): 值小于0x80的为ASCII字符 | en:(10000000): if the value is smaller than 0x80, it is the ASCII character
//		{
//			start++;
//		}
//		else if (*start < (0xC0)) // ch:(11000000): 值介于0x80与0xC0之间的为无效UTF-8字符 | en:(11000000): if the value is between 0x80 and 0xC0, it is the invalid UTF-8 character
//		{
//			IsUTF8 = false;
//			break;
//		}
//		else if (*start < (0xE0)) // ch:(11100000): 此范围内为2字节UTF-8字符  | en: (11100000): if the value is between 0xc0 and 0xE0, it is the 2-byte UTF-8 character
//		{
//			if (start >= end - 1)
//			{
//				break;
//			}
//
//			if ((start[1] & (0xC0)) != 0x80)
//			{
//				IsUTF8 = false;
//				break;
//			}
//
//			start += 2;
//		}
//		else if (*start < (0xF0)) // ch:(11110000): 此范围内为3字节UTF-8字符 | en: (11110000): if the value is between 0xE0 and 0xF0, it is the 3-byte UTF-8 character 
//		{
//			if (start >= end - 2)
//			{
//				break;
//			}
//
//			if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
//			{
//				IsUTF8 = false;
//				break;
//			}
//
//			start += 3;
//		}
//		else
//		{
//			IsUTF8 = false;
//			break;
//		}
//	}
//
//	return IsUTF8;
//}

//bool Char2Wchar(const char * pStr, wchar_t * pOutWStr, int nOutStrSize)
//{
//	if (!pStr || !pOutWStr)
//	{
//		return false;
//	}
//
//	bool bIsUTF = IsStrUTF8(pStr, strlen(pStr));
//	UINT nChgType = bIsUTF ? CP_UTF8 : CP_ACP;
//
//	int iLen = MultiByteToWideChar(nChgType, 0, (LPCSTR)pStr, -1, NULL, 0);
//
//	memset(pOutWStr, 0, sizeof(wchar_t) * nOutStrSize);
//
//	if (iLen >= nOutStrSize)
//	{
//		iLen = nOutStrSize - 1;
//	}
//
//	MultiByteToWideChar(nChgType, 0, (LPCSTR)pStr, -1, pOutWStr, iLen);
//
//	pOutWStr[iLen] = 0;
//
//	return true;
//}
//
//bool Wchar2char(wchar_t * pOutWStr, char * pStr)
//{
//	if (!pStr || !pOutWStr)
//	{
//		return false;
//	}
//
//	int nLen = WideCharToMultiByte(CP_ACP, 0, pOutWStr, wcslen(pOutWStr), NULL, 0, NULL, NULL);
//
//	WideCharToMultiByte(CP_ACP, 0, pOutWStr, wcslen(pOutWStr), pStr, nLen, NULL, NULL);
//
//	pStr[nLen] = '\0';
//
//	return true;
//}

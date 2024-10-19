#pragma once
#include "Core/DsTypes.h"

#define STRING_STACK_THRESHOLD 24

namespace Ds
{
	class String
	{
	private:
		char m_StrS[STRING_STACK_THRESHOLD];
		char* m_StrH = nullptr;
		size_t m_Capacity = 0;
		size_t m_Length = 0;
		bool bUseHeap = false;

		void WriteInMemory(const char* str);

	public:
		String();
		String(const char* InStr);
		~String();
		static int GetStringLength(const char* str);
		void Printf();
	};

	

	String::String()
	{}

	inline String::String(const char* InStr)
	{
		if (!InStr)
		{
			return;
		}

		m_Length = String::GetStringLength(InStr);

		if (m_Length > STRING_STACK_THRESHOLD-1)
		{
			bUseHeap = true;
		}

		if (bUseHeap)
		{
			m_StrH = new char[m_Length + 1];
			for (size_t i = 0; i < m_Length; i++)
			{
				m_StrH[i] = InStr[i];
			}
			m_StrH[m_Length] = '\0';
		}
		else
		{
			for (size_t i = 0; i < m_Length; i++)
			{
				m_StrS[i] = InStr[i];
			}
			m_StrS[m_Length] = '\0';
			m_Capacity = 24;
		}
	}

	inline String::~String()
	{
		delete[] m_StrH;
		m_StrH = nullptr;
	}

	inline int String::GetStringLength(const char* str)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			++i;
		}
		return i;
	}

	inline void String::Printf()
	{
		if (bUseHeap)
		{
			std::cout << m_StrH << std::endl;
			std::cout << "Heap" << std::endl;

		}
		else 
		{
			std::cout << m_StrS << std::endl;
			std::cout << "Stack" << std::endl;
		}
	}

	inline void String::WriteInMemory(const char* str)
	{
	}
}
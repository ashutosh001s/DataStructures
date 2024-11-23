#pragma once
#include "Core/DsTypes.h"
#include "iostream"
#include "array"

using namespace std;

#define STRING_STACK_THRESHOLD 24
#define END_OF_STRING '\0'

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
		String() = default;
		String(const char* InStr);
		~String();
		char& GetChar(int index);
		void SetChar(int index, char c);
		static int GetStringLength(const char* str);
		void ToLower();
		void ToUpper();
		void Capatalize();
		void ChangeCase();
		int GetWordCount();

		void Printf();
		float GetSizeInMB() { return (m_Length / 1024.f)/1024.f; };
		std::array<int,3> GetCharAndVowelsAndConsonentsCount();

		friend ostream& operator << (ostream& os, const String& str);
		
	};

	ostream& operator << (ostream& os, const String& str)
	{

		if (str.bUseHeap) // why this is undefined
		{
			os << str.m_StrH;
		}
		else
		{
			os << str.m_StrS;
		}

		return os;
	}

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

	inline char& String::GetChar(int index)
	{
		if (bUseHeap)
		{
			return m_StrH[index];
		}
		return m_StrS[index];
	}

	inline void String::SetChar(int index, char c)
	{
		if (bUseHeap)
		{
			m_StrH[index] = c;
		}
		else
		{
			m_StrS[index] = c;
		}
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

	inline void String::ToLower()
	{
		int i = 0;
		while (GetChar(i) != END_OF_STRING)
		{
			if ((int)GetChar(i) >= 65 && (int)GetChar(i) <= 90)
			{
				SetChar(i, ((int)GetChar(i) + 32));
			}
			++i;
		}
	}

	inline void String::ToUpper()
	{
		int i = 0;
		while (GetChar(i) != END_OF_STRING)
		{
			if ((int)GetChar(i) >= 97 && (int)GetChar(i) <= 122)
			{
				SetChar(i, ((int)GetChar(i) - 32));
			}
			++i;
		}
	}

	inline void String::Capatalize()
	{
		int i = 0;

		if ((int)GetChar(0) >= 97 && (int)GetChar(0) <= 122)
		{
			SetChar(0, ((int)GetChar(0) - 32));
		}
		

		while (GetChar(i) != END_OF_STRING)
		{
			if ((int)GetChar(i) == 32)
			{
				if ((int)GetChar(i+1) >= 97 && (int)GetChar(i+1) <= 122)
				{
					SetChar(i+1, ((int)GetChar(i+1) - 32));
				}
				++i;
			}
			++i;
		}
	}

	inline void String::ChangeCase()
	{
		int i = 0;
		while (GetChar(i) != END_OF_STRING)
		{
			if ((int)GetChar(i) >= 65 && (int)GetChar(i) <= 90)  // Uppercase
			{
				SetChar(i, ((int)GetChar(i) + 32));
			}
			else if ((int)GetChar(i) >= 97 && (int)GetChar(i) <= 122)  // Lowercase
			{
				SetChar(i, ((int)GetChar(i) - 32));
			}
			++i;
		}
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

	/**
	 * Returns Number of Alphabet Characters, Vowels and Consonents in stored string .
	 *
	 * @param void.
	 *
	 * @return index 0  is char , index 1 is Vowels and 2 is Consonents any other index are invalid.
	 */
	inline std::array<int, 3> String::GetCharAndVowelsAndConsonentsCount()
	{
		int i = 0;
		int Consonents = 0, Vowels = 0, Characters = 0;
		while (GetChar(i) != END_OF_STRING)
		{
			if (((int)GetChar(i) >= 97 && (int)GetChar(i) <= 122) || (int)GetChar(i) >= 65 && (int)GetChar(i) <= 90)
			{
				if (GetChar(i) == 'a' || GetChar(i) == 'e' || GetChar(i) == 'i' || GetChar(i) == 'o' || GetChar(i) == 'u' || GetChar(i) == 'A' || GetChar(i) == 'E' || GetChar(i) == 'I' || GetChar(i) == 'O' || GetChar(i) == 'U')
				{
					++Vowels;
				}
				++Characters;
			}
			++i;
		}
		Consonents = Characters - Vowels;

		return { Characters, Vowels, Consonents };
	}

	inline int String::GetWordCount()
	{
		int i = 0;
		int Word = 0;

		if (m_Length == 0)
		{
			return 0;
		}

		while (GetChar(i) != END_OF_STRING)
		{
			if (GetChar(i) == ' ' &&  GetChar(i - 1) != ' ')
			{
				++Word;
			}
			++i;
		}
		Word += 1;
		return Word;
	}

	inline void String::WriteInMemory(const char* str)
	{
	}
}
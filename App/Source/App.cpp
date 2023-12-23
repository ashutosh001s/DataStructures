#include "iostream"
#include "string"
#include "Core/Array.h"

using namespace DS;

//Type definations
using Integers = Array<int>;
using Floats = Array<float>;
using Characters = Array<char>;
using Strings = Array<std::string>;

#define Log(msg) std::cout << msg <<"\n"
#define Print(arr) \
for(size_t i = 0; i < arr.GetLength(); i++)\
{\
	Log(arr[i]); \
} \

int main()
{
	{
		Floats arr = { 24,6.89454521f,10,11 };
		Log((arr.IsSorted() == true ? "True" : "False"));

		arr.BubbleSort();
		Log((arr.IsSorted() == true ? "True" : "False"));

		Print(arr);
	}

	return 0;
}
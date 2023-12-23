#include "iostream"
#include "string"
#include "Core/Array.h"

#define Log(msg) std::cout << msg <<"\n"
#define Print(arr) \
for(size_t i = 0; i < arr.GetLength(); i++)\
{\
	Log(arr[static_cast<int>(i)]); \
} \


int main()
{
	{
		DS::Array<float> arr = { 24,6.89454521f,10,11 };
		Log((arr.IsSorted() == true ? "True" : "False"));

		arr.BubbleSort();
		Log((arr.IsSorted() == true ? "True" : "False"));

		Print(arr);
	}

	return 0;
}
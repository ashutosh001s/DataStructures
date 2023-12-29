#include "iostream"
#include "Core/DsTypes.h"
#include "chrono"

using namespace Ds;

int main()
{
	{
		Int arr = {2,4,6,8,10,12};
		Int arr2(2);

		arr2 = arr;

		arr[0] = 3;

		Print(arr2)
		Print(arr)
		
		//FillList(arr,100000000)
		//BENCHMARK_START()
		////Log("Found at : ",arr.LinearSearch(85000));
		//Log("Found at : ",arr.BinarySearch(85000));
		//BENCHMARK_END()
	}

	return 0;
}
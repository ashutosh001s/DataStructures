#include "iostream"
#include "Core/Array.h"
#include "Core/Set.h"
#include "Core/HelperMacros.h"

using namespace Ds;

int main()
{
    {
        Set<int> even = {0};

        BENCHMARK_START()
        FillSet(even, 100000);
        BENCHMARK_END()

        PrintSet(even)
        /*Int arr = {2,4,6,8,10,12};
        Int arr2(2);

        arr2 = arr;

        arr[0] = 3;

        Print(arr2)
        Print(arr)*/

        // FillList(arr,100000000)
        // BENCHMARK_START()
        ////Log("Found at : ",arr.LinearSearch(85000));
        // Log("Found at : ",arr.BinarySearch(85000));
        // BENCHMARK_END()
    }

    return 0;
}
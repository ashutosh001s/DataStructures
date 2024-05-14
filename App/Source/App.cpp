#include "iostream"
#include "chrono"
#include "Core/Set.h"

using namespace Ds;

#define PrintSet(set)                         \
    std::cout << "( ";                        \
    for (int i = 0; i < set.GetLength(); i++) \
    {                                         \
        std::cout << set[i] << " ";           \
    }                                         \
    std::cout << ")\n";
int main()
{
    {
        Set<int> even = {2, 2, 2, 4, 6, 8, 8, 10, 12};
        Set<int> other = {2,3,4,5,7,8,9,};

        even.Difference(other, true);
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
#include "iostream"
#include "Core/Array.h"
#include "Core/Set.h"
#include "Core/HelperMacros.h"

using namespace Ds;

#define O(...)

#define NewHashTable(type, size) Array<type>(size, 0); 

int FindSingleMissingNaturalNumber(Array<int>* arr);
void FindMissingElements(Array<int>* arr);
void MissingElementUsingHashTable(Array<int>* arr);
void DuplicatesInSortedArray(Array<int>* arr);
void FindDuplicatesInSortedArrayUsingHashTable(Array<int>* arr);
void FindingDuplicatesInUnsortedArray(Array<int>* arr);
void FindingDuplicatesInUnsortedArrayUsingHashTable(Array<int>* arr);
void FindPairOfElementsWithSumK(Array<int>* arr, int Sum);

int main()
{
    {
        /*Set<int> even = { 0 };

        BENCHMARK_START()
            FillSet(even, 10000);
        BENCHMARK_END()

            PrintSet(even)*/

         // Array<int> arr = {6,7,8,9,11,12,15,16,17,18,20, 1};
         /* int missing = FindSingleMissingNaturalNumber(&arr);
          std::cout << "Missing element is : " << missing << "\n";*/
          //MissingElementUsingHashTable(&arr);

          Array<int> arr = {8,3,6,4,6,5,6,8,2,7};
          FindPairOfElementsWithSumK(&arr,10);

            // FillList(arr,100000000)
            // BENCHMARK_START()
            ////Log("Found at : ",arr.LinearSearch(85000));
            // Log("Found at : ",arr.BinarySearch(85000));
            // BENCHMARK_END()
    }

    return 0;
}

int FindSingleMissingNaturalNumber(Array<int> * arr)
{
    int last = arr->Get(arr->GetLength()-1);

    int sum = (last * (last + 1)) / 2;

    int sum2 = 0;

    for (size_t i = 0; i < arr->GetLength(); ++i)
    {
        sum2 += arr->Get(i);
    }

    return sum - sum2;
}

void FindMissingElements(Array<int>* arr)
{
    
    int diff = arr->Get(0);
    for (int i = 0; i < arr->GetLength(); i++)
    {
        int currDiff = arr->Get(i) - i;
        if (currDiff != diff)
        {
            while (currDiff != diff)
            {
                std::cout << "Missing Element : " << diff + i << std::endl;
                ++diff;
            }
        } 
    }
}

void MissingElementUsingHashTable(Array<int>* arr)
{
    Array<int> arrH(arr->Max()+1, 0);


    for (size_t i = 0; i < arr->GetLength(); i++)
    {
        arrH.Set(1,arr->Get(i));
    }

    for (size_t i = arr->Min(); i < arrH.GetLength(); i++)
    {
        if (arrH[i] == 0) {
            std::cout << "Missing Element : " << i << std::endl;
        }
    }
}

void DuplicatesInSortedArray(Array<int>* arr)
{
    int i = 0, j = 0, k;
    while (i < arr->GetLength() - 1)
    {
        if (arr->Get(i) == arr->Get(i+1))
        {
            j = i;
            k = 0;
            std::cout << "Duplicate of " << arr->Get(i);
            while (arr->Get(j) == arr->Get(j + 1))
            {
                ++k;
                ++j;
            }
            std::cout << " " << k << " Times" << std::endl;
            i = j + 1;
        }
        ++i;
    }
}

void FindDuplicatesInSortedArrayUsingHashTable(Array<int>* arr) O(n)
{
    auto H = NewHashTable(int,arr->Max()+1)

    for (size_t i = 0; i < arr->GetLength()-1; i++)
    {
        if (arr->Get(i) == arr->Get(i+1))
        {
            H[arr->Get(i)]++;
        }
    }

    for (size_t i = arr->Min(); i < H.GetLength(); i++)
    {
        if (H[i] > 0)
        {
            std::cout << "Duplicate of " << i << " " << H[i] << " Times" << "\n";
        }
    }
}

void FindingDuplicatesInUnsortedArray(Array<int>* arr) O(n sq)
{
    for (int i = 0; i < arr->GetLength(); i++)
    {
        int count = 0;

        if (arr->Get(i) != -1)
        {
            for (int j = i+1; j < arr->GetLength(); j++)
            {
                if (arr->Get(i) == arr->Get(j))
                {
                    ++count;
                    arr->Set(-1, j);
                }
            }
            std::cout << "Duplicate of " << arr->Get(i) << " " << count << std::endl;
        }
    }
}

void FindingDuplicatesInUnsortedArrayUsingHashTable(Array<int>* arr) O(n)
{
    Array<int> H = NewHashTable(int, arr->Max()+1);

    for (int i = 0; i < arr->GetLength(); i++)
    {
        H[arr->Get(i)]++;
    }

    for (size_t i = 0; i < H.GetLength(); i++)
    {
        if (H[i] > 0) 
        {
            std::cout << i << " count : " << H[i] << std::endl;
        }
    }
}

void FindPairOfElementsWithSumK(Array<int>* arr, int Sum)
{
    for (int i = 0; i < arr->GetLength(); ++i)
    {
        for (int j = i + 1; arr->GetLength(); ++j)
        {
            if ((arr->Get(i) + arr->Get(j)) == Sum)
            {
                std::cout << "Pairs : " << arr->Get(i) << " and " << arr->Get(j) << std::endl;
            }

        }
    }
}
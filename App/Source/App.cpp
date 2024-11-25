#include "iostream"
#include "Core/Array.h"
#include "Core/Set.h"
#include "Core/HelperMacros.h"
#include "Core/String.h"
#include "Core/String.h"


#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

std::string readFile(const std::string& filename);

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
void FindPairOfElementsWithSumKArrayUsingHashTable(Array<int>* arr, int Sum);
void FindPairOfElementsWithSumKInSortedArray(Array<int>* arr, int Sum);
void FindMinAndMax(Array<int>* arr);

int main()
{
    {
        Array<int> arr = { 0 };
        FillList(arr,0, 1000, i); // fill arr from 0 to 1000 
        std::cout << "\nGet at " << arr.Get(692)<<"\n"; // expected 691
        std::cout << "\nFound at " << arr.ParallelLinearSearch(692)<<"\n"; //result is 693
        //Todo 
        /*Set<int> even = { 0 };

        BENCHMARK_START()
            FillSet(even, 10000);
        BENCHMARK_END()

            PrintSet(even)*/

         // Array<int> arr = {6,7,8,9,11,12,15,16,17,18,20, 1};
         /* int missing = FindSingleMissingNaturalNumber(&arr);
          std::cout << "Missing element is : " << missing << "\n";*/
          //MissingElementUsingHashTable(&arr);

         /* Array<int> arr = {5,8,3,9,6,2,10,7,-1,4};
          FindMinAndMax(&arr);*/

        /*std::string msg;
        std::cout << "What is your message: ";
        std::getline(std::cin, msg);*/

        /*std::string content;

        try {
            content = readFile("../Core/Source/Core/Data.txt");
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }


        Ds::String str = content.c_str();
        auto result = str.GetCharAndVowelsAndConsonentsCount();


        std::cout << "Characters Count : " << result[0] << "\n"  << "Vowels Count : " << result[1] << "\n" << "Consonents Count : " << result[2] << "\n" << "Words : " << str.GetWordCount() << std::endl;
       // std::cout << "Size : " << str.GetSizeInMB() <<"MB";

        //str.Printf();

        std::cout << str << std::endl;*/

            // FillList(arr,100000000)
            // BENCHMARK_START()
            ////Log("Found at : ",arr.LinearSearch(85000));
            // Log("Found at : ",arr.BinarySearch(85000));
            // BENCHMARK_END()
    }

    return 0;
}



std::string readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
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

O(n) void FindDuplicatesInSortedArrayUsingHashTable(Array<int>* arr) 
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

O(n sq) void FindingDuplicatesInUnsortedArray(Array<int>* arr)
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

O(n) void FindingDuplicatesInUnsortedArrayUsingHashTable(Array<int>* arr)
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
        for (int j = (i + 1);j < arr->GetLength(); ++j)
        {
            if ((arr->Get(i) + arr->Get(j)) == Sum)
            {
                std::cout << "Pairs : " << arr->Get(i) << " and " << arr->Get(j) << std::endl;
            }

        }
    }
}

void FindPairOfElementsWithSumKArrayUsingHashTable(Array<int>* arr, int Sum)
{
    Array<int> H = NewHashTable(int, arr->Max() + 1);
    
    for (int i = 0; i < arr->GetLength(); ++i)
    {
        auto reqNum = Sum - (*arr)[i];
        if (H.Get(reqNum) > 0)
        {
            std::cout << "Pairs : " << (*arr)[i] << " and " << reqNum << std::endl;
        }
        else
        {
            ++H[(*arr)[i]];
        }
    }
}

void FindPairOfElementsWithSumKInSortedArray(Array<int>* arr, int Sum)
{
    int i = 0, j = arr->GetLength()-1;

    while ((*arr)[i] != (*arr)[j])
    {
        
        if (((*arr)[i] + (*arr)[j]) == Sum)
        {
            std::cout << "Pairs : " << (*arr)[i] << " and " << (*arr)[j] << std::endl;
            ++i;
            --j;
        }
        else if (((*arr)[i] + (*arr)[j]) > Sum)
        {
            --j;
        }
        else if (((*arr)[i] + (*arr)[j]) < Sum)
        {
            ++i;
        }
    }
}

void FindMinAndMax(Array<int>* arr)
{
    int Min = (*arr)[0], Max = (*arr)[0];

    for (size_t i = 0; i < arr->GetLength(); i++)
    {
        if ((*arr)[i] < Min)
        {
            Min = (*arr)[i];
        }
        else if ((*arr)[i] > Max)
        {
            Max = (*arr)[i];
        }
    }

    std::cout << "Min : " << Min << " Max : " << Max << std::endl;
}

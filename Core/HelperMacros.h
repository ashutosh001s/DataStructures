#pragma once
#include "chrono"

#ifdef INCLUDE_ARRAY
#include "Array.h"
#endif

#ifdef INCLUDE_SET
#include "Set.h"
#endif

#define Log(prefix, msg) std::cout << (prefix) << (msg) << "\n"
#define Print(arr)                                 \
	for (size_t i = 0; i < (arr).GetLength(); i++) \
	{                                              \
		Log("", (arr)[static_cast<int>(i)]);       \
	}

#define PrintSet(set)                         \
    std::cout << "( ";                        \
    for (int i = 0; i < set.GetLength(); i++) \
    {                                         \
        std::cout << set[i] << " ";           \
    }                                         \
    std::cout << ")\n";

#define FillList(arr, count)          \
	for (int i = 0; i < (count); i++) \
	{                                 \
		(arr).Append(i + i);          \
	}

#define FillSet(set, count)          \
	for (int i = 0; i < (count); i++) \
	{                                 \
		(set).Append(i + i);          \
	}

#define FillVector(arr, count)        \
	for (int i = 0; i < (count); i++) \
	{                                 \
		(arr).push_back(i + i);       \
	}

#define BENCHMARK_START() const auto start = std::chrono::high_resolution_clock::now();

#define BENCHMARK_END()                                                     \
	const auto end = std::chrono::high_resolution_clock::now();             \
	const std::chrono::duration<double, std::milli> duration = end - start; \
	std::cout << duration.count() << "ms\n";
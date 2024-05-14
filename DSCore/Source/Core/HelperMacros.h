#pragma once
#include "Set.h"
#include "Array.h"

#define Log(prefix, msg) std::cout << (prefix) << (msg) << "\n"
#define Print(arr)                                 \
	for (size_t i = 0; i < (arr).GetLength(); i++) \
	{                                              \
		Log("", (arr)[static_cast<int>(i)]);       \
	}

#define FillList(arr, count)          \
	for (int i = 0; i < (count); i++) \
	{                                 \
		(arr).Append(i + i);          \
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
	std::cout << duration.count() << "ms\n";                                \
	\
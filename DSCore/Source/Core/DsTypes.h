//
// Created by ashut on 13-05-2024.
//

#ifndef CLDS_DSTYPES_H
#define CLDS_DSTYPES_H

enum
{
    Found = 1,
    NotFound = -1
};

enum class Operation
{
    LESS_THAN,
    GREATER_THAN,
    EQUAL_TO
};

template <typename T>
static T Compare(const T &a, const T &b, Operation op)
{
    switch (op)
    {
    case Operation::LESS_THAN:
        return a < b ? a : b;
    case Operation::GREATER_THAN:
        return a > b ? a : b;
    case Operation::EQUAL_TO:
        return a == b && a;
    default:
        std::cerr << "Invalid operation!\n"; // Handle invalid input
        return T();                          // Return a default value or throw an exception
    }
}

#endif // CLDS_DSTYPES_H

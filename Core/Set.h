#pragma once
#ifdef INCLUDE_ARRAY
#include "Array.h"
#endif
#include "DsTypes.h"

#define CreateArray(size) new Ds::Array<T>(static_cast<int>(size));

#define FreeArray(array) \
    m_array->~Array();   \
    m_array = temp;      \
    temp = nullptr;

#define CheckOrReturn(condition) \
    if (!condition)              \
        return;

namespace Ds
{
    template <typename T>
    class Set
    {
    private:
        Ds::Array<T> *m_array;

    public:
        Set() = delete;
        Set(std::initializer_list<T> list);
        T &operator[](int index);
        ~Set();

    public:
        [[nodiscard]] size_t GetLength() const;
        void Append(T x);
        void Union(const Set &otherSet, bool bSorted = false);
        void Difference(const Set &otherSet, bool bSorted = false);
        void Intersection(const Set &otherSet, bool bSorted = false);
        int SetMember(T x, bool bSorted) const;
    };

    static int count = 0;
    template <typename T>
    void Set<T>::Append(T x)
    {
        std::cout << ++count << " Searching...\n";
        if (m_array->LinearSearch(x) == -1)
        {
            std::cout << count << "Appending...\n";
            m_array->Append(x);
        }
    }

    template <typename T>
    Set<T>::Set(std::initializer_list<T> list)
    {
        m_array = new Ds::Array<T>(static_cast<int>(list.size()));
        for (auto arg : list)
        {
            if (m_array->LinearSearch(arg) == -1)
            {
                m_array->Append(arg);
            }
        }
    }

    /**
     * Returns the element at the specified index.
     *
     * @param index The index of the element to return.
     *
     * @return The element at the specified index.
     */
    template <typename T>
    T &Set<T>::operator[](int index)
    {
        // TODO: insert return statement here
        return m_array->Get(index);
    }

    template <typename T>
    Set<T>::~Set()
    {

        m_array = nullptr;
    }

    /**
     * Returns the length of the set.
     *
     * @return The length of the set.
     */
    template <typename T>
    size_t Set<T>::GetLength() const
    {
        return m_array->GetLength();
    }

    /**
     * Computes the union of two sets.
     *
     * @param otherSet The set to compute the union with.
     * @param bSorted Whether the sets are sorted or not.
     *
     * @throws None
     */
    template <typename T>
    inline void Set<T>::Union(const Set &otherSet, const bool bSorted)
    {
        CheckOrReturn(m_array->IsValid())

            auto *temp = CreateArray(m_array->GetLength() + otherSet.GetLength())

                if (bSorted)
        {
            // TODO: Implement Union for sorted set
            int i = 0;
            int j = 0;
            auto arr = otherSet.m_array;

            while (i < GetLength() && j < arr->GetLength())
            {

                if (m_array->Get(i) < arr->Get(j))
                {
                    temp->Append(m_array->Get(i));
                    ++i;
                }
                else if (m_array->Get(i) > arr->Get(j))
                {
                    temp->Append(arr->Get(j));
                    ++j;
                }
                else
                {
                    temp->Append(m_array->Get(i));
                    ++i;
                    ++j;
                }
            }
            while (i < GetLength())
            {
                temp->Append(m_array->Get(i));
                ++i;
            }

            while (j < arr->GetLength())
            {
                temp->Append(arr->Get(j));
                ++j;
            }
        }
        else
        {
            for (size_t i = 0; i < m_array->GetLength(); i++)
            {
                temp->Append(m_array->Get(i));
            }

            for (size_t i = 0; i < otherSet.GetLength(); i++)
            {
                T e = otherSet.m_array->operator[](i);
                if (temp->LinearSearch(e) == NotFound)
                {
                    temp->Append(e);
                }
            }
        }

        FreeArray(m_array)
    }

    template <typename T>
    inline void Set<T>::Difference(const Set &otherSet, const bool bSorted)
    {
        CheckOrReturn(m_array->IsValid())

            auto *temp = CreateArray(m_array->GetLength() + otherSet.GetLength());

        if (bSorted)
        {
            int i = 0, j = 0;
            while (i < GetLength() && j < otherSet.GetLength())
            {
                if (m_array->Get(i) == otherSet.m_array->Get(j))
                {
                    ++i;
                    ++j;
                }
                else if (m_array->Get(i) < otherSet.m_array->Get(j))
                {
                    temp->Append(m_array->Get(i));
                    ++i;
                }
                else
                {
                    ++j;
                }
            }

            while (i < GetLength())
            {
                temp->Append(m_array->Get(i));
                ++i;
            }
            while (j < otherSet.GetLength())
            {
                temp->Append(otherSet.m_array->Get(j));
                ++j;
            }
        }
        else
        {
            for (int i = 0; i < GetLength(); ++i)
            {
                if (otherSet.m_array->LinearSearch(m_array->Get(i)) == NotFound)
                    temp->Append(m_array->Get(i));
            }
        }

        FreeArray(m_array);
    }

    template <typename T>
    inline void Set<T>::Intersection(const Set &otherSet, const bool bSorted)
    {
        CheckOrReturn(m_array->IsValid())

            auto *temp = CreateArray(m_array->GetLength() + otherSet.GetLength());

        if (bSorted)
        {
            int i = 0, j = 0;
            auto arr = otherSet.m_array;

            while (i < GetLength() && j < otherSet.GetLength())
            {
                if (m_array->Get(i) == arr->Get(j))
                {
                    temp->Append(m_array->Get(i));
                    ++i;
                    ++j;
                }
                else if (m_array->Get(i) < arr->Get(j))
                {
                    ++i;
                }
                else
                {
                    ++j;
                }
            }
        }
        else
        {
            for (int i = 0; i < GetLength(); ++i)
            {
                if (otherSet.m_array->LinearSearch(m_array->Get(i)) != NotFound)
                    temp->Append(m_array->Get(i));
            }
        }

        FreeArray(m_array);
    }

    template <typename T>
    int Set<T>::SetMember(const T x, const bool bSorted) const
    {
        if (bSorted)
        {
            return m_array->BinarySearch(x);
        }
        return m_array->LinearSearch(x);
    }

}

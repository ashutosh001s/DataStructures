#pragma once
#include "stdexcept"
#include <type_traits>
#include "initializer_list"

#define NewSize(x) ((x)+5)

namespace DS
{
	template<typename Type>
	class Array
	{
	public:
		void Append(Type x);
		void Insert(int index, Type x);
		Type Get(const int index)const;
		bool Set(const Type x, const int index);
		void Remove(int index);
		int LinearSearch(Type element);
		int BinarySearch(Type element);
		int BinarySearch(Type element, int low , int high);
		void BubbleSort();
		bool IsSorted();
		void Reverse();
		Type Max();
		Type Min();
		void LeftShift(int start);
		void RightShift(int start, bool b_resize);
		bool InsertSorted(Type x);
		inline int GetLength() const { return m_length; }
		inline int GetSize() const { return m_size; }
		


	public:
		Array() = delete;
		Array(int size);
		Array(std::initializer_list<Type> args);
		~Array();
		Type& operator[](int index);

	private:
		Type* m_arr = nullptr;
		int m_size = 0;
		int m_length = 0;
		bool m_initialized = false;

	private:
		void Resize(int size);
		void fill(std::initializer_list<Type>& args);
		void fill(const Array<Type>& from, Array<Type>& to);
		static void fill(const Type  * from, Type * to, const int length);
		inline bool ShouldResize() const{return m_length >= m_size;}
		bool is_index_valid(const int index) const;
		void reset();
		void Swap(Type& x, Type& y);
		bool AreEqual(const double a, const double b, const double epsilon = 1e-6) const;
		bool AreEqual(const float a, const float b, const float epsilon = 1e-6f) const;
	};

	template <typename Type>
	bool Array<Type>::is_index_valid(const int index) const
	{
		if (index >= 0 && index < m_size)
		{
			return true;
		}
		return false;
	}

	template <typename Type>
	void Array<Type>::reset()
	{
		if (m_arr || m_initialized)
		{
			delete [] m_arr;
			m_arr = nullptr;
			m_size = 0;
			m_length = 0;
			m_initialized = false;
		}
	}

	template <typename Type>
	Array<Type>::Array(const int size)
	{
		m_size = size;
		m_arr = new Type[m_size];
		m_length = 0;
		m_initialized = false;
	}


	template <typename Type>
	Array<Type>::Array(std::initializer_list<Type> args)
	{
		fill(args);
	}

	template <typename Type>
	Array<Type>::~Array()
	{
		if (m_arr)
		{
			delete [] m_arr;
		}
	}

	template <typename Type>
	void Array<Type>::fill(std::initializer_list<Type>& args)
	{
		m_size = static_cast<int>(args.size());
		m_arr = new Type[m_size];

		if (m_arr)
		{
			for (auto arg : args)
			{
				m_arr[m_length] = arg;
				++m_length;
			}

			m_initialized = true;
		}
	}

	template <typename Type>
	void Array<Type>::fill(const Array<Type>& from, Array<Type>& to)
	{
		to.reset();
		to.m_size = from.GetSize();
		to.m_arr = new Type[to.m_size];

		fill(from.m_arr, to.m_arr, from.GetLength());

		to.m_length = from.m_length;
		to.m_initialized = true;
	}

	template <typename Type>
	void Array<Type>::fill(const Type* from, Type* to, const int length)
	{
		for (size_t i = 0; i < length; i++)
		{
			to[i] = from[i];
		}
	}

	template <typename Type>
	Type& Array<Type>::operator[](int index)
	{
		return m_arr[index];
	}

	template <typename Type>
	void Array<Type>::Append(Type x)
	{
		if (ShouldResize())
		{
			Resize(NewSize(GetSize()));
		}

		m_arr[m_length] = x;
		++m_length;
	}

	template <typename Type>
	void Array<Type>::Resize(const int size)
	{
		//TODO: Implement resize

		m_size = size;
		Type* temp = new Type[m_size];
		fill(m_arr, temp, m_length);
		delete [] m_arr;
		m_arr = temp;
		temp = nullptr;
	}




	template <typename Type>
	void Array<Type>::RightShift(const int start, const bool b_resize)
	{
		if (b_resize)
		{
			Resize(NewSize(GetSize()));
		}

		for (int i = m_length - 1; i >= start; i--)
		{
			m_arr[(i + 1)] = m_arr[i];
			std::cout << i << " " << m_arr[i + 1] << " = " << m_arr[i] << std::endl;
		}

	}

	template <typename Type>
	void Array<Type>::LeftShift(const int start)
	{
		for (int i = start; i < m_length - 1; i++)
		{
			m_arr[i] = m_arr[i + 1];
		}
		--m_length;
	}

	template <typename Type>
	void Array<Type>::Insert(int index, Type x)
	{
		if (is_index_valid(index))
		{
			RightShift(index, ShouldResize());
			m_arr[index] = x;
			++m_length;
		}
	}

	template <typename Type>
	void Array<Type>::Remove(const int index)
	{
		LeftShift(index);
	}

	template <typename Type>
	bool Array<Type>::InsertSorted(Type x)
	{
		if (!IsSorted())
		{
			return false;
		}

		for (int i = 0; i < GetLength(); i++)
		{
			if (m_arr[i] > x)
			{
				Insert(i, x);

				return true;
			}
		}
		return false;
	}


	template <typename Type>
	Type Array<Type>::Max()
	{
		std::is_arithmetic<Type> b_arithmetic;
		if (b_arithmetic.value)
		{
			Type max = m_arr[0];

			for (int i = 0; i < m_length; i++)
			{
				if (m_arr[i] > max)
				{
					max = m_arr[i];
				}
			}
			return  max;
		}

		throw std::invalid_argument("Type is not arithmatic");
	}

	template <typename Type>
	Type Array<Type>::Min()
	{
		std::is_arithmetic<Type> b_arithmetic;
		if (b_arithmetic.value)
		{
			Type min = m_arr[0];

			for (int i = 0; i < m_length; i++)
			{
				if (m_arr[i] < min)
				{
					min = m_arr[i];
				}
			}
			return  min;
		}

		throw std::invalid_argument("Type is not arithmatic");
	}

	template <typename Type>
	void Array<Type>::Reverse()
	{
		int i = 0;
		int j = m_length - 1;

		while (i < j)
		{
			Swap(m_arr[i], m_arr[j]);
			++i;
			--j;
		}
	}

	template <typename Type>
	bool Array<Type>::IsSorted()
	{
		for (int i = 0; i < m_length - 1; i++)
		{
			if (m_arr[i] > m_arr[i + 1])
			{
				return false;
			}
		}
		return true;
	}

	template <typename Type>
	int Array<Type>::LinearSearch(Type element)
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_arr[i] == element)
			{
				return i;
			}
		}
		return -1;
	}

	template <typename Type>
	int Array<Type>::BinarySearch(Type element)
	{
		if (!IsSorted())
		{
			throw std::runtime_error("Array is not sorted.");
		}

		int low = 0, mid = 0, high = m_length - 1;

		while (low <= high)
		{
			mid = (low + high) / 2;

			if (m_arr[mid] == element)
			{
				return mid;
			}

			if (m_arr[mid] < element)
			{
				low = mid + 1;
			}

			if (m_arr[mid] > element)
			{
				high = mid - 1;
			}
		}
		return -1;
	}

	template <typename Type>
	int Array<Type>::BinarySearch(Type element, int low, int high)
	{
		if (high >= low)
		{
			const int mid = (low + high) / 2;

			if (AreEqual(element, m_arr[mid]))
			{
				return mid;
			}

			if (element < m_arr[mid])
			{
				return BinarySearchRecursive(element, low, mid - 1);
			}

			if (element > m_arr[mid])
			{
				return BinarySearchRecursive(element, mid + 1, high);
			}

		}

		return -1;
	}

	template <typename Type>
	void Array<Type>::BubbleSort()
	{
		while (!IsSorted())
		{
			for (int i = 0; i < GetLength() - 1; i++)
			{
				if (m_arr[i] > m_arr[i + 1])
				{
					Swap(m_arr[i], m_arr[i + 1]);
				}
			}
		}
	}

	template <typename Type>
	Type Array<Type>::Get(const int index)const
	{
		if (index >= 0 && index < m_length)
		{
			return m_arr[index];
		}
		throw std::out_of_range("Index out of range");
	}

	template <typename Type>
	bool Array<Type>::Set(const Type x, const int index)
	{
		if (is_index_valid(index))
		{
			m_arr[index] = x;
			return true;
		}
		return false;
	}

	template <typename Type>
	void Array<Type>::Swap(Type& x, Type& y)
	{
		Type temp = x;
		x = y;
		y = temp;
	}

	template <typename Type>
	bool Array<Type>::AreEqual(const double a, const double b, const double epsilon) const
	{
		return std::abs(a - b) < epsilon;
	}

	template <typename Type>
	bool Array<Type>::AreEqual(const float a, const float b, const float epsilon) const
	{
		return std::abs(a - b) < epsilon;
	}
	
}
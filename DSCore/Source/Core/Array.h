#pragma once
#include "stdexcept"
#include <type_traits>
#include "initializer_list"
#include"string"
#include "thread"
#include <future>

#define NewSize(x) ((x)+5)

enum Status
{
	Ok,
	Err
};

template<typename T>
struct Result
{
	Status status;
	T value;
	const char * msg;
};

namespace Ds
{

	template<typename T>
	class Array  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		void Append(T x);
		void Insert(int index, T x);
		[[nodiscard]] Result<T> Get(int index)const;
		bool Set(T x, int index);
		void Remove(int index);
		int LinearSearch(T element);
		int BinarySearch(T element);
		int BinarySearch(T element, int low , int high);
		void BubbleSort();
		bool IsSorted();
		void Reverse();
		T Max();
		T Min();
		void LeftShift(int start);
		void RightShift(int start, bool b_resize);
		bool InsertSorted(T x);
		void Merge(const Array<T> & arr);
		[[nodiscard]] size_t GetLength() const;
		[[nodiscard]] size_t GetSize() const;
		[[nodiscard]] T* begin() const;
		[[nodiscard]] T* end() const;

		Array() = delete;
		explicit Array(int size);
		Array(std::initializer_list<T> args);
		Array(const Array<T>& from);
		~Array();
		T& operator[](int index);
		Array<T>& operator=(const Array<T>& arr);

	private:
		T* m_arr = nullptr;
		size_t m_size = 0;
		size_t m_length = 0;
		bool m_initialized = false;

		void Resize(int size);
		void fill(std::initializer_list<T>& args);
		void fill(const Array<T>& from, Array<T>& to);
		static void fill(const T  * from, T * to, int length);
		void reset();
		void Swap(T& x, T& y);
		[[nodiscard]] static T Smaller(const T & x, const T & y);
		[[nodiscard]] static T Larger(const T & x, const T & y);

		[[nodiscard]] bool ShouldResize() const;
		[[nodiscard]] bool is_index_valid(int index) const;
		[[nodiscard]] static bool AreEqual(double a, double b, double epsilon = 1e-6);
		[[nodiscard]] static bool AreEqual(float a, float b, float epsilon = 1e-6f);
		[[nodiscard]] static bool AreEqual(int a, int b);
	};

	template <typename T>
	bool Array<T>::is_index_valid(const int index) const
	{
		if (index >= 0 && index < static_cast<int>(m_size))
		{
			return true;
		}
		return false;
	}

	template <typename T>
	void Array<T>::reset()
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

	template <typename T>
	Array<T>::Array(const int size)
	{
		m_size = size;
		m_arr = new T[m_size];
		m_length = 0;
		m_initialized = false;
	}


	template <typename T>
	Array<T>::Array(std::initializer_list<T> args)
	{
		fill(args);
	}

	template <typename T>
	Array<T>::Array(const Array<T>& from)
	{
		fill(from, *this);
	}

	template <typename T>
	Array<T>::~Array()
	{
		delete [] m_arr;
	}

	template <typename T>
	void Array<T>::fill(std::initializer_list<T>& args)
	{
		m_size = static_cast<int>(args.size());
		m_arr = new T[m_size];

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

	template <typename T>
	void Array<T>::fill(const Array<T>& from, Array<T>& to)
	{
		to.reset();
		to.m_size = from.GetSize();
		to.m_arr = new T[to.m_size];

		fill(from.m_arr, to.m_arr, static_cast<int>(from.GetLength()));

		to.m_length = from.m_length;
		to.m_initialized = true;
	}

	template <typename T>
	void Array<T>::fill(const T* from, T* to, const int length)
	{
		for (int i = 0; i < length; i++)
		{
			to[i] = from[i];
		}
	}

	template <typename T>
	T& Array<T>::operator[](int index)
	{
		if (is_index_valid(index))
		{
			return m_arr[index];
		}

		throw std::out_of_range("Given index is out of range");
	}

	template <typename T>
	Array<T>& Array<T>::operator=(const Array<T>& arr)
	{
		fill(arr, *this);
		return *this;
	}


	template <typename T>
	void Array<T>::Append(T x)
	{
		if (ShouldResize())
		{
			Resize(static_cast<int>(NewSize(GetSize())));
		}

		m_arr[m_length] = x;
		++m_length;
		if (!m_initialized)
		{
			m_initialized = true;
		}
	}

	template <typename T>
	void Array<T>::Resize(const int size)
	{
		m_size = size;
		T* temp = new T[m_size];
		fill(m_arr, temp, static_cast<int>(m_length));
		delete [] m_arr;
		m_arr = temp;
		temp = nullptr;
	}




	template <typename T>
	void Array<T>::RightShift(const int start, const bool b_resize)
	{
		if (b_resize)
		{
			Resize(NewSize(GetSize()));
		}

		for (int i = m_length - 1; i >= start; i--)
		{
			m_arr[(i + 1)] = m_arr[i];
			
		}

	}

	template <typename T>
	void Array<T>::LeftShift(const int start)
	{
		for (int i = start; i < m_length - 1; i++)
		{
			m_arr[i] = m_arr[i + 1];
		}
		--m_length;
	}

	template <typename T>
	void Array<T>::Insert(int index, T x)
	{
		if (is_index_valid(index))
		{
			RightShift(index, ShouldResize());
			m_arr[index] = x;
			++m_length;
		}
	}

	template <typename T>
	void Array<T>::Remove(const int index)
	{
		LeftShift(index);
	}

	template <typename T>
	bool Array<T>::InsertSorted(T x)
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

	template<typename T>
	void Array<T>::Merge(const Array<T>& arr)
	{
		Array<T> * temp = new Array<T>(static_cast<int>((arr.GetLength() + GetLength())));

		size_t i = 0, j=0, k=0;

		while (i < GetLength() && j < arr.GetLength())
		{
			if(m_arr[i] < arr.m_arr[j])
			{
				temp->m_arr[k] = m_arr[i];
				++(temp->m_length);
				i++;
				k++;
			}
			else if(m_arr[i] > arr.m_arr[j])
			{
				temp->m_arr[k] = arr.m_arr[j];
				++(temp->m_length);
				j++;
				k++;
			}
		}

		for(; i < GetLength(); i++)
		{
			temp->m_arr[k] = m_arr[i];
			++(temp->m_length);
			k++;
		}

		for(; j < arr.GetLength(); j++)
		{
			temp->m_arr[k] = arr.m_arr[j];
			++(temp->m_length);
			k++;
		}

		delete []m_arr;

		this->m_arr = temp->m_arr;
		this->m_length = temp->m_length;
		this->m_size = temp->m_size;
		this->m_initialized = (m_length > 0);

		temp = nullptr;
	}


	template <typename T>
	size_t Array<T>::GetLength() const
	{ return m_length; }

	template <typename T>
	size_t Array<T>::GetSize() const
	{ return m_size; }

	template<typename T>
	T* Array<T>::begin() const
	{
		 return m_arr; //first element of array
	}

	template <typename T>
	T* Array<T>::end() const
	{
		return m_arr + GetLength(); // last element of array
	}

	template <typename T>
	bool Array<T>::ShouldResize() const
	{return m_length >= m_size;}


	template <typename T>
	T Array<T>::Max()
	{
		std::is_arithmetic<T> b_arithmetic;
		if (b_arithmetic.value)
		{
			T max = m_arr[0];

			for (int i = 0; i < m_length; i++)
			{
				if (m_arr[i] > max)
				{
					max = m_arr[i];
				}
			}
			return  max;
		}

		throw std::invalid_argument("T is not arithmatic");
	}

	template <typename T>
	T Array<T>::Min()
	{
		std::is_arithmetic<T> b_arithmetic;
		if (b_arithmetic.value)
		{
			T min = m_arr[0];

			for (int i = 0; i < m_length; i++)
			{
				if (m_arr[i] < min)
				{
					min = m_arr[i];
				}
			}
			return  min;
		}

		throw std::invalid_argument("T is not arithmatic");
	}

	template <typename T>
	void Array<T>::Reverse()
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

	template <typename T>
	bool Array<T>::IsSorted()
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

	template <typename T>
	int Array<T>::LinearSearch(T element)
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

	template <typename T>
	int Array<T>::BinarySearch(T element)
	{
		int low = 0;
		int mid = 0;
		int high = static_cast<int>(m_length - static_cast<size_t>(1));

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

	template <typename T>
	int Array<T>::BinarySearch(T element, int low, int high)
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
				return BinarySearch(element, low, mid - 1);
			}

			if (element > m_arr[mid])
			{
				return BinarySearch(element, mid + 1, high);
			}

		}

		return -1;
	}


	template <typename T>
	void Array<T>::BubbleSort()
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

	template <typename T>
	Result<T> Array<T>::Get(const int index)const
	{
		if (index >= 0 && index < m_length)
		{
			return {Ok, m_arr[index], ""};
		}

		return {Err, static_cast<T>(-1), "index out of bound"};
	}

	template <typename T>
	bool Array<T>::Set(const T x, const int index)
	{
		if (is_index_valid(index))
		{
			m_arr[index] = x;
			return true;
		}
		return false;
	}

	template <typename T>
	void Array<T>::Swap(T& x, T& y)
	{
		T temp = x;
		x = y;
		y = temp;
	}

	template <typename T>
	T Array<T>::Smaller(const T& x, const T& y)
	{
		if(x>y)
			return y;

		return x;
	}

	template<typename T>
	T Array<T>::Larger(const T& x, const T& y)
	{
		if(x>y)
			return x;

		return y;
	}

	template <typename T>
	bool Array<T>::AreEqual(const double a, const double b, const double epsilon)
	{
		return std::abs(a - b) < epsilon;
	}

	template <typename T>
	bool Array<T>::AreEqual(const float a, const float b, const float epsilon)
	{
		return std::abs(a - b) < epsilon;
	}

	template<typename T>
	inline bool Array<T>::AreEqual(const int a, const int b)
	{
		return a == b;
	}
	
}
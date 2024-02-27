#pragma once
#include <utility>

// small macro to reduce repeated code
#define DEFINE_VARIABLE_AND_CONSTANT(function) \
const function const;                          \
function

template<typename Type> class Vector
{
public:
	Vector();
	Vector(size_t amount);
	Vector(size_t amount, Type value);
	Vector(Type* begin, size_t amount);
	Vector(const Vector<Type>& rhs);
	~Vector();

	void Clear();
	void PushBack(Type&& value);
	void PushBack(const Type& value);
	void PopBack();
	void Resize(size_t newSize);
	size_t GetSize();

	template<typename... Args>
	void PushBack(Args&&... args);

	Vector<Type>& operator=(const Vector<Type>& rhs);

	DEFINE_VARIABLE_AND_CONSTANT(Type& operator[](size_t index));
	DEFINE_VARIABLE_AND_CONSTANT(Type& Back());
	DEFINE_VARIABLE_AND_CONSTANT(Type* begin());
	DEFINE_VARIABLE_AND_CONSTANT(Type* end());
	     
private:
	void Alloc(size_t amount);
	void Realloc(size_t amount);

	static constexpr size_t RESERVE_ON_CREATION = 4;

	Type* data = nullptr;
	size_t size = 0, reserved = RESERVE_ON_CREATION;
};

template<typename Type>
Vector<Type>::Vector()
{
	Alloc(RESERVE_ON_CREATION);
}

template<typename Type>
Vector<Type>::Vector(size_t amount) : size(amount)
{
	Realloc(amount);
}

template<typename Type>
Vector<Type>::Vector(size_t amount, Type value)
{
	Realloc(amount);
	while (size < amount)
		data[size++] = std::move(value);
}

template<typename Type>
Vector<Type>::Vector(Type* begin, size_t amount) : size(amount)
{
	Alloc(amount);
	for (size_t i = 0; i < amount; i++)
		new(&data[i]) Type(begin[i]);
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type>& rhs) : size(rhs.size)
{
	Alloc(rhs.reserved);
	for (size_t i = 0; i < rhs.size; i++)
		new(&data[i]) Type(rhs.data[i]);
}

template<typename Type>
Vector<Type>::~Vector()
{
	delete[] data;
}

template<typename Type>
void Vector<Type>::Clear()
{
	for (size_t i = 0; i < size; i++)
		data[i].~Type();
	size = 0;
}

template<typename Type>
void Vector<Type>::PushBack(Type&& value)
{
	if (size >= reserved) Realloc(reserved * 2);
	data[size++] = std::move(value);
}

template<typename Type>
void Vector<Type>::PushBack(const Type& value)
{
	if (size >= reserved) Realloc(reserved * 2);
	data[size++] = value;
}

template<typename Type>
void Vector<Type>::PopBack()
{
	data[size--].~Type();
}

template<typename Type>
void Vector<Type>::Resize(size_t newSize)
{
	Realloc(newSize * 2);
	while (size < newSize)
		new(&data[size++]) Type();
}

template<typename Type>
size_t Vector<Type>::GetSize()
{
	return size;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& rhs)
{
	Alloc(rhs.reserved);
	for (size_t i = 0; i < rhs.size; i++)
		data[i] = std::move(rhs.data[i]);
	size = rhs.size;
	return *this;
}

template<typename Type>
template<typename...Args>
void Vector<Type>::PushBack(Args&&...args)
{
	if (size >= reserved) Realloc(reserved * 2);
	new(&data[size++]) Type(std::forward<Args>(args)...);
}

template<typename Type>
void Vector<Type>::Alloc(size_t amount)
{
	data = new Type[amount];
	reserved = amount;
}

#pragma warning( push )
#pragma warning( disable : 6386 )
template<typename Type>
void Vector<Type>::Realloc(size_t amount)
{
	Type* newData = new Type[amount];
	for (size_t i = 0; i < size; i++)
		newData[i] = std::move(data[i]);
	reserved = amount;
	std::swap(newData, data);
	delete[] newData;
}
#pragma warning( pop )

#pragma region iterators
template<typename Type>
const Type& Vector<Type>::operator[](size_t index) const { return data[index]; }

template<typename Type>
Type& Vector<Type>::operator[](size_t index) { return data[index]; }

template<typename Type>
const Type& Vector<Type>::Back() const { return data[size - 1]; }

template<typename Type>
Type& Vector<Type>::Back() { return data[size - 1]; }

template<typename Type>
const Type* Vector<Type>::begin() const { return data; }

template<typename Type>
Type* Vector<Type>::begin() { return data; }

template<typename Type>
const Type* Vector<Type>::end() const { return data + size; }

template<typename Type>
Type* Vector<Type>::end() { return data + size; }
#pragma endregion iterators
#undef DEFINE_VARIABLE_AND_CONSTANT
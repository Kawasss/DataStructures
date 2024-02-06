#pragma once
#include <utility>

template<typename Type>
class List
{
public:
	List() = default;
	List(size_t amount);
	List(size_t amount, Type value);
	List(const List<Type>& rhs);
	~List();
	void PopBack();
	void PushBack(Type&& value);
	size_t GetSize();

	Type& operator[](size_t index);
	const Type& operator[](size_t index) const;

	const Type& Back() const;
	Type& Back();

	const Type* begin() const;
	const Type* end() const;
	Type* begin();
	Type* end();

private:
	struct Chain
	{
		Type value{};
		Chain* pNext = nullptr;
		Chain* pPrev = nullptr;
	};

	Chain* first = nullptr;
	Chain* head = nullptr;
	size_t size = 0;
};

template<typename Type>
List<Type>::List(size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		PushBack({});
}

template<typename Type>
List<Type>::List(size_t amount, Type value)
{
	for (size_t i = 0; i < amount; i++)
		PushBack(value);
}

template<typename Type>
List<Type>::List(const List<Type>& rhs)
{
	Chain* ptr = rhs.first;
	for (size_t i = 0; i < rhs.size; i++)
		PushBack(std::move(ptr->value));
}

template<typename Type>
void List<Type>::PopBack()
{
	if (size == 1) first = nullptr;
	head = head->pPrev;
	delete head;
	size--;
}

template<typename Type>
void List<Type>::PushBack(Type&& value)
{
	head = new Chain{ value, nullptr, head };
	if (size == 0) first = head;
	else           head->pPrev->pNext = head;
	size++;
}

template<typename Type>
size_t List<Type>::GetSize()
{
	return size;
}

template<typename Type>
Type& List<Type>::operator[](size_t index)
{
	Chain* ptr = first;
	for (size_t i = 1; i <= index && ptr != nullptr; i++)
		ptr = ptr->pNext;
	return ptr->value;
}

template<typename Type>
const Type& List<Type>::operator[](size_t index) const 
{ 
	Chain* ptr = first;
	for (size_t i = 1; i <= index && ptr != nullptr; i++)
		ptr = ptr->pNext;
	return ptr->value;
}

template<typename Type>
List<Type>::~List()
{
	if (head == nullptr)
		return;
	Chain* ptr = head->pPrev;
	for (size--; size > 0 && ptr != nullptr; size--)
		delete ptr->pNext;
	delete head;
}

#pragma region iterators
template<typename Type>
const Type& List<Type>::Back() const { return *head; }

template<typename Type>
Type& List<Type>::Back() { return *head; }

template<typename Type>
const Type* List<Type>::begin() const { return first; }

template<typename Type>
Type* List<Type>::begin() { return first; }

template<typename Type>
const Type* List<Type>::end() const { return head + 1; }

template<typename Type>
Type* List<Type>::end() { return head + 1; }
#pragma endregion iterators
#pragma once
template<typename Type>
class Optional
{
public:
	Optional() = default;
	Optional<Type>& operator=(Type value);
	bool HasValue();
	void Clear();

private:
	Type value{};
	bool assigned = false;
};

template<typename Type>
Optional<Type>& Optional<Type>::operator=(Type value)
{
	this->value = value;
	assigned = true;
	return *this;
}

template<typename Type>
bool Optional<Type>::HasValue()
{
	return assigned;
}

template<typename Type>
void Optional<Type>::Clear()
{
	assigned = false;
}
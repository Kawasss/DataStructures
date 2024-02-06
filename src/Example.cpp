#include <iostream>

#include "Optional.hpp"
#include "Vector.hpp"
#include "List.hpp"

void OptionalExample()
{
	Optional<int> opt;
	std::cout << opt.HasValue() << '\n';

	opt = 32;
	std::cout << opt.HasValue() << "\n\n";
}

void VectorExample()
{
	Vector<int> vec(11, 6);
	std::cout << vec.GetSize() << '\n';

	Vector<int> v2 = vec;
	for (int i : v2)
		std::cout << i << '\n';

	vec.PushBack(1);
	vec.PopBack();

	std::cout << vec.GetSize() << "\n\n";

	struct MyStruct
	{
		MyStruct() = default;
		MyStruct(float newVar1, int newVar2) : myVar1(newVar1), myVar2(newVar2) {}

		float myVar1;
		int myVar2;
	};

	Vector<MyStruct> v;
	v.PushBack(1.0f, 2);

	std::cout << v[0].myVar2 << "\n\n";

	v.PopBack();
}

void ListExample()
{
	List<int> list;

	list.PushBack(2);
	
	std::cout << list[0] << '\n';

	List<int> list2 = list;

	list.PopBack();

	std::cout << list2.GetSize() << "\n\n";
}

int main(int argc, char** argv)
{
	//OptionalExample();
	VectorExample();
	ListExample();
	return 0;
}
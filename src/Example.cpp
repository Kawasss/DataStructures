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


Vector<int> FibonacciSequence()
{
	Vector<int> ret;
	int x = 0, y = 1, z = 0;
	for (int i = 0; i < 20; i++)
	{
		ret.PushBack(x);
		z = x + y;
		x = y;
		y = z;
	}
	return ret;
}

void VectorExample()
{
	std::cout << "vector example:\n";

	Vector<int> fibo = FibonacciSequence();
	for (int i : fibo)
		std::cout << i << '\n';
}

void ListExample()
{
	std::cout << "list example:\n";

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
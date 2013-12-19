#include <iostream>

void Func1(int a)
{
	std::cout << "Func1(" << a << ")" << std::endl;
}

void Func2(int a, int b)
{
	std::cout << "Func2(" << a << ", " << b << ")" << std::endl;
}

class ABC
{
public:
	ABC(int a, int b) { std::cout << "ABC(" << a << ", " << b << ")" << std::endl; }
};

int main(void)
{
	// Func1(int)
	Func1(1);			// Good!
	Func1({ 1 });		// No error! BAD!
	//Func1({ 1, 2 });	// C2664: cannot convert argument 1 from 'initializer-list' to 'int'. Good!

	// Func2(int, int)
	Func2(1, 2);		// Good!
	//Func2({ 2, 3 });	// C2660: function does not take 1 arguments. Good!

	ABC abc1(1, 2);			// ABC(int, int) Good!
	ABC abc2({ 1, 2 });		// ABC(int, int) BAD!
}
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

// Brace list can be interpreted as a initilizer list of a dummy class (?!?!).
void TestUniformInitialization(void)
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

void FuncDouble(double d) {}

class DoubleClass
{
public:
	DoubleClass(double src) : data(src) { std::cout << "DoubleClass::DoubleClass(" << src << ")" << std::endl; }
	double data;
};

void FuncDClass(const DoubleClass &d) { std::cout << "FuncDClass() with DoubleClass.data = " << d.data << std::endl; }

class TopClass
{
public:
	TopClass(const DoubleClass &src) : data(src.data) { std::cout << "TopClass::TopClass()" << std::endl; }
	double data;
};

void FuncTClass(const TopClass &t) { std::cout << "FuncTClass() with TopClass.data = " << t.data << std::endl; }

void TestArgumentConversion(void)
{
	FuncDouble(1.0);
	FuncDouble(1);	// (1 -> 1.0)

	DoubleClass d1 = 2.0;
	DoubleClass d2 = 2;	// (2 -> 2.0)

	FuncDClass(3.0);	// 3.0 -> DoubleClass temp(3.0)
	FuncDClass(3);		// (3 -> 3.0) -> DoubleClass temp(3.0)
	TopClass t1 = 4.0;	// 4.0 -> DoubleClass temp(4.0)
	TopClass t2 = 4;	// (4 -> 4.0) -> DoubleClass temp(4.0)
	FuncTClass(d1);		// DoubleClass d1 -> TopClass temp(d1)

	//FuncTClass(5.0);	// 5.0 -> DoubleClass temp(5.0) and that's it. temp(5.0) -> TopClass temp2(temp) is not happening.
	//FuncTClass(5);

	// Conclusion:
	// Implicit convesion(upgrading) can happen without any cost.
	// Conversion using a ctor can be done only once for function arguments.
}

int main(void)
{
	TestUniformInitialization();
	TestArgumentConversion();
}
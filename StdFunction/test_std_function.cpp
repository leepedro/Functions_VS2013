#include <algorithm>	// std::transform()
#include <functional>	// std::function<>
#include <cctype>		// std::toupper()
#include <string>		// << std::string<>
#include <iostream>
#include <vector>
#include <numeric>		// std::iota()

int main(void)
{
	// Changes given string to upper characters.
	std::string s1("hello");
	std::cout << s1 << std::endl;
	std::transform(s1.cbegin(), s1.cend(), s1.begin(), std::function<int(int)>(std::toupper));
	std::cout << s1 << std::endl;

	// Increase given vector by 1 and return it to another vector using lambda expression.
	std::vector<int> v1(10), v2(10);
	std::iota(v1.begin(), v1.end(), 0);
	std::transform(v1.cbegin(), v1.cend(), v2.begin(), [](int n) { return n + 1; });	// v2[*] = v1[*] + 1

	// A = B + C using lambda expression.
	std::vector<int> input1(3, 1), input2(3, 1), output1(3);
	std::transform(input1.cbegin(), input1.cend(), input2.cbegin(), output1.begin(), [](int a, int b) { return a + b; });	// C[*] = A[*] + B[*]
}
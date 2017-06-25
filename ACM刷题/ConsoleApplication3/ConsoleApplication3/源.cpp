#include <iostream>
int GCD(int a,int b)
{
	int r;
	if (a < b){
		a = a + b;
		b = a - b;
		a = a - b;
	}
	while (b){
		r = a%b;
		a = b;
		b = r;
	}
	return a;
}
int main()
{
	while (1){
		int a, b;
		std::cin >> a >> b;
		if (a == 0 && b == 0)
			break;
		std::cout << "GCD(" << a << "," << b << ")=" << GCD(a, b) << std::endl;
	}
	return 0;
}
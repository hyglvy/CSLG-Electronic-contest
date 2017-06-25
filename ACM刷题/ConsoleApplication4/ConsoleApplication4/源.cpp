#include <iostream>
double F(const char *str);
double handle(const char *str)
{
	double sum = 0;
	for (int i = 0; str[i]; i++){
		switch (str[i])
		{
		case '+':sum = sum + F(&str[i + 1]); i++; while (str[i] != '+' && str[i] != '-'){ i++; } break;
		case '-':sum = sum - F(&str[i + 1]); i++; while (str[i] != '+' && str[i] != '-'){ i++; } break;
		default:sum = sum + F(&str[i]); break;
		}
	}
	return sum;
}
double F(const char *str)
{
	int i = 0;
	double sum = 0;
	while (str[i] != '+' && str[i] != '-'){
		switch (str[i])
		{
		case '*':sum = sum * (str[i++] - '0'); break;
		case '/':sum = sum / (str[i++] - '0'); break;
		default:sum = sum + str[i] - '0'; break;
		}
		i++;
	}
	return  sum;
}
int main()
{
	int N;
	std::cin >> N;
	if (N>10)
		return -1;
	while (N--){
		char str[50] = { 0 };
		fflush(stdin);
		gets_s(str);
		std::cout << handle(str) << std::endl;
	}
	return 0;
}
#include <iostream>
int main()
{
	int N;
	std::cin >> N;
	for (int i = 0; i < N; i++){
		int Data[3] = { 0 };
		//scanf_s("%d %d %d", &Data[0], &Data[1], &Data[2]);
		std::cin >> Data[0];
		std::cin >> Data[1];
		std::cin >> Data[2];
		int j;
		for (j = 0; j < 3; j++){
			if (Data[j] + Data[(j + 1)%3] <= Data[(j + 2)%3])
				break;
			if (Data[j] - Data[(j + 1) % 3] >= Data[(j + 2) % 3])
				break;
		}
		if (j < 3)
			std::cout << "No" << std::endl;
		else
			std::cout << "Yes" << std::endl;
	}
	return 0;
}
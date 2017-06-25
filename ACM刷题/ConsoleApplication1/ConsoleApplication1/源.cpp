#include <memory.h>
#include <iostream>
#include <stdlib.h>
int main()
{
	int N=0;
	std::cin >> N;
	if (N > 200)
		return 0;
	char *str = (char*)malloc(N*7);
	for (int i = 0; i < N; i++){
		str[i * 7] = '6';
		for (int j = 0; j < 12; j++){
			char c;
			c = getchar();
			if (j>6&&j<12){
				str[i * 7 + j - 6] = c;
			}
		}
		if ((i + 1) == N)
			str[6 + i * 7] = 0;
		else
			str[6 + i * 7] = '\n';
	}
	puts(str);
	return 0;
}
#include "Head.h"
#include "Winio.h"
bool Read_File(int data[][2])
{
	FILE *fp;
	if ((fp = fopen("TimeData.txt", "r")) == NULL){
		printf("File open error!\n");
		return false;
	}
	for (int i = 0; i<12; i++){
		for (int j = 0; j<2; j++){
			fscanf(fp, "%d", &data[i][j]);
		}
	}
	return true;
}
int GetCurrentSecond(void)
{
	return time((time_t*)NULL) % 60;
}

void ParallPortWrite(unsigned char data)
{
	bool bResult;
	printf("debug:���ڴ�:\n");
	bResult = InitializeWinIo();			//���ڳ�ʼ��WINIO
	if (bResult)
	{
		//�˴����޸Ļ���Ӵ���
		SetPortVal(0x378, data, 1);		//���ַΪ0x378�Ĳ������һ���ֽ����ݣ�1�Ķ���0x06��
		printf("debug:0x%x\n", data);		//����Ļ�������������ʾ��Ϣ
		ShutdownWinIo();					//���ڹر�WINIO
		printf("debug:���ڹر�:\n");
	}
	else
	{
		printf("Error during initialization of WinIo.\n");
		exit(1);
	}

}

void show(int n)
{
	char *p = Num[n];
	for (int i = 0; i < 8; i++){
		int H, L;
		H = (*p >= 97) ? (*p - 87) : (*p - 48);
		p++;
		L = (*p >= 97) ? (*p - 87) : (*p - 48);
		p++;
		char str[5];
		stod(H, str);
		printf("%s",str);
		stod(L, str);
		printf("%s\n",str);
	}
}
void stod(int n, char s[])
{
	int i = 0;
	memset(s, 32, 5);
	while (n){
		if (n % 2)
			s[i++] = '*';
		else
			s[i++] = ' ';
		n = n / 2;
	}
	s[4] = 0;
	_strrev(s);
}
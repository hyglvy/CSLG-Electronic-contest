#include <windows.h>
#include <stdio.h>
#include "winio.h"
void delay(unsigned int n)
{
	unsigned int i;
	for(i=0;i<n;i++)
		;
}
void ParallPortWrite(unsigned char data1)
{
	bool bResult;
	printf("debug:���ڴ�:\n");
	bResult = InitializeWinIo();			//���ڳ�ʼ��WINIO
	if (bResult)
	{
		//�˴����޸Ļ���Ӵ���
		SetPortVal(0x378, data1, 1);		//���ַΪ0x378�Ĳ������һ���ֽ����ݣ�1�Ķ���0x06��
		printf("debug:0x%x\n",data1);		//����Ļ�������������ʾ��Ϣ
		ShutdownWinIo();					//���ڹر�WINIO
		printf("debug:���ڹر�:\n");
	}
	else
	{
		printf("Error during initialization of WinIo.\n");
		exit(1);
	}

}

int main()
{	
	ParallPortWrite(0x06);
	return(0);	
}


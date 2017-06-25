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
	printf("debug:并口打开:\n");
	bResult = InitializeWinIo();			//并口初始化WINIO
	if (bResult)
	{
		//此处可修改或添加代码
		SetPortVal(0x378, data1, 1);		//向地址为0x378的并口输出一个字节数据（1的段码0x06）
		printf("debug:0x%x\n",data1);		//向屏幕输出并口数据提示信息
		ShutdownWinIo();					//并口关闭WINIO
		printf("debug:并口关闭:\n");
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


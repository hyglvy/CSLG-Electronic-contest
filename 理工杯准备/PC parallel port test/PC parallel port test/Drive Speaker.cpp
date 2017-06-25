// play.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

// 声明函数指针
typedef bool(_stdcall *pInitializeWinIo)(void);

typedef void(_stdcall *pShutdownWinIo)(void);

typedef bool(_stdcall *pGetPortVal)(
	WORD wPortAddr,
	PVOID pdwPortVal,
	BYTE bSize
	);

typedef bool(_stdcall *pSetPortVal)(
	WORD wPortAddr,
	DWORD dwPortVal,
	BYTE bSize
	);

// 定义函数指针
pInitializeWinIo InitializeWinIo = NULL;
pShutdownWinIo ShutdownWinIo;
pGetPortVal GetPortVal;
pSetPortVal SetPortVal;


void CallIo(UINT hz){
	UCHAR b = 193200 / hz;

	// 定时器与喇叭联通
	int nState;
	GetPortVal(0x61, &nState, 1);
	nState |= 3;
	SetPortVal(0x61, nState, 1);

	// 设置控制寄存器
	SetPortVal(0x43, 0xB6, 1);

	// 设置数据寄存器
	SetPortVal(0x42, (b & 0xF), 1);
	SetPortVal(0x42, ((b >> 4) & 0xF), 1);
}

void CancelIo(){

	// 与PC喇叭断开 取消鸣叫
	int Value;
	GetPortVal(0x61, &Value, 1);
	Value &= 0xFC;
	SetPortVal(0x61, Value, 1);

	// 转入0信号 取消鸣叫
	//         SetPortVal(0x42, 0, 1);
	//         SetPortVal(0x42, 0, 1);
}

int main(int argc, char* argv[])
{
	
	HMODULE hWinIo = LoadLibrary("WinIo32.dll");
	if (hWinIo == NULL){
		cout << "WinIo 加载失败!" << endl;
		return 1;
	};

	InitializeWinIo = (pInitializeWinIo)GetProcAddress(hWinIo, "InitializeWinIo");
	ShutdownWinIo = (pShutdownWinIo)GetProcAddress(hWinIo, "ShutdownWinIo");
	GetPortVal = (pGetPortVal)GetProcAddress(hWinIo, "GetPortVal");
	SetPortVal = (pSetPortVal)GetProcAddress(hWinIo, "SetPortVal");

	if (InitializeWinIo == NULL ||
		ShutdownWinIo == NULL ||
		GetPortVal == NULL ||
		SetPortVal == NULL)
	{
		cout << "获取函数地址失败! \n" << endl;
		return 1;
	}

	bool bState = InitializeWinIo();
	if (!bState)
		cout << "初始化WinIo 失败!" << endl;

	CallIo(8000);
	Sleep(2000);
	CancelIo();

	ShutdownWinIo();

	return 0;
}
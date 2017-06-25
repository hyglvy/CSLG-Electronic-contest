// play.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

// ��������ָ��
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

// ���庯��ָ��
pInitializeWinIo InitializeWinIo = NULL;
pShutdownWinIo ShutdownWinIo;
pGetPortVal GetPortVal;
pSetPortVal SetPortVal;


void CallIo(UINT hz){
	UCHAR b = 193200 / hz;

	// ��ʱ����������ͨ
	int nState;
	GetPortVal(0x61, &nState, 1);
	nState |= 3;
	SetPortVal(0x61, nState, 1);

	// ���ÿ��ƼĴ���
	SetPortVal(0x43, 0xB6, 1);

	// �������ݼĴ���
	SetPortVal(0x42, (b & 0xF), 1);
	SetPortVal(0x42, ((b >> 4) & 0xF), 1);
}

void CancelIo(){

	// ��PC���ȶϿ� ȡ������
	int Value;
	GetPortVal(0x61, &Value, 1);
	Value &= 0xFC;
	SetPortVal(0x61, Value, 1);

	// ת��0�ź� ȡ������
	//         SetPortVal(0x42, 0, 1);
	//         SetPortVal(0x42, 0, 1);
}

int main(int argc, char* argv[])
{
	
	HMODULE hWinIo = LoadLibrary("WinIo32.dll");
	if (hWinIo == NULL){
		cout << "WinIo ����ʧ��!" << endl;
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
		cout << "��ȡ������ַʧ��! \n" << endl;
		return 1;
	}

	bool bState = InitializeWinIo();
	if (!bState)
		cout << "��ʼ��WinIo ʧ��!" << endl;

	CallIo(8000);
	Sleep(2000);
	CancelIo();

	ShutdownWinIo();

	return 0;
}
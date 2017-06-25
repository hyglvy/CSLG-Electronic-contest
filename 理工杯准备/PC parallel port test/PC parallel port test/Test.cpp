//获得数据端口地址
WORD m_nport = (WORD)0x378;
//获得要写入数据端口的值WriteValue(数据范围为0～255)
DWORD m_nValue = (DWORD)WriteValue;
//调用WinIo库函数SetPortVal写端口值
SetPortVal(m_nport, m_nValue, 1);//write a BYTE value to an I/O port 

(2)：控制端口数字输出的VC实现

//获得控制端口地址
WORD m_nport = (WORD)0x37A;
//获得控制端口的值,保持高位值不变，将要输出的值从低4位输出，且使连接器上的电位状态与想输出的值一致
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nport, &temp_dwPortVal, 1); //reads a BYTE value from an I/O port
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //取低8位值,将低4位置为0;高4位不变；
temp_aa = temp_aa ^ 0x0B; //将低4位中C0、C1、C3置为1，C2置为0;高4位不变；//获得要写入控制端口的值WriteValue(数据范围为0～15)
unsigned int WriValue;
WriValue = WriteValue & 0x0F; //取低4位；
temp_aa = temp_aa^WriValue; //将写入值的低4位中的C0、C1、C3取反，C2位不变，高4位保持端口值不变
SetPortVal(m_nport, (DWORD)temp_aa, 1); //写出的值中，高4位保持端口原来的值不变，
//低4位是写入什么电平，连接器上既是什么电平 

(3)：数据端口及控制端口组合成12位数字输出的VC实现

//获得端口地址
WORD m_nportData = (WORD)0x378;
WORD m_nportControl = (WORD)0x37A;
//获得要写入端口的值WriteValue(数据范围为0～4095)
DWORD m_nValue = (DWORD)(WriteValue & 0x0FF);//取低8位值
SetPortVal(m_nportData, m_nValue, 1);//write a BYTE value to Data port
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nportControl, &temp_dwPortVal, 1); //reads a BYTE value from an I/O port
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //取低8位值,将低4位置为0;高4位不变；
temp_aa = temp_aa ^ 0x0B; //将低4位中C0、C1、C3置为1，C2置为0;高4位不变；
unsigned int WriValue;
WriValue = WriValue >> 8;//取高4位值
temp_aa = temp_aa^WriValue; //将写入值的低4位中的C0、C1、C3取反，C2位不变，高4位保持端口值不变
SetPortVal(m_nportControl, (DWORD)temp_aa, 1); //写出的值中，高4位保持端口原来的值不变，
//低4位是写入什么电平，连接器上既是什么电平 

PC并行口数字输入的VC实现

(1)：状态端口数字输入的VC实现

为了测试并行口状态端口的数字输入，可以将数据端口引脚Pin2～Pin6连接到状态端口引脚Pin15、Pin13、Pin12、Pin10、Pin11上。引脚接好后，先从数据端口输出数据，在从状态端口和控制端口读出数据，读出的数据应与写入的数据一致，数据范围为0～31。

DWORD dwPortVal;
unsigned int ValueGet = 0;
//获得端口地址
WORD m_nport = (WORD)0x379;
//获得端口数据
GetPortVal(m_nport, &dwPortVal, 1);
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet ^ 0x80; //保持得到的State值与连接器处的值一直；
ValueGet = ValueGet & 0xF8; //去掉S0 ～S2位；
ValueGet = ValueGet >> 3; //右移3位，将S7～S3变为低5位 

(2)：控制端口数字输入的VC实现

为了测试并行口控制端口的数字输入，可以将数据端口引脚Pin2～Pin5连接到控制端口引脚Pin1、Pin14、Pin16、Pin17上 。引脚接好后，先从数据端口输出数据，在从状态端口和控制端口读出数据，读出的数据应与写入的数据一致，数据范围为0～15。

//获得端口地址
WORD m_nport = (WORD)0x37A;
//===== 将C0～C3位置1，即使连接器上为高电平 ，使控制端口为输入端口=====
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nport, &temp_dwPortVal, 1); //获取端口的当前值
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //取低8位值,将低4位置为0;高4位不变；
temp_aa = temp_aa ^ 0x4; //将低4位中C0、C1、C3置为0，C2置为1;高4位不变；
SetPortVal(m_nport, (DWORD)temp_aa, 1); //写出的值中，高4位保持端口原来的值不变，
//低4位是写高电平，即使连接器上是高电平
//=============================================================
unsigned int ValueGet = 0;
DWORD dwPortVal;
//获得端口数据
GetPortVal(m_nport, &dwPortVal, 1);
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet ^ 0x0B; //保持C0,C1,C3位的值与连接器处的值一至；
ValueGet = ValueGet & 0x0F; //去掉高4位值  

(3)：控制端口及状态端口组合成9位数字输入的VC实现

为了测试并行口的数字输入，可以将数据端口引脚Pin2～Pin9连接到控制端口引脚Pin1、Pin14、Pin16、Pin17和状态端口引脚Pin15、Pin13、Pin12、Pin10上 ，Pin11引脚连接到归地引脚GND或悬空。引脚接好后，先从数据端口输出数据，在从状态端口和控制端口读出数据，读出的数据应与写入的数据一致，当Pin11引脚连接到归地引脚GND时，数据范围为0～255；当Pin11引脚悬空时，数据范围为256～511。

unsigned int ValueGet = 0;
//获得端口地址
WORD m_nportState = (WORD)0x379;
WORD m_nportControl = (WORD)0x37A;
//Read State Port
DWORD dwPortVal;
unsigned int ValueState = 0;
GetPortVal(m_nportState, &dwPortVal, 1);
ValueState = dwPortVal;
ValueState = ValueState ^ 0x80; //保持得到的State值与连接器处的值一直；
ValueState = ValueState & 0xF8; //去掉S0 ～S2位；
ValueState = ValueState << 1; //左移1位，将S7～S3变为高5位
//Read control Port
//========== 将C0～C3位置1，即使连接器上是高电平 ，使控制端口为输入端口=====
GetPortVal(m_nportControl, &dwPortVal, 1); //获取端口的当前值
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet & 0x0F0; //取低8位值,将低4位置为0;高4位不变；
ValueGet = ValueGet ^ 0x4; //将低4位中C0、C1、C3置为0，C2置为1;高4位不变；
SetPortVal(m_nportControl, (DWORD)ValueGet, 1); //写出的值中，高4位保持端口原来的值不变，
//低4位是写高电平，即使连接器上是高电平
//=============================================================
unsigned int ValueControl = 0;
GetPortVal(m_nportControl, &dwPortVal, 1);
ValueControl = (unsigned int)dwPortVal;
ValueControl = ValueControl ^ 0x0B; //保持C0,C1,C3位的值与连接器处的值一至；
ValueControl = ValueControl & 0x0F; //去掉高4位值
//get 9bit value
ValueGet = ValueState^ValueControl;
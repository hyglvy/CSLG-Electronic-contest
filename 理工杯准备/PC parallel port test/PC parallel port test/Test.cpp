//������ݶ˿ڵ�ַ
WORD m_nport = (WORD)0x378;
//���Ҫд�����ݶ˿ڵ�ֵWriteValue(���ݷ�ΧΪ0��255)
DWORD m_nValue = (DWORD)WriteValue;
//����WinIo�⺯��SetPortValд�˿�ֵ
SetPortVal(m_nport, m_nValue, 1);//write a BYTE value to an I/O port 

(2)�����ƶ˿����������VCʵ��

//��ÿ��ƶ˿ڵ�ַ
WORD m_nport = (WORD)0x37A;
//��ÿ��ƶ˿ڵ�ֵ,���ָ�λֵ���䣬��Ҫ�����ֵ�ӵ�4λ�������ʹ�������ϵĵ�λ״̬���������ֵһ��
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nport, &temp_dwPortVal, 1); //reads a BYTE value from an I/O port
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //ȡ��8λֵ,����4λ��Ϊ0;��4λ���䣻
temp_aa = temp_aa ^ 0x0B; //����4λ��C0��C1��C3��Ϊ1��C2��Ϊ0;��4λ���䣻//���Ҫд����ƶ˿ڵ�ֵWriteValue(���ݷ�ΧΪ0��15)
unsigned int WriValue;
WriValue = WriteValue & 0x0F; //ȡ��4λ��
temp_aa = temp_aa^WriValue; //��д��ֵ�ĵ�4λ�е�C0��C1��C3ȡ����C2λ���䣬��4λ���ֶ˿�ֵ����
SetPortVal(m_nport, (DWORD)temp_aa, 1); //д����ֵ�У���4λ���ֶ˿�ԭ����ֵ���䣬
//��4λ��д��ʲô��ƽ���������ϼ���ʲô��ƽ 

(3)�����ݶ˿ڼ����ƶ˿���ϳ�12λ���������VCʵ��

//��ö˿ڵ�ַ
WORD m_nportData = (WORD)0x378;
WORD m_nportControl = (WORD)0x37A;
//���Ҫд��˿ڵ�ֵWriteValue(���ݷ�ΧΪ0��4095)
DWORD m_nValue = (DWORD)(WriteValue & 0x0FF);//ȡ��8λֵ
SetPortVal(m_nportData, m_nValue, 1);//write a BYTE value to Data port
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nportControl, &temp_dwPortVal, 1); //reads a BYTE value from an I/O port
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //ȡ��8λֵ,����4λ��Ϊ0;��4λ���䣻
temp_aa = temp_aa ^ 0x0B; //����4λ��C0��C1��C3��Ϊ1��C2��Ϊ0;��4λ���䣻
unsigned int WriValue;
WriValue = WriValue >> 8;//ȡ��4λֵ
temp_aa = temp_aa^WriValue; //��д��ֵ�ĵ�4λ�е�C0��C1��C3ȡ����C2λ���䣬��4λ���ֶ˿�ֵ����
SetPortVal(m_nportControl, (DWORD)temp_aa, 1); //д����ֵ�У���4λ���ֶ˿�ԭ����ֵ���䣬
//��4λ��д��ʲô��ƽ���������ϼ���ʲô��ƽ 

PC���п����������VCʵ��

(1)��״̬�˿����������VCʵ��

Ϊ�˲��Բ��п�״̬�˿ڵ��������룬���Խ����ݶ˿�����Pin2��Pin6���ӵ�״̬�˿�����Pin15��Pin13��Pin12��Pin10��Pin11�ϡ����ŽӺú��ȴ����ݶ˿�������ݣ��ڴ�״̬�˿ںͿ��ƶ˿ڶ������ݣ�����������Ӧ��д�������һ�£����ݷ�ΧΪ0��31��

DWORD dwPortVal;
unsigned int ValueGet = 0;
//��ö˿ڵ�ַ
WORD m_nport = (WORD)0x379;
//��ö˿�����
GetPortVal(m_nport, &dwPortVal, 1);
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet ^ 0x80; //���ֵõ���Stateֵ������������ֵһֱ��
ValueGet = ValueGet & 0xF8; //ȥ��S0 ��S2λ��
ValueGet = ValueGet >> 3; //����3λ����S7��S3��Ϊ��5λ 

(2)�����ƶ˿����������VCʵ��

Ϊ�˲��Բ��пڿ��ƶ˿ڵ��������룬���Խ����ݶ˿�����Pin2��Pin5���ӵ����ƶ˿�����Pin1��Pin14��Pin16��Pin17�� �����ŽӺú��ȴ����ݶ˿�������ݣ��ڴ�״̬�˿ںͿ��ƶ˿ڶ������ݣ�����������Ӧ��д�������һ�£����ݷ�ΧΪ0��15��

//��ö˿ڵ�ַ
WORD m_nport = (WORD)0x37A;
//===== ��C0��C3λ��1����ʹ��������Ϊ�ߵ�ƽ ��ʹ���ƶ˿�Ϊ����˿�=====
DWORD temp_dwPortVal;
unsigned int temp_aa;
GetPortVal(m_nport, &temp_dwPortVal, 1); //��ȡ�˿ڵĵ�ǰֵ
temp_aa = (unsigned int)temp_dwPortVal;
temp_aa = temp_aa & 0x0F0; //ȡ��8λֵ,����4λ��Ϊ0;��4λ���䣻
temp_aa = temp_aa ^ 0x4; //����4λ��C0��C1��C3��Ϊ0��C2��Ϊ1;��4λ���䣻
SetPortVal(m_nport, (DWORD)temp_aa, 1); //д����ֵ�У���4λ���ֶ˿�ԭ����ֵ���䣬
//��4λ��д�ߵ�ƽ����ʹ���������Ǹߵ�ƽ
//=============================================================
unsigned int ValueGet = 0;
DWORD dwPortVal;
//��ö˿�����
GetPortVal(m_nport, &dwPortVal, 1);
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet ^ 0x0B; //����C0,C1,C3λ��ֵ������������ֵһ����
ValueGet = ValueGet & 0x0F; //ȥ����4λֵ  

(3)�����ƶ˿ڼ�״̬�˿���ϳ�9λ���������VCʵ��

Ϊ�˲��Բ��пڵ��������룬���Խ����ݶ˿�����Pin2��Pin9���ӵ����ƶ˿�����Pin1��Pin14��Pin16��Pin17��״̬�˿�����Pin15��Pin13��Pin12��Pin10�� ��Pin11�������ӵ��������GND�����ա����ŽӺú��ȴ����ݶ˿�������ݣ��ڴ�״̬�˿ںͿ��ƶ˿ڶ������ݣ�����������Ӧ��д�������һ�£���Pin11�������ӵ��������GNDʱ�����ݷ�ΧΪ0��255����Pin11��������ʱ�����ݷ�ΧΪ256��511��

unsigned int ValueGet = 0;
//��ö˿ڵ�ַ
WORD m_nportState = (WORD)0x379;
WORD m_nportControl = (WORD)0x37A;
//Read State Port
DWORD dwPortVal;
unsigned int ValueState = 0;
GetPortVal(m_nportState, &dwPortVal, 1);
ValueState = dwPortVal;
ValueState = ValueState ^ 0x80; //���ֵõ���Stateֵ������������ֵһֱ��
ValueState = ValueState & 0xF8; //ȥ��S0 ��S2λ��
ValueState = ValueState << 1; //����1λ����S7��S3��Ϊ��5λ
//Read control Port
//========== ��C0��C3λ��1����ʹ���������Ǹߵ�ƽ ��ʹ���ƶ˿�Ϊ����˿�=====
GetPortVal(m_nportControl, &dwPortVal, 1); //��ȡ�˿ڵĵ�ǰֵ
ValueGet = (unsigned int)dwPortVal;
ValueGet = ValueGet & 0x0F0; //ȡ��8λֵ,����4λ��Ϊ0;��4λ���䣻
ValueGet = ValueGet ^ 0x4; //����4λ��C0��C1��C3��Ϊ0��C2��Ϊ1;��4λ���䣻
SetPortVal(m_nportControl, (DWORD)ValueGet, 1); //д����ֵ�У���4λ���ֶ˿�ԭ����ֵ���䣬
//��4λ��д�ߵ�ƽ����ʹ���������Ǹߵ�ƽ
//=============================================================
unsigned int ValueControl = 0;
GetPortVal(m_nportControl, &dwPortVal, 1);
ValueControl = (unsigned int)dwPortVal;
ValueControl = ValueControl ^ 0x0B; //����C0,C1,C3λ��ֵ������������ֵһ����
ValueControl = ValueControl & 0x0F; //ȥ����4λֵ
//get 9bit value
ValueGet = ValueState^ValueControl;
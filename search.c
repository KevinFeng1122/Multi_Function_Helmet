#include "reg51.h"

sbit  ZD_BUSY =P1^2; //����Һ��������"æ"(BUSY)�ź�,��������������һλ����������.   
sbit sw1=P3^7;
sbit sw2=P3^6; 
sbit sw3=P3^5;
sbit sw4=P3^4;
sbit sw5=P3^3;
sbit sw6=P3^2;
sbit P1_0=P1^0;
sbit Commu_1=P1^7;//�������ƶԽ�ģ�鿪�ص������ܵ�����P31
#define TXD P1_0
   

unsigned char flag=0,temp=45,place=0;

//��ʱ����*
void Delay2cp(unsigned char i)
{
     while(--i);                     //�պ�����ָ������	   .
}

//������дһ���ֽ�
void WByte(unsigned char input)
{
     unsigned char i=8;
     TXD=(bit)0;                     //������ʼλ
     Delay2cp(39);                  //����8λ����λ
     while(i--)
     {
         TXD=(bit)(input&0x01);     //�ȴ���λ
         Delay2cp(36);
         input=input>>1;
     }
     TXD=(bit)0;                      //����У��λ(��)
	 Delay2cp(48);
     TXD=(bit)1;                     //���ͽ���λ
     Delay2cp(46);
}

void FSsj(unsigned char A)
//ͨ��Ӳ�����ڷ���1�ֽ�
{
	 while(ZD_BUSY);       // ����ն�"æ",��ȴ�
 	 WByte(A);	// ����һ�ֽ�
}
//����FSsj(0x1B);FSsj(0x31);
//=========================================================================================
void CSH( )//��ʼ��
{
	FSsj(0x1B);
	FSsj(0x40);
}
//����CSH(0)
void QPM(unsigned char ys)
//����ĻΪys=0(��ɫ),7(��ʾɫ)
{
	FSsj(0x1B);
	FSsj(0x51);
	FSsj(ys);
}

void YS(unsigned char n)
//��ʱ0.1�� �� 25.5�룬n=1 �� 255
{
	FSsj(0x1B);
	FSsj(0x6C);
	FSsj(n);
}
 // =======================================================================================
 //void JSSJ(unsigned char ys)
//=========================================================================================

void serialinit()
{
	TMOD=0x20;  //���ö�ʱ��1Ϊ������ʽ2
	TH1=0xfd;   //װ��ֵ
	TL1=0xfd;
	TR1=1;     //������ʱ��1
	REN=1;	  // �����������
	SM0=0;	   //���ô��ڹ�����ʽ
	SM1=1;
	EA=1;//���жϴ�
	ES=1;//�����жϴ�
}
 void main(void)
 {	
 	int a=0,b=0,help=0;
   	serialinit();
	while(sw5==1);  
	QPM(0);	
    CSH();
	QPM(0);	
    CSH();
	FSsj(0x1b);FSsj(0x6a);FSsj(0x00);FSsj(0x01);FSsj(0x00);FSsj(0x01);FSsj(0x00);FSsj(0x7f);FSsj(0x00);FSsj(0x3f); //ȫ�����ο�
	FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x04);FSsj(0x00);FSsj(0x10);FSsj(0x1b);FSsj(0x33);
	             FSsj(0x20);FSsj(0x21);FSsj(0x22);FSsj(0x23);FSsj(0x24);FSsj(0x25);FSsj(0x26);FSsj(0x27);FSsj(0x28);FSsj(0x29);	 //�����Ƽ���ѧ������Ŀ
	FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x10);FSsj(0x00);FSsj(0x28);
				FSsj(0x2a);FSsj(0x2b);FSsj(0x2c);FSsj(0x2d);FSsj(0x2e);FSsj(0x2f);FSsj(0x30);FSsj(0x31); //����ͷ���Ѿ�ģ��
	YS(30);		 
	while(1)
	{		
	    QPM(0);	
	    CSH();
		//keep/turn the communication module off
		Commu_1=1;//P31=high	    
		FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x09);FSsj(0x00);FSsj(0x02);FSsj(0x1b);FSsj(0x33);
		FSsj (0x43);FSsj(0x44);FSsj(0x46);FSsj(0x45);FSsj(0x4c);FSsj(0x4d);FSsj(0x4e);FSsj(0x4f);
		FSsj(0x50);FSsj(0x51);FSsj(0x52);FSsj(0x53);//sw1.�鿴����ʹ��˵��
		FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x09);FSsj(0x00);FSsj(0x1e);
		FSsj (0x43);FSsj(0x44);FSsj(0x47);FSsj(0x45);FSsj(0x54);FSsj(0x55);FSsj(0x56);FSsj(0x57);
		FSsj(0x58);FSsj(0x59);FSsj(0x5a);FSsj(0x5e);//sw2.��ʼ����������Ա
	   	while(sw1==1&&sw2==1)
		{
			if(temp==0xbf)
			{
				help=1;
				break;
			}
		}
		if(sw1==0)
		{
			//����˵��
			QPM(0);	
    		CSH();
			FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x09);FSsj(0x00);FSsj(0x02);FSsj(0x1b);FSsj(0x33);
			FSsj(0x43);FSsj(0x44);FSsj(0x4b);FSsj(0x45);FSsj(0x7d);FSsj(0x7e);FSsj(0x7f);FSsj(0x80);
			FSsj(0x81);FSsj(0x82);FSsj(0x83);FSsj(0x84);FSsj(0x74);FSsj(0x43);FSsj(0x44);FSsj(0x46);
			FSsj(0x45);FSsj(0x85);FSsj(0x86);FSsj(0x87);FSsj(0x88);FSsj(0x89);FSsj(0x8a);FSsj(0x74);
			FSsj(0x43);FSsj(0x44);FSsj(0x47);FSsj(0x45);FSsj(0x8b);FSsj(0x8c);FSsj(0x8d);FSsj(0x8e);
			FSsj(0x8f);FSsj(0x90);FSsj(0x9a);	//sw6.����ʱ�������˵���sw1.�鿴�����ص㣬sw2.�鿴ʵʱ����
			while(sw6==1);
			continue;
		}
		if(sw2==0||help==1)
		{
			help=0;
			  //�Ѿ��С�����
			QPM(0);	
    		CSH();
			FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x1c);FSsj(0x00);FSsj(0x15);FSsj(0x1b);FSsj(0x33);
			FSsj(0x2e);FSsj(0x2f);FSsj(0x99);FSsj(0xe8);FSsj(0xe8);FSsj(0xe8);FSsj(0xe8);
			while(temp!=0xcf&&sw6==1)
			{
				FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x40);FSsj(0x00);FSsj(0x15);
				YS(10);FSsj(0xe8);
				SBUF=0Xee;
				while(TI!=1);
					TI=0;
				YS(10);FSsj(0xe8);
				if(temp==0xcf||sw6==0)
				{
					RI=0;
					break;
				}
				SBUF=0Xee;
				while(TI!=1);
					TI=0;
				YS(10);FSsj(0xe8);
				if(temp==0xcf||sw6==0)
				{
					RI=0;
					break;
				}
				SBUF=0Xee;
				while(TI!=1);
					TI=0;
				YS(10);FSsj(0xe8);
				if(temp==0xcf||sw6==0)
				{
					RI=0;
					break;
				}
				SBUF=0Xee;
				while(TI!=1);
					TI=0;
			}
			if(sw6==0)
				continue;
			RI=0;
				//�ӵ�����źţ��Ƿ�鿴�� sw4.�鿴 sw3.���鿴
			QPM(0);	
    		CSH();
			FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x09);FSsj(0x00);FSsj(0x00);FSsj(0x1b);FSsj(0x33);
			FSsj(0x6e);FSsj(0x6f);FSsj(0x70);FSsj(0x71);FSsj(0x72);FSsj(0x73);FSsj(0x74);FSsj(0x75);
			FSsj(0x76);FSsj(0x77);FSsj(0x78);FSsj(0x79);
			FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x16);FSsj(0x00);FSsj(0x1c);
			FSsj(0x43);FSsj(0x44);FSsj(0x49);FSsj(0x45);FSsj(0x7b);FSsj(0x7c);
			FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x16);FSsj(0x00);FSsj(0x2c);
			FSsj(0x43);FSsj(0x44);FSsj(0x48);FSsj(0x45);FSsj(0x7a);FSsj(0x7b);FSsj(0x7c);
			
			//the search teminal's communication module has been turned on;the wearer has been requested to communicate to you.
			Commu_1=0;//P31=low

			while(sw4==1&&sw3==1);
			if(sw4==0)
			{
				//������Ա��Ϣ
				QPM(0);	
    			CSH();
				FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x09);FSsj(0x00);FSsj(0x00);
				FSsj(0x1b);FSsj(0x33);FSsj(0x32);FSsj(0x33);FSsj(0x34);FSsj(0x35);FSsj(0x36);
				FSsj(0x37);FSsj(0x38);FSsj(0x39);FSsj(0x3a);

				//�����ص㣺
				 
				//ʵʱ�¶ȣ�
				
				while(sw6==1)
				{
					if(sw1==0)
					{
						SBUF=0Xbb;
						while(TI!=1);
							TI=0;
						while(sw5==1);
						//(��ӡ�ص�)
						if(temp==0xbd)
						{
							FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x08);FSsj(0x00);FSsj(0x10);
							FSsj(0x3d);FSsj(0x3e);FSsj(0x9a);FSsj(0xa0);FSsj(0xa1);FSsj(0xa2);FSsj(0xa3);FSsj(0xa4);FSsj(0xa5);FSsj(0xa6);
							RI=0;
						}
						else
						{
							FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x10);FSsj(0x00);FSsj(0x10);
							FSsj(0x3b);FSsj(0x3c);FSsj(0x3d);FSsj(0x3e);FSsj(0x9a);FSsj(0x64);FSsj(0x65);FSsj(0x66);
							RI=0;	
						}
					}
					if(sw2==0)
					{
						SBUF=0Xaa;
						while(TI!=1);
							TI=0;
						while(sw5==1);
						//(��ӡ�¶�)
						FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x10);FSsj(0x00);FSsj(0x20);
				 		FSsj(0x3f);FSsj(0x40);FSsj(0x41);FSsj(0x42);FSsj(0x9a);
						a=temp/10;
						FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x48);FSsj(0x00);FSsj(0x26);
						FSsj(0x1b);FSsj(0x31);
						switch(a)
						{
							case 0:FSsj('0');  break;
							case 1:FSsj('1');  break;
							case 2:FSsj('2');  break;
							case 3:FSsj('3');  break;
							case 4:FSsj('4');  break;
							case 5:FSsj('5');  break;
							case 6:FSsj('6');  break;
							case 7:FSsj('7');  break;
							case 8:FSsj('8');  break;
							case 9:FSsj('9');  break;
						}
					    b=temp%10;
						switch(b)
						{
							case 0:FSsj('0');  break;
							case 1:FSsj('1');  break;
							case 2:FSsj('2');  break;
							case 3:FSsj('3');  break;
							case 4:FSsj('4');  break;
							case 5:FSsj('5');  break;
							case 6:FSsj('6');  break;
							case 7:FSsj('7');  break;
							case 8:FSsj('8');  break;
							case 9:FSsj('9');  break;
						}
						FSsj(0x1b);FSsj(0x7a);FSsj(0x00);FSsj(0x55);FSsj(0x00);FSsj(0x20);
						FSsj(0x1b);FSsj(0x33);FSsj(0x69);
					}
				}
				SBUF=0Xcc;
				while(TI!=1);
					TI=0;	
			}
		}						
	}
}
 
void ser() interrupt 4
{										
	temp=SBUF;
	RI=0;
}						 
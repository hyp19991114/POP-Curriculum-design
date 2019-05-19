/* *********************************************************************
*                  ������̳�������ۺ�Ӧ��
*    ѡ    ��  �豸����ϵͳ Equipment Management System
*    ��    ��  ��Զ��        ѧ    ��  183401050225
*    ��    ��  ���1802
*    ���ʱ��  2019��5��31��
* ******************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct _Date
{
	int year,month,date;
};
typedef struct _Equipment
{
	int id;    // �豸���(8λ��)
	char name[50];   // ��������
	char type[50];   // �ͺŹ��
	double price;    // ����
	struct _Date boughtDate;    // ��������
	char person[50];    // ������
	char status[50];    // ʹ��״��
	char postscript[50];    // ��ע( 50���� )
}Equipment;

void ChangeColor();

int main()
{
	char choice;      // choice �������û������ָ�����
	while(true)
	{
		system("cls");            // ����
		system("title �豸����ϵͳ");     // ���Ĵ��ڱ���
		puts("     * * * * * * * *      �豸����ϵͳ      * * * * * * * *     \n");
		puts("     1 - ¼������Ϣ            2 - ���Ҽ�¼        3 - �޸�������Ϣ");
		puts("     4 - �޸Ĵ�����������ɫ    5 - �������м�¼    6 - �˳�ϵͳ\n");
		//���롢��ʾ���޸ġ����ҡ���ӡ��˳�

		printf("��ѡ��");
		choice = getchar();
		fflush(stdin);
		if(choice == '6')
			break;
		else switch(choice)
		{
		case '4':ChangeColor();break;
		default:puts("����������������롣");system("pause");break;
		}

	}


	return 0;
}

/* *********************************************************************
*    ��������ChangeColor
*    �������ܣ����Ĵ��ڱ�����ɫ��������ɫ
* ******************************************************************** */
void ChangeColor()
{
	system("title �豸����ϵͳ  -  ��ɫ�޸�");
	char ColorChoice[3]="";
	puts("��������Ҫ���ĵı�����������ɫ���ַ������ִ�Сд���Իس�������");
	puts("    0 = ��ɫ	   8 = ��ɫ");
	puts("    1 = ��ɫ	   9 = ����ɫ");
	puts("    2 = ��ɫ	   A = ����ɫ");
	puts("    3 = ǳ��ɫ	   B = ��ǳ��ɫ");
	puts("    4 = ��ɫ	   C = ����ɫ");
	puts("    5 = ��ɫ	   D = ����ɫ");
	puts("    6 = ��ɫ	   E = ����ɫ");
	puts("    7 = ��ɫ	   F = ����ɫ");
	puts("ʾ��: ����\"fc\"�����ñ���Ϊ����ɫ������Ϊ����ɫ��");
	puts("����ָ�Ĭ����ɫ��������\"**\"���������˵���������\"##\"��");
	while(true)
	{
		ColorChoice[0]=getchar();
		ColorChoice[1]=getchar();
		fflush(stdin);
		if(strcmp(ColorChoice,"**")==0)     // �ָ�Ĭ����ɫ
		{
			system("color 07");
			break;
		}
		else if(strcmp(ColorChoice,"##")==0)    // �������˵�
			break;
		else if(!isxdigit(ColorChoice[0]) || !isxdigit(ColorChoice[1]))  // �������
			printf("����������������룺");
		else if(ColorChoice[0]==ColorChoice[1])  // ����������ͬɫ
			printf("���ܽ���������������Ϊͬһ��ɫ�����������룺");
		else
		{
			char ColorMode[10]="color ";
			strcat(ColorMode,ColorChoice);
			system(ColorMode);
			break;
		}
	}
	return;
}
/* *********************************************************************
*    ��������InputFromFile
*    �������ܣ����ļ�����������Ϣ
* ******************************************************************** */
void InputFromFile()
{

}






/* *********************************************************************
*    ��������111
*    �������ܣ�111
*    �ӿڲ�����111
*    ����ֵ��111
* ******************************************************************** */
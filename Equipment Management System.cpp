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
	int year,month,day;
};
typedef struct _Equipment
{
	int id;    // �豸���(8λ��)
	char name[50];   // ��������
	char type[50];   // �ͺŹ��
	double price;    // ����
	struct _Date boughtDate;    // ��������
	char person[50];    // ������
	char status[100];    // ʹ��״��
	char postscript[110];    // ��ע(50����)
	struct _Equipment *pre,*next;   // ǰ������ָ��
	_Equipment()   // ���캯����ʼ������ָ��ΪNULL
	{
		pre=NULL;
		next=NULL;
	}
}equip;

void ChangeColor();
inline void PrintDirection();
void InputFromFile();
equip *head=new equip;   // �˳������������"��ͷ���"��˫������
bool isSaved=false;   // true:�ѱ��������   false:�ޱ����¼

int main()
{
	char choice;      // choice �������û������ָ�����
	while(true)
	{
		system("cls");     // ����
		system("title �豸����ϵͳ");     // ���Ĵ��ڱ���
		PrintDirection();

		choice = getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':InputFromFile();break;
		case '2':break;
		case '3':break;
		case '4':break;
		case '5':break;
		case '6':break;
		case '7':break;
		case '8':break;
		case '9':ChangeColor();break;
		case '0':break;

		default:puts("����������������롣");system("pause");break;
		}

	}


	return 0;
}

/* *********************************************************************
|    ��������ChangeColor
|    �������ܣ����Ĵ��ڱ�����ɫ��������ɫ
\  ******************************************************************** */
void ChangeColor()
{
	system("title �豸����ϵͳ  -  ��ɫ�޸�");
	char ColorChoice[3]="";
	puts("��������Ҫ���ĵı�����������ɫ���ַ������ִ�Сд���Իس�������");
	puts("    0 = ��ɫ	     8 = ��ɫ");
	puts("    1 = ��ɫ	     9 = ����ɫ");
	puts("    2 = ��ɫ	     A = ����ɫ");
	puts("    3 = ǳ��ɫ     B = ��ǳ��ɫ");
	puts("    4 = ��ɫ	     C = ����ɫ");
	puts("    5 = ��ɫ	     D = ����ɫ");
	puts("    6 = ��ɫ	     E = ����ɫ");
	puts("    7 = ��ɫ	     F = ����ɫ");
	puts("ʾ��: ����\"fc\"�����ñ���Ϊ����ɫ������Ϊ����ɫ��");
	puts("����ָ�Ĭ����ɫ��������\"**\"���������˵���������\"##\"��");
	printf(">>> ");
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
|    ��������InputFromFile
|    �������ܣ����ļ�����������Ϣ
\  ******************************************************************** */
void InputFromFile()
{
	system("title �豸����ϵͳ - ���ļ�¼����Ϣ");
	puts("�������ļ������ļ��ĵ�ַ���Իس�������ע�⣺��ַ�е�'\\'Ӧд��\"\\\\\"��");
	printf(">>> ");
	char fileName[200];       // �ļ������ַ
	scanf("%[^\n]",fileName);
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL)   // δ�򿪳ɹ�
	{
		puts("�޷���ָ�����ļ��������ԡ�");
		system("pause");
		return;
	}
	equip *p=head;
	while(p->next!=NULL)
	{
		p=p->next;       // ������β��ʼ���������
	}
	char temp[500];   // �ٶ�һ�����ݵ���󳤶�Ϊ500���ַ�
	equip *s;
	int cnt=0;   // ��¼������������
	while(fgets(temp,500,fp)!=NULL)
	{
		s=new equip;
		p->next=s;
		s->pre=p;
		sscanf(temp,"%d %s %s %lf %d-%d-%d %s %s %s",&s->id,s->name,s->type,
			&s->price,&s->boughtDate.year,&s->boughtDate.month,&s->boughtDate.day,
			s->person,s->status,s->postscript);
		p=s;
		cnt++;
	}
	printf("�ɹ����� %d �����ݡ�",cnt);
	system("pause");
	return;
}

/* *********************************************************************
|    ��������PrintDirection
|    �������ܣ������ʾ��Ϣ
\  ******************************************************************** */
inline void PrintDirection()
{
	printf("     * * * * *  �� �� �� �� ϵ ͳ  * * * * *\n\n");
	puts("     * * * * * *   ���� / ���   * * * * * *");
	puts("             1 - ���ļ�¼����Ϣ");
	puts("             2 - ����¼������Ϣ");
	puts("             3 - ����һ������Ϣ");
	puts("     * * * * * *   ��ѯ / ����   * * * * * *");
	puts("             4 - �鿴��Ϣ");
	puts("             5 - �ؼ��ֲ���");
	puts("             6 - ����������Ϣ");
	puts("     * * * * * *   �޸� / ɾ��   * * * * * *");
	puts("             7 - �޸���Ϣ");
	puts("             8 - ɾ����Ϣ");
	puts("     * * * * * *     ϵͳ����    * * * * * *");
	puts("             9 - �޸Ĵ�����������ɫ");
	puts("             0 - �˳�ϵͳ");
	printf("��ѡ��");
}



/* *********************************************************************
|    ��������111
|    �������ܣ�111
|    �ӿڲ�����111
|    ����ֵ��111
\  ******************************************************************** */
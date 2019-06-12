/* *********************************************************************
|                  ������̳�������ۺ�Ӧ��
|    ѡ    ��  �豸����ϵͳ Equipment Management System
|    ��    ��  ��Զ��        ѧ    ��  183401050225
|    ��    ��  ���1802
|    ���ʱ��  2019��6��9��
\  ******************************************************************** */

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

// ����������ȫ�ֱ�������
inline void PrintDirection();
void InputFromFile();
void InputFromStdin();
void AddOnePiece();
void Display();
void PutsData();
void CheckOnePiece();
void KeywordSearch();
void SaveData();
void Modify();
void DeleteOnePiece();
void ChangeColor();
bool Quit();
equip *head=new equip;   // �˳������������"��ͷ���"��˫������
equip *rear=head;     // ��βָ��
bool isSaved=false;   // true:�ѱ�������   false:��δ����

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
		case '1':system("cls"); InputFromFile();  break;   // ���ļ�¼����Ϣ
		case '2':system("cls"); InputFromStdin(); break;   // ����¼������Ϣ
		case '3':system("cls"); AddOnePiece();    break;   // ����һ������Ϣ
		case '4':system("cls"); Display();        break;   // �鿴��Ϣ
		case '5':system("cls"); KeywordSearch();  break;   // �ؼ��ֲ���
		case '6':system("cls"); SaveData();       break;   // ����������Ϣ
		case '7':system("cls"); Modify();         break;   // �޸���Ϣ
		case '8':system("cls"); DeleteOnePiece(); break;   // ɾ����Ϣ
		case '9':system("cls"); ChangeColor();    break;   // �޸Ĵ�����������ɫ
		case '0':system("cls");
			if(Quit()==true)
				return 0;   // �˳�ϵͳ
			else
				break;

		default:puts("����������������롣"); system("pause"); break;
		}
	}

	return 0;
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
	puts("             0 - �˳�ϵͳ\n");
	printf("��ѡ��");
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
	fflush(stdin);
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL)   // δ�򿪳ɹ�
	{
		puts("�޷���ָ�����ļ��������ԡ�");
		system("pause");
		return;
	}
	equip *p=rear;    // ������β��ʼ���������
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
	if(cnt)
	{
		printf("�ɹ����� %d �����ݡ�",cnt);
		isSaved=false;   // �������ݱ���״̬��δ���棩
		rear=p;   // ������βָ��
	}
	else
		printf("δ�ܳɹ���ȡ���ݣ������ļ� %s �Ƿ�Ϊ�ա�\n",fileName);
	fclose(fp);
	system("pause");
	return;
}

/* *********************************************************************
|    ��������InputFromStdin
|    �������ܣ�����Ļ����¼����Ϣ
\  ******************************************************************** */
void InputFromStdin()
{
	system("title �豸����ϵͳ - ����¼������Ϣ");
	puts("�밴���¸�ʽ¼����Ϣ����Crtl+Z�����س��������롣�������ڸ�ʽΪyyyy-mm-dd");
	puts("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע");
	equip *p=rear;    // ������β��ʼ���������
	char temp[500];   // �ٶ�һ�����ݵ���󳤶�Ϊ500���ַ�
	equip *s;
	int cnt=0;   // ��¼������������
	while(scanf("%[^\n]",temp)!=EOF)
	{
		getchar();   // ��������س�
		s=new equip;
		p->next=s;
		s->pre=p;
		sscanf(temp,"%d %s %s %lf %d-%d-%d %s %s %s",&s->id,s->name,s->type,
			&s->price,&s->boughtDate.year,&s->boughtDate.month,&s->boughtDate.day,
			s->person,s->status,s->postscript);
		p=s;
		cnt++;
	}
	if(cnt)
	{
		printf("�ɹ�¼�� %d �����ݡ�",cnt);
		isSaved=false;   // �������ݱ���״̬��δ���棩
		rear=p;   // ������βָ��
	}
	else
		printf("δ¼���κ����ݡ�");
	system("pause");
	return;
}

/* *********************************************************************
|    ��������AddOnePiece
|    �������ܣ�����һ������Ϣ
\  ******************************************************************** */
void AddOnePiece()
{
	system("title �豸����ϵͳ - ����һ������Ϣ");
	equip *p=rear,*s;
	s=new equip;
	p->next=s;
	s->pre=p;
	puts("������������Ϣ��");
	printf("�豸���: ");
	scanf("%d",&s->id);fflush(stdin);
	printf("��������: ");
	scanf("%s",s->name);fflush(stdin);
	printf("�ͺŹ��: ");
	scanf("%s",s->type);fflush(stdin);
	printf("����: ");
	scanf("%lf",&s->price);fflush(stdin);
	printf("�������ڣ���ʽΪyyyy-mm-dd: ");
	scanf("%d-%d-%d",&s->boughtDate.year,&s->boughtDate.month,&s->boughtDate.day);fflush(stdin);
	printf("������: ");
	scanf("%s",s->person);fflush(stdin);
	printf("ʹ��״��: ");
	scanf("%s",s->status);fflush(stdin);
	printf("��ע: ");
	scanf("%s",s->postscript);fflush(stdin);

	printf("\n�ɹ����� 1 ����Ϣ��");
	rear=s;   // ������βָ��
	isSaved=false;   // �������ݱ���״̬��δ���棩
	system("pause");
	return;
}

/* *********************************************************************
|    ��������Display
|    �������ܣ��鿴��Ϣ��ѡ��˵�
\  ******************************************************************** */
void Display()
{
	system("title �豸����ϵͳ - �鿴��Ϣ");
	if(head->next==NULL)   // ��ͷ����⣬����Ϊ��
	{
		puts("\n��ǰϵͳ�����޼�¼��\n");
		system("pause");
		return;
	}

	char choice;
	puts("\t1 - �鿴ȫ����Ϣ");
	puts("\t2 - �鿴ָ����ŵ���Ϣ");
	puts("\t0 - �������˵�");
	printf("��ѡ��");
	while(true)
	{
		choice = getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':PutsData();return;
		case '2':CheckOnePiece();return;
		case '0':return;

		default:printf("����������������룺");
		}
	}
}

/* *********************************************************************
|    ��������PutsData
|    �������ܣ������м�¼�������Ļ
\  ******************************************************************** */
void PutsData()
{
	system("title �豸����ϵͳ - �鿴ȫ����Ϣ");
	equip *p=head->next;
	int cnt=0;   // cnt��¼���ݸ���
	printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
	while(p!=NULL)
	{
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		p=p->next;
		cnt++;
	}
	printf("\n������� %d ����Ϣ��",cnt);

	system("pause");
	return;
}

/* *********************************************************************
|    ��������CheckOnePiece
|    �������ܣ��鿴�����һ����Ϣ
\  ******************************************************************** */
void CheckOnePiece()
{
	system("title �豸����ϵͳ - �鿴ָ����ŵ���Ϣ");
	int foundId;
	printf("���������ѯ�ı�ţ�");
	scanf("%d",&foundId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=foundId)
		p=p->next;
	if(p==NULL)
	{
		printf("δ��ѯ����� %d ��Ӧ����Ϣ���Ƿ�¼�룿\n",foundId);
		puts("\t1 - ¼��\t2 - ����");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':AddOnePiece();break;
		case '2':break;
		default:printf("������󣬼����������˵���");system("pause");break;
		}
	}
	else
	{
		printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		system("pause");
	}

	return;
}

/* *********************************************************************
|    ��������KeywordSearch
|    �������ܣ��������ؼ��ֲ�����Ϣ
\  ******************************************************************** */
void KeywordSearch()
{
	system("title �豸����ϵͳ - �ؼ��ֲ���");
	if(head->next==NULL)   // ��ͷ����⣬����Ϊ��
	{
		puts("\n��ǰϵͳ�����޼�¼���޷����ҡ�\n");
		system("pause");
		return;
	}
	puts("����������ҵ����ݣ�ֻ������һ���ؼ��֣��Իس�������");
	printf(">>> ");
	char keyword[100],temp[500];
	scanf("%s",keyword);
	fflush(stdin);
	equip *p=head->next;
	int cnt=0;   // ��¼���ҵ�����������
	while(p!=NULL)
	{
		sprintf(temp,"%d %s %s %lf %d-%d-%d %s %s %s",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		if(strstr(temp,keyword))
		{
			if(cnt==0)   // ��һ�β��ҵ��������ͷ
				printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
			printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
				p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
				p->person,p->status,p->postscript);
			cnt++;
		}
		p=p->next;
	}
	if(cnt==0)   // δ���ҵ�
		printf("\nδ���ҵ��� %s ����Ϣ��",keyword);
	else
		printf("\n�����ҵ� %d ����Ϣ��",cnt);

	system("pause");
	return;
}

/* *********************************************************************
|    ��������SaveData
|    �������ܣ������м�¼������ļ���
\  ******************************************************************** */
void SaveData()
{
	system("title �豸����ϵͳ - ����������Ϣ");
	if(head->next==NULL)   // ��ͷ����⣬����Ϊ��
	{
		puts("\n��ǰϵͳ�����޼�¼����������Ϣ���ٳ��Ա��档\n");
		system("pause");
		return;
	}

	puts("�������ļ������ļ��ĵ�ַ���Իس�������ע�⣺��ַ�е�'\\'Ӧд��\"\\\\\"��");
	puts("���ر���ʾ������򿪴��������е��ļ������ļ�������ա�");
	printf(">>> ");
	char fileName[200];       // �ļ������ַ
	scanf("%[^\n]",fileName);
	fflush(stdin);
	FILE *fp=fopen(fileName,"w");
	if(fp==NULL)   // δ�򿪳ɹ�
	{
		puts("ϵͳ�����޷���ָ�����ļ��������ԡ�");
		system("pause");
		return;
	}
	equip *p=head->next;
	int cnt=0;   // cnt��¼���ݸ���
	while(p!=NULL)
	{
		fprintf(fp,"%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		p=p->next;
		cnt++;
	}
	printf("�ɹ����� %d �����ݵ� %s ��",cnt,fileName);

	isSaved=true;   // �������ݱ���״̬���ѱ��棩
	fclose(fp);
	system("pause");
	return;
}

/* *********************************************************************
|    ��������Modify
|    �������ܣ��޸�ָ����ŵ���Ϣ
\  ******************************************************************** */
void Modify()
{
	system("title �豸����ϵͳ - �޸���Ϣ");
	if(head->next==NULL)   // ��ͷ����⣬����Ϊ��
	{
		puts("\n��ǰϵͳ�����޼�¼���޷��޸ġ�\n");
		system("pause");
		return;
	}
	int modId;
	printf("��������Ҫ�޸ĵ���Ϣ�ı�ţ�");
	scanf("%d",&modId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=modId)
		p=p->next;
	if(p==NULL)     // û����һ�����޷��޸�
	{
		printf("δ�ҵ���� %d ��Ӧ����Ϣ���޷��޸ġ�\n",modId);
		system("pause");
	}
	else   // �ҵ��ˣ�׼���޸�
	{
		puts("\n��ǰ���ݣ�");
		printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);

		printf("\n\t1 - �޸���Ϣ\t2 - �������˵�\n");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':{
			puts("\n�������޸ĺ�����ݣ�");
			printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
			scanf("%d %s %s %lf %d-%d-%d %s %s %s",&p->id,p->name,p->type,
				&p->price,&p->boughtDate.year,&p->boughtDate.month,&p->boughtDate.day,
				p->person,p->status,p->postscript);
			fflush(stdin);
			printf("�޸ĳɹ���");
			isSaved=false;   // �������ݱ���״̬��δ���棩
			system("pause");break;
				 }
		case '2':break;
		default:printf("���������Ϣδ�޸ġ������������˵���\n");
			system("pause");break;
		}
	}
	return;
}

/* *********************************************************************
|    ��������DeleteOnePiece
|    �������ܣ�ɾ��ָ����ŵ���Ϣ
\  ******************************************************************** */
void DeleteOnePiece()
{
	system("title �豸����ϵͳ - ɾ����Ϣ");
	if(head->next==NULL)   // ��ͷ����⣬����Ϊ��
	{
		puts("\n��ǰϵͳ�����޼�¼���޷�ɾ����\n");
		system("pause");
		return;
	}
	int delId;
	printf("��������Ҫɾ������Ϣ�ı�ţ�");
	scanf("%d",&delId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=delId)
		p=p->next;
	if(p==NULL)     // û����һ�����޷�ɾ��
	{
		printf("δ�ҵ���� %d ��Ӧ����Ϣ���޷�ɾ����\n",delId);
		system("pause");
	}
	else   // �ҵ��ˣ�׼��ɾ��
	{
		printf("�豸���	��������	�ͺŹ��	����	��������	������	ʹ��״��	��ע\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		printf("\n\t1 - ȷ��ɾ��\t2 - ����\n");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':p->pre->next=p->next;
			if(p->next)      // p�������һ�����
				p->next->pre=p->pre;
			delete p;
			printf("��� %d ��Ӧ��Ϣ��ɾ����",delId);
			isSaved=false;   // �������ݱ���״̬��δ���棩
			system("pause");break;
		case '2':break;
		default:printf("���������Ϣδɾ���������������˵���\n");
			system("pause");break;
		}
	}
	return;
}

/* *********************************************************************
|    ��������ChangeColor
|    �������ܣ����Ĵ��ڱ�����ɫ��������ɫ
\  ******************************************************************** */
void ChangeColor()
{
	system("title �豸����ϵͳ  -  ��ɫ�޸�");
	char ColorChoice[3]="";
	puts("��������Ҫ���ĵı�����������ɫ���ַ������ִ�Сд���Իس�������\n");
	puts("    0 = ��ɫ       8 = ��ɫ");
	puts("    1 = ��ɫ       9 = ����ɫ");
	puts("    2 = ��ɫ       A = ����ɫ");
	puts("    3 = ǳ��ɫ     B = ��ǳ��ɫ");
	puts("    4 = ��ɫ       C = ����ɫ");
	puts("    5 = ��ɫ       D = ����ɫ");
	puts("    6 = ��ɫ       E = ����ɫ");
	puts("    7 = ��ɫ       F = ����ɫ\n");
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
			printf("�ѻָ�Ĭ����ɫ��");
			system("pause");
			break;
		}
		else if(strcmp(ColorChoice,"##")==0)    // �������˵�
			break;
		else if(!isxdigit(ColorChoice[0]) || !isxdigit(ColorChoice[1]))  // �������
			printf("����������������룺");
		else if(toupper(ColorChoice[0])==toupper(ColorChoice[1]))  // ����������ͬɫ
			printf("���ܽ���������������Ϊͬһ��ɫ�����������룺");
		else
		{
			char ColorMode[10]="color ";
			strcat(ColorMode,ColorChoice);
			system(ColorMode);
			printf("��ɫ���óɹ���");
			system("pause");
			break;
		}
	}
	return;
}

/* *********************************************************************
|    ��������Quit
|    �������ܣ��˳�ϵͳǰ�����Ϣ�Ƿ��Ѿ����浽�ļ�����δ���������û����档
|              �˳�ǰ��������ռ�ռ��ͷš�
|    ����ֵ��true:Ӧ�˳�ϵͳ   false:�������˵�
\  ******************************************************************** */
bool Quit()
{
	while(!isSaved && head->next!=NULL)   // δ����������ǿ�
	{
		puts("\n��֮ǰ�����ĸ�����δ���浽�ļ����Ƿ񱣴棿");
		puts("\t1 - ���浽�ļ�    2 - ֱ���˳�ϵͳ    0 - �������˵�");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':putchar('\n');SaveData();break;
		case '2':isSaved=true;break;   // ֱ���˳�ϵͳ����Ϊ�����ѱ���
		case '0':return false;
		default:printf("������󣬼����������˵���\n");
			system("pause");fflush(stdin);return false;
		}
	}

	// �ͷ�������ռ�ռ�
	equip *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		delete p->pre;
	}
	delete p;
	return true;
}


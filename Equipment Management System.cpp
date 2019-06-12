/* *********************************************************************
|                  面向过程程序设计综合应用
|    选    题  设备管理系统 Equipment Management System
|    姓    名  黄远鹏        学    号  183401050225
|    班    级  软件1802
|    完成时间  2019年6月9日
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
	int id;    // 设备编号(8位数)
	char name[50];   // 仪器名称
	char type[50];   // 型号规格
	double price;    // 单价
	struct _Date boughtDate;    // 购入日期
	char person[50];    // 领用人
	char status[100];    // 使用状况
	char postscript[110];    // 备注(50字内)
	struct _Equipment *pre,*next;   // 前趋与后继指针
	_Equipment()   // 构造函数初始化两个指针为NULL
	{
		pre=NULL;
		next=NULL;
	}
}equip;

// 函数声明与全局变量定义
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
equip *head=new equip;   // 此程序里的链表是"带头结点"的双向链表
equip *rear=head;     // 链尾指针
bool isSaved=false;   // true:已保存数据   false:尚未保存

int main()
{
	char choice;      // choice 接收由用户输入的指令代码
	while(true)
	{
		system("cls");     // 清屏
		system("title 设备管理系统");     // 更改窗口标题
		PrintDirection();

		choice = getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':system("cls"); InputFromFile();  break;   // 从文件录入信息
		case '2':system("cls"); InputFromStdin(); break;   // 批量录入新信息
		case '3':system("cls"); AddOnePiece();    break;   // 增加一条新信息
		case '4':system("cls"); Display();        break;   // 查看信息
		case '5':system("cls"); KeywordSearch();  break;   // 关键字查找
		case '6':system("cls"); SaveData();       break;   // 保存已有信息
		case '7':system("cls"); Modify();         break;   // 修改信息
		case '8':system("cls"); DeleteOnePiece(); break;   // 删除信息
		case '9':system("cls"); ChangeColor();    break;   // 修改窗口与字体颜色
		case '0':system("cls");
			if(Quit()==true)
				return 0;   // 退出系统
			else
				break;

		default:puts("输入错误，请重新输入。"); system("pause"); break;
		}
	}

	return 0;
}

/* *********************************************************************
|    函数名：PrintDirection
|    函数功能：输出提示信息
\  ******************************************************************** */
inline void PrintDirection()
{
	printf("     * * * * *  设 备 管 理 系 统  * * * * *\n\n");
	puts("     * * * * * *   输入 / 添加   * * * * * *");
	puts("             1 - 从文件录入信息");
	puts("             2 - 批量录入新信息");
	puts("             3 - 增加一条新信息");
	puts("     * * * * * *   查询 / 保存   * * * * * *");
	puts("             4 - 查看信息");
	puts("             5 - 关键字查找");
	puts("             6 - 保存已有信息");
	puts("     * * * * * *   修改 / 删除   * * * * * *");
	puts("             7 - 修改信息");
	puts("             8 - 删除信息");
	puts("     * * * * * *     系统设置    * * * * * *");
	puts("             9 - 修改窗口与字体颜色");
	puts("             0 - 退出系统\n");
	printf("请选择：");
}

/* *********************************************************************
|    函数名：InputFromFile
|    函数功能：从文件读入已有信息
\  ******************************************************************** */
void InputFromFile()
{
	system("title 设备管理系统 - 从文件录入信息");
	puts("请输入文件名或文件的地址，以回车结束。注意：地址中的'\\'应写作\"\\\\\"。");
	printf(">>> ");
	char fileName[200];       // 文件名或地址
	scanf("%[^\n]",fileName);
	fflush(stdin);
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL)   // 未打开成功
	{
		puts("无法打开指定的文件，请重试。");
		system("pause");
		return;
	}
	equip *p=rear;    // 从链表尾开始添加新内容
	char temp[500];   // 假定一条数据的最大长度为500个字符
	equip *s;
	int cnt=0;   // 记录读入数据条数
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
		printf("成功读入 %d 条数据。",cnt);
		isSaved=false;   // 更新数据保存状态（未保存）
		rear=p;   // 更新链尾指针
	}
	else
		printf("未能成功读取数据，请检查文件 %s 是否为空。\n",fileName);
	fclose(fp);
	system("pause");
	return;
}

/* *********************************************************************
|    函数名：InputFromStdin
|    函数功能：从屏幕批量录入信息
\  ******************************************************************** */
void InputFromStdin()
{
	system("title 设备管理系统 - 批量录入新信息");
	puts("请按以下格式录入信息，按Crtl+Z并按回车结束输入。购入日期格式为yyyy-mm-dd");
	puts("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注");
	equip *p=rear;    // 从链表尾开始添加新内容
	char temp[500];   // 假定一条数据的最大长度为500个字符
	equip *s;
	int cnt=0;   // 记录读入数据条数
	while(scanf("%[^\n]",temp)!=EOF)
	{
		getchar();   // 读掉多余回车
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
		printf("成功录入 %d 条数据。",cnt);
		isSaved=false;   // 更新数据保存状态（未保存）
		rear=p;   // 更新链尾指针
	}
	else
		printf("未录入任何数据。");
	system("pause");
	return;
}

/* *********************************************************************
|    函数名：AddOnePiece
|    函数功能：增加一条新信息
\  ******************************************************************** */
void AddOnePiece()
{
	system("title 设备管理系统 - 增加一条新信息");
	equip *p=rear,*s;
	s=new equip;
	p->next=s;
	s->pre=p;
	puts("请输入以下信息：");
	printf("设备编号: ");
	scanf("%d",&s->id);fflush(stdin);
	printf("仪器名称: ");
	scanf("%s",s->name);fflush(stdin);
	printf("型号规格: ");
	scanf("%s",s->type);fflush(stdin);
	printf("单价: ");
	scanf("%lf",&s->price);fflush(stdin);
	printf("购入日期，格式为yyyy-mm-dd: ");
	scanf("%d-%d-%d",&s->boughtDate.year,&s->boughtDate.month,&s->boughtDate.day);fflush(stdin);
	printf("领用人: ");
	scanf("%s",s->person);fflush(stdin);
	printf("使用状况: ");
	scanf("%s",s->status);fflush(stdin);
	printf("备注: ");
	scanf("%s",s->postscript);fflush(stdin);

	printf("\n成功增加 1 条信息。");
	rear=s;   // 更新链尾指针
	isSaved=false;   // 更新数据保存状态（未保存）
	system("pause");
	return;
}

/* *********************************************************************
|    函数名：Display
|    函数功能：查看信息的选择菜单
\  ******************************************************************** */
void Display()
{
	system("title 设备管理系统 - 查看信息");
	if(head->next==NULL)   // 除头结点外，链表为空
	{
		puts("\n当前系统内暂无记录。\n");
		system("pause");
		return;
	}

	char choice;
	puts("\t1 - 查看全部信息");
	puts("\t2 - 查看指定编号的信息");
	puts("\t0 - 返回主菜单");
	printf("请选择：");
	while(true)
	{
		choice = getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':PutsData();return;
		case '2':CheckOnePiece();return;
		case '0':return;

		default:printf("输入错误，请重新输入：");
		}
	}
}

/* *********************************************************************
|    函数名：PutsData
|    函数功能：把已有记录输出到屏幕
\  ******************************************************************** */
void PutsData()
{
	system("title 设备管理系统 - 查看全部信息");
	equip *p=head->next;
	int cnt=0;   // cnt记录数据个数
	printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
	while(p!=NULL)
	{
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		p=p->next;
		cnt++;
	}
	printf("\n共输出了 %d 条信息。",cnt);

	system("pause");
	return;
}

/* *********************************************************************
|    函数名：CheckOnePiece
|    函数功能：查看、输出一条信息
\  ******************************************************************** */
void CheckOnePiece()
{
	system("title 设备管理系统 - 查看指定编号的信息");
	int foundId;
	printf("请输入待查询的编号：");
	scanf("%d",&foundId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=foundId)
		p=p->next;
	if(p==NULL)
	{
		printf("未查询到编号 %d 对应的信息，是否录入？\n",foundId);
		puts("\t1 - 录入\t2 - 返回");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':AddOnePiece();break;
		case '2':break;
		default:printf("输入错误，即将返回主菜单。");system("pause");break;
		}
	}
	else
	{
		printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		system("pause");
	}

	return;
}

/* *********************************************************************
|    函数名：KeywordSearch
|    函数功能：按给出关键字查找信息
\  ******************************************************************** */
void KeywordSearch()
{
	system("title 设备管理系统 - 关键字查找");
	if(head->next==NULL)   // 除头结点外，链表为空
	{
		puts("\n当前系统内暂无记录，无法查找。\n");
		system("pause");
		return;
	}
	puts("请输入想查找的内容，只能输入一个关键字，以回车结束。");
	printf(">>> ");
	char keyword[100],temp[500];
	scanf("%s",keyword);
	fflush(stdin);
	equip *p=head->next;
	int cnt=0;   // 记录查找到的数据条数
	while(p!=NULL)
	{
		sprintf(temp,"%d %s %s %lf %d-%d-%d %s %s %s",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		if(strstr(temp,keyword))
		{
			if(cnt==0)   // 第一次查找到，输出表头
				printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
			printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
				p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
				p->person,p->status,p->postscript);
			cnt++;
		}
		p=p->next;
	}
	if(cnt==0)   // 未查找到
		printf("\n未查找到含 %s 的信息。",keyword);
	else
		printf("\n共查找到 %d 条信息。",cnt);

	system("pause");
	return;
}

/* *********************************************************************
|    函数名：SaveData
|    函数功能：把已有记录输出到文件中
\  ******************************************************************** */
void SaveData()
{
	system("title 设备管理系统 - 保存已有信息");
	if(head->next==NULL)   // 除头结点外，链表为空
	{
		puts("\n当前系统内暂无记录，请输入信息后再尝试保存。\n");
		system("pause");
		return;
	}

	puts("请输入文件名或文件的地址，以回车结束。注意：地址中的'\\'应写作\"\\\\\"。");
	puts("【特别提示】如果打开磁盘中已有的文件，该文件将被清空。");
	printf(">>> ");
	char fileName[200];       // 文件名或地址
	scanf("%[^\n]",fileName);
	fflush(stdin);
	FILE *fp=fopen(fileName,"w");
	if(fp==NULL)   // 未打开成功
	{
		puts("系统错误：无法打开指定的文件，请重试。");
		system("pause");
		return;
	}
	equip *p=head->next;
	int cnt=0;   // cnt记录数据个数
	while(p!=NULL)
	{
		fprintf(fp,"%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		p=p->next;
		cnt++;
	}
	printf("成功保存 %d 条数据到 %s 。",cnt,fileName);

	isSaved=true;   // 更新数据保存状态（已保存）
	fclose(fp);
	system("pause");
	return;
}

/* *********************************************************************
|    函数名：Modify
|    函数功能：修改指定编号的信息
\  ******************************************************************** */
void Modify()
{
	system("title 设备管理系统 - 修改信息");
	if(head->next==NULL)   // 除头结点外，链表为空
	{
		puts("\n当前系统内暂无记录，无法修改。\n");
		system("pause");
		return;
	}
	int modId;
	printf("请输入想要修改的信息的编号：");
	scanf("%d",&modId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=modId)
		p=p->next;
	if(p==NULL)     // 没有这一条，无法修改
	{
		printf("未找到编号 %d 对应的信息，无法修改。\n",modId);
		system("pause");
	}
	else   // 找到了，准备修改
	{
		puts("\n当前内容：");
		printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);

		printf("\n\t1 - 修改信息\t2 - 返回主菜单\n");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':{
			puts("\n请输入修改后的内容：");
			printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
			scanf("%d %s %s %lf %d-%d-%d %s %s %s",&p->id,p->name,p->type,
				&p->price,&p->boughtDate.year,&p->boughtDate.month,&p->boughtDate.day,
				p->person,p->status,p->postscript);
			fflush(stdin);
			printf("修改成功。");
			isSaved=false;   // 更新数据保存状态（未保存）
			system("pause");break;
				 }
		case '2':break;
		default:printf("输入错误，信息未修改。即将返回主菜单。\n");
			system("pause");break;
		}
	}
	return;
}

/* *********************************************************************
|    函数名：DeleteOnePiece
|    函数功能：删除指定编号的信息
\  ******************************************************************** */
void DeleteOnePiece()
{
	system("title 设备管理系统 - 删除信息");
	if(head->next==NULL)   // 除头结点外，链表为空
	{
		puts("\n当前系统内暂无记录，无法删除。\n");
		system("pause");
		return;
	}
	int delId;
	printf("请输入想要删除的信息的编号：");
	scanf("%d",&delId);
	fflush(stdin);
	equip *p=head->next;
	while(p!=NULL && p->id!=delId)
		p=p->next;
	if(p==NULL)     // 没有这一条，无法删除
	{
		printf("未找到编号 %d 对应的信息，无法删除。\n",delId);
		system("pause");
	}
	else   // 找到了，准备删除
	{
		printf("设备编号	仪器名称	型号规格	单价	购入日期	领用人	使用状况	备注\n");
		printf("%d	%s	%s	%.2lf	%d-%d-%d	%s	%s	%s\n",p->id,p->name,p->type,
			p->price,p->boughtDate.year,p->boughtDate.month,p->boughtDate.day,
			p->person,p->status,p->postscript);
		printf("\n\t1 - 确认删除\t2 - 返回\n");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':p->pre->next=p->next;
			if(p->next)      // p不是最后一个结点
				p->next->pre=p->pre;
			delete p;
			printf("编号 %d 对应信息已删除。",delId);
			isSaved=false;   // 更新数据保存状态（未保存）
			system("pause");break;
		case '2':break;
		default:printf("输入错误，信息未删除。即将返回主菜单。\n");
			system("pause");break;
		}
	}
	return;
}

/* *********************************************************************
|    函数名：ChangeColor
|    函数功能：更改窗口背景颜色与字体颜色
\  ******************************************************************** */
void ChangeColor()
{
	system("title 设备管理系统  -  颜色修改");
	char ColorChoice[3]="";
	puts("请输入您要更改的背景与字体颜色，字符不区分大小写，以回车结束：\n");
	puts("    0 = 黑色       8 = 灰色");
	puts("    1 = 蓝色       9 = 淡蓝色");
	puts("    2 = 绿色       A = 淡绿色");
	puts("    3 = 浅绿色     B = 淡浅绿色");
	puts("    4 = 红色       C = 淡红色");
	puts("    5 = 紫色       D = 淡紫色");
	puts("    6 = 黄色       E = 淡黄色");
	puts("    7 = 白色       F = 亮白色\n");
	puts("示例: 输入\"fc\"将设置背景为亮白色，字体为淡红色。");
	puts("如需恢复默认颜色，请输入\"**\"；返回主菜单，请输入\"##\"。");
	printf(">>> ");
	while(true)
	{
		ColorChoice[0]=getchar();
		ColorChoice[1]=getchar();
		fflush(stdin);
		if(strcmp(ColorChoice,"**")==0)     // 恢复默认颜色
		{
			system("color 07");
			printf("已恢复默认颜色。");
			system("pause");
			break;
		}
		else if(strcmp(ColorChoice,"##")==0)    // 返回主菜单
			break;
		else if(!isxdigit(ColorChoice[0]) || !isxdigit(ColorChoice[1]))  // 输入错误
			printf("输入错误，请重新输入：");
		else if(toupper(ColorChoice[0])==toupper(ColorChoice[1]))  // 背景与字体同色
			printf("不能将背景与字体设置为同一颜色。请重新输入：");
		else
		{
			char ColorMode[10]="color ";
			strcat(ColorMode,ColorChoice);
			system(ColorMode);
			printf("颜色设置成功。");
			system("pause");
			break;
		}
	}
	return;
}

/* *********************************************************************
|    函数名：Quit
|    函数功能：退出系统前检查信息是否已经保存到文件，如未保存提醒用户保存。
|              退出前将链表所占空间释放。
|    返回值：true:应退出系统   false:返回主菜单
\  ******************************************************************** */
bool Quit()
{
	while(!isSaved && head->next!=NULL)   // 未保存且链表非空
	{
		puts("\n您之前作出的更改尚未保存到文件，是否保存？");
		puts("\t1 - 保存到文件    2 - 直接退出系统    0 - 返回主菜单");
		printf(">>> ");
		char choice=getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':putchar('\n');SaveData();break;
		case '2':isSaved=true;break;   // 直接退出系统，视为数据已保存
		case '0':return false;
		default:printf("输入错误，即将返回主菜单。\n");
			system("pause");fflush(stdin);return false;
		}
	}

	// 释放链表所占空间
	equip *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		delete p->pre;
	}
	delete p;
	return true;
}


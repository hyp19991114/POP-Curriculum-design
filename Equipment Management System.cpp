/* *********************************************************************
*                  面向过程程序设计综合应用
*    选    题  设备管理系统 Equipment Management System
*    姓    名  黄远鹏        学    号  183401050225
*    班    级  软件1802
*    完成时间  2019年5月31日
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
	int id;    // 设备编号(8位数)
	char name[50];   // 仪器名称
	char type[50];   // 型号规格
	double price;    // 单价
	struct _Date boughtDate;    // 购入日期
	char person[50];    // 领用人
	char status[50];    // 使用状况
	char postscript[50];    // 备注( 50字内 )
}Equipment;

void ChangeColor();

int main()
{
	char choice;      // choice 接收由用户输入的指令代码
	while(true)
	{
		system("cls");            // 清屏
		system("title 设备管理系统");     // 更改窗口标题
		puts("     * * * * * * * *      设备管理系统      * * * * * * * *     \n");
		puts("     1 - 录入新信息            2 - 查找记录        3 - 修改已有信息");
		puts("     4 - 修改窗口与字体颜色    5 - 保存已有记录    6 - 退出系统\n");
		//输入、显示、修改、查找、添加、退出

		printf("请选择：");
		choice = getchar();
		fflush(stdin);
		if(choice == '6')
			break;
		else switch(choice)
		{
		case '4':ChangeColor();break;
		default:puts("输入错误，请重新输入。");system("pause");break;
		}

	}


	return 0;
}

/* *********************************************************************
*    函数名：ChangeColor
*    函数功能：更改窗口背景颜色与字体颜色
* ******************************************************************** */
void ChangeColor()
{
	system("title 设备管理系统  -  颜色修改");
	char ColorChoice[3]="";
	puts("请输入您要更改的背景与字体颜色，字符不区分大小写，以回车结束：");
	puts("    0 = 黑色	   8 = 灰色");
	puts("    1 = 蓝色	   9 = 淡蓝色");
	puts("    2 = 绿色	   A = 淡绿色");
	puts("    3 = 浅绿色	   B = 淡浅绿色");
	puts("    4 = 红色	   C = 淡红色");
	puts("    5 = 紫色	   D = 淡紫色");
	puts("    6 = 黄色	   E = 淡黄色");
	puts("    7 = 白色	   F = 亮白色");
	puts("示例: 输入\"fc\"将设置背景为亮白色，字体为淡红色。");
	puts("如需恢复默认颜色，请输入\"**\"；返回主菜单，请输入\"##\"。");
	while(true)
	{
		ColorChoice[0]=getchar();
		ColorChoice[1]=getchar();
		fflush(stdin);
		if(strcmp(ColorChoice,"**")==0)     // 恢复默认颜色
		{
			system("color 07");
			break;
		}
		else if(strcmp(ColorChoice,"##")==0)    // 返回主菜单
			break;
		else if(!isxdigit(ColorChoice[0]) || !isxdigit(ColorChoice[1]))  // 输入错误
			printf("输入错误，请重新输入：");
		else if(ColorChoice[0]==ColorChoice[1])  // 背景与字体同色
			printf("不能将背景与字体设置为同一颜色。请重新输入：");
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
*    函数名：InputFromFile
*    函数功能：从文件读入已有信息
* ******************************************************************** */
void InputFromFile()
{

}






/* *********************************************************************
*    函数名：111
*    函数功能：111
*    接口参数：111
*    返回值：111
* ******************************************************************** */
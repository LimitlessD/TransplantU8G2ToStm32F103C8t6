#include "pbdata.h"


typedef struct menu//定义一个菜单
{
u8 range_from,range_to; //当前显示的项开始及结束序号
u8 itemCount;//项目总数
u8 selected;//当前选择项
u8 *menuItems[17];//菜单项目
struct menu **subMenus;//子菜单
struct menu *parent;//上级菜单 ,如果是顶级则为null
void (**func)();//选择相应项按确定键后执行的函数
}Menu;

Menu MainMenu = { //定义主菜单
0,3,4,0,//默认显示0-3项，总共4项，当前选择第0项
  {
  "set11",
  "set12",
  "set13",
  "set14"
  }
};

Menu searchMenu = {//查询菜单
0,3,6,0,
{
  "set21",
  "set22",
  "set23",
  "set24",
  "set25",
  "set26"
}
};

Menu *currentMenu;//当前的菜单

//用于显示菜单项.这个函数需要按照屏幕驱动程序修改
void display(u8 line) //显示菜单项并设置选中的项反白
{
int i;
line = 3-(currentMenu->range_to-line);//计算应该高亮的行
Lcd_Fill(0x00);//清除屏幕
for(i = 0;i<4;i++)
{
  Lcd_Disp(i+1,0,currentMenu->menuItems[i+currentMenu->range_from]);
}
highlight(0,line,8,255);//反白显示指定行
}

void func(void)
{
printf("hello");
}
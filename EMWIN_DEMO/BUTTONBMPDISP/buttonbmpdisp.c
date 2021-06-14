#include "GUI.h"
#include "DIALOG.h"
#include "BUTTON.h"
#include "led.h"
#include "beep.h"
#include "buttonbmp.h"
#include "buttonbmpdisp.h"
#include "stdio.h"
#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//STemWin BUTTON位图显示
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/10
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern int flag;

#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_BUTTON_2 (GUI_ID_USER + 0x03)

#define ID_TEXT_0 (GUI_ID_USER + 0x04)
#define ID_TEXT_1 (GUI_ID_USER + 0x05)
#define ID_TEXT_2 (GUI_ID_USER + 0x06)

#define ID_FRAMEWIN_1 (GUI_ID_USER + 0x07)
#define ID_TEXT_3 (GUI_ID_USER + 0x08)
#define ID_TEXT_4 (GUI_ID_USER + 0x09)


#define ID_FRAMEWIN_2 (GUI_ID_USER + 0x10)
#define ID_SLIDER_0 (GUI_ID_USER + 0x11)
#define ID_SLIDER_1 (GUI_ID_USER + 0x12)
#define ID_SLIDER_2 (GUI_ID_USER + 0x13)
#define ID_TEXT_5 (GUI_ID_USER + 0x14)
#define ID_TEXT_6 (GUI_ID_USER + 0x15)
#define ID_TEXT_7 (GUI_ID_USER + 0x16)
#define ID_BUTTON_3 (GUI_ID_USER + 0x17)
#define ID_TEXT_8 (GUI_ID_USER + 0x18)
#define ID_TEXT_9 (GUI_ID_USER + 0x19)
#define ID_TEXT_10 (GUI_ID_USER + 0x20)
#define ID_BUTTON_4 (GUI_ID_USER + 0x21)

#define ID_FRAMEWIN_3 (GUI_ID_USER + 0x22)
#define ID_SLIDER_3 (GUI_ID_USER + 0x23)
#define ID_SLIDER_4 (GUI_ID_USER + 0x24)
#define ID_SLIDER_5 (GUI_ID_USER + 0x25)
#define ID_TEXT_11 (GUI_ID_USER + 0x26)
#define ID_TEXT_12 (GUI_ID_USER + 0x27)
#define ID_TEXT_13 (GUI_ID_USER + 0x28)
#define ID_TEXT_14 (GUI_ID_USER + 0x29)
#define ID_TEXT_15 (GUI_ID_USER + 0x30)
#define ID_TEXT_16 (GUI_ID_USER + 0x31)
#define ID_BUTTON_5 (GUI_ID_USER + 0x32)
#define ID_BUTTON_6 (GUI_ID_USER + 0x33)
#define ID_BUTTON_7 (GUI_ID_USER + 0x34)

char *temperature="0",*RH="0",*light_intensity="0";
GUI_BITMAP buttonbmp_tab[2];
WM_HWIN CreateFramewin1(void);
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin2(void);
WM_HWIN CreateFramewin3(void);
extern int t_pwmval,h_pwmval;
int control_flag=0;
int set_temp,set_humidity,set_light;
u8 heater;
u8 humidifier;
u8 window;
char buf[20];
char buf1[20];
extern u16 adcx;
//对话框资源表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0 , 0, 0, 320, 240, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 200, 50, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 110, 50, 100, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 200, 110, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 200, 160, 110, 40, 0, 0x0, 0 },

};
static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_1 , 0, 0, 320, 240, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 200, 50, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 100, 50, 100, 30, 0, 0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate2[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_2 , 0, 0, 320, 240, 0, 0x64, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 200, 10, 110, 40, 0, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_1, 200, 70, 110, 40, 0, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_2, 200, 130, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 110, 10, 100, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 80, 70, 120, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 120, 130, 100, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_6, 200, 50, 70, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_7, 200, 110, 100, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_8, 200, 170, 70, 30, 0, 0x0, 0 },	
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_3,  4, 170, 110, 40, 0, 0x0, 0 },

};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate3[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_3 , 0, 0, 320, 240, 0, 0x64, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_3, 200, 10, 110, 40, 0, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_4, 200, 90, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_9, 130, 10, 70, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_10, 110, 90, 100, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_4,  4, 170, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_12, 200, 50, 120, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_13, 200, 130, 120, 30, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_14, 200, 210, 120, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_6,  4, 10, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_7,  4, 90, 110, 40, 0, 0x0, 0 },
	
};
//对话框回调函数
static void _cbDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	static u8 modeflag=0;
	static u8 beepflag=0;

	
	
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Greenhouse");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");
			
			//初始化TEXT0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "Switch");	
		
		//初始化BUTTON1
			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetText(hItem, "setvalue");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
		
				//初始化BUTTON1
			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetText(hItem, "operate");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_0: //BUTTON_0的通知代码，控制LED1
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								control_flag=1;
								CreateFramewin1();
								GUI_Clear();

						break;	
					}
					break;
			case ID_BUTTON_1: //BUTTON_1的通知代码，控制BEEP
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								CreateFramewin2();
								GUI_Clear();
							break;
					}
					break;
				case ID_BUTTON_5: //BUTTON_1的通知代码，控制BEEP
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
								t_pwmval=0;
								h_pwmval=0;
								TIM_SetCompare1(TIM5,t_pwmval);
								TIM_SetCompare1(TIM14,h_pwmval);
						
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								CreateFramewin3();
								GUI_Clear();
							break;
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}

}

static void _cbDialog1(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	static u8 modeflag=0;
	static u8 beepflag=0;

	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Greenhouse");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[1],0,0);
			BUTTON_SetText(hItem, "");
			
			
			
		 //初始化TEXT0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "Switch");
			
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Greenhouse");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");
			
			
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{

	
					case ID_BUTTON_2: //BUTTON_0的通知代码，控制LED1
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								CreateFramewin();
								GUI_Clear();
							break;	
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

static void _cbDialog2(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;

	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Setvalue Configure");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
		 //初始化TEXT0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "set_temp");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "set_humidity");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "set_light");	

			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetText(hItem, "Back");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_SLIDER_0: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
					set_temp=SLIDER_GetValue(hItem);
					sprintf(buf,"set_temp=%d",set_temp);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					break;
         }
				break;
				case ID_SLIDER_1: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1);
					set_humidity=SLIDER_GetValue(hItem);
					sprintf(buf,"set_humidity=%d",set_humidity);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					break;
					
         }
				case ID_SLIDER_2: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
					window=SLIDER_GetValue(hItem);
					sprintf(buf,"set_open=%d",window);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					break;
					
         }
				break;
				case ID_BUTTON_3: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								CreateFramewin();
								GUI_Clear();
							break;
					}
				break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

static void _cbDialog3(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	int i;

	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Operate");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
		 //初始化TEXT0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "heater");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
//			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "humidifier");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "window");	

			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
			BUTTON_SetText(hItem, "Back");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			
			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
			BUTTON_SetText(hItem, "up");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			
			hItem=WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
			BUTTON_SetText(hItem, "down");
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_SLIDER_3: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3);
					heater=SLIDER_GetValue(hItem);
					t_pwmval=heater*200;
					sprintf(buf,"heater=%d",heater);
					TIM_SetCompare1(TIM14,t_pwmval);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					break;
         }
				break;
				case ID_SLIDER_4: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_4);
					humidifier=SLIDER_GetValue(hItem);
					h_pwmval=humidifier*200;
					sprintf(buf,"humidifier=%d",humidifier);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					TIM_SetCompare1(TIM5,h_pwmval);
					TIM_SetCompare1(TIM9,h_pwmval);
					break;
					
         }
				case ID_SLIDER_5: // Notifications sent by 'Slider'
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:

					break;
					case WM_NOTIFICATION_RELEASED:

					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_5);
					window=SLIDER_GetValue(hItem);
					sprintf(buf,"window=%d",window);
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
					GUI_SetFont(GUI_FONT_24_ASCII);
					TEXT_SetText(hItem,buf);
					break;
					
         }
				break;
				case ID_BUTTON_4: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							h_pwmval=0;
							t_pwmval=0;
							
								GUI_EndDialog(pMsg->hWin,0);
								GUI_Clear();
								CreateFramewin();
								GUI_Clear();
							break;
					}
				break;
				case ID_BUTTON_6: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
						
						break;
						case WM_NOTIFICATION_RELEASED:
					for(i=0;i<100;i++)
								forward();	
//							LED1=!LED1;
							break;
					}
				break;
				case ID_BUTTON_7: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:

							break;

						case WM_NOTIFICATION_RELEASED:
							for(i=0;i<100;i++)
									backward();
//									LED1=!LED1;
							break;
					}
				break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}


//创建一个对话框
WM_HWIN CreateFramewin(void) 
{
	WM_HWIN hWin;
	flag=0;
	buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

WM_HWIN CreateFramewin1(void) 
{
	WM_HWIN hWin;
	flag=1;
	buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;
	hWin = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
	return hWin;
}

WM_HWIN CreateFramewin2(void) 
{
	WM_HWIN hWin;
	flag=2;
	buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;
	hWin = GUI_CreateDialogBox(_aDialogCreate2, GUI_COUNTOF(_aDialogCreate2), _cbDialog2, WM_HBKWIN, 0, 0);
	return hWin;
}

WM_HWIN CreateFramewin3(void) 
{
	WM_HWIN hWin;
	flag=3;
	buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;
	hWin = GUI_CreateDialogBox(_aDialogCreate3, GUI_COUNTOF(_aDialogCreate3), _cbDialog3, WM_HBKWIN, 0, 0);
	return hWin;
}

//BUTTON按钮上显示位图
void Buttonbmp_Demo(void)
{
	WM_HWIN hWin;
	hWin=CreateFramewin();
	while(1)
	{
		GUI_Delay(100);
	}
}


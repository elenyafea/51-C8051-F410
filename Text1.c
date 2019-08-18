/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F410.h"
#include "nokia_5110.h"
#include "bmp_pixel.h"
char tab_1[]={0x11,0x44,0x22,0x88};
char tab_2[]={0x081,0x24,0x42,0x18};
sbit left=P0^2;
sbit right=P0^3;
bit flag=1;
char mode,i,out_1=0;
unsigned int speed,count,count_over;
sbit p00=P0^0;
sbit SOUND=P1^4;
sbit LIGHT=P1^5;
//*********************************************
void PCA_Init()
{
    PCA0MD    &= ~0x40;
    PCA0MD    = 0x00;
}

void Timer_Init()
{
    TCON      = 0x40;
    TMOD      = 0x10;
    CKCON     = 0x02;
    TH1       = 0xFF;
}

void Port_IO_Init()
{
    // P0.0  -  Skipped,     Push-Pull,  Digital
    // P0.1  -  Skipped,     Open-Drain, Digital
    // P0.2  -  Skipped,     Open-Drain, Digital
    // P0.3  -  Skipped,     Open-Drain, Digital
    // P0.4  -  Skipped,     Push-Pull,  Digital
    // P0.5  -  Skipped,     Push-Pull,  Digital
    // P0.6  -  Skipped,     Push-Pull,  Digital
    // P0.7  -  Skipped,     Push-Pull,  Digital

    // P1.0  -  Skipped,     Open-Drain, Digital
    // P1.1  -  Skipped,     Open-Drain, Digital
    // P1.2  -  Skipped,     Open-Drain, Digital
    // P1.3  -  Skipped,     Open-Drain, Digital
    // P1.4  -  Skipped,     Push-Pull,  Digital
    // P1.5  -  Skipped,     Push-Pull,  Digital
    // P1.6  -  Skipped,     Push-Pull, Digital
    // P1.7  -  Skipped,     Push-Pull, Digital

    // P2.0  -  Skipped,     Push-Pull,  Digital
    // P2.1  -  Skipped,     Push-Pull,  Digital
    // P2.2  -  Skipped,     Push-Pull,  Digital
    // P2.3  -  Skipped,     Push-Pull,  Digital
    // P2.4  -  Skipped,     Push-Pull,  Digital
    // P2.5  -  Skipped,     Push-Pull,  Digital
    // P2.6  -  Skipped,     Push-Pull,  Digital
    // P2.7  -  Skipped,     Push-Pull,  Digital

    P0MDOUT   = 0xF1;
    P1MDOUT   = 0xF0;
    P2MDOUT   = 0xFF;
    XBR1      = 0x40;

}

void Oscillator_Init()
{
    OSCICN    = 0x87;
}

void Interrupts_Init()
{
    IE        = 0x88;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    PCA_Init();
    Timer_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}




//************************************************

 delay(int timer_value)
{ 
	int a;
	for(a=0;a<timer_value;a++);
}

//=================主函数====================  
main()
{  
Init_Device();

speed=0xc000;	  //电机运行速度
SOUND=0;
LIGHT=0;
LCD_init();       //初始化液晶    
	LCD_write_chinese_string(0,0,12,6,0,2);
	LCD_write_chinese_string(0,2,12,6,6,2);
	LCD_write_chinese_string(0,4,12,6,12,2);
while(1)
{ 
  mode=(P0&0x0c)/4;
}

/*mode=1;speed=5*8192;count_over=48*6;
while(flag);flag=1;
mode=2;speed=2*8192;count_over=48*6;TR1=1;
while(flag);flag=1;
mode=3;speed=5*8192;count_over=48*6;TR1=1;
while(flag);flag=1;
mode=0;TR1=1;
while(1);
 {
 if(left==0)
   {
    delay(10000);
    if(left==0)
	 {
      mode=3;
	  while(left==0);	//等待键盘释放
	 }
   }
 if(right==0)
	{
	delay(10000);
	if(right==0)
	 {
	  mode=4;
	  while(right==0);	//等待键盘释放
	 }
	}  


 }*/	 
}  //end mian 
 
//=============定时器1的中断函数==============
 void int_t1() interrupt 3    
{
 TH1=speed/256;            //中断常数
 TL1=speed%256;
// mode=left;
// mode=(mode*2)|right;

 switch (mode)     //mode:方式（0停止，3前进，后退，2左转，1右转，5原地左转，6原地右转）
  {
  	case 0:
	    P2=0;
		break;
	case 3:
	    i++;
		P2=tab_1[i&0x03];
		break;
	/*case 2:
	    i--;
		P2=tab_1[i&0x03];
		break;*/
	case 2:
	    i++;
		P2=tab_1[i&0x03]&0x0f;
		break;
	case 1:
	    i++;
		P2=tab_1[i&0x03]&0xf0;
		break;
	case 5:
		i++;
		P2=tab_2[i&0x03];
		break;
	case 6:
		i--;
		P2=tab_2[i&0x03];
		break;
	case 7:
		P2=0;
		break;
	
	default :
		break;
  }	  //end switch
 if(count>count_over)
 	{
	TR1=0;
	count=0;
	flag=0;
	}
 

}//end int_t0
//=============定时器2的中断函数==============
/* void int_t2() interrupt 5    
{
  p00=!p00;
  TF2H=0;	}*/	   //测试用
 /*count++;
 if(count>count_over)
 	{
	TR1=0;
	count=0;
	flag=0;
	}
 switch (mode)     //mode:方式（0停止，1前进，2后退，3左转，4右转，5原地左转，6原地右转）
  {
  	case 0:
	    P2=0;
		break;
	case 1:
	    i++;
		P2=tab_1[i&0x03];
		break;
	case 2:
	    i--;
		P2=tab_1[i&0x03];
		break;
	case 3:
	    i++;
		P2=tab_1[i&0x03]&0x0f;
		break;
	case 4:
	    i++;
		P2=tab_1[i&0x03]&0xf0;
		break;
	case 5:
		i++;
		P2=tab_2[i&0x03];
		break;
	case 6:
		i--;
		P2=tab_2[i&0x03];
		break;
	case 7:
		P2=0;
		break;
	
	default :
		break;
  }	  //end switch

}//end int_t1	  */
/*//=============定时器0的中断函数==============
 void int_t0() interrupt 1    
{
  TH0=0xd7;
  TL0=0xff;
  key=!key;
  	}	   //测试用
  */
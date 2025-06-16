/*
  功能说明: CT117E增强版单片机LCD驱动程序(竖屏模式)
  开发环境: Keil uVision 4.10
  硬件平台: CT117E增强版单片机
  日期: 2025-06-13
*/
#include "lcd.h"
#include "fonts.h"
//#include "systick.h"
static  vu16 TextColor = 0x0000, BackColor = 0xFFFF;
vu16 dummy;

// 显示模式定义
#define LANDSCAPE_MODE  0  // 横屏模式
#define PORTRAIT_MODE  1  // 竖屏模式
static u8 DisplayMode = PORTRAIT_MODE;  // 默认竖屏模式

/*******************************************************************************
* Function Name  : Delay_LCD
* Description    : 延时函数
* Input          : nCount: 延时计数值
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_LCD(u16 n)
{
    u16 i, j;
    for (i = 0; i < n; ++i)
        for(j = 0; j < 3000; ++j);
}

/*
  uC8230芯片LCD控制器初始化函数(竖屏模式)
*/
void REG_8230_Init(void)
{
    LCD_WriteReg(0x0000, 0x0001);
    Delay_LCD(1000);
    LCD_WriteReg(0x0001, 0x0000);
    LCD_WriteReg(0x0010, 0x1790);
    LCD_WriteReg(0x0060, 0x2700);
    LCD_WriteReg(0x0061, 0x0001);
    LCD_WriteReg(0x0046, 0x0002);
    LCD_WriteReg(0x0013, 0x8010);
    LCD_WriteReg(0x0012, 0x80fe);
    LCD_WriteReg(0x0002, 0x0500);
    
    // 关键修改：设置竖屏显示方向
    LCD_WriteReg(0x0003, 0x1018);  // 调整GRAM写入方向为竖屏模式
    
    LCD_WriteReg(0x0030, 0x0303);
    LCD_WriteReg(0x0031, 0x0303);
    LCD_WriteReg(0x0032, 0x0303);
    LCD_WriteReg(0x0033, 0x0300);
    LCD_WriteReg(0x0034, 0x0003);
    LCD_WriteReg(0x0035, 0x0303);
    LCD_WriteReg(0x0036, 0x0014);
    LCD_WriteReg(0x0037, 0x0303);
    LCD_WriteReg(0x0038, 0x0303);
    LCD_WriteReg(0x0039, 0x0303);
    LCD_WriteReg(0x003a, 0x0300);
    LCD_WriteReg(0x003b, 0x0003);
    LCD_WriteReg(0x003c, 0x0303);
    LCD_WriteReg(0x003d, 0x1400);

    LCD_WriteReg(0x0092, 0x0200);
    LCD_WriteReg(0x0093, 0x0303);
    LCD_WriteReg(0x0090, 0x080d);
    LCD_WriteReg(0x0003, 0x1018);
    LCD_WriteReg(0x0007, 0x0173);
}

void REG_932X_Init(void)
{
    LCD_WriteReg(R227, 0x3008);   // 设置内部时序
    LCD_WriteReg(R231, 0x0012);   // 设置内部时序
    LCD_WriteReg(R239, 0x1231);   // 设置内部时序
    LCD_WriteReg(R1, 0x0000);     // 设置SS和SM位
    LCD_WriteReg(R2, 0x0700);     // 设置1行反转
    
    // 关键修改：设置竖屏显示方向
    LCD_WriteReg(R3, 0x01018);    // I/D=01(水平递增，垂直递减)，AM=1(垂直写入时更新地址)
    
    LCD_WriteReg(R4, 0x0000);     // 调整寄存器
    LCD_WriteReg(R8, 0x0207);     // 设置后沿和前沿
    LCD_WriteReg(R9, 0x0000);     // 设置非显示区域刷新周期
    LCD_WriteReg(R10, 0x0000);    // FMARK功能
    LCD_WriteReg(R12, 0x0000);    // RGB接口设置
    LCD_WriteReg(R13, 0x0000);    // 帧标记位置
    LCD_WriteReg(R15, 0x0000);    // RGB接口极性
    /**************电源启动序列****************/
    LCD_WriteReg(R16, 0x0000);    // SAP, BT[3:0], AP, DSTB, SLP, STB
    LCD_WriteReg(R17, 0x0007);    // DC1[2:0], DC0[2:0], VC[2:0]
    LCD_WriteReg(R18, 0x0000);    // VREG1OUT电压
    LCD_WriteReg(R19, 0x0000);    // VDV[4:0]用于VCOM幅度
    HAL_Delay(200);
    LCD_WriteReg(R16, 0x1690);    // SAP, BT[3:0], AP, DSTB, SLP, STB
    LCD_WriteReg(R17, 0x0227);    // R11H=0x0221 at VCI=3.3V
    HAL_Delay(50);
    LCD_WriteReg(R18, 0x001D);    // 外部参考电压= Vci
    HAL_Delay(50);
    LCD_WriteReg(R19, 0x0800);    // VDV[4:0]用于VCOM幅度
    LCD_WriteReg(R41, 0x0014);    // VCM[5:0]用于VCOMH
    LCD_WriteReg(R43, 0x000B);    // 帧率= 96Hz
    HAL_Delay(50);
    
    // 关键修改：调整GRAM区域为竖屏(240x320)
    LCD_WriteReg(R32, 0x0000);  // GRAM水平地址
    LCD_WriteReg(R33, 0x0000);  // GRAM垂直地址
    /* -----------调整伽马曲线----------- */
    LCD_WriteReg(R48, 0x0007);
    LCD_WriteReg(R49, 0x0707);
    LCD_WriteReg(R50, 0x0006);
    LCD_WriteReg(R53, 0x0704);
    LCD_WriteReg(R54, 0x1F04);
    LCD_WriteReg(R55, 0x0004);
    LCD_WriteReg(R56, 0x0000);
    LCD_WriteReg(R57, 0x0706);
    LCD_WriteReg(R60, 0x0701);
    LCD_WriteReg(R61, 0x000F);
    /* ------------------设置GRAM区域---------------- */
    LCD_WriteReg(R80, 0x0000);    // 水平GRAM起始地址(0-239)
    LCD_WriteReg(R81, 0x00EF);    // 水平GRAM结束地址(239)
    LCD_WriteReg(R82, 0x0000);    // 垂直GRAM起始地址(0-319)
    LCD_WriteReg(R83, 0x013F);    // 垂直GRAM结束地址(319)
    LCD_WriteReg(R96, 0x2700);    // 栅扫描线
    LCD_WriteReg(R97, 0x0001);    // NDL,VLE, REV
    LCD_WriteReg(R106, 0x0000);   // 设置滚动线
    /* --------------部分显示控制----------- */
    LCD_WriteReg(R128, 0x0000);
    LCD_WriteReg(R129, 0x0000);
    LCD_WriteReg(R130, 0x0000);
    LCD_WriteReg(R131, 0x0000);
    LCD_WriteReg(R132, 0x0000);
    LCD_WriteReg(R133, 0x0000);
    /* --------------面板控制------------------- */
    LCD_WriteReg(R144, 0x0010);
    LCD_WriteReg(R146, 0x0000);
    LCD_WriteReg(R147, 0x0003);
    LCD_WriteReg(R149, 0x0110);
    LCD_WriteReg(R151, 0x0000);
    LCD_WriteReg(R152, 0x0000);
    /* 设置GRAM写入方向和BGR = 1 */
    LCD_WriteReg(R3, 0x01018);    // 最终确认竖屏方向
    LCD_WriteReg(R7, 0x0173);     // 262K颜色和显示开启
}
/*******************************************************************************
* Function Name  : STM3210B_LCD_Init
* Description    : 初始化LCD，自动检测控制器并设置对应模式
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Init(void)
{
    LCD_CtrlLinesConfig();
    dummy = LCD_ReadReg(0);

    if(dummy == 0x8230)
    {
        REG_8230_Init();
    }
    else
    {
        REG_932X_Init();
    }
    dummy = LCD_ReadReg(0);
}

// 模式切换函数
void LCD_SetDisplayMode(u8 Mode)
{
    DisplayMode = Mode;
    LCD_Init();  // 重新初始化以应用新模式
}

/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : 设置文本颜色
* Input          : - Color: RGB(5-6-5)颜色码
* Output         : - TextColor: 全局文本颜色变量
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(vu16 Color)
{
    TextColor = Color;
}
/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : 设置背景颜色
* Input          : - Color: RGB(5-6-5)颜色码
* Output         : - BackColor: 全局背景颜色变量
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(vu16 Color)
{
    BackColor = Color;
}
/*******************************************************************************
* Function Name  : LCD_ClearLine
* Description    : 清除指定行
* Input          : - Line: 行号(0-9)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearLine(u8 Line)
{
    LCD_DisplayStringLine(Line, (u8*)"                    ");
}
/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : 清屏
* Input          : Color: 背景颜色
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
    u32 index = 0;
    LCD_SetCursor(0x00, 0x0000);
    LCD_WriteRAM_Prepare(); /* 准备写入GRAM */
    for(index = 0; index < 76800; index++)  // 240x320=76800像素
    {
        LCD_WriteRAM(Color);
    }
}
/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : 设置光标位置(竖屏模式下X/Y交换)
* Input          : - Ypos: 垂直坐标(原Xpos)
*                  - Xpos: 水平坐标(原Ypos)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u8 Ypos, u16 Xpos)
{
    LCD_WriteReg(R32, Ypos);  // 原Xpos改为Ypos(垂直坐标)
    LCD_WriteReg(R33, Xpos);  // 原Ypos改为Xpos(水平坐标)
}
/*******************************************************************************
* Function Name  : LCD_DrawChar
* Description    : 在LCD上绘制字符(竖屏模式坐标调整)
* Input          : - Xpos: 水平起始坐标
*                  - Ypos: 垂直起始坐标
*                  - c: 字符数据指针
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c)
{
    u32 index = 0, i = 0;
    u8 Yaddress = 0;

    Yaddress = Xpos;
    LCD_SetCursor(Yaddress, Ypos);

    for(index = 0; index < 24; index++)
    {
        LCD_WriteRAM_Prepare(); /* 准备写入GRAM */
        for(i = 0; i < 16; i++)
        {
            if((c[index] & (1 << i)) == 0x00)
            {
                LCD_WriteRAM(BackColor);
            }
            else
            {
                LCD_WriteRAM(TextColor);
            }
        }
        Yaddress++;
        LCD_SetCursor(Yaddress, Ypos);
    }
}
/*******************************************************************************
* Function Name  : LCD_DisplayChar
* Description    : 显示单个字符(16x24点阵，竖屏模式调整)
* Input          : - Line: 垂直行号
*                  - Column: 水平列号
*                  - Ascii: ASCII码(0x20-0x7E)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii)
{
    Ascii -= 32;
    LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
}
/*******************************************************************************
* Function Name  : LCD_DisplayStringLine
* Description    : 在LCD上显示字符串(竖屏模式从右向左显示)
* Input          : - Line: 垂直行位置
*                  - *ptr: 字符串指针
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayStringLine(u8 Line, u8 *ptr)
{
    u32 i = 0;
    u16 refcolumn = 239;  // 竖屏模式起始列(右侧开始)
    
    while ((*ptr != 0) && (i < 20))
    {
        LCD_DisplayChar(Line, refcolumn, *ptr);
        refcolumn -= 16;  // 向左移动16像素(字符宽度)
        ptr++;
        i++;
    }
}
/*******************************************************************************
* Function Name  : LCD_SetDisplayWindow
* Description    : 设置显示窗口(竖屏模式宽高交换)
* Input          : - Ypos: 垂直起始坐标
*                  - Xpos: 水平起始坐标
*                  - Height: 窗口高度(原宽度)
*                  - Width: 窗口宽度(原高度)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetDisplayWindow(u8 Ypos, u16 Xpos, u8 Height, u16 Width)
{
    if(Ypos >= Width)
    {
        LCD_WriteReg(R80, (Ypos - Width + 1));
    }
    else
    {
        LCD_WriteReg(R80, 0);
    }
    LCD_WriteReg(R81, Ypos);
    
    if(Xpos >= Height)
    {
        LCD_WriteReg(R82, (Xpos - Height + 1));
    }
    else
    {
        LCD_WriteReg(R82, 0);
    }
    
    LCD_WriteReg(R83, Xpos);
    LCD_SetCursor(Ypos, Xpos);
}
/*******************************************************************************
* Function Name  : LCD_WindowModeDisable
* Description    : 禁用窗口模式
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WindowModeDisable(void)
{
    LCD_SetDisplayWindow(239, 0x13F, 240, 320);
    LCD_WriteReg(R3, 0x1018);
}
/*******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : 绘制直线(竖屏模式方向逻辑调整)
* Input          : - Ypos: 垂直起始坐标
*                  - Xpos: 水平起始坐标
*                  - Length: 线长
*                  - Direction: 方向(Vertical/Horizontal)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawLine(u8 Ypos, u16 Xpos, u16 Length, u8 Direction)
{
    u32 i = 0;

    LCD_SetCursor(Ypos, Xpos);
    if(Direction == Horizontal)
    {
        // 水平线：X坐标递增
        LCD_WriteRAM_Prepare(); 
        for(i = 0; i < Length; i++)
        {
            LCD_WriteRAM(TextColor);
            Xpos++;
            LCD_SetCursor(Ypos, Xpos);
        }
    }
    else
    {
        // 垂直线：Y坐标递增
        LCD_WriteRAM_Prepare(); 
        for(i = 0; i < Length; i++)
        {
            LCD_WriteRAM(TextColor);
            Ypos++;
            LCD_SetCursor(Ypos, Xpos);
        }
    }
}
/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : 绘制矩形(竖屏模式宽高交换)
* Input          : - Ypos: 垂直起始坐标
*                  - Xpos: 水平起始坐标
*                  - Height: 矩形高度(原宽度)
*                  - Width: 矩形宽度(原高度)
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u8 Ypos, u16 Xpos, u8 Height, u16 Width)
{
    // 绘制上下边(水平线)
    LCD_DrawLine(Ypos, Xpos, Width, Horizontal);
    LCD_DrawLine((Ypos + Height), Xpos, Width, Horizontal);
    
    // 绘制左右边(垂直线)
    LCD_DrawLine(Ypos, Xpos, Height, Vertical);
    LCD_DrawLine(Ypos, (Xpos - Width + 1), Height, Vertical);
}
/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : 绘制圆形(竖屏模式坐标调整)
* Input          : - Ypos: 圆心垂直坐标
*                  - Xpos: 圆心水平坐标
*                  - Radius: 半径
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u8 Ypos, u16 Xpos, u16 Radius)
{
    s32  D;
    u32  CurX;
    u32  CurY;

    D = 3 - (Radius << 1);
    CurX = 0;
    CurY = Radius;

    while (CurX <= CurY)
    {
        // 调整所有坐标点的X/Y位置
        LCD_SetCursor(Ypos + CurX, Xpos + CurY);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos + CurX, Xpos - CurY);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos - CurX, Xpos + CurY);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos - CurX, Xpos - CurY);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos + CurY, Xpos + CurX);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos + CurY, Xpos - CurX);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos - CurY, Xpos + CurX);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        LCD_SetCursor(Ypos - CurY, Xpos - CurX);
        LCD_WriteRAM_Prepare(); 
        LCD_WriteRAM(TextColor);

        if (D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}
/*******************************************************************************
* Function Name  : LCD_DrawMonoPict
* Description    : 绘制单色图片
* Input          : - Pict: 图片数组指针
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawMonoPict(uc32 *Pict)
{
    u32 index = 0, i = 0;

    LCD_SetCursor(0, 319);

    LCD_WriteRAM_Prepare(); 
    for(index = 0; index < 2400; index++)
    {
        for(i = 0; i < 32; i++)
        {
            if((Pict[index] & (1 << i)) == 0x00)
            {
                LCD_WriteRAM(BackColor);
            }
            else
            {
                LCD_WriteRAM(TextColor);
            }
        }
    }
}
/*******************************************************************************
* Function Name  : LCD_WriteBMP
* Description    : 显示BMP图片(竖屏模式需注意图片数据格式)
* Input          : - BmpAddress: BMP图片在内部Flash的地址
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteBMP(u32 BmpAddress)
{
    u32 index = 0, size = 0;

    size = *(vu16 *) (BmpAddress + 2);
    size |= (*(vu16 *) (BmpAddress + 4)) << 16;

    index = *(vu16 *) (BmpAddress + 10);
    index |= (*(vu16 *) (BmpAddress + 12)) << 16;
    size = (size - index) / 2;
    BmpAddress += index;

    LCD_WriteReg(R3, 0x1008);
    LCD_WriteRAM_Prepare();
    for(index = 0; index < size; index++)
    {
        LCD_WriteRAM(*(vu16 *)BmpAddress);
        BmpAddress += 2;
    }
    LCD_WriteReg(R3, 0x1018);
}
/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : 写入LCD寄存器
* Input          : - LCD_Reg: 寄存器地址
*                  - LCD_RegValue: 写入值
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
    GPIOB->BRR  |= GPIO_PIN_9;
    GPIOB->BRR  |= GPIO_PIN_8;
    GPIOB->BSRR |= GPIO_PIN_5;

    GPIOC->ODR = LCD_Reg;
    GPIOB->BRR  |= GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |= GPIO_PIN_5;
    GPIOB->BSRR |= GPIO_PIN_8;

    GPIOC->ODR = LCD_RegValue;
    GPIOB->BRR  |= GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |= GPIO_PIN_5;
    GPIOB->BSRR |= GPIO_PIN_8;
}
/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : 读取LCD寄存器
* Input          : None
* Output         : None
* Return         : 寄存器值
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
    u16 temp;

    GPIOB->BRR |= GPIO_PIN_9;
    GPIOB->BRR |= GPIO_PIN_8;
    GPIOB->BSRR |= GPIO_PIN_5;

    GPIOC->ODR = LCD_Reg;
    GPIOB->BRR |= GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |= GPIO_PIN_5;
    GPIOB->BSRR |= GPIO_PIN_8;

    LCD_BusIn();
    GPIOA->BRR |= GPIO_PIN_8;
    __nop();
    __nop();
    __nop();
    temp = GPIOC->IDR;
    GPIOA->BSRR |= GPIO_PIN_8;

    LCD_BusOut();
    GPIOB->BSRR |= GPIO_PIN_9;

    return temp;
}
/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : 准备写入RAM
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    GPIOB->BRR  |=  GPIO_PIN_9;
    GPIOB->BRR  |=  GPIO_PIN_8;
    GPIOB->BSRR |=  GPIO_PIN_5;

    GPIOC->ODR = R34;
    GPIOB->BRR  |=  GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |=  GPIO_PIN_5;
    GPIOB->BSRR |=  GPIO_PIN_8;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |=  GPIO_PIN_9;
}
/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : 写入RAM
* Input          : - RGB_Code: RGB(5-6-5)颜色码
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{
    GPIOB->BRR  |=  GPIO_PIN_9;
    GPIOB->BSRR |=  GPIO_PIN_8;
    GPIOB->BSRR |=  GPIO_PIN_5;

    GPIOC->ODR = RGB_Code;
    GPIOB->BRR  |=  GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |=  GPIO_PIN_5;
    GPIOB->BSRR |=  GPIO_PIN_8;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |=  GPIO_PIN_9;
}
/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : 读取RAM
* Input          : None
* Output         : None
* Return         : RAM值
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
    u16 temp;

    GPIOB->BRR  |=  GPIO_PIN_9;
    GPIOB->BRR  |=  GPIO_PIN_8;
    GPIOB->BSRR |=  GPIO_PIN_5;

    GPIOC->ODR = R34;
    GPIOB->BRR  |=  GPIO_PIN_5;
    __nop();
    __nop();
    __nop();
    GPIOB->BSRR |=  GPIO_PIN_5;
    GPIOB->BSRR |=  GPIO_PIN_8;

    LCD_BusIn();
    GPIOA->BRR |=  GPIO_PIN_8;
    __nop();
    __nop();
    __nop();
    temp = GPIOC->IDR;
    GPIOA->BSRR |=  GPIO_PIN_8;

    LCD_BusOut();
    GPIOB->BSRR |=  GPIO_PIN_9;

    return temp;
}
/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : 开启LCD电源
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PowerOn(void)
{
    LCD_WriteReg(R16, 0x0000);
    LCD_WriteReg(R17, 0x0000);
    LCD_WriteReg(R18, 0x0000);
    LCD_WriteReg(R19, 0x0000);
    Delay_LCD(20);
    LCD_WriteReg(R16, 0x17B0);
    LCD_WriteReg(R17, 0x0137);
    Delay_LCD(5);
    LCD_WriteReg(R18, 0x0139);
    Delay_LCD(5);
    LCD_WriteReg(R19, 0x1d00);
    LCD_WriteReg(R41, 0x0013);
    Delay_LCD(5);
    LCD_WriteReg(R7, 0x0173);
}
/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : 开启显示
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
    LCD_WriteReg(R7, 0x0173);
}
/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : 关闭显示
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
    LCD_WriteReg(R7, 0x0);
}
/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : 配置LCD控制引脚(推挽模式)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin =  GPIO_PIN_8 ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LCD_BusOut();

    GPIOA->BSRR |= 0x0100;
    GPIOB->BSRR |= 0x0220;
}

/*******************************************************************************
* Function Name  : LCD_BusIn
* Description    : 配置并行接口为输入模式(PortC)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_BusIn(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_All;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*******************************************************************************
* Function Name  : LCD_BusOut
* Description    : 配置并行接口为输出模式(PortC)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_BusOut(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_All;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*******************************************************************************
* Function Name  : LCD_DrawPicture
* Description    : 显示16色图片(竖屏模式需注意像素映射)
* Input          : - picture: 图片数组指针
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawPicture(const u8 *picture)
{
    int index;
    LCD_SetCursor(0x00, 0x0000);

    LCD_WriteRAM_Prepare(); 
    
    // 竖屏模式下像素排列需与横屏区分，此处假设输入数据已适配竖屏
    for(index = 0; index < 76800; index++)
    {
        LCD_WriteRAM(picture[2 * index + 1] << 8 | picture[2 * index]);
    }
}
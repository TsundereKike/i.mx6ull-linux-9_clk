#include "bsp_clk.h"
/*
*@brief: 使能i.mx6ull外设时钟
*@param in:  NULL
*@param out: NULL
*@ret:    NULL
*/
void clk_enable(void)
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}
void imx6u_clk_init(void)
{
    if(((CCM->CCSR) & 0x4)==0) /*pll_main_clk*/
    {
        CCM->CCSR &= ~(1<<8); /*配置step_clk时钟源为24MHz OSC*/
        CCM->CCSR |= (1<<2); /*配置pll_sw_clk时钟源为step_clk*/
    }
    CCM_ANALOG->PLL_ARM = (1<<13) | ((58<<0) & 0x7f); /*设置pll_main_clk为1056MHz*/
    CCM->CACRR = 0x0; /*ARM内核时钟设置为pll_sw_clk时钟的2分频 = 1056MHz/2 = 528MHz*/
    CCM->CCSR &= ~(1<<2); /*配置pll_sw_clk时钟源为pll_main_clk*/
}

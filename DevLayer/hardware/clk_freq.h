#ifndef CLK_FREQ_H
#define CLK_FREQ_H

#ifdef __cplusplus
extern "C" {
#endif


#define SYS_CLK          ( HAL_RCC_GetSysClockFreq()  )
#define HCLK_CLK         ( HAL_RCC_GetHCLKFreq()      )
#define APB1_CLK         ( HAL_RCC_GetPCLK1Freq()     )
#define APB2_CLK         ( HAL_RCC_GetPCLK2Freq()     )
#define APB3_CLK         ( HAL_RCCEx_GetD1PCLK1Freq() )
#define APB4_CLK         ( HAL_RCCEx_GetD3PCLK1Freq() )


#define APB1_TIM_CLK     ( ((RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) == 0U) ? \
                           APB1_CLK : (2 * APB1_CLK) )

#define APB2_TIM_CLK     ( ((RCC->D2CFGR & RCC_D2CFGR_D2PPRE2) == 0U) ? \
                           APB2_CLK : (2 * APB2_CLK) )

#define APB3_TIM_CLK     ( ((RCC->D1CFGR & RCC_D1CFGR_D1PPRE)  == 0U) ? \
                           APB3_CLK : (2 * APB3_CLK) )

#define APB4_TIM_CLK     ( ((RCC->D3CFGR & RCC_D3CFGR_D3PPRE)  == 0U) ? \
                           APB4_CLK : (2 * APB4_CLK) )


#ifdef __cplusplus
}
#endif

#endif /* CLK_FREQ_H */

/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  * 
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "USARTCMD.h"
#include "motordriver.h" 

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

void TIM15_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM15, TIM_IT_CC1) != RESET){
		TIM_ClearITPendingBit(TIM15, TIM_IT_CC1);
	}	
	
//	if(TIM_GetFlagStatus(TIM15, TIM_FLAG_CC1) != RESET){
//		TIM_ClearFlag(TIM15, TIM_FLAG_CC1);
//	}	
}

void TIM16_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM16, TIM_IT_CC1) != RESET){
		TIM_ClearITPendingBit(TIM16, TIM_IT_CC1);
		MotorRunning(&Motor1);
	}
}


void TIM17_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM17, TIM_IT_CC1) != RESET){
		TIM_ClearITPendingBit(TIM17, TIM_IT_CC1);
		MotorRunning(&Motor2);
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

	if(!(timeTickLast == timeTick)){timeTick=0;}
	if(timeTick >= 0xfffffff0)timeTick = 0;
	
	timeTick++;
	timeTickLast = timeTick;
}

/*******************************************************************************
* Function Name  : EXTI4_15_IRQHandler
* Description    : This function handles External lines 4 to 15 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_15_IRQHandler(void)
{
}


/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static uint8_t escape_flag=0;
static uint8_t Usart_buf[30];
uint8_t counter=0;
static uint8_t rcv_flag=0;

#define PROTOCOLLEN 14
void USART1_IRQHandler(void)
{
	uint8_t CharRcv;	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//
	{ 
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
		CharRcv = USART_ReceiveData(USART1);
		//��ͷ
		if(CharRcv == 0xfd){
			rcv_flag=1;
			counter = 0;
		}
		//��β
		if(CharRcv == 0xf8){
			if(counter == PROTOCOLLEN-1){
				DealUsartCMD(Usart_buf);
			}
			rcv_flag=0;
			counter = 0;			
		}
		//ת��
		if(rcv_flag==1){
			if(escape_flag==1){
				escape_flag=0;
				CharRcv = (CharRcv & 0x0f) | 0xf0;
			}			
			if(CharRcv == 0xfe){
				escape_flag=1;
			}else{
				Usart_buf[counter] = CharRcv;			
				counter++;
			}
		}
		//����
		if(counter == PROTOCOLLEN){
			rcv_flag=0;
			counter = 0;
		}		
	}
}

void WWDG_IRQHandler(void){
//	WWDG_SetCounter(127);
//  WWDG_ClearFlag();
}




/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "digit_cnn.h"
#include "digit_cnn_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
stm32_vcp vcp;

ai_handle network = AI_HANDLE_NULL;
ai_float activations[AI_DIGIT_CNN_DATA_ACTIVATIONS_SIZE];
ai_float in_data[AI_DIGIT_CNN_IN_1_SIZE];
ai_float out_data[AI_DIGIT_CNN_OUT_1_SIZE];

static ai_buffer *ai_input;
static ai_buffer *ai_output;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void aiInit(void){
  char buf[50];
  int buf_len = 0;
  ai_network_params params;
  ai_error ai_err;

  // Create instance of neural network
  ai_err = ai_digit_cnn_create(&network, NULL);
  if (ai_err.type != AI_ERROR_NONE)
  {
    buf_len = sprintf(buf, "Error: could not create NN instance\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
    while(1);
  }

  ai_digit_cnn_data_params_get(&params);
  // Initialize neural network
  AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, 0, activations);
  if (!ai_digit_cnn_init(network, &params))
  {
    buf_len = sprintf(buf, "Error: could not initialize NN\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
    while(1);
  }

  ai_input = ai_digit_cnn_inputs_get(network, NULL);
  ai_output = ai_digit_cnn_outputs_get(network, NULL);
}

int aiRun(const void *in_data, void *out_data){
  ai_i32 n_batch;
  ai_error err;

  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].data = AI_HANDLE_PTR(out_data);
  n_batch = ai_digit_cnn_run(network, &ai_input[0], &ai_output[0]);

  if (n_batch != 1) {
    printf("Error: could not run inference\r\n");
    err = ai_digit_cnn_get_error(network);
    printf("E: AI error - type=0x%x code=0x%x\r\n", err.type, err.code);
  };

  return 0;
}

void tic(){
  __HAL_TIM_SetCounter(&htim11, 0);
  HAL_TIM_Base_Start(&htim11);
}

uint16_t toc(){
  HAL_TIM_Base_Stop(&htim11);
  uint16_t duration = __HAL_TIM_GetCounter(&htim11);
  return duration;
}

uint16_t get_packet_size(){
  uint16_t packet_size = 0;
  uint8_t *ptr = (uint8_t*)&packet_size;
  for(int i = 1; i < 3; i++){
    *(ptr++) = *(vcp.rx_buffer + i);
  }
  return packet_size;
}

void copy_byte(uint8_t *src, uint8_t* dst, uint16_t size){
  for(int i = 0; i < size; i++){
    *(dst++) = *(src++);
  }
}

uint8_t unpack_data(){
  uint8_t *dst;
  switch(vcp.rx_buffer[0]){
  case 'I':
    dst = (uint8_t*)in_data;
    break;
  }

  copy_byte(&vcp.rx_buffer[3], dst, vcp.rx_buffer_index-3);
  vcp.rx_buffer_index=0;
  return (vcp.rx_buffer[0] == 'I')?1:0;
}

uint16_t f_argmax(float *data, uint16_t len){
  uint16_t max_pos = 0;
  for(int i = 0; i < len; i++){
    if(data[max_pos]<data[i]){
        max_pos = i;
    }
  }
  return max_pos;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char buf[50];
  int buf_len = 0;
  uint16_t duration;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  aiInit();
  HAL_UART_Receive_IT(&huart2, &vcp.rx_data, 1);

  buf_len = sprintf(buf, "\r\n\r\nSTM32 X-Cube-AI classifier for MNIST\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);

  uint16_t packet_size = 0;
  uint16_t predict = 0;
  uint8_t mcu_status = 0; // 0:Receive Test Image, 1: execute mcu process
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if(mcu_status){
      tic();
      aiRun(in_data, out_data);
      duration = toc();
      predict = f_argmax(out_data, AI_DIGIT_CNN_OUT_1_SIZE);

      HAL_UART_Transmit(&huart2, (uint8_t *)&predict, 2, 10);
      HAL_UART_Transmit(&huart2, (uint8_t *)&duration, 2, 10);
      printf("Predict: %u | Duration: %u\r\n", predict, duration);
      mcu_status=0;
    }else{
      if (vcp.rx_buffer_index>=3 && packet_size==0){
        packet_size = get_packet_size();
      }
      if (vcp.rx_buffer_index >= packet_size+3 && packet_size){
        mcu_status = unpack_data();
        packet_size = 0;
      }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx=0; DataIdx<len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

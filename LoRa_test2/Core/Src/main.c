/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint8_t check_ver;
uint8_t check_ver2;
uint8_t addrval;
bool testvar;
bool testvar2;
uint32_t costtime;
LoRa myLoRa;
float testfloat;
uint32_t lastTic;
uint16_t intervalTime;
uint8_t FlightModeON;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
float hex2float(uint8_t* hexNum);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  myLoRa.hSPIx = &hspi4;
  myLoRa.CS_port = SPI4_CS_GPIO_Port;
  myLoRa.CS_pin = SPI4_CS_Pin;
  myLoRa.reset_port = LoRa_RST_GPIO_Port;
  myLoRa.reset_pin = LoRa_RST_Pin;
  myLoRa.DIO0_port = DIO0_GPIO_Port;
  myLoRa.DIO0_pin = DIO0_Pin;
  myLoRa.DIO1_port = DIO1_GPIO_Port;
  myLoRa.DIO1_pin = DIO1_Pin;
  myLoRa.DIO2_port = DIO2_GPIO_Port;
  myLoRa.DIO2_pin = DIO2_Pin;
  myLoRa.LoRa_modem = LORA_MODEM;
  myLoRa.frequency = 425;           //MHz
  myLoRa.bandWidth = BW_125KHz;
  myLoRa.crcRate = CR_4_5;
  myLoRa.implicit_on = EXPLICIT;
  myLoRa.CRCon = 0;
  myLoRa.spredingFactor = SF_7;
  myLoRa.preamble = 10;
  myLoRa.paselect = RFO;
  myLoRa.maxpower = 7;
  myLoRa.outputpower = 10;                //0~15
//  myLoRa.paselect = PA_BOOST;
//  myLoRa.maxpower = 7;
//  myLoRa.outputpower = 15;
  myLoRa.PaDac = 0x84;      //0x84:max power = 17dBm   0x87:max power = 20dBm in PA_BOOST pin//-4~15
  HAL_GPIO_WritePin(FEM_CPS_GPIO_Port, FEM_CPS_Pin, GPIO_PIN_SET);      //low frequency port switch, RESET for transmit, SET for receive
//  HAL_GPIO_WritePin(FEM_CTX_GPIO_Port, FEM_CTX_Pin, GPIO_PIN_RESET);    //high frequency port switch
  myLoRa.PaOcp = 20;                     //output current protect, default=0x0B=11, max=27
  myLoRa.TCXOon = 0;
  myLoRa.packetSize = 68;

  LoRa_init(&myLoRa);              //initialize LoRa configuration
  lastTic = 0;
  intervalTime = 1000;
  FlightModeON = 1;
//  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
//	  HAL_Delay(1);
//	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
//	  HAL_Delay(100);
	  //test program of LoRa_readReg(), SPI send to MOSI: register address, SPI read from MISO: register data
//	  uint8_t adrs = 0x00;
//	  uint16_t adrs_leng = sizeof(adrs);
//	  uint8_t output;
//	  uint16_t output_length = 1;
//	  LoRa_readReg(&myLoRa, &adrs, adrs_leng, &check_ver, output_length);  //in LoRa user manual, read register = 0XXXXXXX
//	  addrval = output;

	  //test program of LoRa_writeReg(), SPI send to MOSIc: 1.register address 2.1 Byte data
//	  uint8_t adrs2 = SX127x_OpMode;
//	  uint16_t adrs2_leng = sizeof(adrs2);
//	  uint8_t send_value;
//	  send_value = 0x01;
//	  adrs2 = adrs2|0x80;   //in LoRa user manual, write register = 1XXXXXXX
//	  uint16_t send_length = 1;
//	  LoRa_writeReg(&myLoRa, &adrs2, adrs2_leng, &send_value, send_length);

	  //test program of LoRa_read_single()
//	  uint8_t adrs3 = SX127x_OpMode;
//	  uint8_t output2;
//	  output2 = LoRa_read_single(&myLoRa, adrs3);

	  //test program of LoRa_write_single()
//	  uint8_t adrs4 = SX127x_OpMode;
//	  uint8_t send_value2;
//	  send_value2 = 0x09;
//	  LoRa_write_single(&myLoRa, adrs4, send_value2);

	  //test program of LoRa_BurstWrite()
//	  uint8_t adrs4 = SX127x_OpMode;
//	  uint8_t send_value2[2];
//	  uint8_t value2_leng = sizeof(send_value2);
//	  send_value2[0] = 0x09;
//	  send_value2[1] = 0x01;
//	  LoRa_BurstWrite(&myLoRa, adrs4, send_value2, value2_leng);

	  //test program of LoRa_gotoMode()
//	  LoRa_gotoMode(&myLoRa, STANDBY_MODE);
//	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

//	  testvar=1;
//	  //test program of LoRa_transmit()
//	  uint8_t send_value3[myLoRa.packetSize];
//	  uint8_t value3_leng = sizeof(send_value3)/sizeof(send_value3[0]);
//	  uint8_t state;
//
//	  for (int i = 0; i<myLoRa.packetSize;i++){
//		  send_value3[i]=i;
//	  }
//	  state = LoRa_transmit(&myLoRa, send_value3, value3_leng, TRANSMIT_TIMEOUT);
//
//	  testvar=0;
////	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
//	  HAL_Delay(500);


	  //LoRa_transmit()
//	  uint8_t send_value[myLoRa.packetSize];
//	  uint8_t send_leng = sizeof(send_value)/sizeof(send_value[0]);
//	  uint8_t state;
////	  assign transmit data start
//	  for (int i = 0;i<=myLoRa.packetSize;i++){
//		  send_value[i] = i;
//	  }
////	  assign transmit data end
//	  HAL_GPIO_WritePin(FEM_CPS_GPIO_Port, FEM_CPS_Pin, GPIO_PIN_RESET);      //low frequency port switch, RESET for transmit, SET for receive
//      state = LoRa_transmit(&myLoRa, send_value, send_leng, TRANSMIT_TIMEOUT);

	  //LoRa_receive()
      uint8_t read_value[128];
      uint8_t read_leng = sizeof(read_value)/sizeof(read_value[0]);
      HAL_GPIO_WritePin(FEM_CPS_GPIO_Port, FEM_CPS_Pin, GPIO_PIN_SET);      //low frequency port switch, RESET for transmit, SET for receive
      check_ver = LoRa_receive(&myLoRa, read_value, read_leng);//return received size
      for(int i =0;i<read_leng;i++){
    	  check_ver2 = read_value[i];
      }

/*
	  //IMU data structure
	  PacketCounter_adrs[0] = 0x10;
	  PacketCounter_adrs[1] = 0x20;
	  PacketCounter_length = 0x02;
	  PacketCounter_value[0] = 0x12; //12F5(hex) = 4853(dec)
	  PacketCounter_value[1] = 0xF5;

	  SampleTimeFine_adrs[0] = 0x10;
	  SampleTimeFine_adrs[0] = 0x60;
	  SampleTimeFine_length = 0x04;
	  SampleTimeFine_value[0] = 0x00;
	  SampleTimeFine_value[1] = 0x61;
	  SampleTimeFine_value[2] = 0x61;
	  SampleTimeFine_value[3] = 0x4A;

	  DeltaV_adrs[0] = 0x40;
	  DeltaV_adrs[1] = 0x10;
	  DeltaV_length = 0x0C;
	  DeltaV_x_value[0] = 0xBF;  //float to hex method(f2h): (sign bit)(1.mantissa(dec)*2^(exponent(dec)-127))
	  DeltaV_x_value[1] = 0x13;
	  DeltaV_x_value[2] = 0x12;
	  DeltaV_x_value[3] = 0x66;
	  DeltaV_y_value[0] = 0xBC;
	  DeltaV_y_value[1] = 0x33;
	  DeltaV_y_value[2] = 0xE5;
	  DeltaV_y_value[3] = 0xFE;
	  DeltaV_z_value[0] = 0x3F;
	  DeltaV_z_value[1] = 0x4A;
	  DeltaV_z_value[2] = 0x4C;
	  DeltaV_z_value[3] = 0x80;*/

//	  uint8_t EulerAngles_Roll[4];
//	  EulerAngles_adrs[0] = 0x20;
//	  EulerAngles_adrs[1] = 0x30;
//	  EulerAngles_length = 0x0C; //length = 12
//	  EulerAngles_Roll[0] = 0x00;  //f2h    read from IMU
//	  EulerAngles_Roll[1] = 0x00;
//	  EulerAngles_Roll[2] = 0xF4;
//	  EulerAngles_Roll[3] = 0x41;
//	  testfloat = hex2float(EulerAngles_Roll);     //hex convert to float example
//	  EulerAngles_Pitch[0] = 0xE4;
//	  EulerAngles_Pitch[1] = 0x43;
//	  EulerAngles_Pitch[2] = 0x28;
//	  EulerAngles_Pitch[3] = 0x50;
//	  EulerAngles_Yaw[0] = 0xCE;
//	  EulerAngles_Yaw[1] = 0x40;
//	  EulerAngles_Yaw[2] = 0x10;
//	  EulerAngles_Yaw[3] = 0x0C;

 /* FreeAcceleration_adrs[0] = 0x40;
	  FreeAcceleration_adrs[1] = 0x30;
	  FreeAcceleration_length = 0x0C;
	  FreeAcceleration_x_value[0] = 0x3D;  //f2h
	  FreeAcceleration_x_value[1] = 0x32;
	  FreeAcceleration_x_value[2] = 0xA1;
	  FreeAcceleration_x_value[3] = 0xA8;
	  FreeAcceleration_y_value[0] = 0xBC;
	  FreeAcceleration_y_value[1] = 0x19;
	  FreeAcceleration_y_value[2] = 0x9B;
	  FreeAcceleration_y_value[3] = 0xE5;
	  FreeAcceleration_z_value[0] = 0x3C;
	  FreeAcceleration_z_value[1] = 0x42;
	  FreeAcceleration_z_value[2] = 0x0C;
	  FreeAcceleration_z_value[3] = 0x00;

	  RateOfTurn_adrs[0] = 0x80;
	  RateOfTurn_adrs[1] = 0x20;
	  RateOfTurn_length = 0x0C;
	  RateOfTurn_x_value[0] = 0xBD;  //f2h
	  RateOfTurn_x_value[1] = 0x30;
	  RateOfTurn_x_value[2] = 0x11;
	  RateOfTurn_x_value[3] = 0x60;
	  RateOfTurn_y_value[0] = 0x3D;
	  RateOfTurn_y_value[1] = 0x0A;
	  RateOfTurn_y_value[2] = 0xC0;
	  RateOfTurn_y_value[3] = 0x6D;
	  RateOfTurn_z_value[0] = 0xBC;
	  RateOfTurn_z_value[1] = 0x9F;
	  RateOfTurn_z_value[2] = 0x7A;
	  RateOfTurn_z_value[3] = 0x18;

	  DeltaQ_adrs[0] = 0x80;
	  DeltaQ_adrs[1] = 0x30;
	  DeltaQ_length = 0x10;  //length = 16
	  DeltaQ_q0_value[0] = 0x3F;  //f2h
	  DeltaQ_q0_value[1] = 0x7F;
	  DeltaQ_q0_value[2] = 0xFF;
	  DeltaQ_q0_value[3] = 0xB8;
	  DeltaQ_q1_value[0] = 0xBB;
	  DeltaQ_q1_value[1] = 0x0E;
	  DeltaQ_q1_value[2] = 0x3E;
	  DeltaQ_q1_value[3] = 0x1D;
	  DeltaQ_q2_value[0] = 0x3A;
	  DeltaQ_q2_value[1] = 0xDA;
	  DeltaQ_q2_value[2] = 0xED;
	  DeltaQ_q2_value[3] = 0x2E;
	  DeltaQ_q3_value[0] = 0xBA;
	  DeltaQ_q3_value[1] = 0x80;
	  DeltaQ_q3_value[2] = 0xAC;
	  DeltaQ_q3_value[3] = 0x88;

	  Temperature_adrs[0] = 0x08;
	  Temperature_adrs[1] = 0x10;
	  Temperature_length = 0x04;
	  Temperature_value[0] = 0x41;  //f2h
	  Temperature_value[1] = 0xF2;
	  Temperature_value[2] = 0xA0;
	  Temperature_value[3] = 0x00;

	  BaroPressure_adrs[0] = 0x30;
	  BaroPressure_adrs[1] = 0x10;
	  BaroPressure_length = 0x04;
	  BaroPressure_value[0] = 0x00;
	  BaroPressure_value[1] = 0x01;
	  BaroPressure_value[2] = 0x84;
	  BaroPressure_value[3] = 0x4E;

	  StatusWord_adrs[0] = 0xE0;
	  StatusWord_adrs[1] = 0x20;
	  StatusWord_length = 0x04;
	  StatusWord_value[0] = 0x00;
	  StatusWord_value[1] = 0x00;
	  StatusWord_value[2] = 0x00;
	  StatusWord_value[3] = 0x03;

	  //motor data
	  motor_deflect_adrs = 0x00;  //define by myself
	  motor_deflect_length = 0x04;
	  motor_deflect_value[0] = 0x01;
	  motor_deflect_value[1] = 0x02;
	  motor_deflect_value[2] = 0x03;
	  motor_deflect_value[3] = 0x04;
*/

//	  switch (FlightModeON){
//	  case 1://on the ground
//	  //LoRa_transmit()
//	  uint8_t send_value[myLoRa.packetSize];
//	  uint8_t send_leng = sizeof(send_value)/sizeof(send_value[0]);
//	  uint8_t state;
////	  assign transmit data start
//	  for (int i = 0;i<=myLoRa.packetSize;i++){
//		  send_value[i] = i;
//	  }
////	  assign transmit data end
//	  HAL_GPIO_WritePin(FEM_CPS_GPIO_Port, FEM_CPS_Pin, GPIO_PIN_RESET);      //low frequency port switch, RESET for transmit, SET for receive
//      state = LoRa_transmit(&myLoRa, send_value, send_leng, TRANSMIT_TIMEOUT);
//
//	  //LoRa_receive()
//      lastTic = HAL_GetTick();
//      while(HAL_GetTick()-lastTic<intervalTime){
//    	  uint8_t read_value[2];
//    	  uint8_t read_leng = sizeof(read_value)/sizeof(read_value[0]);
//    	  HAL_GPIO_WritePin(FEM_CPS_GPIO_Port, FEM_CPS_Pin, GPIO_PIN_SET);      //low frequency port switch, RESET for transmit, SET for receive
//    	  check_ver = LoRa_receive(&myLoRa, read_value, 0);//return received size
//      }
//		  break;
//	  case 2://flight mode
//		  send_length = sizeof(send_value)/sizeof(send_value[0]);
//		  state = LoRa_transmit(&myLoRa, send_value, send_length, TRANSMIT_TIMEOUT);
//		  break;
//	  }



//	  for (int i = 0;i<=3;i++){
//		  send_value[i] = EulerAngles_Roll[i];
//	  }
//	  state = LoRa_transmit(&myLoRa, send_value, value3_leng, TRANSMIT_TIMEOUT);

//	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
//	  HAL_Delay(200);
//	  testvar = 0;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float hex2float(uint8_t* hexNum){
    union {
        char conv_char[4];
        float output_float;
    } uni;
    uni.conv_char[3] = (char)(hexNum[3]);
    uni.conv_char[2] = (char)(hexNum[2]);
    uni.conv_char[1] = (char)(hexNum[1]);
    uni.conv_char[0] = (char)(hexNum[0]);

    return uni.output_float;
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
//	testvar=1;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);



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

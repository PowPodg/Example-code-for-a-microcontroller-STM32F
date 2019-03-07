#include "analog_in.h"
/*
 * Choice ADC1 and ADC3, because only ADC1 and ADC3 can generate a DMA request.
 */
volatile u16 Data_ADC_Data_IU_DMA[SizeArray_U_I*2];
//------------------------------ADC for measure current -------------------------------------------------
void ADC1_I_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;       //sequence length (the total quantity of conversions)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//Sample time 7.5 cycles - The total conversion time is Sampling time + 12.5 cycles ~ 1.43us (CLK=14MHz for ADC)
	//for number conversion 1 in regular sequence, set ADC1 Channel_1
	//ADC_Channel_1 is pin PA1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1,ADC_SampleTime_7Cycles5);  // define regular conversion config
	ADC_Init (ADC1, &ADC_InitStructure);	//set config of ADC1

	  /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

// enable ADC1
	ADC_Cmd (ADC1,ENABLE);	//enable ADC1

// Enable ADC1 DMA */
//    ADC_DMACmd(ADC1, ENABLE);

	//	ADC calibration (optional, but recommended at power on)
		ADC_ResetCalibration(ADC1);	// Reset previous calibration
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);	// Start new calibration
		while(ADC_GetCalibrationStatus(ADC1));


}
//-------------------------------ADC for measure voltage------------------------------------------
void ADC3_U_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;       //sequence length (the total quantity of conversions)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//Sample time 7.5 cycles - The total conversion time is Sampling time + 12.5 cycles ~ 1.43us (CLK=14MHz for ADC)
	//for number conversion 1 in regular sequence, set ADC3 Channel_2
	//ADC_Channel_2 is pin PA2
	ADC_RegularChannelConfig(ADC3,ADC_Channel_2, 1,ADC_SampleTime_7Cycles5);  // define regular conversion config
	ADC_Init (ADC3, &ADC_InitStructure);	//set config of ADC3

	// Enable ADC3 DMA
    ADC_DMACmd(ADC3, ENABLE);

// enable ADC3
	ADC_Cmd (ADC3,ENABLE);	//enable ADC3




	//	ADC calibration (optional, but recommended at power on)
		ADC_ResetCalibration(ADC3);	// Reset previous calibration
		while(ADC_GetResetCalibrationStatus(ADC2));
		ADC_StartCalibration(ADC3);	// Start new calibration
		while(ADC_GetCalibrationStatus(ADC3));


}

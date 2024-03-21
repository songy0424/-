#include "bsp_adc.h"
#include "init.h"

__IO uint16_t ADC_ConvertedValue;

static void ADC1_GPIO_Config(void)
{
	GPIO_INIT(GPIOA,GPIO_Pin_1,GPIO_Mode_AIN);
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	ADC_InitTypeDef ADC_InitStruct;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE );
	
	ADC_InitStruct.ADC_Mode = 							ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = 			DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = 	ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = 					ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 			1;
	
	ADC_Init(ADC_x,&ADC_InitStruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

	ADC_Cmd(ADC_x, ENABLE);
	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADC_x, ENABLE);
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
}

void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC_Mode_Config();	
}

float Read_ADC_data(void)
{
	float kk=0;
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//����_ADC�������-����    ״̬�Ĵ���Ϊ0
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//�ȴ�ת������
	kk=(((float)ADC_GetConversionValue(ADC1)/4096)*33); 
	//�ٷֱ�ֵת���ɵ�ѹֵ��    ��Ϊ��ȡ�����ݼĴ�����״̬�Ĵ����Զ���0
	
//	kk=(float) ADC_ConvertedValue/4096*12.7;
	return kk;
	//���ص�ѹֵ
}

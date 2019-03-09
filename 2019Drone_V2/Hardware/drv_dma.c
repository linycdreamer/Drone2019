#include "drv_dma.h"
/**
  * @brief  Initializes the DMAy Channelx according to the specified parameters
  * @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
  *   DMA Channel.
  * @param DMA_PeripheralBaseAddr  Specifies the peripheral base address for DMAy Channelx. 
  * @param DMA_MemoryBaseAddr      Specifies the memory base address for DMAy Channelx. 
  * @param DMA_DIR                 Specifies if the peripheral is the source or destination. 
  *        @arg DMA_DIR_PeripheralDST              
  *        @arg DMA_DIR_PeripheralSRC              
  * @param DMA_BufferSize          Specifies the buffer size, in data unit, of the specified Channel. 
  * @param DMA_PeripheralInc       Specifies whether the Peripheral address register is incremented or not.
  *        @arg DMA_PeripheralInc_Enable          
  *        @arg DMA_PeripheralInc_Disable         
  * @param DMA_MemoryInc           Specifies whether the memory address register is incremented or not.
  *        @arg DMA_MemoryInc_Enable              
  *        @arg DMA_MemoryInc_Disable          
  * @param DMA_PeripheralDataSize  Specifies the Peripheral data width.
  *        @arg DMA_PeripheralDataSize_Byte       
  *        @arg DMA_PeripheralDataSize_HalfWord    
  *        @arg DMA_PeripheralDataSize_Word       
  * @param DMA_MemoryDataSize      Specifies the Memory data width.
  *        @arg DMA_MemoryDataSize_Byte           
  *        @arg DMA_MemoryDataSize_HalfWord       
  *        @arg DMA_MemoryDataSize_Word           
  * @param DMA_Mode                Specifies the operation mode of the DMAy Channelx.    
  *        @arg DMA_Mode_Circular                  
  *        @arg DMA_Mode_Normal                   
  * @param DMA_Priority            Specifies the software priority for the DMAy Channelx.   
  *        @arg DMA_Priority_VeryHigh              
  *        @arg DMA_Priority_High                 
  *        @arg DMA_Priority_Medium               
  *        @arg DMA_Priority_Low                  
  * @param DMA_M2M   
  *        @arg DMA_M2M_Enable                    
  *        @arg DMA_M2M_Disable                    
  * @retval : None
  */
void DMA_Config(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t DMA_PeripheralBaseAddr,uint32_t DMA_MemoryBaseAddr,
	                uint32_t DMA_DIR,uint32_t DMA_BufferSize,uint32_t DMA_PeripheralInc,
                    uint32_t DMA_MemoryInc,uint32_t DMA_PeripheralDataSize,uint32_t DMA_MemoryDataSize,
                    uint32_t DMA_Mode,uint32_t DMA_Priority,uint32_t DMA_M2M)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMAy_Channelx);
	DMA_InitStructure.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DMA_MemoryBaseAddr;
	DMA_InitStructure.DMA_DIR = (uint32_t)DMA_DIR;	
	DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize;
	DMA_InitStructure.DMA_Mode = DMA_Mode;
	DMA_InitStructure.DMA_Priority = DMA_Priority;
	DMA_InitStructure.DMA_M2M = DMA_M2M;
	DMA_Init(DMAy_Channelx, &DMA_InitStructure);

}



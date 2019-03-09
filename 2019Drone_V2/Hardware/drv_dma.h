#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "misc.h"
void DMA_Config(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t DMA_PeripheralBaseAddr,uint32_t DMA_MemoryBaseAddr,
	                uint32_t DMA_DIR,uint32_t DMA_BufferSize,uint32_t DMA_PeripheralInc,
                    uint32_t DMA_MemoryInc,uint32_t DMA_PeripheralDataSize,uint32_t DMA_MemoryDataSize,
                    uint32_t DMA_Mode,uint32_t DMA_Priority,uint32_t DMA_M2M);
#endif


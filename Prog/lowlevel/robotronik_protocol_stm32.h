#ifndef RPV1_STM32_H
#define RPV1_STM32_H

#define CAT_MK(x, y) x##y
#define CAT(x, y) CAT_MK(x,y)
#define USARTx(x) CAT(USART, x)
#define DMAx(x) CAT(DMA, x)
#define LL_DMA_CHANNEL_x(x) CAT(LL_DMA_CHANNEL_, x)
#define REMAINING_DATA(dma_x, dma_channel_x) LL_DMA_GetDataLength(DMAx(dma_x), LL_DMA_CHANNEL_x(dma_channel_x))
#define RECEIVED_DATA(dma_x, dma_channel_x) (RP_BUFFER_SIZE - REMAINING_DATA(dma_x, dma_channel_x))

#define RP_INIT_UART_DMA(dma, dma_channel, usart, iface)		\
  LL_DMA_SetMemoryAddress(dma, dma_channel, (uint32_t) iface.buffer_in); \
  LL_DMA_SetDataLength(dma, dma_channel, sizeof(iface.buffer_in));	\
  LL_DMA_SetPeriphAddress(dma, dma_channel, (uint32_t) &usart->RDR);	\
  LL_DMA_EnableIT_HT(dma, dma_channel);					\
  LL_DMA_EnableIT_TC(dma, dma_channel);					\
  LL_DMA_EnableChannel(dma, dma_channel);				\
									\
  LL_USART_EnableDMAReq_RX(usart);					\
  LL_USART_EnableIT_IDLE(usart);					\
  LL_USART_Enable(usart);

#define USARTx_IRQHandler(usart_x, dma_x, dma_channel_x, iface)		\
  /* When USART is IDLE, ie. the last frame period was empty. */	\
  if(LL_USART_IsActiveFlag_IDLE(USARTx(usart_x))){				\
    /* Acquit interrupt */						\
    LL_USART_ClearFlag_IDLE(USARTx(usart_x));					\
    									\
    /* Number of bytes received since the last Transfert Complete event */ \
    uint16_t next_pos = RECEIVED_DATA(dma_x, dma_channel_x);		\
									\
    /* Number of bytes to process */					\
    uint16_t len = next_pos - iface.sync_pos;					\
									\
    if(len > 0){							\
      RP_Process_Data(&iface, iface.buffer_in + iface.sync_pos, len);	\
    }									\
    iface.sync_pos = next_pos; 		\
    }

#define FLAG_END(flag, dma_x, dma_channel_x) CAT(flag, dma_channel_x)(CAT(DMA, dma_x))
#define LL_DMA_IsActiveFlag_xx(flag, dma_x, dma_channel_x) CAT(LL_DMA_IsActiveFlag_, FLAG_END(flag, dma_x, dma_channel_x))
#define LL_DMA_ClearFlag_xx(flag, dma_x, dma_channel_x) CAT(LL_DMA_ClearFlag_, FLAG_END(flag, dma_x, dma_channel_x))

#define DMAx_Streamx_IRQHandler(dma_x, dma_channel_x, iface)	\
  uint16_t next_pos;						\
  /* Transfert Complete, ie. buffer loop complete */		\
  if(LL_DMA_IsActiveFlag_xx(TC, dma_x, dma_channel_x)){		\
    /* Acquit interrupt */					\
    LL_DMA_ClearFlag_xx(TC, dma_x, dma_channel_x);		\
    								\
    /* Process the data until the end of the buffer */			\
    RP_Process_Data(&iface, iface.buffer_in + iface.sync_pos, RP_BUFFER_SIZE - iface.sync_pos); \
									\
    iface.sync_pos = 0;								\
  }/* Transfert Half Complete */					\
  else if(LL_DMA_IsActiveFlag_xx(HT, dma_x, dma_channel_x)){		\
  /*									\
   * This is necessary to process the beginning of buffer before it	\
   * overflows, in case of a big packet.				\
   */									\
									\
    /* Acquit interrupt */						\
    LL_DMA_ClearFlag_xx(HT, dma_x, dma_channel_x);			\
									\
    /* Number of bytes received since the last Transfert Complete event */ \
    next_pos = RECEIVED_DATA(dma_x, dma_channel_x);			\
									\
    RP_Process_Data(&iface, iface.buffer_in + iface.sync_pos, next_pos - iface.sync_pos); \
									\
    iface.sync_pos = next_pos;							\
  }

#endif

#include "tinyOS.h"

void tMemBlockInit (tMemBlock * memblock, uint8_t * memStart, uint32_t blockSize,uint32_t blockCnt)
{
	uint8_t * memBlockStart = (uint8_t *) memStart;
	uint8_t * memBlockEnd = memBlockStart +blockSize * blockCnt;
	
	if (blockSize < sizeof (tNode))
	{
		return;
	}
	
	tEventInit(&memblock->event, tEventTypeMemBlock);
	memblock->memStart = memStart;
	memblock->blockSize = blockSize;
	memblock->maxCount = blockCnt;
	
	tListInit(&memblock->blockList);
	while (memBlockStart< memBlockEnd)
	{
		tNodeInit((tNode *) memBlockStart);
		tListAddLast(&memblock->blockList, (tNode *)memBlockStart);
		
		memBlockStart += blockSize;
	}
}

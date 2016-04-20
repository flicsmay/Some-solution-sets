#include "csapp.h"

/*
	The behavior of :	malloc()
						place()
	should be changed in this problem
 */

#define WORD_SIZE		4
#define DOUBLE_SIZE		8
#define CHUNK_SIZE		(1 << 12)


static void placeHeaderFooter(void *basePointer, size_t actualNeedSize)
{
	size_t sparedSize = GET_SIZE(HEADER(basePointer));
	size_t remainedSize = sparedSize - actualNeedSize;

	if (remainedSize >= DOUBLE_SIZE) {
		PUT(HEADER(basePointer), PACK(actualNeedSize, 1));
		basePointer = NEXT_BLOCK_HEADER(basePointer);

		PUT(HEADER(basePointer), PACK(remainedSize, 0));
		PUT(FOOTER(basePointer), PACK(remainedSize, 0));
	}
	else
		PUT(HEADER(basePointer), PACK(sparedSize, 1));
}



void *mm_malloc(size_t requireSize)
{
	size_t actualSize;
	size_t extendHeapSize;
	char *basePointer;

	if (requireSize == 0)
		return NULL;

	if (requireSize <= WORD_SIZE)
		actualSize = DOUBLE_SIZE;
	else
		actualSize = DOUBLE_SIZE * ((requireSize + WORD_SIZE) / DOUBLE_SIZE);

	if ((basePointer = find_fit(requireSize)) != NULL) {
		placeHeaderFooter(basePointer, actualSize);
		return basePointer;
	}

	extendHeapSize = max(actualSize, CHUNK_SIZE);
	if ((basePointer = extend_heap(extendHeapSize / WORD_SIZE)) == NULL)
		return NULL;
	placeHeaderFooter(basePointer, actualSize);
	return basePointer;
}
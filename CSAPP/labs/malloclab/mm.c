/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "Ateam",
    /* First member's full name */
    "flicsmay",
    /* First member's email address */
    "490284973@qq.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

#define WORD_SIZE							4
#define DOUBLE_SIZE							8
#define ALIGNMENT							DOUBLE_SIZE
#define MIN_BLOCK_SIZE						DOUBLE_SIZE
#define HEADER_SIZE							WORD_SIZE
#define FOOTER_SIZE							WORD_SIZE
#define SIZE_T_SIZE							(ALIGN(sizeof(size_t)))


/* rounds up to the nearest multiple of ALIGNMENT */

#define ALIGN(size)							(((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1)) // rounds up to the nearest mutiply of alignment
#define GET_SIZE(headptr)					(*(unsigned int *)(headptr) & ~(ALIGNMENT - 1))

#define MAX(x, y)							((x) > (y) ? (x) : (y))

// test if the block allocation

#define IS_ALLOCATED(headptr)				(*(unsigned int *)(headptr) & 0x1)
#define IS_FREED(headptr)					(!IS_ALLOCATED(headptr))
#define IS_PREVIOUS_FREED(headptr)			(!(*(unsigned int *)(headptr) & (0x1 << 1)))
#define IS_EPLIOGUE(headptr)				(!(GET_SIZE(headptr)))

#define HEADER(contentptr)					((char *)(contentptr) - HEADER_SIZE)
#define FOOTER(headptr)						((char *)(headptr) + GET_SIZE(headptr) - FOOTER_SIZE)

// used to put header and footer

#define PLACE_HEADER(headptr, blockSize)	(*(unsigned int *)(headptr) = blockSize)
#define PLACE_FOOTER(headptr)				(*(unsigned int *)FOOTER(headptr) = GET_SIZE(headptr))
#define PLACE_EPLIOGUE(headptr)				(PLACE_HEADER(headptr, 1))
#define CHANGE_SIZE(headptr, blockSize)		(*(unsigned int *)(headptr) = (blockSize & ~0x7))

// set the header indicate bits to allocated or unallocated

#define SET_ALLOCATE_DEFAULT(headptr)		(*(unsigned int *)(headptr) |= 0x7)
#define SET_UNALLOCATE(headptr)				(*(unsigned int *)(headptr) &= (~0x1))
#define SET_PREVIOUS_FREE(headptr)			(*(unsigned int *)(headptr) &= (~(0x1 << 1)))

// given the current headpointer compute the next and previous header address

#define PREVIOUS_BLOCK_HEADER(headptr)		((char *)(headptr) - GET_SIZE((char *)(headptr) - FOOTER_SIZE))
#define NEXT_BLOCK_HEADER(headptr)			((char *)(headptr) + GET_SIZE((char *)(headptr)))

// return address of the content

#define CONTENT_ADDRESS(headptr)			((char *)(headptr) + HEADER_SIZE)



static char *HeapHeader;


static void * findSuitableSpace(size_t requiredSize);
static void placeHeaderFooter(void *headerptr, size_t requestedSize);
static void * extendHeap(size_t wordsRequired);
static void * coalesceFreeBlock(void *headerPointer);


int mm_init(void)
{
	mem_init();
	
	if ((HeapHeader = mem_sbrk(4 * WORD_SIZE)) == (void *)-1)
		return -1;
	// padder to alignment
	PLACE_HEADER(HeapHeader, 0);
	// place the prologue
	PLACE_HEADER(HeapHeader, DOUBLE_SIZE);
	PLACE_FOOTER(HeapHeader);
	SET_ALLOCATE_DEFAULT(HeapHeader);
	HeapHeader += 3 *WORD_SIZE;
	// place the epliogue
	PLACE_EPLIOGUE(HeapHeader);
	SET_ALLOCATE_DEFAULT(HeapHeader);

	if (extendHeap(mem_pagesize() / WORD_SIZE) == NULL)
		return -1;

    return 0;
}


void *mm_malloc(size_t requiredSize)
{
	size_t actualRequiredSize;
	size_t needExtendHeapSize;
	void * headerPointer;

	if (requiredSize == 0)
		return NULL;

	if ((requiredSize + HEADER_SIZE) < MIN_BLOCK_SIZE)
		actualRequiredSize = ALIGNMENT;
	else
		actualRequiredSize = ALIGN(requiredSize + HEADER_SIZE);
	
	if ((headerPointer = findSuitableSpace(actualRequiredSize)) != NULL) {
		placeHeaderFooter(headerPointer, actualRequiredSize);
		return CONTENT_ADDRESS(headerPointer);
	}

	needExtendHeapSize = MAX(requiredSize, mem_pagesize());
	if ((headerPointer = extendHeap(needExtendHeapSize / WORD_SIZE)) == NULL)
		return NULL;
	placeHeaderFooter(headerPointer, actualRequiredSize);
	return CONTENT_ADDRESS(headerPointer);
}


void mm_free(void *contentPointer)
{
	void * headerPointer = HEADER(contentPointer);

	SET_UNALLOCATE(headerPointer);
	PLACE_FOOTER(headerPointer);
	SET_PREVIOUS_FREE(NEXT_BLOCK_HEADER(headerPointer));

	coalesceFreeBlock(headerPointer);
}


void *mm_realloc(void *contentPointer, size_t requiredSize)
{
	void * headerPointer;
	void * basePointer;
	size_t actualRequiredSize;
	size_t oldSize;
	int index;

	if (contentPointer == NULL)
		mm_malloc(requiredSize);
	headerPointer = HEADER(contentPointer);

	if (IS_FREED(headerPointer))
		return NULL;

	if (requiredSize == 0)
		mm_free(contentPointer);

	oldSize = GET_SIZE(headerPointer);
	actualRequiredSize = oldSize + HEADER_SIZE;

	if (actualRequiredSize <= oldSize)
		return contentPointer;

	if (IS_EPLIOGUE(NEXT_BLOCK_HEADER(headerPointer)))
	{
		if (extendHeap((ALIGN(actualRequiredSize - oldSize)) / WORD_SIZE) == NULL)
			return NULL;
		CHANGE_SIZE(headerPointer, actualRequiredSize);
		PLACE_EPLIOGUE(NEXT_BLOCK_HEADER(headerPointer)); // place new epliogue

		// just keep the old epliogue there
		return CONTENT_ADDRESS(headerPointer);
	}
	// used malloc to set a new spaces
	if ((basePointer = mm_malloc(requiredSize)) == NULL)
		return NULL;

	for (index = 0; index < (oldSize - HEADER_SIZE); index++)
	{
		((unsigned int *)basePointer)[index] = ((unsigned int *)contentPointer)[index];
	}

	mm_free(contentPointer);
	return basePointer;
}


static void *findSuitableSpace(size_t requiredSize)
{
	void *headerPointer;

	for (headerPointer = HeapHeader; !(IS_EPLIOGUE(headerPointer)); headerPointer = NEXT_BLOCK_HEADER(headerPointer)) {
		if ((IS_FREED(headerPointer)) && requiredSize <= GET_SIZE(headerPointer))
			return headerPointer;
	}
	return NULL;
}


static void placeHeaderFooter(void *headerPtr, size_t requestedSize)
{
	size_t sparedSize = GET_SIZE(headerPtr);
	size_t remainedSize = sparedSize - requestedSize;

	if (remainedSize >= ALIGNMENT)
	{
		PLACE_HEADER(headerPtr, requestedSize);
		SET_ALLOCATE_DEFAULT(headerPtr);

		headerPtr = NEXT_BLOCK_HEADER(headerPtr);
		PLACE_HEADER(headerPtr, remainedSize);
		PLACE_FOOTER(headerPtr);
	}
	else
	{
		PLACE_HEADER(headerPtr, sparedSize);
	}
}


static void *extendHeap(size_t wordsRequired)
{
	void *headerPointer;
	size_t bytesRequired;

	bytesRequired = (wordsRequired % 2) ? (wordsRequired + 1) * WORD_SIZE : wordsRequired * WORD_SIZE;
	if ((long)(headerPointer = mem_sbrk(bytesRequired)) == -1)
		return NULL;

	headerPointer = FOOTER_SIZE; // set headptr to the current epilogue

	PLACE_HEADER(headerPointer, bytesRequired);
	PLACE_FOOTER(headerPointer);
	PLACE_EPLIOGUE(NEXT_BLOCK_HEADER(headerPointer));

	return coalesceFreeBlock(headerPointer);
}


static void * coalesceFreeBlock(void *headerPointer)
{
	size_t isPreviousFreed = IS_PREVIOUS_FREED(headerPointer);
	size_t isNextFreed = IS_FREED(NEXT_BLOCK_HEADER(headerPointer));
	size_t totalSize = GET_SIZE(headerPointer);

	if (!isNextFreed  && !isPreviousFreed) {
		return headerPointer;
	}
	else if (isNextFreed && !isPreviousFreed)
	{
		totalSize += GET_SIZE(NEXT_BLOCK_HEADER(headerPointer));
		PLACE_HEADER(headerPointer, totalSize);
		PLACE_FOOTER(headerPointer);
	}
	else if (!isNextFreed && isPreviousFreed)
	{
		totalSize += GET_SIZE(PREVIOUS_BLOCK_HEADER(headerPointer));
		headerPointer = PREVIOUS_BLOCK_HEADER(headerPointer);
		PLACE_HEADER(headerPointer, totalSize);
		PLACE_FOOTER(headerPointer);
	}
	else
	{
		totalSize += (GET_SIZE(NEXT_BLOCK_HEADER(headerPointer)) + GET_SIZE(PREVIOUS_BLOCK_HEADER(headerPointer)));
		headerPointer = PREVIOUS_BLOCK_HEADER(headerPointer);
		PLACE_HEADER(headerPointer, totalSize);
		PLACE_FOOTER(headerPointer);
	}
	return headerPointer;
}




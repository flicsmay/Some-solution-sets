#include "csapp.h"

static char * last_fit;

// use next fit policy to find a appropriate space
static void *find_fit(size_t asize)
{
	char *oldlast_fit = last_fit;

	// search form the last fit
	for (; GET_SIZE(HDRP(last_fit)) > 0; last_fit = NEXT_BLKP(last_fit))
		if (!GET_ALLOC(HDRP(last_fit)) && (asize <= GET_SIZE(HDRP(last_fit))))
			return last_fit;

	// if unfind above then search from the beginning
	for (last_fit = heap_listp; last_fit < oldlast_fit; last_fit = NEXT_BLKP(last_fit))
		if (!GET_ALLOC(HDRP(last_fit)) && (asize <= GET_SIZE(HDRP(last_fit))))
			return last_fit;

	// find nothing
	return NULL;
}

/*************************/
/*
	Meanwhile we should change the behavior of : coalesce()
	Don't make last_fir point to a freed place.

	if the last_fit point to the middle of a freed space
	then set it to the front of freed space
 */
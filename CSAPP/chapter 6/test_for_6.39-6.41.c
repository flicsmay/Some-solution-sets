/********************************************
 ********* test for 6.39 - 6.41 *************
 ********************************************/

#include <stdio.h>

#define N					16
#define BASE_ADDR			0
#define BLOCK_SIZE			64
#define CACHE_SIZE			1024
#define CACHE_SET			(CACHE_SIZE / BLOCK_SIZE)
struct point_color;
#define POINT_COLOR_SIZE	(sizeof(struct point_color) / sizeof(int))


struct point_color{
	int addr_0;
	int addr_1;
	int addr_2;
	int addr_3;
};

// regard the structure as an array which have 4[int] elems.
// But It may only correct while there are not alignment.
typedef int color_square_addr[N][N][POINT_COLOR_SIZE];

typedef int cache_simultor[CACHE_SET];

void clean_cache(cache_simultor cache)
{
	int i;
	
	for (i = 0; i < CACHE_SET; i++)
		cache[i] = 0;
}

void calculate_addr(color_square_addr addr)
{
	int i, j, k;
	int fst_addr_in_block = BASE_ADDR; // record the frst addr in cache block
	int addrs = BASE_ADDR;
	int size_int = sizeof(int);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < POINT_COLOR_SIZE; k++)
			{
				addr[i][j][k] = fst_addr_in_block;

				addrs += size_int;
				if (addrs % BLOCK_SIZE == 0)
					fst_addr_in_block = addrs;
			}
}

/* return 1 if occur a miss in cache */
int is_miss_cache(int addr, cache_simultor cache)
{
	int map_cache = addr % CACHE_SET;

	if (cache[map_cache] != addr)
	{
		cache[map_cache] = addr;
		return 1;
	}
	return 0;
}


void test_for_6_39(color_square_addr addr, cache_simultor cache)
{
	int i, j, k;
	int miss = 0;
	int total = 0;

	clean_cache(cache);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < POINT_COLOR_SIZE; k++)
			{
				miss += is_miss_cache(addr[i][j][k], cache);
				total++;
			}
	printf("***** 6.39 *****\n");
	printf("writen    : %d\n", total);
	printf("miss      : %d\n", miss);
	printf("miss rate : %.3f\n", (float)miss / (float)total);
}

void test_for_6_40(color_square_addr addr, cache_simultor cache)
{
	int i, j, k;
	int miss = 0;
	int total = 0;

	clean_cache(cache);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < POINT_COLOR_SIZE; k++)
			{
				miss += is_miss_cache(addr[j][i][k], cache);
				total++;
			}
	printf("***** 6.40 *****\n");
	printf("writen    : %d\n", total);
	printf("miss      : %d\n", miss);
	printf("miss rate : %.3f\n", (float)miss / (float)total);
}

void test_for_6_41(color_square_addr addr, cache_simultor cache)
{
	int i, j;
	int miss = 0;
	int total = 0;

	clean_cache(cache);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			miss += is_miss_cache(addr[i][j][2], cache);
			total++;
		}

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			miss += is_miss_cache(addr[i][j][0], cache);
			miss += is_miss_cache(addr[i][j][1], cache);
			miss += is_miss_cache(addr[i][j][3], cache);
			total += 3;
		}
	printf("***** 6.41 *****\n");
	printf("writen    : %d\n", total);
	printf("miss      : %d\n", miss);
	printf("miss rate : %.3f\n", (float)miss / (float)total);
}



int main()
{
	color_square_addr addr;
	cache_simultor cache;

	calculate_addr(addr);
	test_for_6_39(addr, cache);
	test_for_6_40(addr, cache);
	test_for_6_41(addr, cache);
}
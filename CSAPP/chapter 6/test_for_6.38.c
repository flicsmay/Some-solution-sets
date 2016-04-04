/************************************
 * A auto test program for 6.38
 ************************************/


#include <stdio.h>

#define N 60
#define BASE_ADDR	0x08000000
#define BLOCK_SZ	16
#define CACHE_SZ	4096
#define CACHE_SET	(CACHE_SZ / BLOCK_SZ)

typedef int address_t[N][N];
typedef int cache_simulator[CACHE_SET];

void calcul_addr(address_t a)
{
	int i, j;
	int addr_b = BASE_ADDR;
	int addr = BASE_ADDR;
	int sz_int = sizeof(int);
	
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			a[i][j] = addr_b;
			
			// set the four addrs indentical as the frist
			// in cache for easily checken.
			addr += sz_int;
			if (addr % BLOCK_SZ == 0)
				addr_b = addr;
		}
}

void clean_cache(int *cache_sim)
{
	int i;
	
	for (i = 0; i < CACHE_SET; i++)
		cache_sim[i] = 0;
}

/* return 1 if cache is miss */
int is_cache_miss(int addr, int *cache_sim)
{
	int cache_map = addr % CACHE_SET;

	// if miss then put addr in to the cache
	if (cache_sim[cache_map] != addr)
	{
		cache_sim[cache_map] = addr;
		return 1;
	}
	return 0;
}


float miss_rate_sumA(address_t a, int *cache_sim)
{
	int i, j;
	int total = 0;
	int miss = 0;
	
	clean_cache(cache_sim);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			miss += is_cache_miss(a[i][j], cache_sim);
			total++;
		}

	return (float)miss / (float)total;
}


float miss_rate_sumB(address_t a, int *cache_sim)
{
	int i, j;
	int total = 0;
	int miss = 0;

	clean_cache(cache_sim);

	for (j = 0; j < N; j++)
		for (i = 0; i < N; i++)
		{
			miss += is_cache_miss(a[i][j], cache_sim);
			total++;
		}

	return (float)miss / (float)total;
}

float miss_rate_sumC(address_t a, int *cache_sim)
{
	int i, j;
	int total = 0;
	int miss = 0;

	clean_cache(cache_sim);

	for (j = 0; j < N; j += 2)
		for (i = 0; i < N; i += 2)
		{
			// I'm not sure whether my order is correct or not.
			miss += is_cache_miss(a[i][j], cache_sim);
			miss += is_cache_miss(a[i+1][j], cache_sim);
			miss += is_cache_miss(a[i][j+1], cache_sim);
			miss += is_cache_miss(a[i+1][j+1], cache_sim);
			total += 4;
		}

	return (float)miss / (float)total;
}


int main()
{
	address_t addr;
	cache_simulator cache_sim;

	calcul_addr(addr);
	
	printf("%.3f\n", miss_rate_sumA(addr, cache_sim));
	printf("%.3f\n", miss_rate_sumB(addr, cache_sim));
	printf("%.3f\n", miss_rate_sumC(addr, cache_sim));
}
/*Problem 2.63*/

/*
 * perform logical right shift using
 * an arithmetic right shift
 * parameter k in the range of 0 to w-1
 */
unsigned srl(unsigned x, int k)
{
	/* Perform shift arithmetically*/
	unsigned xsra = (int)x >> k;

	unsigned w = (sizeof(int)) << 3;
	unsigned mask = 1 << (w - k);
	
	//make a mask that cover the least significant w-k bits, then imple and-op
	return xsra & (mask - 1);
}

/*
 * performs an archithmetic right shift
 * using a logical right shift
 * parameter k in the range of 0 to w-1 
 */
int sra(int x, int k)
{
	/* Perform shift logically */
	int xsrl = (unsigned)x >> k;

	unsigned w = (sizeof(int)) << 3;
	unsigned mask = (-1) << (w - k);

	if (x < 0)
	{
		//make a mask that switch most significant k bits then or-op
		return xsrl | mask;
	}
	return xsrl;
}


//int main()
//{
//	int i = 0xF1234567;
//
//	printf("%.2x\n", srl(i, 16));
//	printf("%.2x\n", sra(i, 16));
//}
////imple 16bits right shift should print 0xf123 and 0xfffff123
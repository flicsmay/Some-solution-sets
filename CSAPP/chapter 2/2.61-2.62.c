/*Prolems 2.61-2.62*/

//2.61
//A. !(~x)								//any bit of x equal 1
//B. !x									//any bit of x equal 0
//C. !((x & (0xFF)) ^ (0xFF))			//any bit in the least significant byte of x equals 1
//D. !(x >> ((sizeof(int) - 1) << 3))	//any bit in the most sifnificant byte of x equals 0


//2.62

/* return 1 when run on a machine that uses arithmetic right shifts */
int int_shifts_are_arithmetic(void)
{
	int i = -1;
	
	return (i >> 1) == -1;
}


//int main()
//{
//	(int_shifts_are_arithmetic()) ?
//		printf("YES\n") :
//		printf("NO\n");
//}
////it is using arithmetic shifts on my pc
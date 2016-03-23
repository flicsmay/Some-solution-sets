/* Problem 2.75 */

#include <limits.h>

int signed_high_prod(int x, int y);

/*
 * Return the high-order w-bits of two unsigned intergers mutiply.
 * call the function of signed_high_prod which will implement next.
 * As don't have to follow bit-lever integer rules , I will using
 *  mutiply and conditional (same as signed_high_prod)
 */
unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int w = sizeof(int) << 3;
	unsigned x_wth = x >> (w - 1); // remain the most signficant bit in x
	unsigned y_wth = y >> (w - 1); // remain the most signficant bit in y


	// in the Equation 2.18 (book chapt 2.34)
	// (x' * y') = [(x +x(w-1) * 2^w) * (y + y(w-1) * 2^2w)]
	// so (x' * y') / 2^w ( that is to remain high-order) can be conver to as follow
	return signed_high_prod(x, y) + x_wth * y + y_wth * x + x_wth * y_wth * (1 << w);
}


/*
 * Return the high-order w bits when 2 signed w-bits intergers mutiply
 * Simulate the procedure of the mutiply of binary numbers
 * My version of this procedure is rather complicated. You may use assemble or sth what :)
 */
int signed_high_prod(int x, int y)
{
	int w = sizeof(int) << 3;
	int high_w_bit = 0;
	int add_one = 1;// the high-order bit should add 1 when result is negati and low-order bits all 1
	int negative = 0;// indicate that whether the result is negative or not
	int i = 0;

	negative = (x < 0) ^ (y < 0);

	// switch tow-complement to unsigned the same below
	if (x < 0)
	{
		x = ~x;
		if (x != INT_MAX)
			x += 1;// should add 1 after NOT-op to keep the value. the same below
	}
	if (y < 0)
	{
		y = ~y;
		if (y != INT_MAX)
			y += 1;
	}

	// mutiply procedure
	for (i = 0; i < (w - 1); i++)
	{
		if (x & 0x1)
			high_w_bit += y;
		x >>= 1;
		if (add_one && (high_w_bit & 0x1) == 1)// if have 1 bit is 1 (0 after reverse) don't need to add1
			add_one = 0;
		high_w_bit >>= 1;
	}
	high_w_bit >>= 1;// one more shift right 
	if (negative)
	{
		high_w_bit = ~high_w_bit;// if negative then reverse
		if (add_one)
			high_w_bit += 1;
	}
	return high_w_bit;
}



//int main()
//{
//	int x = 1024 * 1024;// 2 exp 20
//	unsigned ux = 0x10000000;// 2 exp 28
//
//	printf("%.2x\n", signed_high_prod(x, -x));
//	printf("%.2x\n", unsigned_high_prod(ux, ux));
//}
//// print 0xffffff00 and 0x1000000
//// that is -(2^8) (20 +20 - 32) and 2^25 (28 + 28 - 31)
//// My two founction are not that robust so when you input INT_MIN
//// in anyone of arguments then the result is wrong :(




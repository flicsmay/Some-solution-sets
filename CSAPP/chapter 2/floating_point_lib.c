/* A small library for 2.91-2.96 */


typedef unsigned float_bits;

/* Return 1 if argument f is NaN, f is must 32-bits */
int is_NaN_32(float_bits f)
{
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	return (exp == 0xFF) && (frac != 0);
}


/* For testing */

unsigned f2u(float f)
{
	return *((unsigned *)&f);
}

float u2f(unsigned u)
{
	return *((float *)&u);
}


/* I used really want to write some more functions to test 
   whether my function is correct or not, as be asked to test 
   all functions with 2^32 all value. 
   I may back sometimes to finish it. I'm too lazy.. :^) */
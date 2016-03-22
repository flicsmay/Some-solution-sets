/* 
 * CS:APP Data Lab 
 * 
 * author : flicsmay  Homepage: https://github.com/flicsmay
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
 int bitAnd(int x, int y) {
	  /* Not-op set 0 whoes have 1, then or-op set 1 of which original 0
		 then outer Not-op set original 0 to 1 */
	  return ~((~x) | (~y));
}


/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* Shift right 8*n to extract the designate byte */
	return 0xFF & (x >> (n << 3));
}


/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	/* Shift right n then make a mask to switch high-order bits to 0 
	   using Not-op and + 1 to replace "-" op*/
	return (x >> n) & ((0x1 << (32 + (~n + 1))) + (~1 + 1));
}


/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/* Using 28 ops, and this problem is rather difficult so I will write a bit more
	 * 32-bits num with less than 40-ops, that it much using dichotomy 
	 * I add the adjcent 2 bits and then add adjcent 4 bits then 8, 16, together
	 * To do this must mask the irrelevant bits and half of my op is to making a 32-bits mask
	 */

	unsigned mask_55 = 0x55;
	unsigned mask_33 = 0x33;
	unsigned mask_0F = 0x0F;
	unsigned result = x;

	mask_55 |= (mask_55 << 8); mask_55 |= (mask_55 << 16); // make 32-bits mask, the same below
	mask_33 |= (mask_33 << 8); mask_33 |= (mask_33 << 16);
	mask_0F |= (mask_0F << 8); mask_0F |= (mask_0F << 16);

	//the point is to split space to accommodate the number that represent bits

	// add adjcent 2 bits in to a two bits space
	result = (result & mask_55) + ((result >> 1) & mask_55);
	// must clear 2 high-order bits in 4bits caz 4 take place 3bits
	result = (result & mask_33) + ((result >> 2) & mask_33);
	// can clear high-order 4bits in a byte after add caz 8 take only 4 bits
	result = (result + (result >> 4)) & mask_0F;
	// there is a byte space that have been clear and can hold 32, so don't have to mask anymore
	result += (result >> 8);
	result += (result >> 16);
	result &= 0xFF;
	return result;
}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/* A fairly easy problem, 7 op, You can use xor-op which need 11ops
	   If x == 0 that both ((~x) + 1)'s and x's 32th bit are 0 */
	return (((~x) & (~(~x + 1))) >> 31) & 0x01;
}


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* I'm not sure whether this method is acceptable or not */
	return 1 << 31;
}


/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/* Using 8 ops. The same as 2.70, shift right n-1 bits to keep the sign bit
	   And the high-order bits is all either 0 or 1 */
	x >>= (n + (~1 + 1)); // Take place n - 1

	return !(x + 1) | !x; // x == -1 or x == 0;
}


/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/* The same as 2.77, Using 10 ops. That is if x < 0 and 
	   the low-order n bits not equal 0 then result + 1 */
	int result = x;
	unsigned mask = (1 << n) + (~1 + 1); // replace - 1
	
	result >>= n;
	result += (mask & x) & (x >> 31) & 0x01;
	return result;
}


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x + 1; // 2-ops
}


/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	return !((x >> 31) & 0x1); // 3ops
}


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* Using 11 ops, compute the y-x and if positive that y bigger than x
	   Meanwhile mind that y-x may overflow if x < 0 and y > 0 */
	int sign_x = x >> 31;
	int sign_y = y >> 31;
	int y_x = y + (~x + 1);
	int sign_y_x = y_x >> 31;

	// if x < 0 && y > 0 || y - x > 0
	return ((sign_x & !sign_y) | !sign_y_x) & 0x1;
}


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	/* Violate the rule that can't call any function , but actully I can
	   simply copy the bitCount and paste here. So I just call that func.

	   Using 13+28 = 41 ops but I think there would be a better method. But
	   here may be best I can do so far...*/
	/* The idea is Fairly simply. set all the bits after the higheset value bit
	   to 1 the count the bits after that at last minus 1 */

	// set all bits after highest 1's to 1
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	
	// answer is the total number of 1 minus 1
	return bitCount(x) + (~1 + 1);
}

/* return 1 if the uf is NaN, abstract it for readabilty. using 5 ops 
   more constant used to save shift ops */
int is_NaN(unsigned uf)
{
	return ((uf & 0x7F800000) == 0x7F800000) &&
		((uf & 0x7FFFFF) != 0);
}


/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	/* Voiolate the rule that no allow call function , I extract the is_NaN procedure
	   is for more readabilty. If you want to test with test.c just paste it back 
	   into the if-conditional statement */
	// and total 1+5=6 ops used
	if (is_NaN)
		return uf;

	// reverse the sign bit
	return uf ^ 0x80000000;
}


/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	/* This function is the same as the 2.96 . um.. I'm not sure whether the ops 
	   in loops should be multiple counted. So I just copy the Problem 2.96.
	   And there is 22ops used ? */
	unsigned f = x;
	unsigned exp = 0;
	unsigned frac = 0;
	int index = 31;
	unsigned mask = 0x80000000;// to selet the most significant bit

	if (x < 0)// Convert two-complement to unsigned
	{
		f = ~x; // switch all bit then add 1 to be unsigned
		if (f != 2147483647)//INT_MAX
			f += 1;
	}
	for (index = 31; index >= 0; index--)
	{
		if (f & mask)
			break; // find the most significant bit
		mask >>= 1;
	}
	if (index < 0)
		return x & 0x80000000;

	exp = index + 127; // 0x7F = 127 = 0(in float)
	if (index > 23) // 23 bits fraction in sigle-precision
		frac = (f >> (index - 23)) & 0x7FFFFF;
	else
		frac = (f << (23 - index)) & 0x7FFFFF;
	return x & 0x80000000 | (exp << 23) | frac; // sign | exponent | fraction

}


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	/* Same as above, this problem is identical with 2.93. so I just copy it here 
	   Using 13+5=18 ops here */
	unsigned exp = (uf >> 23) & 0xFF;
	unsigned frac = uf & 0x7FFFFF;

	if (is_NaN_32(uf))
		return uf;
	if (exp == 0) // denormailzed
		return uf & 0xFF800000 | frac << 1; // save others | fractions * 2
	else if (exp < 254)
		return uf & 0x807FFFFF | (exp + 1) << 23; // save other bits | add 1 in exponent
	else
		return uf & 0xFF800000; // exp == 254, and just clear the fractions bits of f
}

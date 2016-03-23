/* Prombles 3.54 - 3.59 */

/* 3.54 */

/* write C code for decode2 that will have an effect equivalent 
   to our assembly code */
int decode2(int x, int y, int z)
{
	int result;

	y = y - x;
	result = y;
	result <<= 31;
	result >>= 31;
	y *= x;
	return result ^ y;
}

/* 3.55 */

// Write comments to interpret how the assembly works
// _l suffix denote the low-32bits and _h denote high-order 32 bits
// ; dest at %ebp+8, x at %ebp+12, y at %ebp+16
// movl		16(%ebp),	%esi	; y_l		-> esi
// movl		12(%ebp),	%eax	; x			-> eax
// movl		%eax	,	%edx	; x			-> edx
// sarl		$31		,	%edx	; xs		-> edx // x_sign
// movl		20(%ebp),	%ecx	; y_h		-> ecx
// imull	%eax	,	%ecx	; (x*y_h)_l	-> ecx
// movl		%edx	,	%ebx	; xs		-> ebx
// imull	%esi	,	%ebx	; y_l*xs	-> ebx
// addl		%ebx	,	%ecx	; y_l*xs + (x*y_h)_l	-> ecx
// mull		%esi				; (x*y_l)_h	-> edx ,x*l_32	-> eax
// leal		(%ecx,%edx), %edx	; y_l*xs + (x*y_h)_l + (x*y_l)_h -> edx
// movl		8(%ebp)	,	%ecx	; dest		-> ecx
// movl		%eax	,	(%ecx)	; x*l_32	-> *dest // low-order 32 bits of result
// movl		%edx	,	4(%ecx)	; y_l*xs + (x*y_h)_l + (x*y_l)_h -> *(dest + 4) // high-order 32 bits of result

/*	Please Read Problem 3.12 & it's solution before read this Note, 
 *	There are something different between 3.12 and this problem.
 *	The parameter x in 3.12 is unsigned and the type is int this time
 *	which make this problem a bit harder. But if you remeber the equaction
 *	(2-5) that you will draw a conclusion that the high-order 32 bits of result
 *	equal y_l*xs + (x*y_h)_l + (x*y_l)_h and that's the answer. 
 *
 *	U(y) * T(x) = U(y) * U(x) - U(x) * Xw-1 * 2^w -- (2-5) :: that's why sarl $31 
 */


/* 3.56 */

// A-E can be infer form the code
int loop(int x, int n)
{
	int result = -1; // line 3
	int mask;
	for (mask = 1; mask != 0; mask << (n % 256)) // used %cl in assmbly, so n % 256
		result ^= (x & mask); // line 7 - 8
	return result;
}

/* 3.57 */
int cread_alt(int *xp)
{
	int z = 0; // store a 0 for return
	int *p = xp ? xp : &z; // built a new pointer to prevent the dereference of a nullpointer
	return *p; // no pointer dereference until ensure it isn't a nullptr
}

/* 3.58 */

/* Enumerated type creats set of constants numbered 0 and upward */
typedef enum{ MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;

int switch3(int *p1, int *p2, mode_t action)
{
	// Fairly simple problem

	int result = 0;
	switch (action)
	{
	case MODE_A:
		result = *p1;
		*p2 = *p1;
		break;

	case MODE_B:
		result = *p1 + *p2;
		*p2 = result;
		break;

	case MODE_C:
		result = *p1;
		*p2 = 15;
		break;

	case MODE_D: // result = 17 implement in MODE_E
		*p2 = *p1;
		/* no break here */

	case MODE_E:
		result = 17;
		break;

	default:
		result = -1;
	}
	return result;
}


/* 3.59 */
// Haven't passing test with complier, so I'm not sure wheter I'm right or not.
int switch_prob(int x, int n)
{
	int result = x;

	switch (n)
	{
	case 32: // line 6 
	case 34: // table [0] == [2]
		result *= 4; // line 10
		break; // line 11

	case 35:
		result /= 4; // line 12
		break;
		
	case 36:
		result *= 3; // line 14
	case 37:
		result *= result; // line 15
	case 33: // It's also right without this line.
	default:
		result += 10; // line 16
		break;
	}

	return result;
}
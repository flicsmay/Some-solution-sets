/* Prombles 3.54 - */

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
// sarl		$31		,	%edx	; xs		-> edx
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
 *	U(y) * T(x) = U(y) * U(x) - Xw-1 * 2^w (2-5) :: that why sarl $31 
 */
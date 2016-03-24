/* Problems 3.60 - */

/* 3.60 */

// A. A[i][j][k] = Xd + L(i*S*T + j*T + k) // in this problem L = 4;
// B. S = 9, T = 11, R = 5; // (S*T = 99) (T = 11) (S*T*R) = 1980/4;

/* 3.61 */

// As my IDE doesn't support C99.. so I'm no sure whether or not my answer is right.
// There are 4 value that must bu used : Arow, Brow, result and 4*n
// so there are only one element that used to check the bounds
//int var_prod_else(int n, int A[n][n], int B[n][n], int i, int k)
//{
//	int result = 0;
//	int *p_A = &A[i][0];
//	int *p_B = &B[0][k];
//	int *pEnd = &A[i][n];
//
//	while (p_A != pEnd)
//	{
//		result += *p_A * *p_B;
//		p_B += n;
//		p_A++; // A[i+1][j];
//	}
//	
//	return result;
//}


/* 3.62 */

// A. M = 13. (52/4)
// B. %edi -> i , %ecx -> j // line 8 & 9
// The sample version of code using a resiger (%ebx) to save the adress of A[j][i] 
// and then add an offset to update A[j+1][i]. MeanWhile it use another resiger (%esi)
// to save the base adress of A[i][x]
// C.

// The same as above. My IDE doesn't support C99 so..
//void transpose(int M, int A[M][M])
//{
//	int i, j;
//	int t = 0;
//	int *p_row;
//	int *p_col;
//
//	for (i = 0; i < M; i++)
//	{
//		p_row = &A[i][0]; // use a variable to save base address
//		p_col = &A[0][j]; // the same above
//		for (j = 0; j < M, j++)
//		{
//			t = *p_row;
//			*p_row = *p_col;
//			*p_col = t;
//			p_row++; // A[i+1] same as line 5 in assmbly
//			p_col += M; // add offset
//		}
//	}
//}


/* 3.63 */
// E1(n) = 2n+1 // deduced from line 7 . 8
// E2(n) = 12n // deduce from line 9 & 19


/* 3.64 */

// A. 8(%ebp) = &result , 12(%ebp) = s1.a , 16(%ebp) = s1.p // It's very simple to draw the soultion
// B. offset  value		// take %ebp as standard of 0
//		12		y
//		8		x
//		4		return address (prod)
//		0		saved %ebp (current %ebp as well)
//		-4		s2.diff
//		-8		s2.sum
//		-12		s1.p
//		-16		s1.a
//		-20		adress of s2 (s2.sum's adress, That is offset -8)
//		-24		return adress (word_sum) // after call word_sum

// C. push the initial adress of the structure in.
// D. directly update the value of acceptor, through the passed adress.


/* 3.65 */

// It seems to be 92/2 = 46 = A*B and 12 = B
// But if B = 12 the &u should be 12*2 + 4 + 12 = 40 but no 36
// So, there must be alignment there. A*B could be either 46 or 45
// and B could be 9 , 10 or 11. Notice that both A and B are integer
// A = 5 and B = 9 is right answer.


/* 3.66 */
// This problem is so hard to me that I have take a lot of time trying to solve it.
// lines			operations						comments

// 3	mov		0x8(%ebp), %eax			; i -> %eax
// 6	mov		0xc(%ebp), %ecx			; &bp -> %ecx
// 9	lea		(%eax,%eax,4), %eax		; 5i -> %eax
// c	add		0x4(%ecx,%eax,4), %eax	; [bp+20i+4] + 5i  = x -> %eax
// 10	mov		0xb8(%ecx), %edx		; [bp+0xb8] -> %edx
// 16	add		(%ecx), %edx			; [bp] + [bp+0xb8] = n -> %edx
// 18	mov		%edx, 0x8(%ecx,%eax,4)	; n -> [bp + 4*x + 8]

// As we see that [bp] and [b+0xb8] should be denote bp->left and bp->right respectively
// Then we can deduce that size(a[])*CNT = 180 /*size(a[]) no equal sizeof(a[])*/ and 
// we can deduce that Add(ap->x[ap->idx]) = bp + 4*x + 8  -(1). Meanwhile the address of
// Add(ap->x[0]) = bp + 4 + size(a[]) + offset  // offset is offset between a[i] and s[]
// then Add(ap->x[ap->idx]) = bp + 4 + size(a[])*i + offset + sizeof(x[])*idx	 -(2)
// So acc to (1)(2) 4 + 4*x = size(a[])*i + offset + sizeof(x[])*idx
// That is 4 + 4*([bp+20i+4]) + 20*i = size(a[])*i + offset + sizeof(x[])*idx
// Then we can guess that [bp+20i+4] is ap->idx and sothat offset = 4;
// so 20*i + 4*idx = size(a[])*i + sizeof(x[])*idx
// and size(a[]) = 20 sizeof(x[]) = 4 is the possible and most reasonable result
// And CNT = 180/20 = 9
// Since sizeof(s[]) = 4 we can fill this structure
//struct a_struct
//{
//	int idx;
//	int s[4];
//};
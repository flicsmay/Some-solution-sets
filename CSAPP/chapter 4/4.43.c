/* Problems 4.43 - */

/* 4.43 */

// A. Definitely not, pushl %esp should save %esp in stack but not %esp-4
// B. Can use another resiger
// movl REG, %eax	subl $4, %esp	movl %eax, (%esp)

/* 4.44 */

// A. Not, popl %esp should put %esp in stack but not %esp+4
// B. movl %esp, %eax	addl $4, %esp	movl %eax, (%esp)

/* 4.45 */

/* Bubble sort: Array version */
void bubble_a(int *data, int count)
{
	int i, last, t;
	int *p_f, *p_n;

	for (last = count - 1; last > 0; last--)
	{
		*p_f = data;
		*p_n = data + 1;
		for (i = 0; i < last; i++)
		{
			if (*p_f > *p_n)
			{
				t = *p_f;
				*p_f = *p_n;
				*p_n = t;
			}
			*p_f++;
			*p_n++;
		}
	}
}

/*
	It is so hard that write a procedure with so little instruction.
	I use the resiger generally as follow
	eax : p_f
	ebx : p_n
	ecx : last
	edx : t & used for exchange p_f with p_n
	esi : i
	edi : used for passing constant integer
	Anyway, my answer must be bad..

	bubble_a
		pushl		%ebp
		rrmovl		%esp, %ebp
		mrmovl		8(%ebp), %eax		; ecx = data
		mrmovl		12(%ebp), %ecx		; edx = count

	Outer_loop
		irmovl		$1, %edi			;
		subl		%edi, %ecx			; last - 1
		jg			End
		rrmovl		%eax, %ebx			; p_n = p_f
		irmovl		$4, %edi
		addl		%edi, %ebx			; p_n++

	Inner_loop
		rrmovl		%ecx, %edx			; save at edx to compare i with last
		subl		%esi, %edx			; cmp
		jle			Outer_loop
		rrmovl		%eax, %edx			;
		subl		%ebx, %edx			; cmp *p_f with *p_n
		jle			Skip_exchange
		rrmovl		%ecx, %edx			; exchange two pointer
		rrmovl		%ebx, %ecx			;
		rrmovl		%edx, %ebx			;

	Skip_exchange
		irmovl		$4, %edi			; add pointers
		addl		%edi, %eax			;
		addl		%edi, %ebx			;
		irmovl		$1, %edi			;
		addl		%edi, %esi			; add 1 to i
		jmp			Inner_loop
	End
		leave
		ret
*/
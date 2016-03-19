/*Problems 2.55 - 2.57*/

/* You can find identical source code of this 
   soluction on your book */
#include <stdio.h>

/*
 * the reason why it have to use unsigned char* but not char*
 * is that when a char transfer to 32bit in printf if the highest bit
 * is 1 it will implement a sign extension and will printf "ffffffXX"
 */
typedef unsigned char *byte_pointer;

void show_byte(byte_pointer start, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x)
{
	show_byte((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
	show_byte((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
	show_byte((byte_pointer)&x, sizeof(void *));
}


//int main()
//{
//	int i = 1;
//	float f = 12345.0;
//	int *p = &i;
//	show_int(i);
//	show_float(f);
//	show_pointer(p);
//}
////and my own computer is little-endian

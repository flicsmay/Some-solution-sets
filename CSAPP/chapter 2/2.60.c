/*Porblem 2.60*/

/* return an unsigned value which byte i of argument x has been
   replaced by byte b */
unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	//multipy i by 3 to indicate a byte and then move b to position
	//then mask x and then or-op
	return (x & ~(0xFF << (i << 3))) | (b << (i << 3));
}


//int main()
//{
//	unsigned i = 0x12345678;
//	unsigned char mask = 0xAB;
//
//	printf("%.2x \n", replace_byte(i, 2, mask));
//	printf("%.2x \n", replace_byte(i, 0, mask));
//}
////the output should be 0x12ab5678 and 0x123456ab
/*Problem 2.59*/


/* yield a word consisting of least significant
   byte of x and remaining bytes of y */
unsigned combine_hex(unsigned x, unsigned y)
{
	//x op-and with 0xff to remani the lowest byte
	//y op-and with 0xff..00 remain the all but last bytes 
	return (x & 0xFF) | (y & (~0xFF));
}


//int main()
//{
//	unsigned x = 0x89ABCDEF;
//	unsigned y = 0x76543210;
//
//	printf("%x\n", combine_hex(x, y));
//}
////the output should be 0x765432EF
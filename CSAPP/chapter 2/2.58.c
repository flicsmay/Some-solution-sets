/*Problem 2.58*/

/*return 1 if run on little-endian machine
 should be regardless a machine wordsize*/
int is_little_endian(void)
{
	int i = 1;
	//(unsigned char*)&i change i to a bytepointer
	//and the frist byte of little endian must be 1
	//as minimum of int have 2 byte
	return *((unsigned char *)&i);
}


//int main()
//{
//	(is_little_endian()) ? 
//		printf("YES") : printf("NO");
//}

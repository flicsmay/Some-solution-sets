/*Problem 2.64*/

/* Return 1 when any odd bit of x equals 1; 0 otherwise
   Assume w=32 */
int any_odd_one(unsigned x)
{
	//double exclamation is for changing the int to boolean
	return !!(x & 0x55555555);
}
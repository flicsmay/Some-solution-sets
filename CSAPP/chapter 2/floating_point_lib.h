/* A small library for the Problems 
   form 2.91 to 2.96 */

// From problem 2.91 to 2.96. The solutions must to 
// follow the Bit-level floating-point coding rule (in page 131 eng ver)
// May not use any floating-point data tpyes, operations, or constants
// Instead, should perform the bit manipulations that implement floating-point operas

#ifndef _FLOATING_POINT_LIB_H
#define _FLOATING_POINT_LIB_H

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Return 1 if argument f is NaN, f is must 32-bits */
int is_NaN_32(float_bits f);

/* For testing */

/* Return a unsigned integer with a float input */
unsigned f2u(float f);

/* Return a float with a unsigned input */
float u2f(unsigned u);

#endif
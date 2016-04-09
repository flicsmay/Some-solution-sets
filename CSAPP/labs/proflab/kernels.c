/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "flicsmay",              /* Team name */

    "lee",     /* First member full name */
    "flicsmay@163.com",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KER
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_unrolling_4_descr[] = "rotate: unrolling by 4";
void rotate_unrolling_4(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j += 4)
        {
            dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            dst[RIDX(dim-2-j, i, dim)] = src[RIDX(i, j+1, dim)];
            dst[RIDX(dim-3-j, i, dim)] = src[RIDX(i, j+2, dim)];
            dst[RIDX(dim-4-j, i, dim)] = src[RIDX(i, j+3, dim)]; 
        }
    }
}

/*
 * unrolling row by 4 to do tranport frist and change it's rows
 * run slower in a smaller dim but faster in a larger dim
 */
char rotate_unrolling_row_4_descr[] = "rotate: transpose method and unrolling by 4";
void rotate_unrolling_row_4(int dim, pixel *src, pixel *dst)
{
    int i, j;
    pixel tmp[dim*dim];

    for (i = 0; i < dim; i+=4)
    {
        for (j = 0; j < dim; j++)
        {
            tmp[RIDX(j, i, dim)]   = src[RIDX(i, j, dim)];
            tmp[RIDX(j, i+1, dim)] = src[RIDX(i+1, j, dim)];
            tmp[RIDX(j, i+2, dim)] = src[RIDX(i+2, j, dim)];
            tmp[RIDX(j, i+3, dim)] = src[RIDX(i+3, j, dim)];
        }
    }
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j+=4)
        {
            dst[RIDX(dim-1-i, j, dim)] = tmp[RIDX(i, j, dim)];
            dst[RIDX(dim-1-i, j+1, dim)] = tmp[RIDX(i, j+1, dim)];
            dst[RIDX(dim-1-i, j+2, dim)] = tmp[RIDX(i, j+2, dim)];
            dst[RIDX(dim-1-i, j+3, dim)] = tmp[RIDX(i, j+3, dim)];
        }
}

void rotate(int dim, pixel *src, pixel *dst)
{
    rotate_unrolling_row_4(dim, src, dst);
}


char rotate_unrolling_8_descr[] = "rotate: transpose method and unrolling by 8";
void rotate_unrolling_8(int dim, pixel *src, pixel *dst)
{
    int i, j;
    pixel tmp[dim*dim];

    for (i = 0; i < dim; i+=8)
    {
        for (j = 0; j < dim; j++)
        {
            tmp[RIDX(j, i, dim)]   = src[RIDX(i, j, dim)];
            tmp[RIDX(j, i+1, dim)] = src[RIDX(i+1, j, dim)];
            tmp[RIDX(j, i+2, dim)] = src[RIDX(i+2, j, dim)];
            tmp[RIDX(j, i+3, dim)] = src[RIDX(i+3, j, dim)];
            tmp[RIDX(j, i+4, dim)] = src[RIDX(i+4, j, dim)];
            tmp[RIDX(j, i+5, dim)] = src[RIDX(i+5, j, dim)];
            tmp[RIDX(j, i+6, dim)] = src[RIDX(i+6, j, dim)];
            tmp[RIDX(j, i+7, dim)] = src[RIDX(i+7, j, dim)];
        }
    }
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j+=8)
        {
            dst[RIDX(dim-1-i, j, dim)] = tmp[RIDX(i, j, dim)];
            dst[RIDX(dim-1-i, j+1, dim)] = tmp[RIDX(i, j+1, dim)];
            dst[RIDX(dim-1-i, j+2, dim)] = tmp[RIDX(i, j+2, dim)];
            dst[RIDX(dim-1-i, j+3, dim)] = tmp[RIDX(i, j+3, dim)];
            dst[RIDX(dim-1-i, j+4, dim)] = tmp[RIDX(i, j+4, dim)];
            dst[RIDX(dim-1-i, j+5, dim)] = tmp[RIDX(i, j+5, dim)];
            dst[RIDX(dim-1-i, j+6, dim)] = tmp[RIDX(i, j+6, dim)];
            dst[RIDX(dim-1-i, j+7, dim)] = tmp[RIDX(i, j+7, dim)];
        }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate_unrolling_4, rotate_unrolling_4_descr); 
    add_rotate_function(&rotate_unrolling_row_4, rotate_unrolling_row_4_descr);   
    add_rotate_function(&rotate_unrolling_8, rotate_unrolling_8_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

pixel_sum avg_col3(int dim, int i, int j, pixel *src)
{
    pixel_sum tmp;
    pixel *top = &src[RIDX(i-1, j, dim)];
    pixel *mid = &src[RIDX(i, j, dim)];
    pixel *bot = &src[RIDX(i+1, j, dim)];

    tmp.red = top->red + mid->red + bot->red;
    tmp.green = top->green + mid->green + bot->green;
    tmp.blue = top->blue + mid->blue + bot->blue;

    return tmp;
} 

pixel avg_9(pixel_sum *left, pixel_sum *mid, pixel_sum *right)
{
    pixel tmp;

    tmp.red =(unsigned short) ((left->red + mid->red + right->red)/9);
    tmp.green =(unsigned short) ((left->green + mid->green + right->green)/9);
    tmp.blue =(unsigned short) ((left->blue + mid->blue + right->blue)/9);

    return tmp;
}

void avg_board(int dim, pixel *src, pixel *dst)
{
    int i, j;
    pixel_sum tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;

    for (j = 0; j < dim; j++)
        dst[RIDX(0, j, dim)] = avg(dim, 0, j, src);

    for (i = 1; i < dim-1; i++)
    {
        dst[RIDX(i, 0, dim)] = avg(dim, i, 0, src);
        for (j = 1; j < dim-4; j+=4)
        {
            tmp0 = avg_col3(dim, i, j-1, src);
            tmp1 = avg_col3(dim, i, j, src);
            tmp2 = avg_col3(dim, i, j+1, src);
            tmp3 = avg_col3(dim, i, j+2, src);
            tmp4 = avg_col3(dim, i, j+3, src);
            tmp5 = avg_col3(dim, i, j+4, src);
            dst[RIDX(i, j, dim)] = avg_9(&tmp0, &tmp1, &tmp2);
            dst[RIDX(i, j+1, dim)] = avg_9(&tmp1, &tmp2, &tmp3);
            dst[RIDX(i, j+2, dim)] = avg_9(&tmp2, &tmp3, &tmp4);
            dst[RIDX(i, j+3, dim)] = avg_9(&tmp3, &tmp4, &tmp5);
        }
        for (; j < dim; j++)
            dst[RIDX(i, j, dim)] = avg(dim, i, j, src);

    }
    for (j = 0; j < dim; j++)
        dst[RIDX(dim-1, j, dim)] = avg(dim, dim-1, j, src);
}



/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    avg_board(dim, src, dst);   
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}


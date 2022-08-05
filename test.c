#include "libbf/libbf.h"
#include <stdio.h>
#include <stdlib.h>




//static int	check_trivial(double x, double y)
//{
//	double	q;
//
//	if (x * x + 2 * x + 1 + y * y < 0.0625)
//		return (1);
//	q = (x - 0.25) * (x - 0.25) + y * y;
//	if (q * (q + (x - 0.25)) < y * y * 0.25)
//		return (1);
//	return (0);
//}

/* number of bits per base 10 digit */
#define BITS_PER_DIGIT 3.32192809488736234786
#define MAX_PREC 1000000
static bf_context_t bf_ctx;

static void *my_bf_realloc(void *opaque, void *ptr, size_t size)
{
    return realloc(ptr, size);
}


void	distance_to_origin(bf_t *r, bf_t *a, bf_t *b)
{
	bf_t tmp, tmp2;
	bf_init(&bf_ctx, &tmp);
	bf_init(&bf_ctx, &tmp2);
	bf_mul(&tmp, a, a, MAX_PREC, BF_RNDN);
	bf_mul(&tmp2, b, b, MAX_PREC, BF_RNDN);
	bf_add(r, &tmp, &tmp2, MAX_PREC, BF_RNDN);
	bf_delete(&tmp);
	bf_delete(&tmp2);
}

//1 -> still inside  0 -> escaped
int	escape_check(bf_t *xn, bf_t *yn)
{
	bf_t tmp;
	bf_t tmp2;
	bf_init(&bf_ctx, &tmp);
	bf_init(&bf_ctx, &tmp2);
	distance_to_origin(&tmp, xn, yn);
	bf_set_ui(&tmp2, 4);
	int ret = bf_cmp_le(&tmp, &tmp2);
	bf_delete(&tmp);
	bf_delete(&tmp2);
	return (ret);
}

int	mandel(int depth_max, bf_t *x, bf_t *y, bf_t *xn, bf_t *yn)
{
	int		depth;
	bf_t	tmp;
	bf_t	tmp2;
	bf_t	tmp3;

	bf_init(&bf_ctx, &tmp);
	bf_init(&bf_ctx, &tmp2);
	bf_init(&bf_ctx, &tmp3);
	//if (check_trivial(x, y))
	//	return (depth_max);
	depth = 0;
	while (escape_check(xn, yn) && depth < depth_max)
	{
		
		//tmp = xn * xn - yn * yn + x;
		bf_mul(&tmp, xn, xn, MAX_PREC, BF_RNDN);
		bf_mul(&tmp2, yn, yn, MAX_PREC, BF_RNDN);
		bf_sub(&tmp, &tmp, &tmp2, MAX_PREC, BF_RNDN);
		bf_add(&tmp, &tmp, x, MAX_PREC, BF_RNDN);

		//yn = 2 * xn * yn + y;
		bf_set_ui(&tmp2, 2);
		bf_mul(&tmp3, &tmp2, xn, MAX_PREC, BF_RNDN);
		bf_mul(&tmp3, &tmp3, yn, MAX_PREC, BF_RNDN);
		bf_add(yn, &tmp3, y, MAX_PREC, BF_RNDN);

		//xn = tmp;
		bf_set(xn, &tmp);
		depth++;
	}
	bf_delete(&tmp);
	bf_delete(&tmp2);
	bf_delete(&tmp3);
	return (depth);
}

int main()
{
	int base = 10;
	bf_t x, y, xn, yn;

	bf_context_init(&bf_ctx, my_bf_realloc, NULL);

	bf_init(&bf_ctx, &x);
	bf_init(&bf_ctx, &y);
	bf_init(&bf_ctx, &xn);
	bf_init(&bf_ctx, &yn);

	bf_set_ui(&x, 0);
	bf_set_float64(&y, 0.5);
	bf_set_ui(&xn, 0);
	bf_set_ui(&yn, 0);

	size_t	tmp2;
	//char *tmp = bf_ftoa(&tmp2, &z, 10, MAX_PREC, BF_RNDN);
	printf("%d\n", mandel(500, &x, &y, &xn, &yn));

	bf_delete(&x);
	bf_delete(&y);
	bf_delete(&xn);
	bf_delete(&yn);
    bf_context_end(&bf_ctx);
	return 0;
}
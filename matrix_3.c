#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// 矩阵分块+循环展开+寄存器优化
void matrix(double *a, double *b, double *c, long n)
{
    int i_in, j_in, k_in, iTile, jTile, kTile;
    iTile = jTile = 32, kTile = 8;
    long i_out, j_out, k_out, iOutBound, jOutBound, kOutBound;
    iOutBound = n / iTile, jOutBound = n / jTile, kOutBound = n / kTile;
    double tmp0, tmp1, tmp2, tmp3;

    for (i_out = 0; i_out < iOutBound; i_out++)
        for (j_out = 0; j_out < jOutBound; j_out++)
            for (k_out = 0; k_out < kOutBound; k_out++)
                for (i_in = 0; i_in < iTile; i_in++)
                    for (j_in = 0; j_in < jTile; j_in += 4)
                    {
                        tmp0 = tmp1 = tmp2 = tmp3 = 0.0;
                        for (k_in = 0; k_in < kTile; k_in++)
                        {
                            tmp0 +=
                                a[(i_out * iTile + i_in) * n + (k_out * kTile + k_in)] *
                                b[(k_out * kTile + k_in) * n + (j_out * jTile + j_in)];
                            tmp1 += a[(i_out * iTile + i_in) * n + (k_out * kTile + k_in)] *
                                    b[(k_out * kTile + k_in) * n + (j_out * jTile + j_in + 1)];
                            tmp2 += a[(i_out * iTile + i_in) * n + (k_out * kTile + k_in)] *
                                    b[(k_out * kTile + k_in) * n + (j_out * jTile + j_in + 2)];
                            tmp3 += a[(i_out * iTile + i_in) * n + (k_out * kTile + k_in)] *
                                    b[(k_out * kTile + k_in) * n + (j_out * jTile + j_in + 3)];
                        }
                        c[(i_out * iTile + i_in) * n + (j_out * jTile + j_in)] += tmp0;
                        c[(i_out * iTile + i_in) * n + (j_out * jTile + j_in + 1)] += tmp1;
                        c[(i_out * iTile + i_in) * n + (j_out * jTile + j_in + 2)] += tmp2;
                        c[(i_out * iTile + i_in) * n + (j_out * jTile + j_in + 3)] += tmp3;
                    }
}

int main(void)
{
    double *ptr_a;
    double *ptr_b;
    double *ptr_c;
    struct timeval tv1, tv2;
    long i, j, n, sec, usec, temp;

    // printf("Input matrix size :");
    // scanf("%ld",&n);
    n = 2048;
    temp = n * n * 8;
    ptr_a = malloc(temp);
    ptr_b = malloc(temp);
    ptr_c = malloc(temp);

    for (i = 0; i < n; i++)
    {
        temp = i * n;
        for (j = 0; j < n; j++)
        {
            ptr_a[temp + j] = 2.0;
            ptr_b[temp + j] = -2.0;
            ptr_c[temp + j] = 0.0;
        }
    }
    gettimeofday(&tv1, NULL);
    matrix(ptr_a, ptr_b, ptr_c, n);
    gettimeofday(&tv2, NULL);
    usec = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
    sec = usec / 1000000;
    usec = usec - sec * 1000000;
    printf("time elapse %ld s: %ld us\n", sec, usec);

    double rst = -4.0 * n;
    for (i = 0; i < n; i++)
    {
        temp = i * n;
        for (j = 0; j < n; j++)
            if (ptr_c[temp + j] != rst)
            {
                printf("error!\n");
                goto out_tag;
            }
    }
out_tag:
    free(ptr_a);
    free(ptr_b);
    free(ptr_c);
    return 0;
}

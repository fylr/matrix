#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// 循环展开+寄存器优化
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j += 8)
        {
            tmp0 = tmp1 = tmp2 = tmp3 = tmp4 = tmp5 = tmp6 = tmp7 = 0.0;
            for (k = 0; k < n; k++)
            {
                tmp0 += a[i * n + k] * b[k * n + j];
                tmp1 += a[i * n + k] * b[k * n + j + 1];
                tmp2 += a[i * n + k] * b[k * n + j + 2];
                tmp3 += a[i * n + k] * b[k * n + j + 3];
                tmp4 += a[i * n + k] * b[k * n + j + 4];
                tmp5 += a[i * n + k] * b[k * n + j + 5];
                tmp6 += a[i * n + k] * b[k * n + j + 6];
                tmp7 += a[i * n + k] * b[k * n + j + 7];
            }
            c[i * n + j] = tmp0;
            c[i * n + j + 1] = tmp1;
            c[i * n + j + 2] = tmp2;
            c[i * n + j + 3] = tmp3;
            c[i * n + j + 4] = tmp4;
            c[i * n + j + 5] = tmp5;
            c[i * n + j + 6] = tmp6;
            c[i * n + j + 7] = tmp7;
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

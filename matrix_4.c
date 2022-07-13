#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// 调整计算顺序ikj+循环展开
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double r;

    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++)
        {
            r = a[i * n + k];
            for (j = 0; j < n; j += 8)
            {
                c[i * n + j] += r * b[k * n + j];
                c[i * n + j + 1] += r * b[k * n + j + 1];
                c[i * n + j + 2] += r * b[k * n + j + 2];
                c[i * n + j + 3] += r * b[k * n + j + 3];
                c[i * n + j + 4] += r * b[k * n + j + 4];
                c[i * n + j + 5] += r * b[k * n + j + 5];
                c[i * n + j + 6] += r * b[k * n + j + 6];
                c[i * n + j + 7] += r * b[k * n + j + 7];
            }
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

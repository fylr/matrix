#/bin/bash

echo "0. 性能参考基准"
gcc -O2 -mfpmath=sse -o matrix matrix.c
sync && sleep 3 && sync
./matrix
echo -e "---------------------------------------------------------\n"

echo "1. 寄存器优化"
gcc -O2 -mfpmath=sse -o matrix_1 matrix_1.c
sync && sleep 3 && sync
./matrix_1
echo -e "---------------------------------------------------------\n"

echo "2. 循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -o matrix_2 matrix_2.c
sync && sleep 3 && sync
./matrix_2
echo -e "---------------------------------------------------------\n"

echo "3. 矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -o matrix_3 matrix_3.c
sync && sleep 3 && sync
./matrix_3
echo -e "---------------------------------------------------------\n"

echo "4. 调整计算顺序ikj+循环展开"
gcc -O2 -mfpmath=sse -o matrix_4 matrix_4.c
sync && sleep 3 && sync
./matrix_4
echo -e "---------------------------------------------------------\n"

echo "5. 向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -msse3 -o matrix_5 matrix_5.c
sync && sleep 3 && sync
./matrix_5
echo -e "---------------------------------------------------------\n"

echo "6. OpenMP并行化+向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -msse3 -fopenmp -o matrix_6 matrix_6.c
sync && sleep 3 && sync
./matrix_6
echo -e "---------------------------------------------------------\n"

echo "7. 编译参数优化+OpenMP并行化+向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -O3 -mfma -Ofast -mfpmath=sse -msse3 -fopenmp -o matrix_7 matrix_6.c
sync && sleep 3 && sync
./matrix_7
echo -e "---------------------------------------------------------\n"
#/bin/bash

mkdir -p bin/

echo "0. 性能参考基准"
gcc -O2 -mfpmath=sse -o bin/matrix matrix.c
sync && sleep 3 && sync
./bin/matrix
echo -e "---------------------------------------------------------\n"

echo "1. 寄存器优化"
gcc -O2 -mfpmath=sse -o bin/matrix_1 matrix_1.c
sync && sleep 3 && sync
./bin/matrix_1
echo -e "---------------------------------------------------------\n"

echo "2. 循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -o bin/matrix_2 matrix_2.c
sync && sleep 3 && sync
./bin/matrix_2
echo -e "---------------------------------------------------------\n"

echo "3. 矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -o bin/matrix_3 matrix_3.c
sync && sleep 3 && sync
./bin/matrix_3
echo -e "---------------------------------------------------------\n"

echo "4. 调整计算顺序ikj+循环展开"
gcc -O2 -mfpmath=sse -o bin/matrix_4 matrix_4.c
sync && sleep 3 && sync
./bin/matrix_4
echo -e "---------------------------------------------------------\n"

echo "5. 向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -msse3 -o bin/matrix_5 matrix_5.c
sync && sleep 3 && sync
./bin/matrix_5
echo -e "---------------------------------------------------------\n"

echo "6. OpenMP并行化+向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -O2 -mfpmath=sse -msse3 -fopenmp -o bin/matrix_6 matrix_6.c
sync && sleep 3 && sync
./bin/matrix_6
echo -e "---------------------------------------------------------\n"

echo "7. 编译参数优化+OpenMP并行化+向量指令SSE3+矩阵分块+循环展开+寄存器优化"
gcc -Ofast -mfma -mfpmath=sse -msse3 -fopenmp -o bin/matrix_7 matrix_6.c
sync && sleep 3 && sync
./bin/matrix_7
echo -e "---------------------------------------------------------\n"

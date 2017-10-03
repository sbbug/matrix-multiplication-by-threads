#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>//互斥型资源信号量
#include <thread>

using namespace std;
#define  size  4
mutex mtx[size]; //4个资源信号量
thread myThread[size]; //开辟四个线程，每一行有一个线程去负责计算


void output(int **M){
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			cout << M[i][j] << "  ";
		}
		cout << endl;
	}
}

void MatrixMultiplication(int const * const * matrixA, int const * const * matrixB, int** matrixC, int row) {
	mtx[row].lock();//加锁
	//进入临界区
	for (int i = 0;i < size;i++) {
         for (int j = 0;j < size;j++) {
             matrixC[row][i] += matrixA[row][j] * matrixB[j][i];//临界区
		 }	
	}
	//退出临界区
	mtx[row].unlock();//下锁
}

int main()
{
	int** matrixA;
	int** matrixB;
	int** matrixC;

	matrixA = new int*[size];
	matrixB = new int*[size];
	matrixC = new int*[size];

	for (int i = 0; i<size; i++) {
		matrixA[i] = new int[size];
		matrixB[i] = new int[size];
		matrixC[i] = new int[size];
	}
    //矩阵初始化数值
	int count = 1;
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			matrixA[i][j] = count;
			matrixB[i][j] = count;
			count++;
			matrixC[i][j] = 0;
		}
	}
	//为每一个线程分配任务
	for (int row = 0; row<size; row++) {
		myThread[row] = thread(MatrixMultiplication, matrixA, matrixB, matrixC, row);
	}
	//开始执行每一个线程
	for (int num = 0; num<size; num++) {
		myThread[num].join();
    }
	//输出结果
	cout << "矩阵A\n";output(matrixA);
	cout << "\n\t*\t\n";output(matrixB);
	cout << "\n\t=\t\n";
	output(matrixC);

	system("PAUSE");
	return 0;
}

/*输出结果:
矩阵A
1  2  3  4
5  6  7  8
9  10  11  12
13  14  15  16

*
1  2  3  4
5  6  7  8
9  10  11  12
13  14  15  16

=
90  100  110  120
202  228  254  280
314  356  398  440
426  484  542  600
请按任意键继续. . .
*/
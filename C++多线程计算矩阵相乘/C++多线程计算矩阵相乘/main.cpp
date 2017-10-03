#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>//��������Դ�ź���
#include <thread>

using namespace std;
#define  size  4
mutex mtx[size]; //4����Դ�ź���
thread myThread[size]; //�����ĸ��̣߳�ÿһ����һ���߳�ȥ�������


void output(int **M){
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			cout << M[i][j] << "  ";
		}
		cout << endl;
	}
}

void MatrixMultiplication(int const * const * matrixA, int const * const * matrixB, int** matrixC, int row) {
	mtx[row].lock();//����
	//�����ٽ���
	for (int i = 0;i < size;i++) {
         for (int j = 0;j < size;j++) {
             matrixC[row][i] += matrixA[row][j] * matrixB[j][i];//�ٽ���
		 }	
	}
	//�˳��ٽ���
	mtx[row].unlock();//����
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
    //�����ʼ����ֵ
	int count = 1;
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			matrixA[i][j] = count;
			matrixB[i][j] = count;
			count++;
			matrixC[i][j] = 0;
		}
	}
	//Ϊÿһ���̷߳�������
	for (int row = 0; row<size; row++) {
		myThread[row] = thread(MatrixMultiplication, matrixA, matrixB, matrixC, row);
	}
	//��ʼִ��ÿһ���߳�
	for (int num = 0; num<size; num++) {
		myThread[num].join();
    }
	//������
	cout << "����A\n";output(matrixA);
	cout << "\n\t*\t\n";output(matrixB);
	cout << "\n\t=\t\n";
	output(matrixC);

	system("PAUSE");
	return 0;
}

/*������:
����A
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
�밴���������. . .
*/
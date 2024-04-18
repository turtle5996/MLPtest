#include <iostream>
#include<stdio.h>
#include "MLP.h"
CMLP MultiLayer;

int main() {
	printf("�й� : 20190831\n�̸� :������\n ���� : ������ �����Ű�� �н�\n\n");
	int h_layer[1] = { 2 };

	MultiLayer.Create(2, h_layer, 1, 1);

	printf("�н� �� ����ġ\n");

	double x[4][2] = { {0,0},{0,1},{1,0},{1,1} };
	MultiLayer.m_Weight[0][0][1] = -0.8;
	MultiLayer.m_Weight[0][1][1] = 0.5;
	MultiLayer.m_Weight[0][2][1] = 0.4;

	MultiLayer.m_Weight[0][0][2] = 0.1;
	MultiLayer.m_Weight[0][1][2] = 0.9;
	MultiLayer.m_Weight[0][2][2] = 1.0;

	printf("layer = 0 : [1] bias = %.4f %.4f %.4f [2] bias= %.4f %.4f %.4f \n", 
		MultiLayer.m_Weight[0][0][1], MultiLayer.m_Weight[0][1][1], MultiLayer.m_Weight[0][2][1]
	, MultiLayer.m_Weight[0][0][2], MultiLayer.m_Weight[0][1][2], MultiLayer.m_Weight[0][2][2]);


	MultiLayer.m_Weight[1][0][1] = -0.3;
	MultiLayer.m_Weight[1][1][1] = -1.2;
	MultiLayer.m_Weight[1][2][1] = 1.1;

	printf("layer = 1 : [1] bias = %.4f %.4f %.4f \n\n",
		MultiLayer.m_Weight[1][0][1], MultiLayer.m_Weight[1][1][1], MultiLayer.m_Weight[1][2][1]);
	MultiLayer.pInValue[1] = 1;
	MultiLayer.pInValue[2] = 1;

	MultiLayer.pCorrectOutValue[1] = 0;
	MultiLayer.Forward();
	MultiLayer.BackPopagationLearning();

	printf("%lf %lf=%lf \n", MultiLayer.pInValue[1], MultiLayer.pInValue[1], MultiLayer.pOutValue[1]);

	/*for (int i = 0; i < 4; i++) {
		//MultiLayer.pInValue[0] = 1;       //���̾
		MultiLayer.pInValue[1] = x[i][0]; //���̾
		MultiLayer.pInValue[2] = x[i][1]; //���̾


		MultiLayer.Forward();
		printf("%lf %lf=%lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);

	}
	*/
	printf("\n");

	int layer, snode, enode,node;

	//��庰 ��°�
	printf("��庰 ��°�\n");
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer; layer++) {
		printf("layer = %d:", layer);
		for (node = 1; node <= MultiLayer.m_NumNodes[layer]; node++)
			printf(" %lf", MultiLayer.m_NodeOut[layer][node]);
		printf("\n");
	}
	printf("\n");

	//������簪
	printf("������簪\n");
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer; layer++) {
		printf("layer = %d: ", layer);
		for (snode = 1; snode <= MultiLayer.m_NumNodes[layer]; snode++) {
			printf("%.4lf ", MultiLayer.m_ErrorGradient[layer][snode]);
		}
		printf("\n");
	}
	printf("\n");

	//����ġ ���
	printf("�н� �� ����ġ\n");
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer - 1; layer++) {
		printf("layer = %d ", layer);
		for (enode = 1; enode <= MultiLayer.m_NumNodes[layer + 1]; enode++) {
			printf("[%d]bias = ", enode);
			for (snode = 0; snode <= MultiLayer.m_NumNodes[layer]; snode++) {
				printf("%.4lf ", 
					MultiLayer.m_Weight[layer][snode][enode]);
			}
		}
		printf("\n");	
	}


	
	return 0;
}

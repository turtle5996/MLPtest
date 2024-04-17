#include <iostream>
#include<stdio.h>
#include "MLP.h"
CMLP MultiLayer;

int main() {
	int h_layer[1] = { 2 };

	MultiLayer.Create(2, h_layer, 1, 1);

	double x[4][2] = { {0,0},{0,1},{1,0},{1,1} };
	MultiLayer.m_Weight[0][0][1] = -0.8;
	MultiLayer.m_Weight[0][1][1] = 0.5;
	MultiLayer.m_Weight[0][2][1] = 0.4;

	MultiLayer.m_Weight[0][0][2] = 0.1;
	MultiLayer.m_Weight[0][1][2] = 0.9;
	MultiLayer.m_Weight[0][2][2] = 1.0;

	MultiLayer.m_Weight[1][0][1] = -0.3;
	MultiLayer.m_Weight[1][1][1] = -1.2;
	MultiLayer.m_Weight[1][2][1] = 1.1;

	MultiLayer.pInValue[1] = 1;
	MultiLayer.pInValue[2] = 1;

	MultiLayer.pCorrectOutValue[1] = 0;
	MultiLayer.Forward();
	MultiLayer.BackPopagationLearning();

	printf("%lf %lf=%lf \n", MultiLayer.pInValue[1], MultiLayer.pInValue[1], MultiLayer.pOutValue[1]);

	/*for (int i = 0; i < 4; i++) {
		//MultiLayer.pInValue[0] = 1;       //바이어스
		MultiLayer.pInValue[1] = x[i][0]; //바이어스
		MultiLayer.pInValue[2] = x[i][1]; //바이어스


		MultiLayer.Forward();
		printf("%lf %lf=%lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);

	}
	*/
	printf("\n");

	int layer, snode, enode,node;

	//가중치 출력
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer - 1; layer++) {
		for (snode = 0; snode <= MultiLayer.m_NumNodes[layer]; snode++) {
			for (enode = 1; enode <= MultiLayer.m_NumNodes[layer + 1]; enode++) {
				printf("w[%d][%d][%d]=%lf,", layer, snode, enode,
					MultiLayer.m_Weight[layer][snode][enode]);
			}
			printf("\n");
		}
		printf("\n");	
	}


	//?
	for (layer = 0; layer < MultiLayer.m_iNumTotalLayer; layer++) {
	   for(node=0;node<=MultiLayer.m_NumNodes[layer];node++)
		   printf("NodeOut[%d][%d]=%lf\n", layer, node, MultiLayer.m_NodeOut[layer][node]);
	   printf("\n");
	}
	return 0;
}

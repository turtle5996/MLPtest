#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MLP.h"

//������
CMLP::CMLP() {
	m_iNumInNodes = 0;
	m_iNumOutNodes = 0;

	m_NumNodes = NULL;
	m_Weight = NULL;
	m_NodeOut = NULL;

	pInValue = NULL;
	pOutValue = NULL;
	pCorrectOutValue = NULL;

}

//�Ҹ���
CMLP::~CMLP() {
	int layer,snode,enode;
	if (m_NodeOut != NULL) {
		for (layer = 0; layer < m_iNumTotalLayer + 1; layer++) 
			free(m_NodeOut[layer]);
		free(m_NodeOut);
	}

	if (m_Weight != NULL) {
		for (layer = 0; layer < m_iNumTotalLayer - 1; layer++) {
			if (m_Weight[layer] != NULL) {
				for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
					free(m_Weight[layer][snode]);
				free(m_Weight[layer]);
			}
		}
		free(m_Weight);
	}

	if (m_NumNodes != NULL) free(m_NumNodes);

}

bool CMLP::Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	int layer, snode, enode;
	m_iNumInNodes = InNode;
	m_iNumOutNodes = OutNode;
	m_iNumHiddenLayer = numHiddenLayer;
	m_iNumTotalLayer = numHiddenLayer + 2;

	//m_NumNodes �� ���� �޷θ� �Ҵ�
	m_NumNodes = (int*)malloc((m_iNumTotalLayer + 1) * sizeof(int)); //����(+1)

	m_NumNodes[0] = m_iNumInNodes;
	for (layer = 0; layer < m_iNumHiddenLayer; layer++) 
		m_NumNodes[layer + 1] = pHiddenNode[layer];
	m_NumNodes[m_iNumTotalLayer - 1] = m_iNumOutNodes;
	m_NumNodes[m_iNumTotalLayer] = m_iNumOutNodes;

	//�� ��庰 �޸� �Ҵ�
	m_NodeOut = (double**)malloc((m_iNumTotalLayer + 1) * sizeof(double*)); //����+1
	for (layer = 0; layer < m_iNumTotalLayer; layer++)
		m_NodeOut[layer] = (double*)malloc((m_NumNodes[layer] + 1) * sizeof(double)); //���̾�� ���� +!

	//����(��³��� ���� ����, ���̾�� �ʿ������ ÷�ڴ� 1���� n����
	m_NodeOut[m_iNumTotalLayer] = (double*)malloc((m_NumNodes[m_iNumTotalLayer-1] + 1) * sizeof(double));
	

	//����ġ �޸� �Ҵ� m_weight[����layer][���۳��][������]
	m_Weight = (double***)malloc((m_iNumTotalLayer - 1) * sizeof(double**));
	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++) {
		m_Weight[layer] = (double**)malloc((m_NumNodes[layer] + 1) * sizeof(double*)); //���̾ +1
		for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
			m_Weight[layer][snode] = (double*)malloc((m_NumNodes[layer + 1] + 1) * sizeof(double)); // �������̾��� ���� 
	}

	pInValue = m_NodeOut[0];
	pOutValue = m_NodeOut[m_iNumTotalLayer - 1];
	pCorrectOutValue = m_NodeOut[m_iNumTotalLayer];

	InitW();
	
	//���̾�� ���� ��°� =1

	for (layer = 0; layer < m_iNumTotalLayer + 1; layer++) m_NodeOut[layer][0] = 1;

	return true;
}


void CMLP::InitW()
{
	int layer, snode, enode;

	srand(time(NULL));

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++) {
		for (snode = 0; snode <= m_NumNodes[layer]; snode++) {  //for ���̾�� ���� 0����
			for (enode = 0; enode <= m_NumNodes[layer + 1]; enode++) { // �������̾��� ����
				m_Weight[layer][snode][enode] = (double)rand() / RAND_MAX - 0.5;
			}
		}
	}
}


void CMLP::Forward()
{
	int layer, snode, enode;
	double wsum;

	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++) {
		for (enode = 1; enode <= m_NumNodes[layer + 1]; enode++) {
			wsum = 0.0;
			wsum += m_Weight[layer][0][enode] * 1;
			for (snode = 1; snode <= m_NumNodes[layer]; snode++) {
				wsum += m_Weight[layer][snode][enode] * m_NodeOut[layer][snode];
			}

			m_NodeOut[layer+1][enode] = ActivationFunc(wsum);
		}
	}
}


double CMLP::ActivationFunc(double weightsum)
{
	//step func
	/*
	if (weightsum > 0)return 1.0;
	else return 0.0;
	*/
	//sigmoidfunc
	return 1.0/(1.0+exp(-weightsum));
}

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

}


int main(){}

bool CMLP::Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	int layer, snode, enode;
	m_iNumInNodes = InNode;
	m_iNumOutNodes = OutNode;
	m_iNumHiddenLayer = numHiddenLayer;
	m_iNumTotalLayer = numHiddenLayer + 2;

	m_NumNodes = (int*)malloc((m_iNumTotalLayer + 1) * sizeof(int));

	return false;
}

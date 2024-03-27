#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MLP.h"

//생성자
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

//소멸자
CMLP::~CMLP() {

}


int main(){}

bool CMLP::Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer)
{
	// TODO: 여기에 구현 코드 추가.
	int layer, snode, enode;
	m_iNumInNodes = InNode;
	m_iNumOutNodes = OutNode;
	m_iNumHiddenLayer = numHiddenLayer;
	m_iNumTotalLayer = numHiddenLayer + 2;

	//m_NumNodes 를 위한 메로리 할당
	m_NumNodes = (int*)malloc((m_iNumTotalLayer + 1) * sizeof(int)); //정답(+1)

	m_NumNodes[0] = m_iNumInNodes;
	for (layer = 0; layer < m_iNumHiddenLayer; layer++) 
		m_NumNodes[layer + 1] = pHiddenNode[layer];
	m_NumNodes[m_iNumTotalLayer - 1] = m_iNumOutNodes;
	m_NumNodes[m_iNumTotalLayer] = m_iNumOutNodes;

	//각 노드별 메모리 할당
	m_NodeOut = (double**)malloc((m_iNumTotalLayer + 1) * sizeof(double*)); //정답+1
	for (layer = 0; layer < m_iNumTotalLayer; layer++)
		m_NodeOut[layer] = (double*)malloc((m_NumNodes[layer] + 1) * sizeof(double)); //바이어스를 위해 +!

	//정답(출력노드와 같은 개수, 바이어스가 필요없지만 첨자는 1에서 n까지
	m_NodeOut[m_iNumTotalLayer] = (double*)malloc((m_NumNodes[m_iNumTotalLayer-1] + 1) * sizeof(double));
	

	//가중치 메모리 할당 m_weight[시작layer][시작노드][연결노드]
	m_Weight = (double***)malloc((m_iNumTotalLayer - 1) * sizeof(double**));
	for (layer = 0; layer < m_iNumTotalLayer - 1; layer++) {
		m_Weight[layer] = (double**)malloc((m_NumNodes[layer] + 1) * sizeof(double*)); //바이어스 +1
		for (snode = 0; snode < m_NumNodes[layer] + 1; snode++)
			m_Weight[layer][snode] = (double*)malloc((m_NumNodes[layer + 1] + 1) * sizeof(double)); // 다음레이어의 노드수 
	}

	pInValue = m_NodeOut[0];
	pOutValue = m_NodeOut[m_iNumTotalLayer - 1];
	pCorrectOutValue = m_NodeOut[m_iNumTotalLayer];

	
	return false;
}

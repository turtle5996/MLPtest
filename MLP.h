class CMLP

#define LEARNING_RATE 0.1 
{public:
	CMLP();
	~CMLP();

	//신경망 구조선언을 위한 
	int m_iNumInNodes;
	int m_iNumOutNodes;
	int m_iNumHiddenLayer; // hiden layer only
	int m_iNumTotalLayer; //input layer + output layer
	int* m_NumNodes;// [0]-input node, [1]-hidden layer,[m_iNumHiddenLayers + 1],output layer, wjdwkq

	double*** m_Weight;  //[start layer] [시작 노드] [연결 노드]
	double** m_NodeOut; //[layer][node]

	double** m_ErrorGradient; //[layer][node]

	double* pInValue, * pOutValue; //입력레이어, 출력레이어
	double* pCorrectOutValue; //정답레이어
	bool Create(int InNode, int* pHiddenNode, int OutNode, int numHiddenLayer);
private:
	void InitW();
public:
	void Forward();
private:
	double ActivationFunc(double weightsum);
public:
	void BackPopagationLearning();
};

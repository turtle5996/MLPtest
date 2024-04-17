class CMLP

#define LEARNING_RATE 0.1 
{public:
	CMLP();
	~CMLP();

	//�Ű�� ���������� ���� 
	int m_iNumInNodes;
	int m_iNumOutNodes;
	int m_iNumHiddenLayer; // hiden layer only
	int m_iNumTotalLayer; //input layer + output layer
	int* m_NumNodes;// [0]-input node, [1]-hidden layer,[m_iNumHiddenLayers + 1],output layer, wjdwkq

	double*** m_Weight;  //[start layer] [���� ���] [���� ���]
	double** m_NodeOut; //[layer][node]

	double** m_ErrorGradient; //[layer][node]

	double* pInValue, * pOutValue; //�Է·��̾�, ��·��̾�
	double* pCorrectOutValue; //���䷹�̾�
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

#pragma once


#include "SearchEngine.h"

//�������������
class CIDAlphabetaEngine:public CSearchEngine   
{
public:
	CIDAlphabetaEngine();
	virtual ~CIDAlphabetaEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
	int AlphaBeta(int nDepth,int alpha,int beta);

protected:
	int m_nTimeCount;//��ʱ����
};


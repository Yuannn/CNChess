#pragma once


#include "SearchEngine.h"

//alpha-beta��������
class CAlphaBetaEngine:public CSearchEngine
{
public:
	CAlphaBetaEngine();
	virtual ~CAlphaBetaEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);//��������õĽӿڣ�Ϊ��ǰ�������һ������

protected:
	int AlphaBeta(int depth,int alpha,int beta);//alpha-beta����������
};

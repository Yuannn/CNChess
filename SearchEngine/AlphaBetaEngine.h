#pragma once


#include "SearchEngine.h"

//alpha-beta搜索引擎
class CAlphaBetaEngine:public CSearchEngine
{
public:
	CAlphaBetaEngine();
	virtual ~CAlphaBetaEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);//供界面调用的接口，为当前局面产生一步好棋

protected:
	int AlphaBeta(int depth,int alpha,int beta);//alpha-beta的搜索函数
};

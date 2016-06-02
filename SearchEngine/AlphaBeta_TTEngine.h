#pragma once

#include "SearchEngine.h"
#include "TranspositionTable.h"

//加置换表的Alpha-Beta搜索引擎
class CAlphaBeta_TTEngine:public CSearchEngine,public CTranspositionTable   
{
public:
	CAlphaBeta_TTEngine();
	virtual ~CAlphaBeta_TTEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
	int AlphaBeta(int nDepth, int alpha, int beta);
};


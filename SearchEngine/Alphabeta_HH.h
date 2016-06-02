#pragma once


#include "SearchEngine.h"
#include "HistoryHeuristic.h"

//����ʷ������Alpha-Beta��������
class CAlphabeta_HHEngine:public CSearchEngine,public CHistoryHeuristic  
{
public:
	CAlphabeta_HHEngine();
	virtual ~CAlphabeta_HHEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
	int AlphaBeta(int nDepth,int alpha,int beta);
};


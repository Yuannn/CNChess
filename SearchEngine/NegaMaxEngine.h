#pragma once


#include "SearchEngine.h"

//负极大值搜索引擎
class CNegaMaxEngine:public CSearchEngine
{
public:	
	CNegaMaxEngine();
	virtual ~CNegaMaxEngine();
	
public:
	virtual void SearchAGoodMove(BYTE position[10][9]);//走下一步

protected:
	int NegaMax(int nDepth);//负极大值搜索函数
};



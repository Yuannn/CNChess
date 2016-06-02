#pragma once


#include "SearchEngine.h"

//��С������������
class CPVS_Engine:public CSearchEngine
{
public:
	CPVS_Engine();
	virtual ~CPVS_Engine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
	int PrincipalVariation(int depth,int alpha,int beta);
};


#pragma once


#include "SearchEngine.h"

//������ֵ��������
class CNegaMaxEngine:public CSearchEngine
{
public:	
	CNegaMaxEngine();
	virtual ~CNegaMaxEngine();
	
public:
	virtual void SearchAGoodMove(BYTE position[10][9]);//����һ��

protected:
	int NegaMax(int nDepth);//������ֵ��������
};



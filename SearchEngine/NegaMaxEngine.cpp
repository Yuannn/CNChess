

#include "stdafx.h"
#include "Chess.h"
#include "NegaMaxEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegaMaxEngine::CNegaMaxEngine()
{

}

CNegaMaxEngine::~CNegaMaxEngine()
{

}

void CNegaMaxEngine::SearchAGoodMove(BYTE position[10][9])
{
	memcpy(CurPosition, position, 90);//����������̸��Ƶ���Ա������

	m_nMaxDepth = m_nSearchDepth;     //�趨��������		
	NegaMax(m_nMaxDepth);			//���ø�����ֵ��������������߷�
	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);
	//�������޸�Ϊ���߹���	

	memcpy(position, CurPosition, 90);//���޸ĺ�����̸��Ƶ�����������У���ȥ
}

//void CNegaMaxEngine::SearchAGoodMove(BYTE position[][9])
//{
//	memcpy(CurPosition,position,90);//����������̸��Ƶ���Ա������
//
//	m_nMaxDepth=m_nSearchDepth;     //�趨��������		
//	NegaMax(m_nMaxDepth);			//���ø�����ֵ��������������߷�
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);	
//									//�������޸�Ϊ���߹���	
//
//	memcpy(position,CurPosition,90);//���޸ĺ�����̸��Ƶ�����������У���ȥ
//}

int CNegaMaxEngine::NegaMax(int nDepth)
{
	int current=-20000;
	int score;
	int Count,i;
	BYTE type;

	i=IsGameOver(CurPosition,nDepth);//�������Ƿ����
	if(i!=0)
		return i;//��ֽ��������ؼ���/��Сֵ

	if(nDepth<=0)//Ҷ�ӽڵ�ȡ��ֵ
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);

	//�оٵ�ǰ�����һ�����п��ܵ��߷�
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

	for(i=0;i<Count;i++)
	{	
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//�߽�����

		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);     //�����߷������¾���    		
		score=-NegaMax(nDepth-1);					      //�ݹ���ø�����ֵ������һ��ڵ�		
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);   //�ָ���ǰ����

		if(score>current)							      //���score������֪�����ֵ
		{
			current=score;								  //�޸ĵ�ǰ���ֵΪscore
			if(nDepth==m_nMaxDepth)		
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];//��������ʱ��������߷�
		}
	}
	
	return current;//���ؼ���ֵ
}

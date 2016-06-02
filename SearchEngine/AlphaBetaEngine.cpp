

#include "stdafx.h"
#include "AlphaBetaEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBetaEngine::CAlphaBetaEngine()
{

}

CAlphaBetaEngine::~CAlphaBetaEngine()
{

}

void CAlphaBetaEngine::SearchAGoodMove(BYTE position[10][9])
{
	memcpy(CurPosition, position, 90);    //����ǰ���渴�Ƶ�CurPosition

	m_nMaxDepth = m_nSearchDepth;			//�趨�������
	AlphaBeta(m_nMaxDepth, -20000, 20000);//����alphabeta����
	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);

	memcpy(position, CurPosition, 90);	//���߹������̴���
}

//void CAlphaBetaEngine::SearchAGoodMove(BYTE position[][9])
//{
//	memcpy(CurPosition,position,90);    //����ǰ���渴�Ƶ�CurPosition
//
//	m_nMaxDepth=m_nSearchDepth;			//�趨�������
//	AlphaBeta(m_nMaxDepth,-20000,20000);//����alphabeta����
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);	
//
//	memcpy(position,CurPosition,90);	//���߹������̴���
//}

int CAlphaBetaEngine::AlphaBeta(int nDepth,int alpha,int beta)
{
	int score;
	int Count,i;
	BYTE type;

	i=IsGameOver(CurPosition,nDepth);//����Ƿ���Ϸ����
	if(i!=0)
		return i;//���������ع�ֵ

	//Ҷ�ӽڵ�ȡ��ֵ
	if(nDepth<=0)
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);

	//�˺����ҳ���ǰ�������п��ܵ��߷���Ȼ��Ž�m_pMG ->m_MoveList����
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

	//�����п��ܵ��߷�
	for(i=0;i<Count;i++)
	{		
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//�߽�����

		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);  //����ǰ����Ӧ�ô��߷�����Ϊ�ӽڵ�ľ���
		score=-AlphaBeta(nDepth-1,-beta,-alpha);       //�ݹ������ӽڵ�
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);//���˽ڵ�ľ���ָ�Ϊ��ǰ�ڵ�

		if(score>alpha)
		{
			alpha=score;//��������ֵ

			//�������ڵ�ʱ��������߷�
			if(nDepth==m_nMaxDepth)
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
		}
		
		if(alpha>=beta)
			break;//��֦����������ʣ�µĽڵ�
	}

	return alpha;//���ؼ���ֵ
}

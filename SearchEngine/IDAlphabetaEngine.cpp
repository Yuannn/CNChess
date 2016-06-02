

#include "stdafx.h"
#include "IDAlphabetaEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDAlphabetaEngine::CIDAlphabetaEngine()
{

}

CIDAlphabetaEngine::~CIDAlphabetaEngine()
{

}

void CIDAlphabetaEngine::SearchAGoodMove(BYTE position[10][9])
{
	CHESSMOVE backupmove;//����߷��ı���

	memcpy(CurPosition, position, 90);
	m_nTimeCount = GetTickCount();

	//���������
	for (m_nMaxDepth = 1; m_nMaxDepth <= m_nSearchDepth; m_nMaxDepth++)
		if (AlphaBeta(m_nMaxDepth, -20000, 20000) != 66666)//�����������û�б���ֹ����������߷�
			backupmove = m_cmBestMove;

	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);

	memcpy(position, CurPosition, 90);//��������߷�
}

//void CIDAlphabetaEngine::SearchAGoodMove(BYTE position[][9])
//{
//	CHESSMOVE backupmove;//����߷��ı���
//
//	memcpy(CurPosition,position,90);
//	m_nTimeCount=GetTickCount();
//
//	//���������
//	for(m_nMaxDepth=1;m_nMaxDepth<=m_nSearchDepth;m_nMaxDepth++)
//		if(AlphaBeta(m_nMaxDepth,-20000,20000)!=66666)//�����������û�б���ֹ����������߷�
//			backupmove=m_cmBestMove;
//
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);
//	
//	memcpy(position,CurPosition,90);//��������߷�
//}

int CIDAlphabetaEngine::AlphaBeta(int nDepth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;

	i=IsGameOver(CurPosition, nDepth);
	if(i!=0)
		return i;

	if(nDepth<=0)//Ҷ�ӽڵ�ȡ��ֵ
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

	//���� if���֮�ڴ��룬���ڵ����ײ�ڵ�����˳��
	//���ĳ�߷����ϴε������� BestMove���������ڵ�һλ
	if(nDepth==m_nMaxDepth && m_nMaxDepth>1)
		for(i=1;i<Count;i++) 
		{
			if(m_pMG->m_MoveList[nDepth][i].From.x==m_cmBestMove.From.x
				&& m_pMG->m_MoveList[nDepth][i].From.y==m_cmBestMove.From.y
				&& m_pMG->m_MoveList[nDepth][i].To.x==m_cmBestMove.To.x	
				&& m_pMG->m_MoveList[nDepth][i].To.y==m_cmBestMove.To.y)	
			{
				//���������߷���λ��
				m_pMG->m_MoveList[nDepth][i]=m_pMG->m_MoveList[nDepth][0];
				m_pMG->m_MoveList[nDepth][0]=m_cmBestMove;
			}				
		}	

	for(i=0;i<Count;i++) 
	{
		if(nDepth==m_nMaxDepth)//�쿴�Ƿ��ѵ��޶�ʱ�䣬10 ��
		{
			m_pThinkProgress->StepIt();//�߽�����
			if(GetTickCount()-m_nTimeCount>=1000000)
				return 66666;//������ֹ���
		}

		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);  //�����ӽڵ�
		score=-AlphaBeta(nDepth-1,-beta,-alpha);		  //�ݹ�����
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);//�����ӽڵ�

		if(score>alpha)
		{
			alpha=score;
			if(nDepth==m_nMaxDepth)
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];//��������߷�
		}
        if(alpha>=beta) 
              break;//beta��֦			
	}

	return alpha;//�������ֵ
}



#include "stdafx.h"
#include "AlphaBeta_TTEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBeta_TTEngine::CAlphaBeta_TTEngine()
{

}

CAlphaBeta_TTEngine::~CAlphaBeta_TTEngine()
{

}

void CAlphaBeta_TTEngine::SearchAGoodMove(BYTE position[10][9])
{
	memcpy(CurPosition, position, 90);

	CalculateInitHashKey(CurPosition);//�����ʼ���̵Ĺ�ϣֵ
	m_nMaxDepth = m_nSearchDepth;
	AlphaBeta(m_nMaxDepth, -20000, 20000);
	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);

	memcpy(position, CurPosition, 90);
}

//void CAlphaBeta_TTEngine::SearchAGoodMove(BYTE position[][9])
//{
//	memcpy(CurPosition,position,90);
//
//	CalculateInitHashKey(CurPosition);//�����ʼ���̵Ĺ�ϣֵ
//	m_nMaxDepth=m_nSearchDepth;
//	AlphaBeta(m_nMaxDepth,-20000,20000);
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);	
//
//	memcpy(position,CurPosition,90);
//}

int CAlphaBeta_TTEngine::AlphaBeta(int nDepth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;
	int side;

	i=IsGameOver(CurPosition,nDepth);
	if(i!=0)
		return i;
	
	//�쿴��ǰ�ڵ��Ƿ����û���������Ч����
	side=(m_nMaxDepth-nDepth)%2;
	score=LookUpHashTable(alpha,beta,nDepth,side); 
	if(score!=66666) 
		return score;//���У�ֱ�ӷ��ر��е�ֵ

	//Ҷ�ӽڵ�ȡ��ֵ
	if(nDepth<=0)
	{
		score=m_pEval->Eveluate(CurPosition,side,m_nUserChessColor);
		EnterHashTable(exact,score,nDepth,side);//����õĹ�ֵ�Ž��û���
		return score;
	}

	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,side,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

    int eval_is_exact=0;//�������ͱ�־

	for(i=0;i<Count;i++)//�Ե�ǰ�ڵ����һ��ÿһ���ܵ��߷�
	{
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//�߽�����

		Hash_MakeMove(&m_pMG->m_MoveList[nDepth][i],CurPosition);//�������߷�����Ӧ�ӽڵ�Ĺ�ϣֵ
		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);			 //�����ӽڵ�
		
		score=-AlphaBeta(nDepth-1,-beta,-alpha);//�ݹ������ӽڵ�

		Hash_UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type,CurPosition);//�ָ���ǰ�ڵ�Ĺ�ϣֵ 
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);				   //�����ӽڵ�
        if(score>=beta)//beta��֦
		{
			EnterHashTable(lower_bound,score,nDepth,side);//���ڵ��±߽�����û���
            return score;//�����±߽�
        }

		if(score>alpha)
		{
			alpha=score;    //ȡ���ֵ
			eval_is_exact=1;//�趨ȷ��ֵ��־
			if(nDepth==m_nMaxDepth)
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
		}
	}

	//����������Ž��û���
    if(eval_is_exact) 
		EnterHashTable(exact,alpha,nDepth,side);	  //ȷ��ֵ
    else 
		EnterHashTable(upper_bound,alpha,nDepth,side);//�ϱ߽�

	return alpha;//�������ֵ/�Ͻ�
}

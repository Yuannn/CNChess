

#include "stdafx.h"
#include "PVS_Engine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPVS_Engine::CPVS_Engine()
{

}

CPVS_Engine::~CPVS_Engine()
{

}

void CPVS_Engine::SearchAGoodMove(BYTE position[10][9])
{
	memcpy(CurPosition, position, 90);

	m_nMaxDepth = m_nSearchDepth;
	PrincipalVariation(m_nMaxDepth, -20000, 20000);
	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);

	memcpy(position, CurPosition, 90);
}

//void CPVS_Engine::SearchAGoodMove(BYTE position[][9])
//{
//	memcpy(CurPosition,position,90);
//
//	m_nMaxDepth=m_nSearchDepth;
//	PrincipalVariation(m_nMaxDepth,-20000,20000);	
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);	
//
//	memcpy(position, CurPosition, 90);
//}

int CPVS_Engine::PrincipalVariation(int nDepth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;
	int best;

	i=IsGameOver(CurPosition, nDepth);
	if(i!=0)
		return i;

	//Ҷ�ӽڵ�ȡ��ֵ
	if(nDepth<=0)
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}
	
	type=MakeMove(&m_pMG->m_MoveList[nDepth][0]);   //������һ���ڵ�
	best=-PrincipalVariation(nDepth-1,-beta,-alpha);//ʹ��ȫ����������һ���ڵ�
	UnMakeMove(&m_pMG->m_MoveList[nDepth][0],type); //������һ���ڵ� 
	
	//�������ڵ㱣������߷�
	if(nDepth==m_nMaxDepth)
		m_cmBestMove=m_pMG->m_MoveList[nDepth][0];
	
	//�ӵڶ����ڵ��𣬶�ÿһ�ڵ�
	for(i=1;i<Count;i++)
	{
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//�߽�����

		if(best<beta)//�������Beta��֦
		{
			if(best>alpha)
				alpha=best;

			type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);       //�����Ӹ��ڵ�
			score=-PrincipalVariation(nDepth-1,-alpha-1,-alpha);//ʹ�ü�խ������

			if(score>alpha && score<beta) 
			{
				best=-PrincipalVariation(nDepth-1,-beta,-score);//failhigh����������
				
				//�������ڵ㱣������߷�
				if(nDepth==m_nMaxDepth)
					m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
			}
			else
				if(score>best)
				{
					best=score;//խ����������
					if(nDepth==m_nMaxDepth)
						m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
				}

			UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);//�����ӽڵ�
		}
	}

	return best;//�������ֵ
}

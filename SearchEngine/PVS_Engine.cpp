

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

	//叶子节点取估值
	if(nDepth<=0)
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//在根节点设定进度条
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}
	
	type=MakeMove(&m_pMG->m_MoveList[nDepth][0]);   //产生第一个节点
	best=-PrincipalVariation(nDepth-1,-beta,-alpha);//使用全窗口搜索第一个节点
	UnMakeMove(&m_pMG->m_MoveList[nDepth][0],type); //撤销第一个节点 
	
	//靠近根节点保存最佳走法
	if(nDepth==m_nMaxDepth)
		m_cmBestMove=m_pMG->m_MoveList[nDepth][0];
	
	//从第二个节点起，对每一节点
	for(i=1;i<Count;i++)
	{
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//走进度条

		if(best<beta)//如果不能Beta剪枝
		{
			if(best>alpha)
				alpha=best;

			type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);       //产生子个节点
			score=-PrincipalVariation(nDepth-1,-alpha-1,-alpha);//使用极窄窗搜索

			if(score>alpha && score<beta) 
			{
				best=-PrincipalVariation(nDepth-1,-beta,-score);//failhigh，重新搜索
				
				//靠近根节点保存最佳走法
				if(nDepth==m_nMaxDepth)
					m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
			}
			else
				if(score>best)
				{
					best=score;//窄窗搜索命中
					if(nDepth==m_nMaxDepth)
						m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
				}

			UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);//撤销子节点
		}
	}

	return best;//返回最佳值
}

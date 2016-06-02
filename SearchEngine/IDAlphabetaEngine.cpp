

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
	CHESSMOVE backupmove;//最佳走法的备份

	memcpy(CurPosition, position, 90);
	m_nTimeCount = GetTickCount();

	//迭代深化搜索
	for (m_nMaxDepth = 1; m_nMaxDepth <= m_nSearchDepth; m_nMaxDepth++)
		if (AlphaBeta(m_nMaxDepth, -20000, 20000) != 66666)//如果本次搜索没有被中止，保存最佳走法
			backupmove = m_cmBestMove;

	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);

	memcpy(position, CurPosition, 90);//传出最佳走法
}

//void CIDAlphabetaEngine::SearchAGoodMove(BYTE position[][9])
//{
//	CHESSMOVE backupmove;//最佳走法的备份
//
//	memcpy(CurPosition,position,90);
//	m_nTimeCount=GetTickCount();
//
//	//迭代深化搜索
//	for(m_nMaxDepth=1;m_nMaxDepth<=m_nSearchDepth;m_nMaxDepth++)
//		if(AlphaBeta(m_nMaxDepth,-20000,20000)!=66666)//如果本次搜索没有被中止，保存最佳走法
//			backupmove=m_cmBestMove;
//
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);
//	
//	memcpy(position,CurPosition,90);//传出最佳走法
//}

int CIDAlphabetaEngine::AlphaBeta(int nDepth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;

	i=IsGameOver(CurPosition, nDepth);
	if(i!=0)
		return i;

	if(nDepth<=0)//叶子节点取估值
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//在根节点设定进度条
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

	//此下 if语句之内代码，用于调整底层节点排列顺序
	//如果某走法在上次迭代中是 BestMove，将其排在第一位
	if(nDepth==m_nMaxDepth && m_nMaxDepth>1)
		for(i=1;i<Count;i++) 
		{
			if(m_pMG->m_MoveList[nDepth][i].From.x==m_cmBestMove.From.x
				&& m_pMG->m_MoveList[nDepth][i].From.y==m_cmBestMove.From.y
				&& m_pMG->m_MoveList[nDepth][i].To.x==m_cmBestMove.To.x	
				&& m_pMG->m_MoveList[nDepth][i].To.y==m_cmBestMove.To.y)	
			{
				//交换两个走法的位置
				m_pMG->m_MoveList[nDepth][i]=m_pMG->m_MoveList[nDepth][0];
				m_pMG->m_MoveList[nDepth][0]=m_cmBestMove;
			}				
		}	

	for(i=0;i<Count;i++) 
	{
		if(nDepth==m_nMaxDepth)//察看是否已到限定时间，10 秒
		{
			m_pThinkProgress->StepIt();//走进度条
			if(GetTickCount()-m_nTimeCount>=1000000)
				return 66666;//返回中止标记
		}

		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);  //产生子节点
		score=-AlphaBeta(nDepth-1,-beta,-alpha);		  //递归搜索
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);//撤销子节点

		if(score>alpha)
		{
			alpha=score;
			if(nDepth==m_nMaxDepth)
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];//保存最佳走法
		}
        if(alpha>=beta) 
              break;//beta剪枝			
	}

	return alpha;//返回最大值
}

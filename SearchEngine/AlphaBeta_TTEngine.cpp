

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

	CalculateInitHashKey(CurPosition);//计算初始棋盘的哈希值
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
//	CalculateInitHashKey(CurPosition);//计算初始棋盘的哈希值
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
	
	//察看当前节点是否在置换表中有有效数据
	side=(m_nMaxDepth-nDepth)%2;
	score=LookUpHashTable(alpha,beta,nDepth,side); 
	if(score!=66666) 
		return score;//命中，直接返回表中的值

	//叶子节点取估值
	if(nDepth<=0)
	{
		score=m_pEval->Eveluate(CurPosition,side,m_nUserChessColor);
		EnterHashTable(exact,score,nDepth,side);//将求得的估值放进置换表
		return score;
	}

	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,side,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//在根节点设定进度条
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

    int eval_is_exact=0;//数据类型标志

	for(i=0;i<Count;i++)//对当前节点的下一步每一可能的走法
	{
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//走进度条

		Hash_MakeMove(&m_pMG->m_MoveList[nDepth][i],CurPosition);//产生该走法所对应子节点的哈希值
		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);			 //产生子节点
		
		score=-AlphaBeta(nDepth-1,-beta,-alpha);//递归搜索子节点

		Hash_UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type,CurPosition);//恢复当前节点的哈希值 
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);				   //撤销子节点
        if(score>=beta)//beta剪枝
		{
			EnterHashTable(lower_bound,score,nDepth,side);//将节点下边界存入置换表
            return score;//返回下边界
        }

		if(score>alpha)
		{
			alpha=score;    //取最大值
			eval_is_exact=1;//设定确切值标志
			if(nDepth==m_nMaxDepth)
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];
		}
	}

	//将搜索结果放进置换表
    if(eval_is_exact) 
		EnterHashTable(exact,alpha,nDepth,side);	  //确切值
    else 
		EnterHashTable(upper_bound,alpha,nDepth,side);//上边界

	return alpha;//返回最佳值/上界
}

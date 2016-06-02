

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
	memcpy(CurPosition, position, 90);//将传入的棋盘复制到成员变量中

	m_nMaxDepth = m_nSearchDepth;     //设定搜索层数		
	NegaMax(m_nMaxDepth);			//调用负极大值搜索函数找最佳走法
	m_umUndoMove.cmChessMove = m_cmBestMove;
	m_umUndoMove.nChessID = MakeMove(&m_cmBestMove);
	//将棋盘修改为已走过的	

	memcpy(position, CurPosition, 90);//将修改后的棋盘复制到传入的棋盘中，传去
}

//void CNegaMaxEngine::SearchAGoodMove(BYTE position[][9])
//{
//	memcpy(CurPosition,position,90);//将传入的棋盘复制到成员变量中
//
//	m_nMaxDepth=m_nSearchDepth;     //设定搜索层数		
//	NegaMax(m_nMaxDepth);			//调用负极大值搜索函数找最佳走法
//	m_umUndoMove.cmChessMove=m_cmBestMove;
//	m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);	
//									//将棋盘修改为已走过的	
//
//	memcpy(position,CurPosition,90);//将修改后的棋盘复制到传入的棋盘中，传去
//}

int CNegaMaxEngine::NegaMax(int nDepth)
{
	int current=-20000;
	int score;
	int Count,i;
	BYTE type;

	i=IsGameOver(CurPosition,nDepth);//检查棋局是否结束
	if(i!=0)
		return i;//棋局结束，返回极大/极小值

	if(nDepth<=0)//叶子节点取估值
		return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);

	//列举当前棋局下一步所有可能的走法
	Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
	if(nDepth==m_nMaxDepth)
	{
		//在根节点设定进度条
		m_pThinkProgress->SetRange(0,Count);
		m_pThinkProgress->SetStep(1);
	}

	for(i=0;i<Count;i++)
	{	
		if(nDepth==m_nMaxDepth)
			m_pThinkProgress->StepIt();//走进度条

		type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);     //根据走法产生新局面    		
		score=-NegaMax(nDepth-1);					      //递归调用负极大值搜索下一层节点		
		UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);   //恢复当前局面

		if(score>current)							      //如果score大于已知的最大值
		{
			current=score;								  //修改当前最大值为score
			if(nDepth==m_nMaxDepth)		
				m_cmBestMove=m_pMG->m_MoveList[nDepth][i];//靠近根部时保存最佳走法
		}
	}
	
	return current;//返回极大值
}

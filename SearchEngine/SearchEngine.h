#pragma once


#include "Eveluation.h"
#include "MoveGenerator.h"
#include "GradientProgressCtrl.h"

//搜索引擎的基类
class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9])=0;        //走下一步
	CHESSMOVE GetBestMove(){return m_cmBestMove;};			//得到最佳走法
	UNDOMOVE GetUndoMove(){return m_umUndoMove;};			//得到悔棋走法
	void SetSearchDepth(int nDepth){m_nSearchDepth=nDepth;};//设定最大搜索深度
	void SetEveluator(CEveluation* pEval){m_pEval=pEval;};  //设定估值引擎
	void SetMoveGenerator(CMoveGenerator* pMG){m_pMG =pMG;};//设定走法产生器
	void SetThinkProgress(CGradientProgressCtrl* pThinkProgress){m_pThinkProgress=pThinkProgress;};
															//设定显示思考进度的进度条
	void SetUserChessColor(int nUserChessColor){m_nUserChessColor=nUserChessColor;};
															//设定用户为黑方或红方

	void UndoChessMove(BYTE position[10][9],CHESSMOVE* move,BYTE nChessID);//悔棋
	void RedoChessMove(BYTE position[10][9],CHESSMOVE* move);              //还原

protected:
	int IsGameOver(BYTE position[10][9],int nDepth);//判断是否已分胜负
	BYTE MakeMove(CHESSMOVE* move);				    //根据某一走法产生走了之后的棋盘
	void UnMakeMove(CHESSMOVE* move,BYTE nChessID); //恢复为走过之前的棋盘	

public:
	int m_nUserChessColor;

protected:
	CGradientProgressCtrl* m_pThinkProgress;
								    //用以显示思考进度的进度条指针
	BYTE CurPosition[10][9];		//搜索时用于记录当前节点棋盘状态的数组
	CHESSMOVE m_cmBestMove;			//记录最佳走法
	UNDOMOVE m_umUndoMove;
	CMoveGenerator* m_pMG;			//走法产生器
	CEveluation* m_pEval;			//估值核心
	int m_nSearchDepth;				//最大搜索深度
	int m_nMaxDepth;				//当前搜索的最大搜索深度
};



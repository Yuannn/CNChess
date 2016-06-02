

#include "stdafx.h"
#include "Chess.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearchEngine::CSearchEngine()
{
}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;
	delete m_pEval;
}

void CSearchEngine::UndoChessMove(BYTE position[10][9], CHESSMOVE * move, BYTE nChessID)
{
	position[move->From.y][move->From.x] = position[move->To.y][move->To.x];//将目标位置棋子拷回原位  	
	position[move->To.y][move->To.x] = nChessID;
}

void CSearchEngine::RedoChessMove(BYTE position[10][9], CHESSMOVE * move)
{
	position[move->To.y][move->To.x] = position[move->From.y][move->From.x];
	position[move->From.y][move->From.x] = NOCHESS;
}

int CSearchEngine::IsGameOver(BYTE position[10][9], int nDepth)
{
	int i, j;
	BOOL RedLive = FALSE, BlackLive = FALSE;

	//检查红方九宫是否有帅
	for (i = 7; i<10; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	//检查黑方九宫是否有将
	for (i = 0; i<3; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	i = (m_nMaxDepth - nDepth + 1) % 2;//取当前奇偶标志,奇数层为电脑方,偶数层为用户方
									   //红方不在
	if (!RedLive)
		if (i)
			return 19990 + nDepth; //奇数层返回极大值
		else
			return -19990 - nDepth;//偶数层返回极小值

								   //黑方不在
	if (!BlackLive)
		if (i)
			return -19990 - nDepth;//奇数层返回极小值
		else
			return 19990 + nDepth; //偶数层返回极大值

	return 0;//将帅都在，返回0
}

BYTE CSearchEngine::MakeMove(CHESSMOVE* move)
{
	BYTE nChessID;

	nChessID=CurPosition[move->To.y][move->To.x];   //取目标位置棋子
    CurPosition[move->To.y][move->To.x]=CurPosition[move->From.y][move->From.x];
													//把棋子移动到目标位置	
	CurPosition[move->From.y][move->From.x]=NOCHESS;//将原位置清空
	
	return nChessID;//返回被吃掉的棋子
}

//void CSearchEngine::RedoChessMove(BYTE position[][9],CHESSMOVE* move)
//{
//    position[move->To.y][move->To.x]=position[move->From.y][move->From.x];
//	position[move->From.y][move->From.x]=NOCHESS;
//}

void CSearchEngine::UnMakeMove(CHESSMOVE* move, BYTE nChessID)
{
	CurPosition[move->From.y][move->From.x]=CurPosition[move->To.y][move->To.x];//将目标位置棋子拷回原位  	
	CurPosition[move->To.y][move->To.x]=nChessID;								//恢复目标位置的棋子
}

//void CSearchEngine::UndoChessMove(BYTE position[][9],CHESSMOVE* move, BYTE nChessID)
//{
//	position[move->From.y][move->From.x]=position[move->To.y][move->To.x];//将目标位置棋子拷回原位  	
//	position[move->To.y][move->To.x]=nChessID;							  //恢复目标位置的棋子
//}

//int CSearchEngine::IsGameOver(BYTE position[][9], int nDepth)
//{
//	int i,j;
//	BOOL RedLive=FALSE,BlackLive=FALSE;
//
//	//检查红方九宫是否有帅
//	for(i=7;i<10;i++)
//		for(j=3;j<6;j++)
//		{
//			if(position[i][j]==B_KING)
//				BlackLive=TRUE;
//			if(position[i][j]==R_KING)
//				RedLive=TRUE;
//		}
//
//	//检查黑方九宫是否有将
//	for(i=0;i<3;i++)
//		for(j=3;j<6;j++)
//		{
//			if(position[i][j]==B_KING)
//				BlackLive=TRUE;
//			if(position[i][j]==R_KING)
//				RedLive=TRUE;
//		}
//
//	i=(m_nMaxDepth-nDepth+1)%2;//取当前奇偶标志,奇数层为电脑方,偶数层为用户方
//	//红方不在
//	if(!RedLive)
//		if(i)
//			return 19990+nDepth; //奇数层返回极大值
//		else
//			return -19990-nDepth;//偶数层返回极小值
//
//	//黑方不在
//	if(!BlackLive)
//		if(i)
//			return -19990-nDepth;//奇数层返回极小值
//		else
//			return 19990+nDepth; //偶数层返回极大值
//		
//	return 0;//将帅都在，返回0
//}

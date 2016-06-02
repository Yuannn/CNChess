

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
	position[move->From.y][move->From.x] = position[move->To.y][move->To.x];//��Ŀ��λ�����ӿ���ԭλ  	
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

	//���췽�Ź��Ƿ���˧
	for (i = 7; i<10; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	//���ڷ��Ź��Ƿ��н�
	for (i = 0; i<3; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	i = (m_nMaxDepth - nDepth + 1) % 2;//ȡ��ǰ��ż��־,������Ϊ���Է�,ż����Ϊ�û���
									   //�췽����
	if (!RedLive)
		if (i)
			return 19990 + nDepth; //�����㷵�ؼ���ֵ
		else
			return -19990 - nDepth;//ż���㷵�ؼ�Сֵ

								   //�ڷ�����
	if (!BlackLive)
		if (i)
			return -19990 - nDepth;//�����㷵�ؼ�Сֵ
		else
			return 19990 + nDepth; //ż���㷵�ؼ���ֵ

	return 0;//��˧���ڣ�����0
}

BYTE CSearchEngine::MakeMove(CHESSMOVE* move)
{
	BYTE nChessID;

	nChessID=CurPosition[move->To.y][move->To.x];   //ȡĿ��λ������
    CurPosition[move->To.y][move->To.x]=CurPosition[move->From.y][move->From.x];
													//�������ƶ���Ŀ��λ��	
	CurPosition[move->From.y][move->From.x]=NOCHESS;//��ԭλ�����
	
	return nChessID;//���ر��Ե�������
}

//void CSearchEngine::RedoChessMove(BYTE position[][9],CHESSMOVE* move)
//{
//    position[move->To.y][move->To.x]=position[move->From.y][move->From.x];
//	position[move->From.y][move->From.x]=NOCHESS;
//}

void CSearchEngine::UnMakeMove(CHESSMOVE* move, BYTE nChessID)
{
	CurPosition[move->From.y][move->From.x]=CurPosition[move->To.y][move->To.x];//��Ŀ��λ�����ӿ���ԭλ  	
	CurPosition[move->To.y][move->To.x]=nChessID;								//�ָ�Ŀ��λ�õ�����
}

//void CSearchEngine::UndoChessMove(BYTE position[][9],CHESSMOVE* move, BYTE nChessID)
//{
//	position[move->From.y][move->From.x]=position[move->To.y][move->To.x];//��Ŀ��λ�����ӿ���ԭλ  	
//	position[move->To.y][move->To.x]=nChessID;							  //�ָ�Ŀ��λ�õ�����
//}

//int CSearchEngine::IsGameOver(BYTE position[][9], int nDepth)
//{
//	int i,j;
//	BOOL RedLive=FALSE,BlackLive=FALSE;
//
//	//���췽�Ź��Ƿ���˧
//	for(i=7;i<10;i++)
//		for(j=3;j<6;j++)
//		{
//			if(position[i][j]==B_KING)
//				BlackLive=TRUE;
//			if(position[i][j]==R_KING)
//				RedLive=TRUE;
//		}
//
//	//���ڷ��Ź��Ƿ��н�
//	for(i=0;i<3;i++)
//		for(j=3;j<6;j++)
//		{
//			if(position[i][j]==B_KING)
//				BlackLive=TRUE;
//			if(position[i][j]==R_KING)
//				RedLive=TRUE;
//		}
//
//	i=(m_nMaxDepth-nDepth+1)%2;//ȡ��ǰ��ż��־,������Ϊ���Է�,ż����Ϊ�û���
//	//�췽����
//	if(!RedLive)
//		if(i)
//			return 19990+nDepth; //�����㷵�ؼ���ֵ
//		else
//			return -19990-nDepth;//ż���㷵�ؼ�Сֵ
//
//	//�ڷ�����
//	if(!BlackLive)
//		if(i)
//			return -19990-nDepth;//�����㷵�ؼ�Сֵ
//		else
//			return 19990+nDepth; //ż���㷵�ؼ���ֵ
//		
//	return 0;//��˧���ڣ�����0
//}

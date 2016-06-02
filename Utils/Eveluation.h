#pragma once


//定义每种棋子价值
//兵100，士250，象250，车1400，马700，炮700，王无穷大
#define BASEVALUE_PAWN       100
#define BASEVALUE_BISHOP	 250
#define BASEVALUE_ELEPHANT   250
#define BASEVALUE_HORSE		 700
#define BASEVALUE_CANON		 700
#define BASEVALUE_CAR		 1400
#define BASEVALUE_KING	     10000

//定义棋子灵活性，也就是每多一个可走位置应加的分值
//兵15，士1，象1，车6，马12，炮6，王0
#define FLEXIBILITY_PAWN	 15
#define FLEXIBILITY_BISHOP   1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_CAR		 6
#define FLEXIBILITY_HORSE	 12
#define FLEXIBILITY_CANON	 6
#define FLEXIBILITY_KING     0

//估值核心
class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();

public:
	virtual int Eveluate(BYTE position[10][9],BOOL bIsRedTurn,int nUserChessColor);
												 //估值函数，对传入的棋盘打分，bIsRedTurn表示轮到谁走棋
	int GetAccessCount(){return m_nAccessCount;};//得到访问节点数
	void ClearAccessCount(){m_nAccessCount=0;};  //重置访问节点数为0

protected:
	void AddPoint(int x,int y);						     //将一个位置加入相关位置队列
	bool CanTouch(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY);
													     //判断位置From的棋子是否能走到位置To
	int GetRelatePiece(BYTE position[10][9],int j,int i);//列举与指定位置的棋子相关的棋子
	int GetBingValue(int x,int y,BYTE CurSituation[][9]);//为每一个兵返回附加值，CurSituation是棋盘，不是兵返回0

protected:
	int m_BaseValue[15];		 //存放棋子基本价值
	int m_FlexValue[15];		 //存放棋子灵活性分值
	short m_AttackPos[10][9];	 //存放每一位置被威胁的信息
	BYTE m_GuardPos[10][9];      //存放每一位置被保护的信息
	BYTE m_FlexibilityPos[10][9];//存放每一位置上棋子的灵活性分值
	int m_chessValue[10][9];	 //存放每一位置上棋子的总价值
	int nPosCount;				 //记录一棋子的相关位置个数
	POINT RelatePos[20];		 //记录一棋子的相关位置
	long m_nAccessCount;
};



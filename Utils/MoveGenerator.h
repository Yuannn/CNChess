#pragma once

#include "Define.h"

//走法产生器
class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();

public:
//	static BOOL IsValidMove(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY,int nUserChessColor);
																	                    //走法是否有效
	BOOL IsValidMove(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY,int nUserChessColor);
	int CreatePossibleMove(BYTE position[10][9],int nPly,int nSide,int nUserChessColor);//产生所有可能的走法

protected:
	void Gen_BPawnMove(BYTE position[10][9],int i,int j,int nPly);   //产生黑卒的走法,nPly表明插入到List第几层
	void Gen_RPawnMove(BYTE position[10][9], int i,int j,int nPly);  //产生红兵的走法,nPly表明插入到List第几层

	void Gen_BBishopMove(BYTE position[10][9],int i,int j,int nPly); //产生黑士的走法,nPly表明插入到List第几层
	void Gen_RBishopMove(BYTE position[10][9],int i,int j,int nPly); //产生红士的走法,nPly表明插入到List第几层

	void Gen_CarMove(BYTE position[10][9], int i,int j,int nPly);    //产生车的走法,nPly表明插入到List第几层
	void Gen_HorseMove(BYTE position[10][9], int i,int j,int nPly);  //产生马的走法,nPly表明插入到List第几层
	void Gen_ElephantMove(BYTE position[10][9],int i,int j,int nPly);//产生相/象的走法,nPly表明插入到List第几层

	void Gen_KingMove(BYTE position[10][9],int i,int j,int nPly);	 //产生将/帅的走法,nPly表明插入到List第几层
	void Gen_CanonMove(BYTE position[10][9],int i,int j,int nPly);   //产生炮的走法,nPly表明插入到List第几层

	int AddMove(int nFromX,int nToX,int nFromY,int nToY,int nPly,int nChessID);
																	 //在m_MoveList中插入一个走法,nPly表明插入到List第几层

public:
	CHESSMOVE m_MoveList[8][80];//存放CreatePossibleMove产生的所有走法的队列

protected:
	int m_nMoveCount;//记录m_MoveList中走法的数量
	int m_nUserChessColor;
};



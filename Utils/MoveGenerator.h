#pragma once

#include "Define.h"

//�߷�������
class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();

public:
//	static BOOL IsValidMove(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY,int nUserChessColor);
																	                    //�߷��Ƿ���Ч
	BOOL IsValidMove(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY,int nUserChessColor);
	int CreatePossibleMove(BYTE position[10][9],int nPly,int nSide,int nUserChessColor);//�������п��ܵ��߷�

protected:
	void Gen_BPawnMove(BYTE position[10][9],int i,int j,int nPly);   //����������߷�,nPly�������뵽List�ڼ���
	void Gen_RPawnMove(BYTE position[10][9], int i,int j,int nPly);  //����������߷�,nPly�������뵽List�ڼ���

	void Gen_BBishopMove(BYTE position[10][9],int i,int j,int nPly); //������ʿ���߷�,nPly�������뵽List�ڼ���
	void Gen_RBishopMove(BYTE position[10][9],int i,int j,int nPly); //������ʿ���߷�,nPly�������뵽List�ڼ���

	void Gen_CarMove(BYTE position[10][9], int i,int j,int nPly);    //���������߷�,nPly�������뵽List�ڼ���
	void Gen_HorseMove(BYTE position[10][9], int i,int j,int nPly);  //��������߷�,nPly�������뵽List�ڼ���
	void Gen_ElephantMove(BYTE position[10][9],int i,int j,int nPly);//������/����߷�,nPly�������뵽List�ڼ���

	void Gen_KingMove(BYTE position[10][9],int i,int j,int nPly);	 //������/˧���߷�,nPly�������뵽List�ڼ���
	void Gen_CanonMove(BYTE position[10][9],int i,int j,int nPly);   //�����ڵ��߷�,nPly�������뵽List�ڼ���

	int AddMove(int nFromX,int nToX,int nFromY,int nToY,int nPly,int nChessID);
																	 //��m_MoveList�в���һ���߷�,nPly�������뵽List�ڼ���

public:
	CHESSMOVE m_MoveList[8][80];//���CreatePossibleMove�����������߷��Ķ���

protected:
	int m_nMoveCount;//��¼m_MoveList���߷�������
	int m_nUserChessColor;
};



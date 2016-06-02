#pragma once


#include "Eveluation.h"
#include "MoveGenerator.h"
#include "GradientProgressCtrl.h"

//��������Ļ���
class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();

public:
	virtual void SearchAGoodMove(BYTE position[10][9])=0;        //����һ��
	CHESSMOVE GetBestMove(){return m_cmBestMove;};			//�õ�����߷�
	UNDOMOVE GetUndoMove(){return m_umUndoMove;};			//�õ������߷�
	void SetSearchDepth(int nDepth){m_nSearchDepth=nDepth;};//�趨����������
	void SetEveluator(CEveluation* pEval){m_pEval=pEval;};  //�趨��ֵ����
	void SetMoveGenerator(CMoveGenerator* pMG){m_pMG =pMG;};//�趨�߷�������
	void SetThinkProgress(CGradientProgressCtrl* pThinkProgress){m_pThinkProgress=pThinkProgress;};
															//�趨��ʾ˼�����ȵĽ�����
	void SetUserChessColor(int nUserChessColor){m_nUserChessColor=nUserChessColor;};
															//�趨�û�Ϊ�ڷ���췽

	void UndoChessMove(BYTE position[10][9],CHESSMOVE* move,BYTE nChessID);//����
	void RedoChessMove(BYTE position[10][9],CHESSMOVE* move);              //��ԭ

protected:
	int IsGameOver(BYTE position[10][9],int nDepth);//�ж��Ƿ��ѷ�ʤ��
	BYTE MakeMove(CHESSMOVE* move);				    //����ĳһ�߷���������֮�������
	void UnMakeMove(CHESSMOVE* move,BYTE nChessID); //�ָ�Ϊ�߹�֮ǰ������	

public:
	int m_nUserChessColor;

protected:
	CGradientProgressCtrl* m_pThinkProgress;
								    //������ʾ˼�����ȵĽ�����ָ��
	BYTE CurPosition[10][9];		//����ʱ���ڼ�¼��ǰ�ڵ�����״̬������
	CHESSMOVE m_cmBestMove;			//��¼����߷�
	UNDOMOVE m_umUndoMove;
	CMoveGenerator* m_pMG;			//�߷�������
	CEveluation* m_pEval;			//��ֵ����
	int m_nSearchDepth;				//����������
	int m_nMaxDepth;				//��ǰ����������������
};



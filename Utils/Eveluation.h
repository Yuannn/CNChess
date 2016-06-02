#pragma once


//����ÿ�����Ӽ�ֵ
//��100��ʿ250����250����1400����700����700���������
#define BASEVALUE_PAWN       100
#define BASEVALUE_BISHOP	 250
#define BASEVALUE_ELEPHANT   250
#define BASEVALUE_HORSE		 700
#define BASEVALUE_CANON		 700
#define BASEVALUE_CAR		 1400
#define BASEVALUE_KING	     10000

//������������ԣ�Ҳ����ÿ��һ������λ��Ӧ�ӵķ�ֵ
//��15��ʿ1����1����6����12����6����0
#define FLEXIBILITY_PAWN	 15
#define FLEXIBILITY_BISHOP   1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_CAR		 6
#define FLEXIBILITY_HORSE	 12
#define FLEXIBILITY_CANON	 6
#define FLEXIBILITY_KING     0

//��ֵ����
class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();

public:
	virtual int Eveluate(BYTE position[10][9],BOOL bIsRedTurn,int nUserChessColor);
												 //��ֵ�������Դ�������̴�֣�bIsRedTurn��ʾ�ֵ�˭����
	int GetAccessCount(){return m_nAccessCount;};//�õ����ʽڵ���
	void ClearAccessCount(){m_nAccessCount=0;};  //���÷��ʽڵ���Ϊ0

protected:
	void AddPoint(int x,int y);						     //��һ��λ�ü������λ�ö���
	bool CanTouch(BYTE position[10][9],int nFromX,int nFromY,int nToX,int nToY);
													     //�ж�λ��From�������Ƿ����ߵ�λ��To
	int GetRelatePiece(BYTE position[10][9],int j,int i);//�о���ָ��λ�õ�������ص�����
	int GetBingValue(int x,int y,BYTE CurSituation[][9]);//Ϊÿһ�������ظ���ֵ��CurSituation�����̣����Ǳ�����0

protected:
	int m_BaseValue[15];		 //������ӻ�����ֵ
	int m_FlexValue[15];		 //�����������Է�ֵ
	short m_AttackPos[10][9];	 //���ÿһλ�ñ���в����Ϣ
	BYTE m_GuardPos[10][9];      //���ÿһλ�ñ���������Ϣ
	BYTE m_FlexibilityPos[10][9];//���ÿһλ�������ӵ�����Է�ֵ
	int m_chessValue[10][9];	 //���ÿһλ�������ӵ��ܼ�ֵ
	int nPosCount;				 //��¼һ���ӵ����λ�ø���
	POINT RelatePos[20];		 //��¼һ���ӵ����λ��
	long m_nAccessCount;
};



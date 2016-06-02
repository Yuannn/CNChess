#pragma once


#include "Define.h"

//������ö���͵��������ͣ���ȷ���±߽磬�ϱ߽�
enum ENTRY_TYPE{exact,lower_bound,upper_bound};

//��ϣ����Ԫ�صĽṹ����
typedef struct HASHITEM
{
	LONGLONG checksum;	  //64λУ����
	ENTRY_TYPE entry_type;//��������
	short depth;		  //ȡ�ô�ֵʱ�Ĳ��
	short eval;			  //�ڵ��ֵ
}HashItem;

//�û�����
class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();

public:
	void EnterHashTable(ENTRY_TYPE entry_type,short eval,short depth,int TableNo);
																    //����ǰ�ڵ��ֵ�����ϣ��
	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);//��ѯ��ϣ���е�ǰ�ڵ�����
	void Hash_UnMakeMove(CHESSMOVE* move,BYTE nChessID,BYTE CurPosition[10][9]);  
																	//���������߷��Ĺ�ϣֵ����ԭ���߹�֮ǰ��
	void Hash_MakeMove(CHESSMOVE* move,BYTE CurPosition[10][9]);	//���������߷������������µĹ�ϣֵ
	void CalculateInitHashKey(BYTE CurPosition[10][9]);				//����������̵Ĺ�ϣֵ
	void InitializeHashKey();										//��ʼ��������飬������ϣ��

protected:
	LONGLONG Rand64();//����64λ�������
	LONG Rand32();	  //����32λ�������

public:	
	UINT m_nHashKey32[15][10][9];	   //32λ������飬��������32λ��ϣֵ
	ULONGLONG m_ulHashKey64[15][10][9];//64λ������飬��������64λ��ϣֵ
	HashItem *m_pTT[10];			   //�û���ͷָ��
	UINT m_HashKey32;				   //32λ��ϣֵ
	LONGLONG m_HashKey64;			   //64λ��ϣֵ
};



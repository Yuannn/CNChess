

#include "stdafx.h"
#include "Chess.h"
#include "Eveluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//�������������������˱��ڲ�ͬλ�õĸ���ֵ
//�������ǹ���֮��Խ�����Ͻ���ֵԽ��
////����ĸ���ֵ����
//const int BA0[10][9]=
//{
//	{0,0,0,0,0,0,0,0,0},
//	{90,90,110,120,120,120,110,90,90},
//	{90,90,110,120,120,120,110,90,90},
//	{70,90,110,110,110,110,110,90,70},
//	{70,70,70, 70,70, 70, 70,70,70},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//};
//
////����ĸ���ֵ����
//const int BA1[10][9]=
//{
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0},
//	{70,70,70, 70,70, 70, 70,70,70},
//	{70,90,110,110,110,110,110,90,70},
//	{90,90,110,120,120,120,110,90,90},
//	{90,90,110,120,120,120,110,90,90},
//	{0,0,0,0,0,0,0,0,0},
//};

//����ĸ���ֵ����
const int BA0[10][9]=
{
	{0,0,0,0,0,0,0,0,0},
	{120,120,140,150,150,150,140,120,120},
	{120,120,140,150,150,150,140,120,120},
	{100,120,140,140,140,140,140,120,100},
	{100,100,100,100,100,100,100,100,100},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
};

//����ĸ���ֵ����
const int BA1[10][9]=
{
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{100,100,100,100,100,100,100,100,100},
	{100,120,140,140,140,140,140,120,100},
	{120,120,140,150,150,150,140,120,120},
	{120,120,140,150,150,150,140,120,120},
	{0,0,0,0,0,0,0,0,0},
};

int CEveluation::GetRelatePiece(BYTE position[10][9], int j, int i)
{
	nPosCount = 0;
	BYTE nChessID;
	BYTE flag;
	int x, y;

	nChessID = position[i][j];

	switch (nChessID)
	{
	case R_KING://��˧
	case B_KING://�ڽ�
				//ѭ�����Ź�֮����Щλ�ÿɵ���/����
				//ɨ�����߾͹���������������
		for (y = 0; y<3; y++)
			for (x = 3; x<6; x++)
				if (CanTouch(position, j, i, x, y))//�ܷ񵽴�
					AddPoint(x, y);//�ɴﵽ/������λ�ü�������

								   //ѭ�����Ź�֮����Щλ�ÿɵ���/����
								   //ɨ�����߾͹���������������
		for (y = 7; y<10; y++)
			for (x = 3; x<6; x++)
				if (CanTouch(position, j, i, x, y))//�ܷ񵽴�
					AddPoint(x, y);//�ɴﵽ/������λ�ü�������

		break;

	case R_BISHOP://��ʿ
				  //ѭ�����Ź�֮����Щλ�ÿɵ���/����
		for (y = 7; y<10; y++)
			for (x = 3; x<6; x++)
				if (CanTouch(position, j, i, x, y))
					AddPoint(x, y);//�ɴﵽ/������λ�ü�������

		break;

	case B_BISHOP://��ʿ
				  //ѭ�����Ź�֮����Щλ�ÿɵ���/����
		for (y = 0; y<3; y++)
			for (x = 3; x<6; x++)
				if (CanTouch(position, j, i, x, y))
					AddPoint(x, y);//�ɴﵽ/������λ�ü�������

		break;

	case R_ELEPHANT://����
	case B_ELEPHANT://����
					//����
		x = j + 2;
		y = i + 2;
		if (x<9 && y<10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//����
		x = j + 2;
		y = i - 2;
		if (x<9 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//����
		x = j - 2;
		y = i + 2;
		if (x >= 0 && y<10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//����
		x = j - 2;
		y = i - 2;
		if (x >= 0 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		break;

	case R_HORSE://����
	case B_HORSE://����
				 //������·��ܷ񵽴�/����
		x = j + 2;
		y = i + 1;
		if ((x<9 && y<10) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������Ϸ��ܷ񵽴�/����
		x = j + 2;
		y = i - 1;
		if ((x<9 && y >= 0) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������·��ܷ񵽴�/����
		x = j - 2;
		y = i + 1;
		if ((x >= 0 && y<10) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������Ϸ��ܷ񵽴�/����
		x = j - 2;
		y = i - 1;
		if ((x >= 0 && y >= 0) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������·��ܷ񵽴�/����
		x = j + 1;
		y = i + 2;
		if ((x<9 && y<10) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������Ϸ��ܷ񵽴�/����
		x = j + 1;
		y = i - 2;
		if ((x<9 && y >= 0) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������·��ܷ񵽴�/����
		x = j - 1;
		y = i + 2;
		if ((x >= 0 && y<10) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		//������Ϸ��ܷ񵽴�/����
		x = j - 1;
		y = i - 2;
		if ((x >= 0 && y >= 0) && CanTouch(position, j, i, x, y))
			AddPoint(x, y);

		break;

	case R_CAR://�쳵
	case B_CAR://�ڳ�
			   //��������ܷ񵽴�/����
		x = j + 1;
		y = i;
		while (x<9)
		{
			if (NOCHESS == position[y][x])//�հ�
				AddPoint(x, y);
			else {
				//������һ������
				AddPoint(x, y);
				break;//�����λ�ò�������
			}
			x++;
		}

		//��������ܷ񵽴�/����
		x = j - 1;
		y = i;
		while (x >= 0)
		{
			if (NOCHESS == position[y][x])//�հ�
				AddPoint(x, y);
			else {
				//������һ������
				AddPoint(x, y);
				break;//�����λ�ò�������
			}
			x--;
		}

		//��������ܷ񵽴�/����
		x = j;
		y = i + 1;
		while (y<10)
		{
			if (NOCHESS == position[y][x])//�հ�
				AddPoint(x, y);
			else {
				//������һ������
				AddPoint(x, y);
				break;//�����λ�ò�������
			}
			y++;
		}

		//��������ܷ񵽴�/����
		x = j;
		y = i - 1;
		while (y >= 0)
		{
			if (NOCHESS == position[y][x])//�հ�
				AddPoint(x, y);
			else {
				//������һ������
				AddPoint(x, y);
				break;//�����λ�ò�������
			}
			y--;
		}

		break;

	case R_PAWN://���
				//�ۿ���ǰ�Ƿ񵽵�
		y = i - 1;
		x = j;
		if (y >= 0)
			AddPoint(x, y);//û���ף�����
		if (i<5)
		{
			//���ѹ���
			y = i;
			x = j + 1;//����
			if (x<9)
				AddPoint(x, y);//δ���ұߣ�����
			x = j - 1;//����
			if (x >= 0)
				AddPoint(x, y);//δ����ߣ�����
		}

		break;

	case B_PAWN://����
				//�ۿ���ǰ�Ƿ񵽵�
		y = i + 1;
		x = j;
		if (y<10)
			AddPoint(x, y);//û���ף�����
		if (i>4)
		{
			//���ѹ���
			y = i;
			x = j + 1;//����
			if (x<9)
				AddPoint(x, y);//δ���ұߣ�����
			x = j - 1;//����
			if (x >= 0)
				AddPoint(x, y);//δ����ߣ�����
		}

		break;

	case B_CANON://����
	case R_CANON://����
				 //��������ܷ񵽴�/������λ��
		x = j + 1;
		y = i;
		flag = FALSE;
		while (x<9)
		{
			if (NOCHESS == position[y][x])
			{
				//�հ�λ��
				if (!flag)
					AddPoint(x, y);
			}
			else
			{
				if (!flag)
					flag = TRUE;//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x, y);
					break;
				}
			}
			x++;//��������
		}

		//��������ܷ񵽴�/������λ��
		x = j - 1;
		y = i;
		flag = FALSE;
		while (x >= 0)
		{
			if (NOCHESS == position[y][x])
			{
				//�հ�λ��
				if (!flag)
					AddPoint(x, y);
			}
			else
			{
				if (!flag)
					flag = TRUE;//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x, y);
					break;
				}
			}
			x--;//��������
		}

		//��������ܷ񵽴�/������λ��
		x = j;
		y = i + 1;
		flag = FALSE;
		while (y<10)
		{
			if (NOCHESS == position[y][x])
			{
				//�հ�λ��
				if (!flag)
					AddPoint(x, y);
			}
			else
			{
				if (!flag)
					flag = TRUE;//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x, y);
					break;
				}
			}
			y++;//��������
		}

		//��������ܷ񵽴�/������λ��
		x = j;
		y = i - 1;
		flag = FALSE;
		while (y >= 0)
		{
			if (NOCHESS == position[y][x])
			{
				//�հ�λ��
				if (!flag)
					AddPoint(x, y);
			}
			else
			{
				if (!flag)
					flag = TRUE;//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x, y);
					break;
				}
			}
			y--;//��������
		}

		break;

	default:
		break;
	}

	return nPosCount;
}

int CEveluation::GetBingValue(int x,int y,BYTE CurSituation[][9])
{
	if(CurSituation[y][x]==R_PAWN)
		return BA0[y][x];

	if(CurSituation[y][x]==B_PAWN)
		return BA1[y][x];

	return 0;
}

CEveluation::CEveluation()
{
	//��ʼ��ÿ�����ӵĻ�����ֵ����
	m_BaseValue[B_KING]=BASEVALUE_KING;
	m_BaseValue[B_CAR]=BASEVALUE_CAR;
	m_BaseValue[B_HORSE]=BASEVALUE_HORSE;
	m_BaseValue[B_BISHOP]=BASEVALUE_BISHOP;
	m_BaseValue[B_ELEPHANT]=BASEVALUE_ELEPHANT;
	m_BaseValue[B_CANON]=BASEVALUE_CANON;
	m_BaseValue[B_PAWN]=BASEVALUE_PAWN;

	m_BaseValue[R_KING]=BASEVALUE_KING;
	m_BaseValue[R_CAR]=BASEVALUE_CAR;
	m_BaseValue[R_HORSE]=BASEVALUE_HORSE;
	m_BaseValue[R_BISHOP]=BASEVALUE_BISHOP;
	m_BaseValue[R_ELEPHANT]=BASEVALUE_ELEPHANT;
	m_BaseValue[R_CANON]=BASEVALUE_CANON;
	m_BaseValue[R_PAWN]=BASEVALUE_PAWN;

	//��ʼ������Է�ֵ����
	m_FlexValue[B_KING]=FLEXIBILITY_KING;
	m_FlexValue[B_CAR]=FLEXIBILITY_CAR;
	m_FlexValue[B_HORSE]=FLEXIBILITY_HORSE;
	m_FlexValue[B_BISHOP]=FLEXIBILITY_BISHOP;
	m_FlexValue[B_ELEPHANT]=FLEXIBILITY_ELEPHANT;
	m_FlexValue[B_CANON]=FLEXIBILITY_CANON;
	m_FlexValue[B_PAWN]=FLEXIBILITY_PAWN;

	m_FlexValue[R_KING]=FLEXIBILITY_KING;
	m_FlexValue[R_CAR]=FLEXIBILITY_CAR;
	m_FlexValue[R_HORSE]=FLEXIBILITY_HORSE;
	m_FlexValue[R_BISHOP]=FLEXIBILITY_BISHOP;
	m_FlexValue[R_ELEPHANT]=FLEXIBILITY_ELEPHANT;
	m_FlexValue[R_CANON]=FLEXIBILITY_CANON;
	m_FlexValue[R_PAWN]=FLEXIBILITY_PAWN;

	m_nAccessCount=0;
}

CEveluation::~CEveluation()
{

}

int CEveluation::Eveluate(BYTE position[10][9], BOOL bIsRedTurn, int nUserChessColor)
{
	int i, j, k;
	int nChessType, nTargetType;

	m_nAccessCount++;//ÿ����һ�ξ�����һ��

					 //��ʼ��
	memset(m_chessValue, 0, 360);
	memset(m_AttackPos, 0, 180);
	memset(m_GuardPos, 0, 90);
	memset(m_FlexibilityPos, 0, 90);

	//ɨ�����̣��ҳ�ÿһ�����ӣ�������в/���������ӣ������������
	for (i = 0; i<10; i++)
		for (j = 0; j<9; j++)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];   //ȡ��������
				GetRelatePiece(position, j, i);//�ҳ��������������λ��
				for (k = 0; k<nPosCount; k++)     //��ÿһĿ��λ��
				{
					nTargetType = position[RelatePos[k].y][RelatePos[k].x];//ȡĿ����������
					if (nTargetType == NOCHESS)//����ǿհף����������
						m_FlexibilityPos[i][j]++;
					else//������
					{
						if (IsSameSide(nChessType, nTargetType))
						{
							//�������ӣ�Ŀ���ܱ���
							m_GuardPos[RelatePos[k].y][RelatePos[k].x]++;
						}
						else
						{
							//�з����ӣ�Ŀ������в
							m_AttackPos[RelatePos[k].y][RelatePos[k].x]++;
							m_FlexibilityPos[i][j]++;//���������
							switch (nTargetType)
							{
							case R_KING://��˧
								if (!bIsRedTurn)//�ֵ�������
									return 18888;//����ʧ�ܼ�ֵ
								break;

							case B_KING://�ڽ�
								if (bIsRedTurn)//�ֵ�������
									return 18888;//����ʧ�ܼ�ֵ
								break;

							default:
								//������в�����Ӽ�����в��ֵ
								m_AttackPos[RelatePos[k].y][RelatePos[k].x] += (30 + (m_BaseValue[nTargetType] - m_BaseValue[nChessType]) / 10) / 10;
								break;
							}
						}
					}
				}
			}
		}

	//�����ѭ��ͳ��ɨ�赽������
	for (i = 0; i<10; i++)
		for (j = 0; j<9; j++)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				m_chessValue[i][j]++;
				//������Ӵ������ֵ��Ϊ0����ÿһ���ӵ�����Լ�ֵ�ӽ����Ӽ�ֵ
				m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];
				//���ϱ��ĸ���ֵ
				m_chessValue[i][j] += GetBingValue(j, i, position);
			}
		}

	//�����ѭ������ͳ��ɨ�赽������
	int nHalfvalue;
	for (i = 0; i<10; i++)
		for (j = 0; j<9; j++)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				nHalfvalue = m_BaseValue[nChessType] / 16;      //���ӻ�����ֵ��1/16��Ϊ��в/��������			
				m_chessValue[i][j] += m_BaseValue[nChessType];//ÿ�����ӵĻ�����ֵ�������ܼ�ֵ
				if (IsRed(nChessType))//����
				{
					if (m_AttackPos[i][j])//��ǰ�����������в
					{
						if (bIsRedTurn)//�ֵ�������
						{
							if (nChessType == R_KING)//����Ǻ콫
								m_chessValue[i][j] -= 20;//��ֵ����20
							else
							{
								//��ֵ��ȥ2��nHalfvalue
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])//�Ƿ񱻼������ӱ���
									m_chessValue[i][j] += nHalfvalue;//�������ټ���nHalfvalue
							}
						}
						else//��ǰ���屻��в���ֵ�������
						{
							if (nChessType == R_KING)//�Ƿ��Ǻ�˧
								return 18888;//����ʧ�ܼ�ֵ	
							m_chessValue[i][j] -= nHalfvalue * 10;//��ȥ10����nHalfvalue,��ʾ��в�̶ȸ�
							if (m_GuardPos[i][j])//���������
								m_chessValue[i][j] += nHalfvalue * 9;//�������ټ���9����nHalfvalue
						}
						//����в�����Ӽ�����в���ֹһ������в
						//һ���������ĳ�������ֵ����û�з�ӳ��������
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{
						//û����в
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;//�ܱ�������һ���
					}
				}
				else
				{
					//����Ǻ���
					if (m_AttackPos[i][j])
					{
						//����в
						if (!bIsRedTurn)
						{
							//�ֵ�������
							if (nChessType == B_KING)//����Ǻڽ�
								m_chessValue[i][j] -= 20;//���Ӽ�ֵ����20
							else
							{
								//���Ӽ�ֵ����2��nHalfvalue
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])//����ܱ���									
									m_chessValue[i][j] += nHalfvalue;//���Ӽ�ֵ����nHalfvalue
							}
						}
						else
						{
							//�ֵ�������
							if (nChessType == B_KING)//�Ǻڽ�
								return 18888;//����ʧ�ܼ�ֵ							
							m_chessValue[i][j] -= nHalfvalue * 10;//���Ӽ�ֵ����10��nHalfvalue
							if (m_GuardPos[i][j])//�ܱ���
								m_chessValue[i][j] += nHalfvalue * 9;//�������ټ���9��nHalfvalue
						}
						//����в�������ټ�����в��
						//��ֹһ������вһ���������ĳ�,����ֵ����û�з�ӳ���������
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{
						//������в
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;//�ܱ�������һ���
					}
				}
			}
		}

	//����ͳ����ÿ�����ӵ��ܼ�ֵ
	//����ͳ�ƺ�������ܷ�
	int nRedValue = 0; int nBlackValue = 0;
	for (i = 0; i<10; i++)
		for (j = 0; j<9; j++)
		{
			nChessType = position[i][j];
			if (nChessType != NOCHESS)
			{
				if (IsRed(nChessType))
					nRedValue += m_chessValue[i][j];  //�Ѻ����ֵ����
				else
					nBlackValue += m_chessValue[i][j];//�Ѻ����ֵ����
			}
		}

	if (nUserChessColor == REDCHESS)
	{
		if (bIsRedTurn)
			return nRedValue - nBlackValue;//����ֵ������߷��ع�ֵ

		return nBlackValue - nRedValue;//����ֵ������߷��ظ���ֵ
	}

	if (bIsRedTurn)
		return nBlackValue - nRedValue;//����ֵ������߷��ظ���ֵ			

	return nRedValue - nBlackValue;//����ֵ������߷��ع�ֵ
}

//int CEveluation::Eveluate(BYTE position[][9], BOOL bIsRedTurn,int nUserChessColor)
//{
//	int i,j,k;
//	int nChessType,nTargetType;
//	
//	m_nAccessCount++;//ÿ����һ�ξ�����һ��
//
//	//��ʼ��
//	memset(m_chessValue,0,360);
//	memset(m_AttackPos,0,180);
//	memset(m_GuardPos,0,90);
//	memset(m_FlexibilityPos,0,90);
//
//	//ɨ�����̣��ҳ�ÿһ�����ӣ�������в/���������ӣ������������
//	for(i=0;i<10;i++)
//		for(j=0;j<9;j++)
//		{
//			if(position[i][j]!=NOCHESS)
//			{
//				nChessType=position[i][j];   //ȡ��������
//				GetRelatePiece(position,j,i);//�ҳ��������������λ��
//				for(k=0;k<nPosCount;k++)     //��ÿһĿ��λ��
//				{				
//					nTargetType=position[RelatePos[k].y][RelatePos[k].x];//ȡĿ����������
//					if(nTargetType==NOCHESS)//����ǿհף����������
//						m_FlexibilityPos[i][j]++;
//					else//������
//					{
//						if(IsSameSide(nChessType,nTargetType))
//						{
//							//�������ӣ�Ŀ���ܱ���
//							m_GuardPos[RelatePos[k].y][RelatePos[k].x]++;
//						}
//						else
//						{
//							//�з����ӣ�Ŀ������в
//							m_AttackPos[RelatePos[k].y][RelatePos[k].x]++;
//							m_FlexibilityPos[i][j]++;//���������
//							switch(nTargetType)
//							{
//								case R_KING://��˧
//									if(!bIsRedTurn)//�ֵ�������
//										return 18888;//����ʧ�ܼ�ֵ
//									break;
//								
//								case B_KING://�ڽ�
//									if(bIsRedTurn)//�ֵ�������
//										return 18888;//����ʧ�ܼ�ֵ
//									break;
//									
//								default:
//									//������в�����Ӽ�����в��ֵ
//									m_AttackPos[RelatePos[k].y][RelatePos[k].x]+=(30 +(m_BaseValue[nTargetType]- m_BaseValue[nChessType])/10)/10;
//									break;
//							}
//						}
//					}
//				}
//			}
//		}
//
//	//�����ѭ��ͳ��ɨ�赽������
//	for(i=0;i<10;i++)
//		for(j=0;j<9;j++)
//		{
//			if(position[i][j]!=NOCHESS)
//			{
//				nChessType=position[i][j];
//				m_chessValue[i][j]++;
//				//������Ӵ������ֵ��Ϊ0����ÿһ���ӵ�����Լ�ֵ�ӽ����Ӽ�ֵ
//				m_chessValue[i][j]+=m_FlexValue[nChessType]*m_FlexibilityPos[i][j];
//				//���ϱ��ĸ���ֵ
//				m_chessValue[i][j]+=GetBingValue(j,i,position);
//			}
//		}
//
//	//�����ѭ������ͳ��ɨ�赽������
//	int nHalfvalue;
//	for(i=0;i<10;i++)
//		for(j=0;j<9;j++)
//		{
//			if(position[i][j]!=NOCHESS)
//			{
//				nChessType=position[i][j];			
//				nHalfvalue=m_BaseValue[nChessType]/16;      //���ӻ�����ֵ��1/16��Ϊ��в/��������			
//				m_chessValue[i][j]+=m_BaseValue[nChessType];//ÿ�����ӵĻ�����ֵ�������ܼ�ֵ
//				if(IsRed(nChessType))//����
//				{
//					if(m_AttackPos[i][j])//��ǰ�����������в
//					{
//						if(bIsRedTurn)//�ֵ�������
//						{						
//							if(nChessType==R_KING)//����Ǻ콫
//								m_chessValue[i][j]-=20;//��ֵ����20
//							else
//							{
//								//��ֵ��ȥ2��nHalfvalue
//								m_chessValue[i][j]-=nHalfvalue*2;
//								if(m_GuardPos[i][j])//�Ƿ񱻼������ӱ���
//									m_chessValue[i][j]+=nHalfvalue;//�������ټ���nHalfvalue
//							}
//						}
//						else//��ǰ���屻��в���ֵ�������
//						{
//							if(nChessType==R_KING)//�Ƿ��Ǻ�˧
//								return 18888;//����ʧ�ܼ�ֵ	
//							m_chessValue[i][j]-=nHalfvalue*10;//��ȥ10����nHalfvalue,��ʾ��в�̶ȸ�
//							if(m_GuardPos[i][j])//���������
//								m_chessValue[i][j]+=nHalfvalue*9;//�������ټ���9����nHalfvalue
//						}
//						//����в�����Ӽ�����в���ֹһ������в
//						//һ���������ĳ�������ֵ����û�з�ӳ��������
//						m_chessValue[i][j]-=m_AttackPos[i][j];
//					}
//					else
//					{
//						//û����в
//						if(m_GuardPos[i][j])
//							m_chessValue[i][j]+=5;//�ܱ�������һ���
//					}
//				}
//				else
//				{
//					//����Ǻ���
//					if(m_AttackPos[i][j])
//					{
//						//����в
//						if(!bIsRedTurn)
//						{
//							//�ֵ�������
//							if(nChessType==B_KING)//����Ǻڽ�
//								m_chessValue[i][j]-=20;//���Ӽ�ֵ����20
//							else
//							{ 
//								//���Ӽ�ֵ����2��nHalfvalue
//								m_chessValue[i][j]-=nHalfvalue*2;
//								if(m_GuardPos[i][j])//����ܱ���									
//									m_chessValue[i][j] +=nHalfvalue;//���Ӽ�ֵ����nHalfvalue
//							}
//						}
//						else
//						{
//							//�ֵ�������
//							if(nChessType==B_KING)//�Ǻڽ�
//								return 18888;//����ʧ�ܼ�ֵ							
//							m_chessValue[i][j]-=nHalfvalue*10;//���Ӽ�ֵ����10��nHalfvalue
//							if(m_GuardPos[i][j])//�ܱ���
//								m_chessValue[i][j]+=nHalfvalue*9;//�������ټ���9��nHalfvalue
//						}
//						//����в�������ټ�����в��
//						//��ֹһ������вһ���������ĳ�,����ֵ����û�з�ӳ���������
//						m_chessValue[i][j]-=m_AttackPos[i][j];
//					}
//					else
//					{
//						//������в
//						if(m_GuardPos[i][j])
//							m_chessValue[i][j]+=5;//�ܱ�������һ���
//					}
//				}
//			}
//		}
//		
//	//����ͳ����ÿ�����ӵ��ܼ�ֵ
//	//����ͳ�ƺ�������ܷ�
//	int nRedValue=0;int nBlackValue=0;
//	for(i=0;i<10;i++)
//		for(j=0;j<9;j++)
//		{
//			nChessType=position[i][j];
//			if(nChessType!=NOCHESS)
//			{
//				if(IsRed(nChessType))
//					nRedValue+=m_chessValue[i][j];  //�Ѻ����ֵ����
//				else
//					nBlackValue+=m_chessValue[i][j];//�Ѻ����ֵ����
//			}
//		}
//
//	if(nUserChessColor==REDCHESS)
//	{
//		if(bIsRedTurn)
//			return nRedValue-nBlackValue;//����ֵ������߷��ع�ֵ
//
//		return nBlackValue-nRedValue;//����ֵ������߷��ظ���ֵ
//	}
//
//	if(bIsRedTurn)
//		return nBlackValue-nRedValue;//����ֵ������߷��ظ���ֵ			
//	
//	return nRedValue-nBlackValue;//����ֵ������߷��ع�ֵ
//}

//int CEveluation::GetRelatePiece(BYTE position[][9], int j, int i)
//{
//	nPosCount=0;
//	BYTE nChessID;
//	BYTE flag;
//	int x,y;
//	
//	nChessID=position[i][j];
//
//	switch(nChessID)
//	{
//	case R_KING://��˧
//	case B_KING://�ڽ�
//		//ѭ�����Ź�֮����Щλ�ÿɵ���/����
//		//ɨ�����߾͹���������������
//		for(y=0;y<3;y++)
//			for(x=3;x<6;x++)
//				if(CanTouch(position,j,i,x,y))//�ܷ񵽴�
//					AddPoint(x,y);//�ɴﵽ/������λ�ü�������
//
//		//ѭ�����Ź�֮����Щλ�ÿɵ���/����
//		//ɨ�����߾͹���������������
//		for(y=7;y<10;y++)
//			for(x=3;x<6;x++)
//				if(CanTouch(position,j,i,x,y))//�ܷ񵽴�
//					AddPoint(x,y);//�ɴﵽ/������λ�ü�������
//
//		break;
//
//	case R_BISHOP://��ʿ
//		//ѭ�����Ź�֮����Щλ�ÿɵ���/����
//		for(y=7;y<10;y++)
//			for(x=3;x<6;x++)
//				if(CanTouch(position,j,i,x,y))
//					AddPoint(x,y);//�ɴﵽ/������λ�ü�������
//		
//		break;
//
//	case B_BISHOP://��ʿ
//		//ѭ�����Ź�֮����Щλ�ÿɵ���/����
//		for(y=0;y<3;y++)
//			for(x=3;x<6;x++)
//				if(CanTouch(position,j,i,x,y))
//					AddPoint(x,y);//�ɴﵽ/������λ�ü�������
//		
//		break;
//
//	case R_ELEPHANT://����
//	case B_ELEPHANT://����
//		//����
//		x=j+2;
//		y=i+2;
//		if(x<9 && y<10 && CanTouch(position,j,i,x,y))
//			AddPoint(x,y);
//
//		//����
//		x=j+2;
//		y=i-2;
//		if(x<9 && y>=0 && CanTouch(position,j,i,x,y))
//			AddPoint(x,y);
//
//		//����
//		x=j-2;
//		y=i+2;
//		if(x>=0 && y<10 && CanTouch(position,j,i,x,y))
//			AddPoint(x,y);
//
//		//����
//		x=j-2;
//		y=i-2;
//		if(x>=0 && y>=0 && CanTouch(position,j,i,x,y))
//			AddPoint(x,y);
//
//		break;
//
//		case R_HORSE://����
//		case B_HORSE://����
//			//������·��ܷ񵽴�/����
//			x=j+2;
//			y=i+1;
//			if((x<9 && y<10)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������Ϸ��ܷ񵽴�/����
//			x=j+2;
//			y=i-1;
//			if((x<9 && y>=0)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������·��ܷ񵽴�/����
//			x=j-2;
//			y=i+1;
//			if((x>=0 && y<10)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������Ϸ��ܷ񵽴�/����
//			x=j-2;
//			y=i-1;
//			if((x>=0 && y>=0)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������·��ܷ񵽴�/����
//			x=j+1;
//			y=i+2;
//			if((x<9 && y<10)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������Ϸ��ܷ񵽴�/����
//			x=j+1;
//			y=i-2;
//			if((x<9 && y>=0)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������·��ܷ񵽴�/����
//			x=j-1;
//			y=i+2;
//			if((x>=0 && y<10)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			//������Ϸ��ܷ񵽴�/����
//			x=j-1;
//			y=i-2;
//			if((x>=0 && y>=0)&&CanTouch(position,j,i,x,y))
//				AddPoint(x,y);
//
//			break;
//
//		case R_CAR://�쳵
//		case B_CAR://�ڳ�
//			//��������ܷ񵽴�/����
//			x=j+1;
//			y=i;
//			while(x<9)
//			{
//				if(NOCHESS==position[y][x])//�հ�
//					AddPoint(x,y);
//				else{
//					//������һ������
//					AddPoint(x,y);
//					break;//�����λ�ò�������
//				}
//				x++;
//			}
//
//			//��������ܷ񵽴�/����
//			x=j-1;
//			y=i;
//			while(x>=0)
//			{
//				if(NOCHESS==position[y][x])//�հ�
//					AddPoint(x,y);
//				else{
//					//������һ������
//					AddPoint(x,y);
//					break;//�����λ�ò�������
//				}
//				x--;
//			}
//
//			//��������ܷ񵽴�/����
//			x=j;
//			y=i+1;
//			while(y<10)
//			{
//				if(NOCHESS==position[y][x])//�հ�
//					AddPoint(x,y);
//				else{
//					//������һ������
//					AddPoint(x,y);
//					break;//�����λ�ò�������
//				}
//				y++;
//			}
//
//			//��������ܷ񵽴�/����
//			x=j;
//			y=i-1;
//			while(y>=0)
//			{
//				if(NOCHESS==position[y][x])//�հ�
//					AddPoint(x,y);
//				else{
//					//������һ������
//					AddPoint(x,y);
//					break;//�����λ�ò�������
//				}
//				y--;
//			}
//
//			break;
//
//		case R_PAWN://���
//			//�ۿ���ǰ�Ƿ񵽵�
//			y=i-1;
//			x=j;
//			if(y>=0)
//				AddPoint(x,y);//û���ף�����
//			if(i<5)
//			{
//				//���ѹ���
//				y=i;
//				x=j+1;//����
//				if(x<9)
//					AddPoint(x,y);//δ���ұߣ�����
//				x=j-1;//����
//				if(x>=0)
//					AddPoint(x,y);//δ����ߣ�����
//			}
//
//			break;
//
//		case B_PAWN://����
//			//�ۿ���ǰ�Ƿ񵽵�
//			y=i+1;
//			x=j;
//			if(y<10)
//				AddPoint(x,y);//û���ף�����
//			if(i>4)
//			{
//				//���ѹ���
//				y=i;
//				x=j+1;//����
//				if(x<9)
//					AddPoint(x,y);//δ���ұߣ�����
//				x=j-1;//����
//				if(x>=0)
//					AddPoint(x,y);//δ����ߣ�����
//			}
//
//			break;
//
//		case B_CANON://����
//		case R_CANON://����
//			//��������ܷ񵽴�/������λ��
//			x=j+1;
//			y=i;
//			flag=FALSE;
//			while(x<9)
//			{
//				if(NOCHESS==position[y][x])
//				{
//					//�հ�λ��
//					if(!flag)
//						AddPoint(x,y);
//				}
//				else
//				{
//					if(!flag)
//						flag=TRUE;//�ǵ�һ������
//					else
//					{
//						//�ǵڶ�������
//						AddPoint(x,y);
//						break;
//					}
//				}
//				x++;//��������
//			}
//
//			//��������ܷ񵽴�/������λ��
//			x=j-1;
//			y=i;
//			flag=FALSE;
//			while(x>=0)
//			{
//				if(NOCHESS==position[y][x])
//				{
//					//�հ�λ��
//					if(!flag)
//						AddPoint(x,y);
//				}
//				else
//				{
//					if(!flag)
//						flag=TRUE;//�ǵ�һ������
//					else
//					{
//						//�ǵڶ�������
//						AddPoint(x,y);
//						break;
//					}
//				}
//				x--;//��������
//			}
//
//			//��������ܷ񵽴�/������λ��
//			x=j;
//			y=i+1;
//			flag=FALSE;
//			while(y<10)
//			{
//				if(NOCHESS==position[y][x])
//				{
//					//�հ�λ��
//					if(!flag)
//						AddPoint(x,y);
//				}
//				else
//				{
//					if(!flag)
//						flag=TRUE;//�ǵ�һ������
//					else
//					{
//						//�ǵڶ�������
//						AddPoint(x,y);
//						break;
//					}
//				}
//				y++;//��������
//			}
//
//			//��������ܷ񵽴�/������λ��
//			x=j;
//			y=i-1;
//			flag=FALSE;
//			while(y>=0)
//			{
//				if(NOCHESS==position[y][x])
//				{
//					//�հ�λ��
//					if(!flag)
//						AddPoint(x,y);
//				}
//				else
//				{
//					if(!flag)
//						flag=TRUE;//�ǵ�һ������
//					else
//					{
//						//�ǵڶ�������
//						AddPoint(x,y);
//						break;
//					}
//				}
//				y--;//��������
//			}
//
//			break;
//
//		default:
//			break;
//		}
//
//	return nPosCount;
//}

bool CEveluation::CanTouch(BYTE position[][9], int nFromX, int nFromY, int nToX, int nToY)
{
	int i,j;
	int nMoveChessID,nTargetID;

	if(nFromX==nToX && nFromY==nToY)
		return false;//Ŀ����Դ��ͬ���Ƿ�

	nMoveChessID=position[nFromX][nFromY];
	nTargetID=position[nToX][nToY];

	if(IsSameSide(nMoveChessID,nTargetID))
		return false;//���Լ����壬�Ƿ�

	switch(nMoveChessID)
	{
	case B_KING://�ڽ�
		if(nTargetID==R_KING)//�ж��Ƿ�˧����
		{
			if(nFromX!=nToX)//�����겻���
				return false;//��˧����ͬһ��

			for(i=nFromY+1;i<nToY;i++)
				if(position[i][nFromX]!=NOCHESS)
					return false;//�м��������
		}
		else
		{
			if(nToY>2 || nToX>5 || nToX<3)
				return false;//Ŀ����ھŹ�֮��

			if(abs(nFromY-nToY)+abs(nFromX-nToX)>1)
				return false;//��˧ֻ��һ��ֱ��
		}

		break;

	case R_KING://��˧
		if(nTargetID==B_KING)//�ж��Ƿ�˧����
		{
			if(nFromX!=nToX)//�����겻���
				return false;//��˧����ͬһ��

			for(i=nFromY-1;i>nToY;i--)
				if(position[i][nFromX]!=NOCHESS)
					return false;//�м��������
		}
		else
		{
			if(nToY<7 || nToX>5 || nToX<3)
				return false;//Ŀ����ھŹ�֮��

			if(abs(nFromY-nToY)+abs(nFromX-nToX)>1)
				return false;//��˧ֻ��һ��ֱ��
		}

		break;

	case R_BISHOP://��ʿ
		if(nToY<7 || nToX>5 || nToX<3)
			return false;//ʿ���Ź�

		if(abs(nFromX-nToX)!=1 || abs(nFromY-nToY)!=1)
			return false;//ʿ��б��

		break;

	case B_BISHOP://��ʿ
		if(nToY>2 || nToX>5 || nToX<3)
			return false;//ʿ���Ź�

		if(abs(nFromX-nToX)!=1 || abs(nFromY-nToY)!=1)
			return false;//ʿ��б��

		break;

	case R_ELEPHANT://����
		if(nToY<5)
			return false;//�಻�ܹ���

		if(abs(nFromX-nToX)!=2 || abs(nFromY-nToY)!=2)
			return false;//��������

		if(position[(nFromY +nToY)/2][(nFromX +nToX)/2]!=NOCHESS)
			return FALSE;//���۱���

		break;

	case B_ELEPHANT://����
		if(nToY>4)
			return false;//���ܹ���

		if(abs(nFromX-nToX)!=2 || abs(nFromY-nToY)!=2)
			return false;//��������

		if(position[(nFromY +nToY)/2][(nFromX +nToX)/2]!=NOCHESS)
			return FALSE;//���۱���

		break;

	case B_PAWN://����
		if(nToY<nFromY)
			return false;//�䲻�ܻ�ͷ

		if(nFromY<5 && nFromY==nToY)
			return FALSE;//�����ǰֻ��ֱ��

		if(nToY-nFromY+abs(nToX -nFromX)>1)
			return FALSE;//��ֻ��һ��ֱ��

		break;

	case R_PAWN://���
		if(nToY<nFromY)
			return false;//�����ܻ�ͷ

		if(nFromY>4 && nFromY==nToY)
			return FALSE;//������ǰֻ��ֱ��

		if(nToY-nFromY+abs(nToX -nFromX)>1)
			return FALSE;//��ֻ��һ��ֱ��

		break;

	case B_CAR://�ڳ�
	case R_CAR://�쳵
		if(nFromY!=nToY && nFromX!=nToX)
			return FALSE;//����ֱ��

		if(nFromY==nToY)
		{
			if(nFromX<nToX)
			{
				for(i=nFromX+1;i<nToX;i++)
					if(position[nFromY][i]!=NOCHESS)
						return FALSE;
			}
			else
			{
				for(i=nToX+1;i<nFromX;i++)
					if(position[nFromY][i]!=NOCHESS)
						return FALSE;
			}
		}
		else
		{
			if(nFromY<nToY)
			{
				for(j=nFromY+1;j<nToY;j++)
					if(position[j][nFromX]!=NOCHESS)
						return FALSE;
			}
			else
			{
				for(j=nToY+1;j<nFromY;j++)
					if(position[j][nFromX]!=NOCHESS)
						return FALSE;
			}
		}
		
		break;

	case B_HORSE://����
	case R_HORSE://����
		if(!((abs(nToX-nFromX)==1 && abs(nToY -nFromY)==2) || (abs(nToX-nFromX)==2&&abs(nToY -nFromY)==1)))
			return FALSE;//��������

		if(nToX-nFromX==2)
		{
			i=nFromX+1;
			j=nFromY;
		}
		else
			if(nFromX-nToX==2)
			{
				i=nFromX-1;
				j=nFromY;
			}
			else
				if(nToY-nFromY==2)
				{
					i=nFromX;
					j=nFromY+1;
				}
				else
					if(nFromY-nToY==2)
					{
						i=nFromX;
						j=nFromY-1;
					}

		if(position[j][i]!=NOCHESS)
			return FALSE;//������
		
		break;

	case B_CANON://����
	case R_CANON://����
		if(nFromY!=nToY && nFromX!=nToX)
			return FALSE;//����ֱ��

		//�ڳ���ʱ������·���в���������
		if(position[nToY][nToX]==NOCHESS)
		{
			if(nFromY==nToY)
			{
				if(nFromX<nToX)
				{
					for(i=nFromX+1;i<nToX;i++)
						if(position[nFromY][i]!=NOCHESS)
							return FALSE;
				}
				else
				{
					for(i=nToX+1;i<nFromX;i++)
						if(position[nFromY][i]!=NOCHESS)
							return FALSE;
				}
			}
			else
			{
				if(nFromY<nToY)
				{
					for(j=nFromY+1;j<nToY;j++)
						if(position[j][nFromX]!=NOCHESS)
							return FALSE;
				}
				else
				{
					for(j=nToY+1;j<nFromY;j++)
						if(position[j][nFromX]!=NOCHESS)
							return FALSE;
				}
			}
		}		
		else//�ڳ���ʱ
		{
			int j=0;
			if(nFromY==nToY)
			{
				if(nFromX<nToX)
				{
					for(i=nFromX+1;i<nToX;i++)
						if(position[nFromY][i]!=NOCHESS)
							j++;
						if(j!=1)
							return FALSE;
				}
				else
				{
					for(i=nToX+1;i<nFromX;i++)
						if(position[nFromY][i]!=NOCHESS)
							j++;
						if(j!=1)
							return FALSE;
				}
			}
			else
			{
				if(nFromY<nToY)
				{
					for(j=nFromY+1;j<nToY;j++)
						if(position[j][nFromX]!=NOCHESS)
							j++;
					if(j!=1)
						return FALSE;
				}
				else
				{
					for(j=nToY+1;j<nFromY;j++)
						if(position[j][nFromX]!=NOCHESS)
							j++;
					if(j!=1)
						return FALSE;
				}
			}
		}
		
		break;

	default:
		return false;
	}
		
	return true;
}

void CEveluation::AddPoint(int x, int y)
{
	RelatePos[nPosCount].x=x;
	RelatePos[nPosCount].y=y;

	nPosCount++;
}

//bool CEveluation::CanTouch(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY)
//{
//	int i, j;
//	int nMoveChessID, nTargetID;
//
//	if (nFromX == nToX && nFromY == nToY)
//		return false;//Ŀ����Դ��ͬ���Ƿ�
//
//	nMoveChessID = position[nFromX][nFromY];
//	nTargetID = position[nToX][nToY];
//
//	if (IsSameSide(nMoveChessID, nTargetID))
//		return false;//���Լ����壬�Ƿ�
//
//	switch (nMoveChessID)
//	{
//	case B_KING://�ڽ�
//		if (nTargetID == R_KING)//�ж��Ƿ�˧����
//		{
//			if (nFromX != nToX)//�����겻���
//				return false;//��˧����ͬһ��
//
//			for (i = nFromY + 1; i<nToY; i++)
//				if (position[i][nFromX] != NOCHESS)
//					return false;//�м��������
//		}
//		else
//		{
//			if (nToY>2 || nToX>5 || nToX<3)
//				return false;//Ŀ����ھŹ�֮��
//
//			if (abs(nFromY - nToY) + abs(nFromX - nToX)>1)
//				return false;//��˧ֻ��һ��ֱ��
//		}
//
//		break;
//
//	case R_KING://��˧
//		if (nTargetID == B_KING)//�ж��Ƿ�˧����
//		{
//			if (nFromX != nToX)//�����겻���
//				return false;//��˧����ͬһ��
//
//			for (i = nFromY - 1; i>nToY; i--)
//				if (position[i][nFromX] != NOCHESS)
//					return false;//�м��������
//		}
//		else
//		{
//			if (nToY<7 || nToX>5 || nToX<3)
//				return false;//Ŀ����ھŹ�֮��
//
//			if (abs(nFromY - nToY) + abs(nFromX - nToX)>1)
//				return false;//��˧ֻ��һ��ֱ��
//		}
//
//		break;
//
//	case R_BISHOP://��ʿ
//		if (nToY<7 || nToX>5 || nToX<3)
//			return false;//ʿ���Ź�
//
//		if (abs(nFromX - nToX) != 1 || abs(nFromY - nToY) != 1)
//			return false;//ʿ��б��
//
//		break;
//
//	case B_BISHOP://��ʿ
//		if (nToY>2 || nToX>5 || nToX<3)
//			return false;//ʿ���Ź�
//
//		if (abs(nFromX - nToX) != 1 || abs(nFromY - nToY) != 1)
//			return false;//ʿ��б��
//
//		break;
//
//	case R_ELEPHANT://����
//		if (nToY<5)
//			return false;//�಻�ܹ���
//
//		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
//			return false;//��������
//
//		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
//			return FALSE;//���۱���
//
//		break;
//
//	case B_ELEPHANT://����
//		if (nToY>4)
//			return false;//���ܹ���
//
//		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
//			return false;//��������
//
//		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
//			return FALSE;//���۱���
//
//		break;
//
//	case B_PAWN://����
//		if (nToY<nFromY)
//			return false;//�䲻�ܻ�ͷ
//
//		if (nFromY<5 && nFromY == nToY)
//			return FALSE;//�����ǰֻ��ֱ��
//
//		if (nToY - nFromY + abs(nToX - nFromX)>1)
//			return FALSE;//��ֻ��һ��ֱ��
//
//		break;
//
//	case R_PAWN://���
//		if (nToY<nFromY)
//			return false;//�����ܻ�ͷ
//
//		if (nFromY>4 && nFromY == nToY)
//			return FALSE;//������ǰֻ��ֱ��
//
//		if (nToY - nFromY + abs(nToX - nFromX)>1)
//			return FALSE;//��ֻ��һ��ֱ��
//
//		break;
//
//	case B_CAR://�ڳ�
//	case R_CAR://�쳵
//		if (nFromY != nToY && nFromX != nToX)
//			return FALSE;//����ֱ��
//
//		if (nFromY == nToY)
//		{
//			if (nFromX<nToX)
//			{
//				for (i = nFromX + 1; i<nToX; i++)
//					if (position[nFromY][i] != NOCHESS)
//						return FALSE;
//			}
//			else
//			{
//				for (i = nToX + 1; i<nFromX; i++)
//					if (position[nFromY][i] != NOCHESS)
//						return FALSE;
//			}
//		}
//		else
//		{
//			if (nFromY<nToY)
//			{
//				for (j = nFromY + 1; j<nToY; j++)
//					if (position[j][nFromX] != NOCHESS)
//						return FALSE;
//			}
//			else
//			{
//				for (j = nToY + 1; j<nFromY; j++)
//					if (position[j][nFromX] != NOCHESS)
//						return FALSE;
//			}
//		}
//
//		break;
//
//	case B_HORSE://����
//	case R_HORSE://����
//		if (!((abs(nToX - nFromX) == 1 && abs(nToY - nFromY) == 2) || (abs(nToX - nFromX) == 2 && abs(nToY - nFromY) == 1)))
//			return FALSE;//��������
//
//		if (nToX - nFromX == 2)
//		{
//			i = nFromX + 1;
//			j = nFromY;
//		}
//		else
//			if (nFromX - nToX == 2)
//			{
//				i = nFromX - 1;
//				j = nFromY;
//			}
//			else
//				if (nToY - nFromY == 2)
//				{
//					i = nFromX;
//					j = nFromY + 1;
//				}
//				else
//					if (nFromY - nToY == 2)
//					{
//						i = nFromX;
//						j = nFromY - 1;
//					}
//
//		if (position[j][i] != NOCHESS)
//			return FALSE;//������
//
//		break;
//
//	case B_CANON://����
//	case R_CANON://����
//		if (nFromY != nToY && nFromX != nToX)
//			return FALSE;//����ֱ��
//
//						 //�ڳ���ʱ������·���в���������
//		if (position[nToY][nToX] == NOCHESS)
//		{
//			if (nFromY == nToY)
//			{
//				if (nFromX<nToX)
//				{
//					for (i = nFromX + 1; i<nToX; i++)
//						if (position[nFromY][i] != NOCHESS)
//							return FALSE;
//				}
//				else
//				{
//					for (i = nToX + 1; i<nFromX; i++)
//						if (position[nFromY][i] != NOCHESS)
//							return FALSE;
//				}
//			}
//			else
//			{
//				if (nFromY<nToY)
//				{
//					for (j = nFromY + 1; j<nToY; j++)
//						if (position[j][nFromX] != NOCHESS)
//							return FALSE;
//				}
//				else
//				{
//					for (j = nToY + 1; j<nFromY; j++)
//						if (position[j][nFromX] != NOCHESS)
//							return FALSE;
//				}
//			}
//		}
//		else//�ڳ���ʱ
//		{
//			int j = 0;
//			if (nFromY == nToY)
//			{
//				if (nFromX<nToX)
//				{
//					for (i = nFromX + 1; i<nToX; i++)
//						if (position[nFromY][i] != NOCHESS)
//							j++;
//					if (j != 1)
//						return FALSE;
//				}
//				else
//				{
//					for (i = nToX + 1; i<nFromX; i++)
//						if (position[nFromY][i] != NOCHESS)
//							j++;
//					if (j != 1)
//						return FALSE;
//				}
//			}
//			else
//			{
//				if (nFromY<nToY)
//				{
//					for (j = nFromY + 1; j<nToY; j++)
//						if (position[j][nFromX] != NOCHESS)
//							j++;
//					if (j != 1)
//						return FALSE;
//				}
//				else
//				{
//					for (j = nToY + 1; j<nFromY; j++)
//						if (position[j][nFromX] != NOCHESS)
//							j++;
//					if (j != 1)
//						return FALSE;
//				}
//			}
//		}
//
//		break;
//
//	default:
//		return false;
//	}
//
//	return true;
//}

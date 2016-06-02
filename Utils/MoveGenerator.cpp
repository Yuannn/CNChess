

#include "stdafx.h"
#include "chess.h"
#include "MoveGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static BYTE THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveGenerator::CMoveGenerator()
{
	
}

CMoveGenerator::~CMoveGenerator()
{
	
}

int CMoveGenerator::AddMove(int nFromX,int nFromY,int nToX,int nToY,int nPly,int nChessID)
{
	m_MoveList[nPly][m_nMoveCount].From.x=nFromX;
	m_MoveList[nPly][m_nMoveCount].From.y=nFromY;
	m_MoveList[nPly][m_nMoveCount].To.x=nToX;
	m_MoveList[nPly][m_nMoveCount].To.y=nToY;
	m_MoveList[nPly][m_nMoveCount].nChessID=nChessID;
	m_nMoveCount++;

	return m_nMoveCount;
}

//nPlyָ����ǰ�����Ĳ�����ÿ�㽫�߷����ڲ�ͬ��λ�ã����⸲��
//nSideָ��������һ�����߷���TRUEΪ�췽��FALSE�Ǻڷ�
int CMoveGenerator::CreatePossibleMove(BYTE position[][9],int nPly,int nSide,int nUserChessColor)
{
	int nChessID;
	int i,j;

	m_nMoveCount=0;
	m_nUserChessColor=nUserChessColor;

	for(j=0;j<9;j++)
		for(i=0;i<10;i++)
		{
			if(position[i][j]!=NOCHESS)
			{
				nChessID=position[i][j];

				if(nUserChessColor==REDCHESS)
				{
					if(!nSide && IsRed(nChessID))
						continue;//��Ҫ���������߷�����������
					
					if(nSide && IsBlack(nChessID))
						continue;//��Ҫ���������߷�����������
				}
				else
				{
					if(nSide && IsRed(nChessID))
						continue;//��Ҫ���������߷�����������
					
					if(!nSide && IsBlack(nChessID))
						continue;//��Ҫ���������߷�����������
				}

				switch(nChessID)
				{
				case R_KING://��˧
				case B_KING://�ڽ�
					Gen_KingMove(position,i,j,nPly);
					break;

				case R_BISHOP://��ʿ
					Gen_RBishopMove(position,i,j,nPly);
					break;
				
				case B_BISHOP://��ʿ
					Gen_BBishopMove(position,i,j,nPly);
					break;
				
				case R_ELEPHANT://����
				case B_ELEPHANT://����
					Gen_ElephantMove(position,i,j,nPly);
					break;
				
				case R_HORSE://����
				case B_HORSE://����
					Gen_HorseMove(position,i,j,nPly);
					break;
				
				case R_CAR://�쳵
				case B_CAR://�ڳ�
					Gen_CarMove(position,i,j,nPly);
					break;

				case R_PAWN://���
					Gen_RPawnMove(position,i,j,nPly);
					break;
				
				case B_PAWN://����
					Gen_BPawnMove(position,i,j,nPly);
					break;
				
				case B_CANON://����
				case R_CANON://����
					Gen_CanonMove(position,i,j,nPly);
					break;
				
				default:
					break;
				}
			}
		}

	return m_nMoveCount;
}

void CMoveGenerator::Gen_KingMove(BYTE position[10][9],int i,int j,int nPly)
{
	int x,y;
	
	for(y=0;y<3;y++)
		for(x=3;x<6;x++)
			if(IsValidMove(position,j,i,x,y,m_nUserChessColor))
				AddMove(j,i,x,y,nPly,position[i][j]);

	for(y=7;y<10;y++)
		for(x=3;x<6;x++)
			if(IsValidMove(position,j,i,x,y,m_nUserChessColor))
				AddMove(j,i,x,y,nPly,position[i][j]);
}

//��ʿ
void CMoveGenerator::Gen_RBishopMove(BYTE position[10][9],int i,int j,int nPly)
{
	int x,y;
	
	for(y=7;y<10;y++)
		for(x=3;x<6;x++)
			if(IsValidMove(position,j,i,x,y,m_nUserChessColor))
				AddMove(j,i,x,y,nPly,position[i][j]);
}

//��ʿ
void CMoveGenerator::Gen_BBishopMove(BYTE position[10][9],int i,int j,int nPly)
{
	int x,y;

	for(y=0;y<3;y++)
		for(x=3;x<6;x++)
			if(IsValidMove(position,j,i,x,y,m_nUserChessColor))
				AddMove(j,i,x,y,nPly,position[i][j]);
}

//��
void CMoveGenerator::Gen_ElephantMove(BYTE position[10][9],int i,int j,int nPly)
{
	int x,y;
	
	//�������·�����Ч�߷�
	x=j+2;
	y=i+2;
	if(x<9 && y<10 && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������Ϸ�����Ч�߷�
	x=j+2;
	y=i-2;
	if(x<9 && y>=0 && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������·�����Ч�߷�
	x=j-2;
	y=i+2;
	if(x>=0 && y<10 && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������Ϸ�����Ч�߷�
	x=j-2;
	y=i-2;
	if(x>=0 && y>=0 && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
}

//��
void CMoveGenerator::Gen_HorseMove(BYTE position[10][9], int i, int j, int nPly)
{
	int x, y;
	
	//�������·�����Ч�߷�
	x=j+2;//��2
	y=i+1;//��1
	if((x<9 && y<10) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������Ϸ�����Ч�߷�
	x=j+2;//��2
	y=i-1;//��1
	if((x<9 && y>=0) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������·�����Ч�߷�
	x=j-2;//��2
	y=i+1;//��1
	if((x>=0 && y<10) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);

	//�������Ϸ�����Ч�߷�
	x=j-2;//��2
	y=i-1;//��1
	if((x>=0 && y>=0) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
	
	//�������·�����Ч�߷�
	x=j+1;//��1
	y=i+2;//��2 
	if((x<9 && y<10) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);

	//�������·�����Ч�߷�
	x=j-1;//��1
	y=i+2;//��2
	if((x>=0 && y<10) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);    
	
	//�������Ϸ�����Ч�߷�
	x=j+1;//��1
	y=i-2;//��2
	if((x<9 && y >=0) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);

	//�������Ϸ�����Ч�߷�
	x=j-1;//��1
	y=i-2;//��2
	if((x>=0 && y>=0) && IsValidMove(position,j,i,x,y,m_nUserChessColor))
		AddMove(j,i,x,y,nPly,position[i][j]);
}

//���
void CMoveGenerator::Gen_RPawnMove(BYTE position[10][9], int i, int j, int nPly)
{
	int x,y;
	int nChessID;
	
	nChessID=position[i][j];

	if(m_nUserChessColor==REDCHESS)
	{
		y=i-1;//��ǰ
		x=j;
		if(y>0 && !IsSameSide(nChessID,position[y][x]))
			AddMove(j,i,x,y,nPly,position[i][j]);//ǰ�����谭
		
		if(i<5)//�Ƿ��ѹ���
		{
			y=i;
			
			x=j+1;//�ұ�
			if(x<9 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
			
			x=j-1;//���
			if(x>=0 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
	}
	else
	{
		y=i+1;//��ǰ
		x=j;
		if(y>0 && !IsSameSide(nChessID,position[y][x]))
			AddMove(j,i,x,y,nPly,position[i][j]);//ǰ�����谭
		
		if(i>4)//�Ƿ��ѹ���
		{
			y=i;
			
			x=j+1;//�ұ�
			if(x<9 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
			
			x=j-1;//���
			if(x>=0 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
	}
}

//����
void CMoveGenerator::Gen_BPawnMove(BYTE position[10][9],int i,int j,int nPly)
{
	int x,y;
	int nChessID;
	
	nChessID=position[i][j];

	if(m_nUserChessColor==REDCHESS)
	{
		y=i+1;//��ǰ
		x=j;
		if(y<10 && !IsSameSide(nChessID,position[y][x]))
			AddMove(j,i,x,y,nPly,position[i][j]);//ǰ�����谭
		
		if(i>4)//�Ƿ��ѹ���
		{
			y=i;
			
			x=j+1;//�ұ�
			if(x<9 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
			
			x=j-1;//���
			if(x>=0 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
	}
	else
	{
		y=i-1;//��ǰ
		x=j;
		if(y<10 && !IsSameSide(nChessID,position[y][x]))
			AddMove(j,i,x,y,nPly,position[i][j]);//ǰ�����谭
		
		if(i<5)//�Ƿ��ѹ���
		{
			y=i;
			
			x=j+1;//�ұ�
			if(x<9 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
			
			x=j-1;//���
			if(x>=0 && !IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
	}
}

//��
void CMoveGenerator::Gen_CarMove(BYTE position[10][9], int i, int j, int nPly)
{
	int x,y;
	int nChessID;
	
	nChessID=position[i][j];

	//�������ҵ���Ч���߷�
	x=j+1;
	y=i;
	while(x<9)
	{
		if(NOCHESS==position[y][x])
			AddMove(j,i,x,y,nPly,position[i][j]);
		else
		{
			if(!IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);

			break;
		}
		x++;
	}

	//�����������Ч���߷�
	x=j-1;
	y=i;
	while(x>=0)
	{
		if(NOCHESS==position[y][x])
			AddMove(j,i,x,y,nPly,position[i][j]);
		else
		{
			if(!IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);

			break;
		}
		x--;
	}

	//�������µ���Ч���߷�
	x=j;
	y=i+1;
	while(y<10)
	{
		if(NOCHESS==position[y][x])
			AddMove(j,i,x,y,nPly,position[i][j]);
		else
		{
			if(!IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);

			break;
		}
		y++;
	}

	//�������ϵ���Ч���߷�
	x=j;
	y=i-1;
	while(y>=0)
	{
		if(NOCHESS==position[y][x])
			AddMove(j,i,x,y,nPly,position[i][j]);
		else
		{
			if(!IsSameSide(nChessID,position[y][x]))
				AddMove(j,i,x,y,nPly,position[i][j]);

			break;
		}
		y--;
	}
}

//��
void CMoveGenerator::Gen_CanonMove(BYTE position[10][9], int i, int j, int nPly)
{
	int x,y;
	BOOL flag;
	int nChessID;
	
	nChessID=position[i][j];

	//�������ҵ���Ч���߷�
	x=j+1;
	y=i;
	flag=FALSE;
	while(x<9)
	{
		if(NOCHESS==position[y][x])
		{
			if(!flag)//��������
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
		else
		{
			if(!flag)//û�и����ӣ��������ǵ�һ���ϰ������ñ�־
				flag=TRUE;
			else     //�������ӣ��˴���Ϊ�з����ӣ������
			{
				if(!IsSameSide(nChessID,position[y][x]))
					AddMove(j,i,x,y,nPly,position[i][j]);
				break;
			}
		}
		x++;//������һ��λ��
	}

	//�����������Ч���߷�
	x=j-1;
	y=i;
	flag=FALSE;
	while(x>=0)
	{
		if(NOCHESS==position[y][x])
		{
			if(!flag)//��������
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
		else
		{
			if(!flag)//û�и����ӣ��������ǵ�һ���ϰ������ñ�־
				flag=TRUE;
			else     //�������ӣ��˴���Ϊ�з����ӣ������
			{
				if(!IsSameSide(nChessID,position[y][x]))
					AddMove(j,i,x,y,nPly,position[i][j]);
				break;
			}
		}
		x--;//������һ��λ��
	}

	//�������µ���Ч���߷�
	x=j;
	y=i+1;
	flag=FALSE;
	while(y<10)
	{
		if(NOCHESS==position[y][x])
		{
			if(!flag)//��������
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
		else
		{
			if(!flag)//û�и����ӣ��������ǵ�һ���ϰ������ñ�־
				flag=TRUE;
			else     //�������ӣ��˴���Ϊ�з����ӣ������
			{
				if(!IsSameSide(nChessID,position[y][x]))
					AddMove(j,i,x,y,nPly,position[i][j]);
				break;
			}
		}
		y++;//������һ��λ��
	}

	//�������ϵ���Ч���߷�
	x=j;
	y=i-1;
	flag=FALSE;
	while(y>=0)
	{
		if(NOCHESS==position[y][x])
		{
			if(!flag)//��������
				AddMove(j,i,x,y,nPly,position[i][j]);
		}
		else
		{
			if(!flag)//û�и����ӣ��������ǵ�һ���ϰ������ñ�־
				flag=TRUE;
			else     //�������ӣ��˴���Ϊ�з����ӣ������
			{
				if(!IsSameSide(nChessID,position[y][x]))
					AddMove(j,i,x,y,nPly,position[i][j]);
				break;
			}
		}
		y--;//������һ��λ��
	}
}

BOOL CMoveGenerator::IsValidMove(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY,int nUserChessColor)
{
	int i,j;
	int nMoveChessID,nTargetID;

	if(nFromX==nToX && nFromY==nToY)
		return false;//Ŀ����Դ��ͬ���Ƿ�

	nMoveChessID=position[nFromY][nFromX];
	nTargetID=position[nToY][nToX];

	if(IsSameSide(nMoveChessID,nTargetID))
		return false;//���Լ����壬�Ƿ�

	switch(nMoveChessID)
	{
	case B_KING://�ڽ�
		if(nUserChessColor==REDCHESS)
		{
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
		}
		else
		{
			if(nTargetID==R_KING)//�ж��Ƿ�˧����
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
		}

		break;

	case R_KING://��˧
		if(nUserChessColor==REDCHESS)
		{
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
		}
		else
		{
			if(nTargetID==B_KING)//�ж��Ƿ�˧����
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
		}

		break;

	case R_BISHOP://��ʿ
		if(nUserChessColor==REDCHESS)
		{
			if(nToY<7 || nToX>5 || nToX<3)
				return false;//ʿ���Ź�
		}
		else
		{
			if(nToY>2 || nToX>5 || nToX<3)
				return false;//ʿ���Ź�
		}

		if(abs(nFromX-nToX)!=1 || abs(nFromY-nToY)!=1)
				return false;//ʿ��б��

		break;

	case B_BISHOP://��ʿ
		if(nUserChessColor==REDCHESS)
		{
			if(nToY>2 || nToX>5 || nToX<3)
				return false;//ʿ���Ź�
		}
		else
		{
			if(nToY<7 || nToX>5 || nToX<3)
			return false;//ʿ���Ź�
		}

		if(abs(nFromX-nToX)!=1 || abs(nFromY-nToY)!=1)
			return false;//ʿ��б��

		break;

	case R_ELEPHANT://����
		if(nUserChessColor==REDCHESS)
		{
			if(nToY<5)
				return false;//�಻�ܹ���
		}
		else
		{
			if(nToY>4)
				return false;//�಻�ܹ���
		}

		if(abs(nFromX-nToX)!=2 || abs(nFromY-nToY)!=2)
			return false;//��������

		if(position[(nFromY +nToY)/2][(nFromX +nToX)/2]!=NOCHESS)
			return FALSE;//���۱���

		break;

	case B_ELEPHANT://����
		if(nUserChessColor==REDCHESS)
		{
			if(nToY>4)
				return false;//���ܹ���
		}
		else
		{
			if(nToY<5)
				return false;//���ܹ���
		}

		if(abs(nFromX-nToX)!=2 || abs(nFromY-nToY)!=2)
			return false;//��������

		if(position[(nFromY +nToY)/2][(nFromX +nToX)/2]!=NOCHESS)
			return FALSE;//���۱���

		break;

	case B_PAWN://����
		if(nUserChessColor==REDCHESS)
		{
			if(nToY<nFromY)
				return false;//�䲻�ܻ�ͷ
			
			if(nFromY<5 && nFromY==nToY)
				return FALSE;//�����ǰֻ��ֱ��
		}
		else
		{
			if(nToY>nFromY)
				return false;//�䲻�ܻ�ͷ
			
			if(nFromY>4 && nFromY==nToY)
				return FALSE;//�����ǰֻ��ֱ��
		}

		if(nToY-nFromY+abs(nToX-nFromX)>1)
			return FALSE;//��ֻ��һ��ֱ��

		break;

	case R_PAWN://���
		if(nUserChessColor==REDCHESS)
		{
			if(nToY>nFromY)
				return false;//�����ܻ�ͷ
			
			if(nFromY>4 && nFromY==nToY)
				return FALSE;//������ǰֻ��ֱ��
		}
		else
		{
			if(nToY<nFromY)
				return false;//�����ܻ�ͷ
			
			if(nFromY<5 && nFromY==nToY)
				return FALSE;//������ǰֻ��ֱ��
		}

		if(nFromY-nToY+abs(nToX-nFromX)>1)
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
					for(i=nFromY+1;i<nToY;i++)
						if(position[i][nFromX]!=NOCHESS)
							j++;
					if(j!=1)
						return FALSE;
				}
				else
				{
					for(i=nToY+1;i<nFromY;i++)
						if(position[i][nFromX]!=NOCHESS)
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

//int CMoveGenerator::CreatePossibleMove(BYTE position[10][9], int nPly, int nSide, int nUserChessColor)
//{
//	int nChessID;
//	int i, j;
//
//	m_nMoveCount = 0;
//	m_nUserChessColor = nUserChessColor;
//
//	for (j = 0; j<9; j++)
//		for (i = 0; i<10; i++)
//		{
//			if (position[i][j] != NOCHESS)
//			{
//				nChessID = position[i][j];
//
//				if (nUserChessColor == REDCHESS)
//				{
//					if (!nSide && IsRed(nChessID))
//						continue;//��Ҫ���������߷�����������
//
//					if (nSide && IsBlack(nChessID))
//						continue;//��Ҫ���������߷�����������
//				}
//				else
//				{
//					if (nSide && IsRed(nChessID))
//						continue;//��Ҫ���������߷�����������
//
//					if (!nSide && IsBlack(nChessID))
//						continue;//��Ҫ���������߷�����������
//				}
//
//				switch (nChessID)
//				{
//				case R_KING://��˧
//				case B_KING://�ڽ�
//					Gen_KingMove(position, i, j, nPly);
//					break;
//
//				case R_BISHOP://��ʿ
//					Gen_RBishopMove(position, i, j, nPly);
//					break;
//
//				case B_BISHOP://��ʿ
//					Gen_BBishopMove(position, i, j, nPly);
//					break;
//
//				case R_ELEPHANT://����
//				case B_ELEPHANT://����
//					Gen_ElephantMove(position, i, j, nPly);
//					break;
//
//				case R_HORSE://����
//				case B_HORSE://����
//					Gen_HorseMove(position, i, j, nPly);
//					break;
//
//				case R_CAR://�쳵
//				case B_CAR://�ڳ�
//					Gen_CarMove(position, i, j, nPly);
//					break;
//
//				case R_PAWN://���
//					Gen_RPawnMove(position, i, j, nPly);
//					break;
//
//				case B_PAWN://����
//					Gen_BPawnMove(position, i, j, nPly);
//					break;
//
//				case B_CANON://����
//				case R_CANON://����
//					Gen_CanonMove(position, i, j, nPly);
//					break;
//
//				default:
//					break;
//				}
//			}
//		}
//
//	return m_nMoveCount;
//}

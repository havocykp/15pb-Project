#pragma once
#include "Data.h"
#include "Maps.h"
class CAstar
{
public:
	CAstar();
	~CAstar();
public:
	// ��Ѱ·��
	bool searchPath(CMaps& maps, POS startPoint, POS endPoint);
	// ��ȡ�ƶ�����
	int  getMoveDir(POS startPos);
private:
	// ��ʼ��·��
	void initData(CMaps& maps, POS startPoint);
	// ������Ҫ���ĵ�
	void addToOpenTable(STARNODE * pNode);
	// ����ʧЧ�ĵ�
	void updateInvalidPoint(CMaps& maps, POS startPoint);
	// ���
	void Clear();
private:
	vector<STARNODE*> m_vecOpen;
	vector<STARNODE*> m_vecClose;
	bool m_bOpenMap[MAPHEIGHT][MAPWIDTH];
	STARNODE*  m_pCloseMap[MAPHEIGHT][MAPWIDTH];;
	bool m_bValidMap[MAPHEIGHT][MAPWIDTH];
};


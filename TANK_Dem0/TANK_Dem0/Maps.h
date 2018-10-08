#pragma once
#include <sstream>
#include "Data.h"

class CMaps
{
public:
	// ��ʼ����ǽ
	void initOuterWall();
	// �ϳ�
	void initHeart();
	// ��ʼ����ͼ�е��ϰ���
	void initStaticMapData();
	// �Զ����ͼ
	void customMapData();
	// ��ʾ�Զ����ͼ��Ҫ������
	void showNeedStaticObj();
	// ��ӡ��ͼ��̬����
	void drawMap();
	// �ָ������ֲ��
	void recoverDamagedPlant();
	// ��ȡ��ͼ�ļ�
	void readStaticMapFile(int fileNum);
	// ����̬����㣺 ����m_nMap
	void reDrawMapPoint(int row, int col);
	// ָ��λ�ô�ӡ
	void static printChar(int posX, int posY, const char* pszCha, WORD wArr);
public:
	CMaps();
	~CMaps();
public:
	int m_nMap[MAPHEIGHT][MAPWIDTH];
	TANK * m_pTankMap[MAPHEIGHT][MAPWIDTH];
	BULLET *  m_pBulletMap[MAPHEIGHT][MAPWIDTH];
	vector<POS> m_vecDamagedPlant;
	bool m_isHeartBroken;
};


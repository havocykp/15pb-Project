#include "Bullet.h"

// ���캯��
CBullet::CBullet(CMaps* pMaps)
{
	m_pMaps = pMaps;
}

// ��������
CBullet::~CBullet()
{
}

// �ӵ�---�ϰ���
void CBullet::drawBullet(bool isShow)
{
	int posX;
	int posY;
	int color;

	for (size_t i = 0; i < m_vecBullet.size(); i++)
	{
		if (!m_vecBullet[i]->isValid) {
			continue;
		}
		posX = m_vecBullet[i]->posX;
		posY = m_vecBullet[i]->posY;
		color = m_vecBullet[i]->color;
		if (m_pMaps->m_nMap[posY][posX] == MAP_TREE) {
			// ����Ҫ�����ӵ��� ����ʾҲ������
		}
		else if (isShow) {
			if ((m_pMaps->m_nMap[posY][posX] == MAP_GRASS) || (m_pMaps->m_nMap[posY][posX] == MAP_ICE) || (m_pMaps->m_nMap[posY][posX] == MAP_RIVER)) {
				// ��ʾ�ӵ�������������ӵ�λ�ã�ֲ�ﱻ�ƻ��� ����Ҫ�ָ����ƻ���ֲ�
				m_pMaps->m_vecDamagedPlant.push_back({ posX, posY }); // ͬ������ֲ��
			}
			m_pMaps->printChar(posX, posY, "��", color);
		}
		else {
			if ((m_pMaps->m_nMap[posY][posX] == MAP_GRASS) || (m_pMaps->m_nMap[posY][posX] == MAP_ICE) || (m_pMaps->m_nMap[posY][posX] == MAP_RIVER)) {//����λ����ֲ��
				m_pMaps->m_vecDamagedPlant.push_back({ posX, posY });  // ͬ������ֲ��
			}
			m_pMaps->printChar(posX, posY, "  ", color);
		}


	}
}

// �ӵ�----̹��
void CBullet::removeInvalidBullet()
{
	int posX;
	int posY;

	for (size_t i = 0; i < m_vecBullet.size(); i++)
	{
		// ����ӵ���Ч�������
		if (!m_vecBullet[i]->isValid) {
			continue;
		}
		posX = m_vecBullet[i]->posX;
		posY = m_vecBullet[i]->posY;

		// ̹�˵�ͼ���
		if (m_pMaps->m_pTankMap[posY][posX] != NULL) { // ������̹��
			BULLET* pBullet = m_vecBullet[i];
			TANK* pTank = m_pMaps->m_pTankMap[posY][posX];
			if (pBullet->isNPC != pTank->isNPC) { // ��Ӫ��ͬ�� ��Ѫ
				pTank->curHP -= pBullet->power;
				if (pTank->isNPC && pTank->curHP > 10) {
					CBgm::play(BGM_BULLET_HIT_NPC);//bgm
				}
				else {
					CBgm::play(BGM_BULLET_HIT_ME);//bgm
					pTank->curSpeed -= 2;
				}

			}
			// �ӵ�ʧЧ
			m_vecBullet[i]->isValid = false;
			m_pMaps->m_pBulletMap[posY][posX] = NULL;
			continue;
		}
		// �ϰ�����
		else if (m_pMaps->m_nMap[posY][posX] == MAP_HEART) { // ������ϳ��� �ӵ�ʧЧ
			m_vecBullet[i]->isValid = false;
			//m_pMaps->m_pBulletMap[posY][posX] = NULL;
			m_pMaps->m_isHeartBroken = true;
			continue;
		}
		else if (m_pMaps->m_nMap[posY][posX] == MAP_STONE) { // stone: �ӵ�ʧЧ
			m_vecBullet[i]->isValid = false;
			m_pMaps->m_pBulletMap[posY][posX] = NULL;
			continue;
		}
		else if (m_pMaps->m_nMap[posY][posX] == MAP_SPACE) { // �����򣺲����� 
															
		}
		else if (m_pMaps->m_nMap[posY][posX] == MAP_BRICK) {// ש�飺 ����ʧ
			m_pMaps->m_nMap[posY][posX] = MAP_SPACE;
			m_pMaps->reDrawMapPoint(posY, posX);
			m_vecBullet[i]->isValid = false;
			m_pMaps->m_pBulletMap[posY][posX] = NULL;
			continue;
		}
		else if (m_pMaps->m_nMap[posY][posX] == MAP_TREE) {// ����
														  
		}
		else if (m_pMaps->m_nMap[posY][posX] == MAP_ICE || m_pMaps->m_nMap[posY][posX] == MAP_GRASS || m_pMaps->m_nMap[posY][posX] == MAP_RIVER) { //�ݵغͱ���
																																				   
		}
		else if (posX < 0 || posX >= MAPWIDTH || posY < 0 || posY >= MAPHEIGHT) {
			//printf("�ӵ������쳣����%d, %d��\n", posX, posY);

		}
		else {
			//printf(" ��δ����ĵ�ͼ��̬���� removeInvalidBullet()\n");
			int map = m_pMaps->m_nMap[posY][posX];
			//printf(" x = %d y = %d  %d\n", posX, posY, map);
		}
	}
	// ɾ����Ч�ӵ�
	for (vector<BULLET*>::iterator itr = m_vecBullet.begin(); itr != m_vecBullet.end(); ++itr) {
		if (!(*itr)->isValid) {
			m_vecBullet.erase(itr);
			break;
		}
	}

	// �����ӵ���ͼ
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			m_pMaps->m_pBulletMap[i][j] = NULL;
		}
	}
	for (size_t i = 0; i < m_vecBullet.size(); i++)
	{
		if (!m_vecBullet[i]->isValid) {
			continue;
		}
		posX = m_vecBullet[i]->posX;
		posY = m_vecBullet[i]->posY;
		m_pMaps->m_pBulletMap[posY][posX] = m_vecBullet[i];
	}
}

// ����ӵ��Ƿ���Է�
bool CBullet::runBullet()
{
	// ���������ӵ�
	drawBullet(false);
	for (size_t i = 0; i < m_vecBullet.size(); i++)
	{
		if (!m_vecBullet[i]->isValid) {
			continue;
		}
		// �����ٶ�����
		clock_t start_time = m_vecBullet[i]->last_fly_time;
		clock_t end_time = clock();
		if (end_time - start_time < 50) {
			//continue;
		}
		m_vecBullet[i]->last_fly_time = end_time;

		// �ӵ�����
		int posX = m_vecBullet[i]->posX;
		int posY = m_vecBullet[i]->posY;
		// �޸�����
		switch (m_vecBullet[i]->dir) {
		case DIR_UP:
			posY--;
			break;
		case DIR_DOWN:
			posY++;
			break;
		case DIR_LEFT:
			posX--;
			break;
		case DIR_RIGHT:
			posX++;
			break;
		default:
			//printf("������ӵ��������ԣ�drawbullet\n");
			return false;
			break;
		}
		m_vecBullet[i]->posX = posX;
		m_vecBullet[i]->posY = posY;
		// �ж�ǰ�����Ƿ������ӵ�, ������removeInvalidBullet�м�⣻
		if (m_pMaps->m_pBulletMap[posY][posX]) { // �ӵ� -- �ӵ���� : ��ö�ӵ���ʧЧ
			m_vecBullet[i]->isValid = false;
			m_pMaps->m_pBulletMap[posY][posX]->isValid = false;
		}
	}
	// �Ƴ���Ч�ӵ�
	removeInvalidBullet();
	// ��ʾ
	drawBullet(true);
	return true;
}

// ����ӵ��Ƿ���Է���
void CBullet::canShoot(vector<TANK*>& m_vecTank)
{
	clock_t start_time = m_vecTank[0]->last_shoot_time;
	clock_t end_time = clock();
	if (m_vecTank[0]->isAlive && end_time - start_time > 2000 && m_vecTank[0]->ready == false) {
		//CBgm::play(BGM_READY);//bgm
		m_vecTank[0]->ready = true;
	}
}

// �����ӵ�
void CBullet::shootBullet(vector<TANK *>& m_vecTank, int nTankIndex)
{
	// ��������
	clock_t start_time = m_vecTank[nTankIndex]->last_shoot_time;
	clock_t end_time = clock();
	if (m_vecTank[nTankIndex]->isNPC && end_time - start_time < 4000) {
		return;
	}
	else if (!m_vecTank[nTankIndex]->isNPC && end_time - start_time < 1000) {
		return;
	}
	else if (!m_vecTank[nTankIndex]->isAlive) {
		return;
	}
	// ���̹�˷����ӵ�
	if (!m_vecTank[nTankIndex]->isNPC) {
		CBgm::play(BGM_BOMB);//bgm
	}
	m_vecTank[nTankIndex]->last_shoot_time = end_time;
	m_vecTank[nTankIndex]->ready = false;

	int posX = m_vecTank[nTankIndex]->posX;
	int posY = m_vecTank[nTankIndex]->posY;
	int dir = m_vecTank[nTankIndex]->dir;
	switch (dir) {
	case DIR_UP:
		posY -= 2;
		break;
	case DIR_DOWN:
		posY += 2;
		break;
	case DIR_LEFT:
		posX -= 2;
		break;
	case DIR_RIGHT:
		posX += 2;
		break;
	default:
		//printf("������ӵ���ʼ����shootBullet\n");
		return;
		break;
	}

	// �ӵ����ݳ�ʼ��
	BULLET* pBullet = (BULLET*)malloc(sizeof(BULLET));
	pBullet->posX = posX;
	pBullet->posY = posY;
	pBullet->dir = dir;
	pBullet->isNPC = m_vecTank[nTankIndex]->isNPC;
	pBullet->tankId = nTankIndex;
	pBullet->last_fly_time = 0;
	pBullet->power = 50;
	pBullet->color = m_vecTank[nTankIndex]->color;

	m_vecBullet.push_back(pBullet);
	// �����Ƴ���Ч�ӵ�
	removeInvalidBullet();
	// ��ʾ
	drawBullet(true);
}
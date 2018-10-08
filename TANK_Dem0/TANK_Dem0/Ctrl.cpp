#include "Ctrl.h"

// ���캯��
CCtrl::CCtrl()
{
}

// ��������
CCtrl::~CCtrl()
{
}

// ������Ϸ
void CCtrl::playTank(int gameType)
{
	//CBgm::play(BGM_CLICK);//bgm
	int playerCount = 0;
	if (gameType != 3 && gameType != 2) { // �Ƕ����ͱ༭��ͼ
		playerCount = getPlayerCount(); // ��ʾ���棬��ȡ�������
		if (playerCount == 2) {
			//CBgm::play(BGM_REQUEST_ASSIST);//bgm
		}
	}
	if (gameType != 3 && gameType != 2 && playerCount == 0) { //debug
	 //printf("debug: �����������---\n");
		Sleep(5000);
	}

	int nScore = 0;
	bool autoGoNextLevel = false;
	int nCurrentLevel = 0;
	int nNpcCount = 4;
	while (1) {

		// ��ʼ������Ϸ����
		system("cls");
		CMaps maps;
		CTank tanks(&maps);
		CBullet bullets(&maps);
		if (tanks.m_nScore == 0) {
			tanks.m_nScore = nScore;
		}

		// ����ȫ�����ݣ�push_back�����ݣ�-- need ?
		// clearGlobalData(maps, tanks, bullets);

		if (autoGoNextLevel && nCurrentLevel) { // �Զ�������һ��
			maps.readStaticMapFile(nCurrentLevel); // ��ȡ��ͼ
			maps.drawMap();
			// ��ʼ�����̹��,����ʾ:
			tanks.initPlayerTank(playerCount, nCurrentLevel);
			// ��ʼ��NPC̹�ˣ� ����ʾ
			nNpcCount = nCurrentLevel;
			nNpcCount = nNpcCount > 4 ? 4 : nNpcCount;
			tanks.initNpcTank(nNpcCount, nCurrentLevel);

			//CBgm::play(BGM_START_BATTLE);//bgm

		}
		else if (gameType == 1) { // ͨ����Ϸ
			//CBgm::play(BGM_JOIN);//bgm
			int nChoosedMapFile = chooseLevelPassMenu(maps); // ��ʾ�ؿ��˵���ѡ��
			if (nChoosedMapFile == 0) { // �������˵�
				//CBgm::play(BGM_LEAVE);//bgm
				return;
			}
			else { // ��ȡ��ͼ�ļ�����ȡ��ͼ��Ϣ
				maps.readStaticMapFile(nChoosedMapFile);
				nCurrentLevel = nChoosedMapFile;
			}
			maps.drawMap();
			// ��ʼ�����̹��,����ʾ:
			tanks.initPlayerTank(playerCount);
			// ��ʼ��NPC̹�ˣ� ����ʾ
			tanks.initNpcTank(nNpcCount);

			//CBgm::play(BGM_START_BATTLE);//bgm
		}
		else if (gameType == 2) {// �༭��ͼ
			maps.showNeedStaticObj();
			maps.initOuterWall();
			maps.initHeart();
			maps.drawMap();
			// ��ʼ�����̹��
			tanks.initPlayerTank(2);
			// ��ʼ��NPC̹��
			// tanks.initNpcTank(18);
			// ��ʾ̹��
			tanks.initDrawAllTank(true);

			maps.customMapData();

			return; //change��ֱ�ӷ��ؽ���

		}
		else if (gameType == 3) {//����
			readArchive(maps, tanks, bullets);
			nScore = tanks.m_nScore;
			nCurrentLevel = tanks.m_nLevel;
			maps.drawMap();
			// ���»�һ�����̹�ˣ� ���Զ�����g_pTankMap
			for (size_t i = 0; i < tanks.m_vecTank.size(); i++) {
				if ((!tanks.m_vecTank[i]->isNPC) && tanks.m_vecTank[i]->isAlive) {
					tanks.drawTank(i, true);
				}
				if (!tanks.m_vecTank[i]->isNPC) {
					playerCount++; // �ָ������������һ�ؿ�Ҫ��
				}
			}
		}

		// ̹�˲���
		char chKey;
		int  nDirNum;
		bool hasPause = false;
		while (1) {
			if (_kbhit()) {
				chKey = _getch();
				if (chKey == 27) {// Esc,�浵
					saveArchive(maps, tanks, bullets);
					return;
				}
				else if (chKey == 32) { // �ո���ͣ
					hasPause = !hasPause; 
					continue;
				}
				else if (hasPause) {
					continue;
				}
				else if (chKey == 'f') {// �����ڵ�
					bullets.shootBullet(tanks.m_vecTank, 0); // ���1
				}
				else if (chKey == 'h' && playerCount == 2) {
					bullets.shootBullet(tanks.m_vecTank, 1); // ���2
				}
				else if (chKey == 'w' || chKey == 'a' || chKey == 's' || chKey == 'd') { // �ƶ�����
					nDirNum = dirKey2DirNum(chKey);
					tanks.moveTank(nDirNum, 0);// ̹��1��
				}
				else if (chKey == 'u') {
					tanks.helpPlayer();// ǿ�ƻص�������
				}
				else if (playerCount == 2 && (chKey == 'j' || chKey == 'k' || chKey == 'i' || chKey == 'l')) { //�ƶ�����
					nDirNum = dirKey2DirNum(chKey);
					tanks.moveTank(nDirNum, 1);// ̹��2��
				}
				else {
					//printf("�ǿ��Ƽ��� %c %d %d\n", chKey, chKey, (int)chKey);
				}

			}
			else if (hasPause) {
				continue;
			}
			// ����ڵ��Ƿ���Է���
			bullets.canShoot(tanks.m_vecTank);

			// Npc̹���Զ�����
			tanks.autoRunNpcTank(bullets);
			// �ӵ�����
			bullets.runBullet();
			// �ж��ϳ�
			if (maps.m_isHeartBroken) { // ʧ��: �ϳ����ݻ�
				maps.readStaticMapFile(1001);
				maps.drawMap();
				//CBgm::play(BGM_DROP_FLAG);//bgm
				Sleep(4000);
				return;
			}
			// �ж�̹���������
			int tankResult = tanks.judgeAlive();
			nScore = tanks.m_nScore;
			if (nScore > 0) {
				nScore++;
			}
			// ��ʾս����Ϣ
			showGameInfo(tanks, bullets);

			if (tankResult == -1) { // ʧ��
				maps.readStaticMapFile(1001);
				Sleep(4000);
				//CBgm::play(BGM_FAIL);//bgm
				maps.drawMap();
				Sleep(4000);
				return;
			}
			else if (tankResult == 1) { // ʤ��
				maps.readStaticMapFile(1000);
				maps.drawMap();
				nCurrentLevel = getNextLevel(nCurrentLevel);
				Sleep(2000);
				//CBgm::play(BGM_SUCCESS);//bgm
				autoGoNextLevel = true;
				Sleep(2000);
				system("cls");
				break;

			}
			maps.recoverDamagedPlant();
			// ������ǰ�ؿ�
			tanks.m_nLevel = nCurrentLevel; // �����������ʾ�ʹ浵��
		}
	}
}

// ��һ�ؿ�
int CCtrl::getNextLevel(int nCurrentLevel)
{
	vector<int>  vecPassLevel;// �����еĹؿ�
	for (int i = 1; i < 38; i++) {
		int nFileNum = i;
		stringstream stream;
		stream << nFileNum;
		string  strFile = stream.str();
		strFile.insert(0, "map\\"); // ƴ���ļ�·��
		const char * pFilename = strFile.c_str();
		FILE * pFile;
		errno_t errNum = fopen_s(&pFile, pFilename, "rb");

		if (errNum == 0) {// �ļ�����
			vecPassLevel.push_back(i);
			fclose(pFile);
			if (i > nCurrentLevel) {
				return i;
			}
		}
	}
	// û����һ���ˣ���ͷ��ʼ
	return vecPassLevel[0];

}
// �ؿ�ѡ�����
int CCtrl::chooseLevelPassMenu(CMaps& maps)
{
	vector<int>  vecPassLevel; // �����еĹؿ�
	for (int i = 1; i < 38; i++) {
		int nFileNum = i;
		stringstream stream;
		stream << nFileNum;
		string  strFile = stream.str();
		strFile.insert(0, "map\\"); // ƴ���ļ�·��
		const char * pFilename = strFile.c_str();
		FILE * pFile;
		errno_t errNum = fopen_s(&pFile, pFilename, "rb");

		if (errNum == 0) { // �ļ�����
			vecPassLevel.push_back(i);
			fclose(pFile);
		}
	}
	// ȷ����ʾ����ʼ������row
	int startPosX = int((MAPWIDTH - 8) / 2);
	int startPosY = int((MAPHEIGHT - vecPassLevel.size()) / 2);
	// ��ӡ����
	system("cls");
	for (int i = 0; i < (int)vecPassLevel.size(); i++) {
		int nFileNum = vecPassLevel[i];
		stringstream stream;
		stream << nFileNum;
		string  strFile = stream.str();
		char * pNum = (char *)strFile.c_str();
		CMaps::printChar(startPosX - 6, startPosY + i, "�ؿ� �� ", COLOR_YELLOW);
		CMaps::printChar(startPosX, startPosY + i, pNum, COLOR_YELLOW);
		CMaps::printChar(startPosX + 2, startPosY + i, "  ��", COLOR_YELLOW);
	}
	CMaps::printChar(startPosX - 2, startPosY + vecPassLevel.size(), "�����ء�", COLOR_RED); // ����

	// ��ȡ������
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	int mousePosX = 0;
	int mousePosY = 0;
	while (1)
	{
		ReadConsoleInput(hStdin, &stcRecord, 1, &dwRead);
		if (stcRecord.EventType == MOUSE_EVENT) {
			MOUSE_EVENT_RECORD mer = stcRecord.Event.MouseEvent;
			switch (mer.dwEventFlags)
			{
			case 0:// ������Ԥ����ǰ��ͼ
				if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { // �������
					if (mousePosX > startPosX - 10 && mousePosX < startPosX + 20) // �޶�������ҷ�Χ
						if (mousePosY >= startPosY && mousePosY <= startPosY + (int)vecPassLevel.size() - 1) {    //�޶��������Y����Χ
							int vecIndex = mousePosY - startPosY;
							// ��ȡ��ͼ
							//CBgm::play(BGM_CLICK);//bgm
							maps.readStaticMapFile(vecPassLevel[vecIndex]);
							maps.drawMap();

							for (int i = 0; i < (int)vecPassLevel.size(); i++) {
								int nFileNum = vecPassLevel[i];
								stringstream stream;
								stream << nFileNum;
								string  strFile = stream.str();
								char * pNum = (char *)strFile.c_str();
								CMaps::printChar(startPosX - 6, startPosY + i, "�ؿ� �� ", COLOR_YELLOW);
								CMaps::printChar(startPosX, startPosY + i, pNum, COLOR_YELLOW);
								CMaps::printChar(startPosX + 4, startPosY + i, "  ��", COLOR_YELLOW);
							}
							CMaps::printChar(startPosX - 2, startPosY + vecPassLevel.size(), "�����ء�", COLOR_RED);//����
						}

					// ���صİ�ť
					if (mousePosY == startPosY + (int)vecPassLevel.size()) {
						return 0;
					}

				}
				break;
			case DOUBLE_CLICK: // ˫�������뵱ǰ�ؿ�
				if (mousePosX > startPosX - 10 && mousePosX < startPosX + 20) { // �޶�������ҷ�Χ
					if (mousePosY >= startPosY && mousePosY <= startPosY + (int)vecPassLevel.size() - 1) {    //�޶��������Y����Χ
						int vecIndex = mousePosY - startPosY;
						return vecPassLevel[vecIndex];
					}
					else if (mousePosY == startPosY + (int)vecPassLevel.size()) {
						return 0;
					}
				}
				break;
			case MOUSE_MOVED:
				mousePosX = mer.dwMousePosition.X / 2;
				mousePosY = mer.dwMousePosition.Y;
				break;
			default:
				break;
			}// switch
		}//endif
	}//while
}

// ��ʾ���ѡ��˵�
void CCtrl::showPlayerCountMenu()
{
	CMaps::printChar(30, 14, "�� �� �� ģ ʽ", rand() % 0xF + 0x0);
	CMaps::printChar(30, 18, "�� ˫ �� ģ ʽ", rand() % 0xF + 0x0);
	CMaps::printChar(15, 27, "���������ѡ��[ ]\b\b", rand() % 0xF + 0x0);
}

// ��ȡ���ѡ��
int CCtrl::getPlayerCount()
{
	int playerCount = 0;
	while (playerCount != 1 && playerCount != 2) {
		system("cls");
		showPlayerCountMenu();
		scanf_s("%d", &playerCount);
	}

	return playerCount;

}

// ��ʼ������̨
void CCtrl::initConsoleWindow()
{
	system("mode con cols=145 lines=42");
}

// �л����뷨
void CCtrl::initInputShift()
{
	keybd_event(VK_SHIFT, 0, 0, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

// ���������
int CCtrl::dirKey2DirNum(char keyWord)
{
	switch (keyWord) {
	case 'w':
	case 'i':
		return DIR_UP;
		break;
	case 'a':
	case 'j':
		return DIR_LEFT;
		break;
	case 's':
	case 'k':
		return DIR_DOWN;
		break;
	case 'd':
	case 'l':
		return DIR_RIGHT;
		break;
	default:
		//printf("debug: ���޹��ܵİ����� dirkey2DirNum\n");
		return -1;
		break;
	}
}

// ��ӭ����
void CCtrl::showMenu()
{
	system("title TANK Online");
	CBgm::play(BGM_WELCOME);//bgm

	for (int j = 0; j < 51; ++j)
	{
		Sleep(300);
		CMaps::printChar(j - 1, 2, "                              ", rand() % 0xF + 0x0);
		CMaps::printChar(j, 2, " �񨀡������{�{�{�{�{�{�����>>>>>>>>>>>>>", rand() % 0xF + 0x0);
		CMaps::printChar(j - 1, 3, "                              ", rand() % 0xF + 0x0);
		CMaps::printChar(j, 3, " �{�|�������������|�{�z�y                 ", rand() % 0xF + 0x0);
		CMaps::printChar(j - 1, 4, "                              ", rand() % 0xF + 0x0);
		CMaps::printChar(j, 4, " ����������������������������              ", rand() % 0xF + 0x0);
		CMaps::printChar(j - 1, 5, "                              ", rand() % 0xF + 0x0);
		CMaps::printChar(j, 5, " ���ѡ��ѡ��ѡ��ѡ��ѡ��ѡ���", rand() % 0xF + 0x0);
		//CMaps::printChar(30, 10, "̹ �� �� ս", rand() % 0xF + 0x0);
		
		CMaps::printChar(5, 9, "��������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 10,"��������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 11,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 12,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 13,"����������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 14,"����������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 15,"����������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 16,"����������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 17,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 18,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 19,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 20,"������������������������������������������������������������������������������������������������������������������������", 2);
		CMaps::printChar(5, 21,"������������������������������������������������������������������������������������������������������������������������", 2);

		//��ʼ���˵�
		CMaps::printChar(28, 27, "(ѡ����  �س�ȷ��)", rand() % 0xF + 0x0);
		CMaps::printChar(30, 29, "�� �� �� ģ ʽ", rand() % 0xF + 0x0);
		CMaps::printChar(30, 31, "�� �� �� �� ͼ", rand() % 0xF + 0x0);
		CMaps::printChar(30, 33, "�� �� ȡ �� ��", rand() % 0xF + 0x0);
		CMaps::printChar(30, 35, "�� �� �� �� Ϸ", rand() % 0xF + 0x0);
		CMaps::printChar(20, 37, "���������ѡ��[ ]\b\b", rand() % 0xF + 0x0);
	}

		
}


// �˵�ѡ��

int CCtrl::getMenuChoice()
{
	//CBgm::play(BGM_KAQSA);//bgm
	int menuNum = 0;
	while (menuNum != 1 && menuNum != 2 && menuNum != 3 && menuNum != 4) {
		system("cls");
		showMenu();
		scanf_s("%d", &menuNum);
		int ch;
		while ((ch = getchar()) != EOF && ch != '\n');
	}

	return menuNum;
}

// �浵
void CCtrl::saveArchive(CMaps& maps, CTank& tanks, CBullet& bullets)
{
	for (int i = 0; i < tanks.m_vecTank.size(); i++) {
		tanks.m_vecTank[i]->last_move_time = 0;
		tanks.m_vecTank[i]->last_shoot_time = 0;
	}
	for (int i = 0; i < bullets.m_vecBullet.size(); i++) {
		bullets.m_vecBullet[i]->last_fly_time = 0;

	}

	FILE * pFile;
	fopen_s(&pFile, "savemap.db", "wb");
	// ��ͼg_nMap����
	fwrite(maps.m_nMap, sizeof(int), MAPWIDTH* MAPHEIGHT, pFile);
	// ̹��
	// ̹�˹ؿ�
	int nLevel = tanks.m_nLevel;
	fwrite(&nLevel, sizeof(int), 1, pFile);
	// ̹�˷���
	int nScore = tanks.m_nScore;
	fwrite(&nScore, sizeof(int), 1, pFile);
	// ̹������
	int nTankSize = tanks.m_vecTank.size();
	fwrite(&nTankSize, sizeof(int), 1, pFile);
	// ̹������
	for (int i = 0; i < nTankSize; i++) {
		fwrite(tanks.m_vecTank[i], sizeof(TANK), 1, pFile);
	}

	// �ӵ�
	int nBulletSize = bullets.m_vecBullet.size();
	fwrite(&nBulletSize, sizeof(int), 1, pFile);
	for (int i = 0; i < nBulletSize; i++) {
		fwrite(bullets.m_vecBullet[i], sizeof(BULLET), 1, pFile);
	}
	// ����ֲ���ͼ
	//����
	int nDamagedPlantSize = maps.m_vecDamagedPlant.size();
	fwrite(&nDamagedPlantSize, sizeof(int), 1, pFile);
	//����
	for (int i = 0; i < nDamagedPlantSize; i++) {
		fwrite(&(maps.m_vecDamagedPlant[i]), sizeof(POS), 1, pFile);
	}

	fclose(pFile);
}

// ����
void CCtrl::readArchive(CMaps& maps, CTank& tanks, CBullet& bullets)
{

	FILE * pFile;
	fopen_s(&pFile, "savemap.db", "rb");
	// ��ͼg_nMap����
	fread_s(maps.m_nMap, sizeof(int)*MAPWIDTH*MAPHEIGHT, sizeof(int), MAPWIDTH*MAPHEIGHT, pFile);	
	//̹�˹ؿ�																								
	int nLevel;
	fread_s(&nLevel, sizeof(int), sizeof(int), 1, pFile);		
	tanks.m_nLevel = nLevel;
	// ̹�˷���
	int nScore;
	fread_s(&nScore, sizeof(int), sizeof(int), 1, pFile);
	tanks.m_nScore = nScore;    
	//̹������
	int nTankSize;
	fread_s(&nTankSize, sizeof(int), sizeof(int), 1, pFile);
	//̹������
	for (int i = 0; i < nTankSize; i++) {
		TANK* pTank = (TANK*)malloc(sizeof(TANK));
		fread_s(pTank, sizeof(TANK), sizeof(TANK), 1, pFile);  
		tanks.m_vecTank.push_back(pTank);
		pTank = NULL;
	}

	// �ӵ�
	int nBulletSize;
	fread_s(&nBulletSize, sizeof(int), sizeof(int), 1, pFile);
	for (int i = 0; i < nBulletSize; i++) {
		BULLET* pBullet = (BULLET*)malloc(sizeof(BULLET));
		fread_s(pBullet, sizeof(BULLET), sizeof(BULLET), 1, pFile);
		bullets.m_vecBullet.push_back(pBullet);
		pBullet = NULL;
	}
	// ����ֲ���ͼ
	// ����
	int nDamagedPlantSize;
	fread_s(&nDamagedPlantSize, sizeof(int), sizeof(int), 1, pFile);
	//����
	for (int i = 0; i < nDamagedPlantSize; i++) {
		POS  damagedPlant;
		fread_s(&damagedPlant, sizeof(POS), sizeof(POS), 1, pFile);
		maps.m_vecDamagedPlant.push_back(damagedPlant);
	}
	fclose(pFile);
}

// �������
void CCtrl::clearGlobalData(CMaps& maps, CTank& tanks, CBullet& bullets)
{
	tanks.m_vecTank.clear();
	bullets.m_vecBullet.clear();
	maps.m_vecDamagedPlant.clear();
	for (int row = 0; row < MAPHEIGHT; row++) {
		for (int col = 0; col < MAPWIDTH; col++) {
			maps.m_pTankMap[row][col] = 0;
			maps.m_pBulletMap[row][col] = 0;
			maps.m_nMap[row][col] = 0;
		}
	}
}

// ��ʾ��Ϸ��Ϣ
void CCtrl::showGameInfo(CTank& tanks, CBullet& bullets)
{
	tanks.showTankInfo();

}
#include <Windows.h>
#include <time.h>
#include "EngineMain.h"
#include "EngineDefine.h"
#include "IntroScene.h"
#include "RankScene.h"
#include "SelectScene.h"
#include "AirPlaneGameScene.h"
#include "PaperGameScene.h"
#include "ResultScene.h"

USING_NS_EE;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));

	EngineMain engine("GameOfEveryone", 405, 720);
	SceneManager::GetInstance()->RegistScene(new IntroScene);
	SceneManager::GetInstance()->RegistScene(new RankScene);
	SceneManager::GetInstance()->RegistScene(new SelectScene);
	SceneManager::GetInstance()->RegistScene(new AirPlaneGameScene);
	SceneManager::GetInstance()->RegistScene(new PaperGameScene);
	SceneManager::GetInstance()->RegistScene(new ResultScene);

	return engine.StartEngine(hInstance);
}
#pragma once

enum SCENE_INDEX
{
	SCENE_INDEX_INTRO,
	SCENE_INDEX_RANK,
	SCENE_INDEX_SELECT,
	SCENE_INDEX_AIRPLANEGAME,
	SCENE_INDEX_PAPERGAME,
	SCENE_INDEX_RESULT,
	SCENE_INDEX_END
};

#define SCREEN_WIDTH 405
#define SCREEN_HEIGHT 720

#define GAME_SCREEN_X 0
#define GAME_SCREEN_Y 109
#define GAME_SCREEN_WIDTH 405
#define GAME_SCREEN_HEIGHT 560

#define Z_ORDER_BACK 0
#define Z_ORDER_UIBTN 1
#define Z_ORDER_PAPER_BACK 1
#define Z_ORDER_CLOUD 1
#define Z_ORDER_UILABEL 2
#define Z_ORDER_PAPER_FRONT 2
#define Z_ORDER_STAR 3
#define Z_ORDER_BULLET 4
#define Z_ORDER_AIRPLANE 5
#define Z_ORDER_PAPER_ACTION 5
#define Z_ORDER_UI 10
#define Z_ORDER_UIOBJECT 11
#define Z_ORDER_UITEXT 12

#define READY_TIME 1
#define FEVER_MODE_COUNT 10

#define SAFE_DELETE( p ) { if( p ) { delete ( p ); ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p ); ( p ) = NULL; } }
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
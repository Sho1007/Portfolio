#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define WIN_START_X 100
#define WIN_START_Y 100

#define CENTER_X WIN_WIDTH * 0.5f
#define CENTER_Y WIN_HEIGHT * 0.5f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define MAGENTA RGB(255, 0, 255)
#define CYAN RGB(0, 255, 255)
#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)

#define PI 3.141592f
#define LERP(s, e, t) s * (1 - t) + e * t

#define KEY_DOWN(k) Control::Get()->Down(k)
#define KEY_UP(k) Control::Get()->Up(k)
#define KEY_PRESS(k) Control::Get()->Press(k)

#define DELTA Timer::Get()->GetElapsedTime()

#define TEXTURE TextureManager::Get()
#define AUDIO Audio::Get()
#define SCENE SceneManager::Get()
#define EFFECT EffectManager::Get()
#define CAM Camera::Get()

#include <windows.h>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include "Library/inc/fmod.hpp"
#pragma comment(lib, "Library/lib/x64/fmod_vc.lib")		// 정적 라이브러리 추가

using namespace std;

//Framework Header
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Math.h"
#include "Framework/Math/GameManager.h"

using namespace GameMath;

#include "Framework/Utility/Control.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Audio.h"
#include "Framework/Utility/DataManager.h"
#include "Framework/Utility/Xml.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/TextureManager.h"
#include "Framework/Render/Animation.h"

#include "Framework/Camera/Camera.h"
//Object Header
#include "Objects/Basic/Object.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/EffectManager.h"
#include "Objects/Basic/Button.h"
#include "Objects/Basic/HpBar.h"

#include "Objects/Arcanoid/Bar.h"
#include "Objects/Arcanoid/Ball.h"
#include "Objects/Arcanoid/Brick.h"
#include "Objects/Arcanoid/BrickManager.h"

#include "Objects/Character/Mario.h"

#include "Objects/Landscape/Landscape.h"
#include "Objects/Landscape/Map.h"

#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"

#include "Objects/Fortress/Enemy.h"
#include "Objects/Fortress/EnemyManager.h"

#include "Objects/Shooting/Player.h"

#include "Objects/Character/HWDragonPlayer.h"
#include "Objects/Landscape/DragonLandscape.h"
#include "Objects/Character/HWDragonEnemy.h"
#include "Objects/Character/HWDragonEnemyManager.h"

#include "Objects/Character/Angie.h"

//Program Header
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include "Program/Program.h"

extern Vector2 mousePos;
extern HWND hWnd;
extern HINSTANCE hInst;
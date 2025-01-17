﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define WIN_START_X 600
#define WIN_START_Y 100

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CENTER_X (SCREEN_WIDTH * 0.5f)
#define CENTER_Y (SCREEN_HEIGHT * 0.5f)

#define CENTER Vector2(CENTER_X, CENTER_Y)

#define FOR(n) for(int i = 0 ; i < n ; i++)
#define FOR_X(n) for(int x = 0 ; x < n ; x++)
#define FOR_Y(n) for(int y = 0 ; y < n ; y++)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define SCENE SceneManager::Get()
#define KEY Keyboard::Get()
#define DELTA Timer::Get()->GetElapsedTime()
#define CAM Environment::Get()->GetMainCamera()
#define FONT Font::Get()
#define DIALOG ImGuiFileDialog::Instance()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <fstream>
#include <algorithm>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

//FMOD
#include <FMOD/fmod.h>
#pragma comment(lib, "fmod_vc.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>

#pragma comment(lib, "ImGui.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//FMOD
#include <FMOD/fmod.hpp>

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef function<void()> Event;
typedef function<void(int)> IntParamEvent;
typedef function<void(void*)> ObjectParamEvent;

//Framework Header
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/Math.h"

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/Font.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Audio.h"

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/IsometricCollider.h"
#include "Framework/Collision/LineCollider.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/ObjectManager.h"
#include "Objects/Basic/PoolingManager.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Action.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/EffectManager.h"

#include "Objects/Algorithm/DNode.h"
#include "Objects/Algorithm/Dijkstra.h"

#include "Objects/UI/ProgressBar.h"
#include "Objects/UI/Button.h"
#include "Objects/UI/Panel.h"
#include "Objects/UI/ImageFont.h"

#include "Objects/Map/Floor.h"
#include "Objects/Map/FloorManager.h"

#include "Objects/CA/UI/MapSelectButton.h"
#include "Objects/CA/UI/UI.h"
#include "Objects/CA/UI/StartUI.h"
#include "Objects/CA/UI/WaitRoomUI.h"
#include "Objects/CA/UI/MapEditUI.h"
#include "Objects/CA/UI/GameUI.h"

#include "Objects/CA/Character/CharacterAction.h"
#include "Objects/CA/Character/CharacterIdle.h"
#include "Objects/CA/Character/CharacterMove.h"
#include "Objects/CA/Character/CharacterBubble.h"
#include "Objects/CA/Character/CharacterAlive.h"
#include "Objects/CA/Character/CharacterDie.h"
#include "Objects/CA/Character/Character.h"

#include "Objects/CA/Map/TileObject/TileObject.h"
#include "Objects/CA/Map/TileObject/TileObjectManager.h"
#include "Objects/CA/Map/Tile/Tile.h"
#include "Objects/CA/Map/Tile/BasicTile.h"
#include "Objects/CA/Map/Tile/ObstacleTile.h"
#include "Objects/CA/Map/TileManager.h"
#include "Objects/CA/Map/EditTileMap.h"

#include "Objects/CA/Monster/MonsterMove.h"
#include "Objects/CA/Monster/MonsterDie.h"
#include "Objects/CA/Monster/MonsterHit.h"
#include "Objects/CA/Monster/MonsterBubble.h"
#include "Objects/CA/Monster/Monster.h"
#include "Objects/CA/Monster/BossIdle.h"
#include "Objects/CA/Monster/BossHit.h"
#include "Objects/CA/Monster/BossAttack.h"
#include "Objects/CA/Monster/Boss.h"
#include "Objects/CA/Monster/MonsterManager.h"

#include "Objects/CA/DataManager.h"
#include "Objects/CA/StageManager.h"


#include "Objects/CA/Item/Item.h"
#include "Objects/CA/Item/ItemManager.h"

#include "Objects/CA/Character/Player.h"

#include "Objects/CA/Bubble/Wave.h"
#include "Objects/CA/Bubble/Waves.h"
#include "Objects/CA/Bubble/Bubble.h"
#include "Objects/CA/Bubble/BubbleManager.h"

#include "Objects/TileGame/Amazon.h"




//Scene Header
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/UIManager.h"
#include "Manager/RenderManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;
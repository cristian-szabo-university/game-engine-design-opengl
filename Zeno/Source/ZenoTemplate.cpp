#include "ZenoTemplate.h"

#include "Game/ZenoGameManager.h"

#include "Render/ZenoRenderManager.h"

#include "Resource/ZenoResourceManager.h"

#include "Entity/ZenoEntityFactory.h"

GameManager* Global<GameManager>::s_pInst = NULL;

ResourceManager* Global<ResourceManager>::s_pInst = NULL;

RenderManager* Global<RenderManager>::s_pInst = NULL;

EntityFactory* Global<EntityFactory>::s_pInst = NULL;

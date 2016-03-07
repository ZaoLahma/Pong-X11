/*
 * gameobjectstorage_x11.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: janne
 */

#include "gamecore/gameobjectstorage_x11.h"

GameObjectStorage_X11* GameObjectStorage_X11::instance = nullptr;
std::mutex GameObjectStorage_X11::instanceCreationMutex;

GameObjectStorage_X11::GameObjectStorage_X11()
{

}

void GameObjectStorage_X11::DropInstance()
{
	delete instance;
	instance = nullptr;
}

GameObjectStorage_X11::~GameObjectStorage_X11()
{
	GameObjectMap::iterator objIter = gameObjectMap.begin();

	while(objIter != gameObjectMap.end())
	{
		delete objIter->second;
		objIter = gameObjectMap.begin();
	}

	gameObjectMap.clear();
}

GameObjectStorage_X11* GameObjectStorage_X11::GetApi()
{
	if(nullptr == instance)
	{
		instanceCreationMutex.lock();

		if(nullptr == instance)
		{
			instance = new GameObjectStorage_X11();
		}

		instanceCreationMutex.unlock();
	}

	return instance;
}

void GameObjectStorage_X11::AddObject(GameObject_X11* gameObjectPtr)
{
	gameObjectMap[gameObjectPtr->GetGameObjectId()] = gameObjectPtr;
}

void GameObjectStorage_X11::RemoveObject(GameObject_X11* gameObjectPtr)
{
	GameObjectMap::iterator gameObjectIter = gameObjectMap.find(gameObjectPtr->GetGameObjectId());

	if(gameObjectMap.end() != gameObjectIter)
	{
		gameObjectMap.erase(gameObjectIter);
	}
}

void GameObjectStorage_X11::Update()
{
	for(auto const& gameObject : gameObjectMap)
	{
		gameObject.second->Update();
	}
}

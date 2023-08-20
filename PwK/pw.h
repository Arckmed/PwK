#pragma once
#include "config.h"
#include "hook.h"
#include "MonsterManager.hpp"
#include "InputManager.hpp"
#include "ChatManager.hpp"
#include "ItemManager.hpp"
#include "vector.h"
#include "log.h"

class PW
{
	std::atomic_bool toggleFarming;
	MonsterManager monster;
	ItemManager item;
	ChatManager chat;

public:
	InputManager input;

	PW();
	void StartAutoFarming();
	void StopAutoFarming();
	void StartAutoTrivia();
	void StopAutoTrivia();

private:
	void AutoFarm();
};

class pw
{ };


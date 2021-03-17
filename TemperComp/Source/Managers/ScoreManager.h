#pragma once

//----------------------------------------------------------

#include "Source/Core/Vec2D.h"
#include "Source/Player/Player.h"

//----------------------------------------------------------

class ScoreManager
{
public:
	static ScoreManager* GetInstance();
	~ScoreManager();

	void Update();
	void SetPlayer( Player* newPlayer );
	int32_t GetScore();
	Vec2D GetPickupPosition();

private:
	ScoreManager();

	static ScoreManager* g_scoreManager;
	Player* m_player;
	Vec2D m_pickupPosition;
	int32_t m_score;
};

//----------------------------------------------------------

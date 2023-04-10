#include "ScoreManager.h"

#include <stdlib.h>
#include <time.h>

//----------------------------------------------------------

ScoreManager* ScoreManager::g_scoreManager = nullptr;

//----------------------------------------------------------

ScoreManager* ScoreManager::GetInstance()
{
	if( g_scoreManager == nullptr )
	{
		g_scoreManager = new ScoreManager();
	}

	return g_scoreManager;
}

//----------------------------------------------------------

ScoreManager::~ScoreManager()
{

}

//----------------------------------------------------------

void ScoreManager::Update()
{
	if( m_player != nullptr )
	{
		if( m_pickupPosition == m_player->GetPosition() )
		{
			++m_score;
			const std::vector<Vec2D> availablePositions = m_player->GetAvailableCellsPositions();

			if( availablePositions.size() > 0 )
			{
				int32_t newPositionIndex = rand() % ( availablePositions.size() - 1 );

				m_pickupPosition = availablePositions[ newPositionIndex ];
				m_player->GrantExtraBodyPart();
			}
		}
	}
}

//----------------------------------------------------------

void ScoreManager::SetPlayer( Player* newPlayer )
{
	m_score = 0;
	m_player = newPlayer;
}

//----------------------------------------------------------

int32_t ScoreManager::GetScore()
{
	return m_score;
}

//----------------------------------------------------------

Vec2D ScoreManager::GetPickupPosition()
{
	return m_pickupPosition;
}

//----------------------------------------------------------

ScoreManager::ScoreManager()
	: m_pickupPosition()
	, m_player(nullptr)
	, m_score(0)
{
	srand( ( unsigned int ) time( NULL ) );
}

//----------------------------------------------------------
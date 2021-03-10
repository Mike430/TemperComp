#include "Player.h"

//----------------------------------------------------------

const size_t g_maxBodyParts = 1024;
const int g_snakeStepSize = 50;
const float g_startSpeed = 0.1f;
const Vec2D g_rectDimensions = { 45.0f, 45.0f };
const Color g_playerColour = { 255, 155, 0, 255 };
const Color g_bodyColour = { 255, 0, 0, 255 };

//----------------------------------------------------------

Player::Player()
	: GameObject()
	, m_moveState( EPlayerMove::MoveUp )
	, m_moveStatePrevious( EPlayerMove::MoveUp )
	, m_moveTimer( g_startSpeed )
	, m_currentTime( 0.0f )
	, m_bodyPartsCount( 100 )
	, m_bodyParts( g_maxBodyParts )
#ifdef EXECUTE_TESTS
	, FakeKeyPressed( ( KeyboardKey ) 0 )
#endif //EXECUTE_TESTS
{}

//----------------------------------------------------------

Player::~Player()
{
	m_bodyParts.empty();
}

//----------------------------------------------------------

void Player::Update( const float deltaTime )
{
	GameObject::Update( deltaTime );

	HandleInput();
	MovePlayer( deltaTime );
}

//----------------------------------------------------------

void Player::Draw() const
{
	DrawRectangle( m_position.x,
				   m_position.y,
				   g_rectDimensions.x,
				   g_rectDimensions.y,
				   g_playerColour );

	for( int i = 0; i < m_bodyParts.size() && i < m_bodyPartsCount; ++i )
	{
		DrawRectangle( m_bodyParts[ i ].x,
					   m_bodyParts[ i ].y,
					   g_rectDimensions.x,
					   g_rectDimensions.y,
					   g_bodyColour );
	}
}

//----------------------------------------------------------

bool Player::CheckKeyPressed( const KeyboardKey Key ) const
{
#ifndef EXECUTE_TESTS
	return IsKeyPressed( Key );
#else
	return FakeKeyPressed == Key;
#endif //EXECUTE_TESTS
}

//----------------------------------------------------------

void Player::HandleInput()
{
	if( CheckKeyPressed( KEY_UP ) && m_moveStatePrevious != EPlayerMove::MoveDown )
	{
		m_moveState = EPlayerMove::MoveUp;
	}

	if( CheckKeyPressed( KEY_DOWN ) && m_moveStatePrevious != EPlayerMove::MoveUp )
	{
		m_moveState = EPlayerMove::MoveDown;
	}

	if( CheckKeyPressed( KEY_LEFT ) && m_moveStatePrevious != EPlayerMove::MoveRight )
	{
		m_moveState = EPlayerMove::MoveLeft;
	}

	if( CheckKeyPressed( KEY_RIGHT ) && m_moveStatePrevious != EPlayerMove::MoveLeft )
	{
		m_moveState = EPlayerMove::MoveRight;
	}
}

//----------------------------------------------------------

void Player::MovePlayer( const float deltaTime )
{
	m_currentTime += deltaTime;

	if( m_currentTime > m_moveTimer )
	{
		m_currentTime = 0.0f;
		m_moveStatePrevious = m_moveState;

		UpdateBody();

		switch( m_moveState )
		{
			case EPlayerMove::MoveUp:
				m_position.y -= g_snakeStepSize;
				break;
			case EPlayerMove::MoveLeft:
				m_position.x -= g_snakeStepSize;
				break;
			case EPlayerMove::MoveRight:
				m_position.x += g_snakeStepSize;
				break;
			default:
				m_position.y += g_snakeStepSize;
				break;
		}
	}
}

//----------------------------------------------------------

void Player::UpdateBody()
{
	if( m_bodyPartsCount < m_bodyParts.size() )
	{
		for( int i = m_bodyPartsCount; i >= 0; --i )
		{
			if( i != 0 )
			{
				m_bodyParts[ i ] = m_bodyParts[ i - 1 ];
			}
			else
			{
				m_bodyParts[ i ] = m_position;
			}
		}
	}
}

//----------------------------------------------------------

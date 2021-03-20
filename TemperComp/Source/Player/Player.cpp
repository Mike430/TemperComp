#include "Player.h"

#include "Source/Managers/ScoreManager.h"

//----------------------------------------------------------

const size_t g_maxBodyParts = 1024;
const float g_snakeStepSize = 50.f;
const float g_startSpeed = 0.1f;
const Vec2D g_rectDimensions = { 45.0f, 45.0f };
const Color g_playerColour = { 255, 155, 0, 255 };
const Color g_playerDeadColour = { 255, 0, 255, 255 };
const Color g_bodyColour = { 255, 0, 0, 255 };

//----------------------------------------------------------

Player::Player( int screenWidth, int screenHeight )
	: GameObject()
	, m_moveState( EPlayerMove::MoveUp )
	, m_moveStatePrevious( EPlayerMove::MoveUp )
	, m_moveTimer( g_startSpeed )
	, m_currentTime( 0.0f )
	, m_screenWidth( screenWidth )
	, m_screenHeight( screenHeight )
	, m_availableSpaces( ( ( m_screenWidth / ( int )g_snakeStepSize )* ( m_screenHeight / ( int )g_snakeStepSize ) ) )
	, m_maxBodyPartsCount( m_availableSpaces - 1 ) // minus 1 for the head part
	, m_bodyPartsCount( 2 )
	, m_bodyParts( m_maxBodyPartsCount )
	, IsDead( false )
#ifdef EXECUTE_TESTS
	, FakeKeyPressed( ( KeyboardKey ) 0 )
#endif //EXECUTE_TESTS
{}

//----------------------------------------------------------

Player::~Player()
{
	m_bodyParts.clear();
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
	for( int i = 0; i < m_bodyPartsCount && i < m_bodyParts.size(); ++i )
	{
		DrawRectangle( ( int ) ( m_bodyParts[ i ].x - g_snakeStepSize ),
					   ( int ) ( m_bodyParts[ i ].y - g_snakeStepSize ),
					   ( int ) g_rectDimensions.x,
					   ( int ) g_rectDimensions.y,
					   g_bodyColour );
	}

	DrawRectangle( ( int ) ( m_position.x - g_snakeStepSize ),
				   ( int ) ( m_position.y - g_snakeStepSize ),
				   ( int ) g_rectDimensions.x,
				   ( int ) g_rectDimensions.y,
				   g_playerColour );
}

//----------------------------------------------------------

const std::vector<Vec2D> Player::GetAvailableCellsPositions() const
{
	std::vector<Vec2D> result;
	result.reserve( m_maxBodyPartsCount - m_bodyPartsCount );

	const int horizontalSpaces = m_screenWidth / ( int ) g_snakeStepSize;
	const int verticalSpaces = m_screenHeight / ( int ) g_snakeStepSize;

	for( int x = 0; x < horizontalSpaces; ++x )
	{
		for( int y = 0; y < verticalSpaces; ++y )
		{
			Vec2D space( ( ( x * g_snakeStepSize ) + g_snakeStepSize ) - ( ( float ) m_screenWidth * 0.5f ), ( ( y * g_snakeStepSize ) + g_snakeStepSize ) - ( ( float ) m_screenHeight * .5f ) );
			bool spaceIsFree = true;

			for( int i = 0; i < m_bodyParts.size() && i < m_bodyPartsCount; ++i )
			{
				if( space == m_position || space == m_bodyParts[ i ] )
				{
					spaceIsFree = false;
					break;
				}
			}

			if( spaceIsFree )
			{
				result.push_back( space );
			}
		}
	}

	return result;
}

//----------------------------------------------------------

void Player::GrantExtraBodyPart()
{
	m_bodyPartsCount = m_bodyPartsCount >= m_maxBodyPartsCount ? m_bodyPartsCount : m_bodyPartsCount + 1;
	m_bodyParts[ m_bodyPartsCount - 1 ] = m_bodyParts[ m_bodyPartsCount - 2 ];
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
	if( !IsDead )
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

			IsDead = ShouldDie();

			ScoreManager* scoreManager = ScoreManager::GetInstance();
			scoreManager->Update();
		}
	}
}

//----------------------------------------------------------

void Player::UpdateBody()
{
	for( int i = m_bodyPartsCount - 1; i >= 0; --i )
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

//----------------------------------------------------------

bool Player::ShouldDie()
{
	float xExtent = ( float ) ( m_screenWidth / 2 );
	float yExtent = ( float ) ( m_screenHeight / 2 );

	// Is outside playspace
	if( m_position.x < -xExtent || m_position.x > xExtent ||
		m_position.y < -yExtent || m_position.y > yExtent )
	{
		return true;
	}

	// Is overlapping a bodypart
	for( int i = 0; i < m_bodyPartsCount && i < m_bodyParts.size(); ++i )
	{
		if( m_position == m_bodyParts[ i ] )
		{
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------

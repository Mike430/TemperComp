#pragma once
#include "Source/Core/GameObject.h"
#include <vector>

//----------------------------------------------------------

#ifdef EXECUTE_TESTS
struct PlayerTestHelpers;
#endif //EXECUTE_TESTS

//----------------------------------------------------------

enum EPlayerMove
{
	MoveUp = 0,
	MoveDown = 1,
	MoveLeft = 2,
	MoveRight = 3,
};

//----------------------------------------------------------

class Player : public GameObject
{
public:
	Player( int32_t screenWidth, int32_t screenHeight );
	~Player();

	// GameObject Inherited
	virtual void Update( const float deltaTime ) override;
	virtual void Draw() const override;
	// GameObject Inherited

	const std::vector<Vec2D> GetAvailableCellsPositions() const;
	void GrantExtraBodyPart();
	bool HasDied() { return IsDead; }

private:
	bool CheckKeyPressed( const KeyboardKey Key ) const;
	void HandleInput();
	void MovePlayer( const float deltaTime );
	void UpdateBody();
	bool ShouldDie();

	EPlayerMove m_moveState;
	EPlayerMove m_moveStatePrevious;
	float m_moveTimer;
	float m_currentTime;
	int32_t m_screenWidth;
	int32_t m_screenHeight;
	int32_t m_availableSpaces;
	int32_t m_maxBodyPartsCount;
	int32_t m_bodyPartsCount;
	std::vector<Vec2D> m_bodyParts;

	bool IsDead;

#ifdef EXECUTE_TESTS
public:
	friend PlayerTestHelpers;
	KeyboardKey FakeKeyPressed;
#endif //EXECUTE_TESTS
};

//----------------------------------------------------------

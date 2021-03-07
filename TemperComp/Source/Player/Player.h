#pragma once
#include "../Core/GameObject.h"
#include <vector>

//----------------------------------------------------------

enum EPlayerMove
{
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
};

//----------------------------------------------------------

class Player : public GameObject
{
public:
	Player();
	~Player();

	// GameObject Inherited
	virtual void Update(const float deltaTime) override;
	virtual void Draw() const override;
	// GameObject Inherited

	Vec2D IndexToTalelessPosition( const int index ) { return Vec2D(); }
	bool PointCoversTale( const Vec2D& position ) { return true; }

private:
	void HandleInput();
	void MovePlayer( const float deltaTime );
	void UpdateBody();

	EPlayerMove m_moveState;
	EPlayerMove m_moveStatePrevious;
	float m_moveTimer;
	float m_currentTime;
	size_t m_bodyPartsCount;
	std::vector<Vec2D> m_bodyParts;
};

//----------------------------------------------------------

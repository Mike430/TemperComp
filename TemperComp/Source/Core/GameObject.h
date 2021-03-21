#pragma once
#include <raylib\include\raylib.h>
#include "Vec2D.h"

class GameObject
{
public:
	GameObject();

	virtual void Update( const float DeltaTime );
	virtual void Draw() const;

	void SetPosition( Vec2D newPosition);
	Vec2D GetPosition() const;

protected:
	Vec2D m_position;
};


#include "GameObject.h"

//----------------------------------------------------------

GameObject::GameObject()
	: m_position( 0.0f, 0.0f )
{}

//----------------------------------------------------------

void GameObject::Update( const float DeltaTime )
{
}

//----------------------------------------------------------

void GameObject::Draw() const
{
}

//----------------------------------------------------------

void GameObject::SetPosition(Vec2D newPosition)
{
	m_position = newPosition;
}

//----------------------------------------------------------

Vec2D GameObject::GetPosition() const
{
	return m_position;
}

//----------------------------------------------------------
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

Vec2D GameObject::GetPosition() const
{
	return m_position;
}

//----------------------------------------------------------
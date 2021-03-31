#include "GameObject.hpp"

GameObject::GameObject()
	: alive(true)
{
}

void GameObject::SetPosition(const olc::vf2d &position)
{
	this->position = position;
}

olc::vf2d GameObject::GetPosition() const
{
	return position;
}

void GameObject::Kill()
{
	alive = false;
}

bool GameObject::IsAlive() const
{
	return alive;
}

#include "Object.hpp"

void Object::SetPosition(const sf::Vector2f &position)
{
	this->position = position;
}

sf::Vector2f Object::GetPosition() const
{
	return position;
}
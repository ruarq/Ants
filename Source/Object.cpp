#include "Object.hpp"

void Object::SetPosition(const sf::Vector2f &position)
{
	this->position = position;
}

sf::Vector2f Object::GetPosition() const
{
	return position;
}

void Object::SetAlive(const bool isAlive)
{
	this->isAlive = isAlive;
}

bool Object::IsAlive() const
{
	return isAlive;
}
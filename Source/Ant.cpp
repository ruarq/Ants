#include "Ant.hpp"

Ant::Ant()
{
	const sf::Texture &antTexture = TextureManager::GetTexture("Ant");
	antSprite.setTexture(antTexture);
	antSprite.setOrigin(static_cast<sf::Vector2f>(antTexture.getSize() / 2u));
	antSprite.setScale(sf::Vector2f(0.8f, 0.8f));
}

void Ant::Update(World &world, const float deltaTime)
{
	position += velocity * deltaTime;
}

void Ant::Render(sf::RenderWindow &window)
{
	// Draw the antSprite
	antSprite.setPosition(position);
	antSprite.setRotation(Angle(sf::Vector2f(0.0f, 1.0f), velocity));
	window.draw(antSprite);
}

void Ant::SetVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

sf::Vector2f Ant::GetVelocity() const
{
	return velocity;
}
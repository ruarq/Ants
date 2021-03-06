#pragma once

#include <cstdint>
#include <vector>
#include <array>

#include "Object.hpp"
#include "Math.hpp"

class Quadtree final
{
	friend class Quad;

private:
	class Node
	{
	public:
		virtual ~Node() = default;

	public:
		virtual void Insert(Object *object) = 0;
		virtual void Destroy() = 0;
	};

	class Region final : public Node
	{
	public:
		void Insert(Object *object) override;
		void Destroy() override;

		std::size_t Size() const;
		std::vector<Object*> Objects() const;

	private:
		std::vector<Object*> objects;
	};

	class Quad final : public Node
	{
	public:
		Quad(const Quadtree &quadtree, const sf::Vector2f &position, const sf::Vector2f &size, const std::uint32_t depth = 0);

	public:
		void Insert(Object *object) override;
		void Destroy() override;

		std::vector<Object*> Query(const sf::Vector2f &point) const;
		std::vector<Object*> Query(const sf::Vector2f &point, const float radius) const;

		void Render(sf::RenderWindow &window);

	private:
		std::uint32_t GetNodeIndex(const sf::Vector2f &point, sf::Vector2f *nodePos = nullptr) const;
		std::vector<Object*> Query(const std::uint32_t nodeIndex) const;

	private:
		const Quadtree &quadtree;
		std::array<Node*, 4> nodes;
		const sf::Vector2f position, size;
		std::uint32_t depth;
	};

public:
	Quadtree(const sf::Vector2f &size, const std::uint32_t maxObjectsPerRegion = 32, const std::uint32_t maxDepth = 64);

public:
	void Insert(Object *object);
	void Clear();

	std::vector<Object*> Query(const sf::Vector2f &point) const;
	std::vector<Object*> Query(const sf::Vector2f &point, const float radius) const;

	void Render(sf::RenderWindow &window);

private:
	Quad *root;
	const sf::Vector2f size;
	const std::uint32_t maxObjectsPerRegion, maxDepth;
};
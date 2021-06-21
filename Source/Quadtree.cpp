#include "Quadtree.hpp"

/**
 * REGION
 */

void Quadtree::Region::Insert(Object *object)
{
	objects.push_back(object);
}

void Quadtree::Region::Destroy()
{
	objects.clear();
}

std::size_t Quadtree::Region::Size() const
{
	return objects.size();
}

std::vector<Object*> Quadtree::Region::Objects() const
{
	return objects;
}


/**
 * QUAD
 */

Quadtree::Quad::Quad(const Quadtree &quadtree, const sf::Vector2f &position, const sf::Vector2f &size, const std::uint32_t depth)
	: quadtree(quadtree)
	, position(position)
	, size(size)
	, depth(depth)
{
	nodes.fill(nullptr);
}

void Quadtree::Quad::Insert(Object *object)
{
	sf::Vector2f quadPos;
	const std::uint32_t nodeIndex = this->GetNodeIndex(object, &quadPos);

	Node* &node = nodes[nodeIndex];

	if (!node)
	{
		node = new Region();
	}

	if (Region *region = dynamic_cast<Region*>(node))
	{
		if (region->Size() >= quadtree.maxObjectsPerRegion && depth + 1 < quadtree.maxDepth)
		{
			node = new Quad(quadtree, quadPos, size / 2.0f, depth + 1);
			for (Object *object : region->Objects())
			{
				node->Insert(object);
			}

			delete region;
		}
	}

	node->Insert(object);
}

void Quadtree::Quad::Destroy()
{
	for (Node* &node : nodes)
	{
		if (node)
		{
			node->Destroy();
			delete node;
			node = nullptr;
		}
	}
}

std::vector<Object*> Quadtree::Quad::GetNeighbors(const Object *object) const
{
	const std::uint32_t nodeIndex = this->GetNodeIndex(object);

	if (Region *region = dynamic_cast<Region*>(nodes[nodeIndex]))
	{
		return region->Objects();
	}
	else if (Quad *quad = dynamic_cast<Quad*>(nodes[nodeIndex]))
	{
		return quad->GetNeighbors(object);
	}
	else
	{
		return std::vector<Object*>();
	}
}

void Quadtree::Quad::Render(sf::RenderWindow &window)
{
	const sf::Vector2f center = position + size / 2.0f;
	sf::RectangleShape shape;
	shape.setSize(size / 2.0f);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);

	// top-left
	shape.setPosition(position);
	window.draw(shape);

	// top-right
	shape.setPosition(sf::Vector2f(center.x, position.y));
	window.draw(shape);

	// bottom-left
	shape.setPosition(sf::Vector2f(position.x, center.y));
	window.draw(shape);

	// bottom-right
	shape.setPosition(center);
	window.draw(shape);

	for (Node *node : nodes)
	{
		if (Quad* quad = dynamic_cast<Quad*>(node))
		{
			quad->Render(window);
		}
	}
}

std::uint32_t Quadtree::Quad::GetNodeIndex(const Object *object, sf::Vector2f *nodePos) const
{
	std::uint32_t nodeIndex;
	const sf::Vector2f center = position + size / 2.0f;

	const sf::Vector2f objectPos = object->GetPosition();

	if (objectPos.x <= center.x && objectPos.y <= center.y) // top-left
	{
		nodeIndex = 0;
		
		if (nodePos)
		{
			*nodePos = position;
		}
	}
	else if (objectPos.x > center.x && objectPos.y <= center.y) // top-right
	{
		nodeIndex = 1;

		if (nodePos)
		{
			*nodePos = sf::Vector2f(center.x, position.y);
		}
	}
	else if (objectPos.x <= center.x && objectPos.y > center.y) // bottom-left
	{
		nodeIndex = 2;

		if (nodePos)
		{
			*nodePos = sf::Vector2f(position.x, center.y);
		}
	}
	else if (objectPos.x > center.x && objectPos.y > center.y) // bottom-right
	{
		nodeIndex = 3;

		if (nodePos)
		{
			*nodePos = center;
		}
	}

	return nodeIndex;
}


/**
 * QUADTREE
 */

Quadtree::Quadtree(const sf::Vector2f &size, const std::uint32_t maxObjectsPerRegion, const std::uint32_t maxDepth)
	: root(new Quad(*this, sf::Vector2f(), size))
	, size(size)
	, maxObjectsPerRegion(maxObjectsPerRegion)
	, maxDepth(maxDepth)
{
}

void Quadtree::Insert(Object *object)
{
	if (sf::FloatRect(sf::Vector2f(), size).contains(object->GetPosition()))
	{
		root->Insert(object);
	}
}

void Quadtree::Clear()
{
	root->Destroy();
}

std::vector<Object*> Quadtree::GetNeighbors(const Object *object) const
{
	if (sf::FloatRect(sf::Vector2f(), size).contains(object->GetPosition()))
	{
		std::vector<Object*> neighbors = root->GetNeighbors(object);
		std::remove(neighbors.begin(), neighbors.end(), object);

		return neighbors;
	}
	else
	{
		return std::vector<Object*>();
	}
}

void Quadtree::Render(sf::RenderWindow &window)
{
	root->Render(window);
}
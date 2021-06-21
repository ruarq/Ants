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
	const std::uint32_t nodeIndex = this->GetNodeIndex(object->GetPosition(), &quadPos);

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

std::vector<Object*> Quadtree::Quad::Query(const sf::Vector2f &point) const
{
	const std::uint32_t nodeIndex = this->GetNodeIndex(point);

	if (Region *region = dynamic_cast<Region*>(nodes[nodeIndex]))
	{
		return region->Objects();
	}
	else if (Quad *quad = dynamic_cast<Quad*>(nodes[nodeIndex]))
	{
		return quad->Query(point);
	}
	else
	{
		return std::vector<Object*>();
	}
}

std::vector<Object*> Quadtree::Quad::Query(const sf::Vector2f &point, const float radius) const
{
	std::vector<Object*> objects;
	const sf::Vector2f regionSize = size / 2.0f;
	const sf::Vector2f center = position + regionSize;

	auto Intersect = [&](const sf::FloatRect &rect)
	{
		const sf::Vector2f rayToRect = sf::Vector2f(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f) - point;
		return rect.contains(point + Normalized(rayToRect) * radius) || Length(rayToRect) <= radius;
	};

	auto AddObjectsFromNode = [&](const std::uint32_t nodeIndex)
	{
		if (Region *region = dynamic_cast<Region*>(nodes[nodeIndex]))
		{
			std::vector<Object*> regionsObjects = region->Objects();
			objects.insert(objects.end(), regionsObjects.begin(), regionsObjects.end());
		}
		else if (Quad *quad = dynamic_cast<Quad*>(nodes[nodeIndex]))
		{
			std::vector<Object*> quadsObjects = quad->Query(point, radius);
			objects.insert(objects.end(), quadsObjects.begin(), quadsObjects.end());
		}
	};

	// top-left
	if (Intersect(sf::FloatRect(position, regionSize)))
	{
		AddObjectsFromNode(0);
	}

	// top-right
	if (Intersect(sf::FloatRect(sf::Vector2f(center.x, position.y), regionSize)))
	{
		AddObjectsFromNode(1);
	}

	// bottom-left
	if (Intersect(sf::FloatRect(sf::Vector2f(position.x, center.y), regionSize)))
	{
		AddObjectsFromNode(2);
	}

	// bottom-right
	if (Intersect(sf::FloatRect(center, regionSize)))
	{
		AddObjectsFromNode(3);
	}

	return objects;
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

std::uint32_t Quadtree::Quad::GetNodeIndex(const sf::Vector2f &point, sf::Vector2f *nodePos) const
{
	std::uint32_t nodeIndex;
	const sf::Vector2f center = position + size / 2.0f;

	if (point.x <= center.x && point.y <= center.y) // top-left
	{
		nodeIndex = 0;
		
		if (nodePos)
		{
			*nodePos = position;
		}
	}
	else if (point.x > center.x && point.y <= center.y) // top-right
	{
		nodeIndex = 1;

		if (nodePos)
		{
			*nodePos = sf::Vector2f(center.x, position.y);
		}
	}
	else if (point.x <= center.x && point.y > center.y) // bottom-left
	{
		nodeIndex = 2;

		if (nodePos)
		{
			*nodePos = sf::Vector2f(position.x, center.y);
		}
	}
	else if (point.x > center.x && point.y > center.y) // bottom-right
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

std::vector<Object*> Quadtree::Query(const sf::Vector2f &point) const
{
	if (sf::FloatRect(sf::Vector2f(), size).contains(point))
	{
		return root->Query(point);
	}
	else
	{
		return std::vector<Object*>();
	}
}

std::vector<Object*> Quadtree::Query(const sf::Vector2f &point, const float radius) const
{
	if (sf::FloatRect(sf::Vector2f(), size).contains(point))
	{
		return root->Query(point, radius);
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
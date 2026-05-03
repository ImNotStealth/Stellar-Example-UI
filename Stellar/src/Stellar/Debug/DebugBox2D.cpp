// Debug draw for Box2D 2.2.1 - 2.3.0 for SFML 2.0 - SFMLDebugDraw.cpp
// Copyright (C) 2013  Matija Lovrekovic
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "DebugBox2D.h"
#include "Stellar/Core/Common.h"
#include "Stellar/Core/Game.h"

namespace Stellar
{
	sf::Vector2f DebugBox2DRenderer::World2Screen(b2Vec2 _worldPos, sf::Vector2f _cam)
	{
		sf::Vector2f screenPos = sf::Vector2f(_worldPos.x - _cam.x, _worldPos.y - _cam.y);

		screenPos.y = -screenPos.y; //Inversion de l'axe Y pour coller à box2D
		screenPos.x *= zoom;
		screenPos.y *= zoom;

		return screenPos;
	}

	void DebugBox2DRenderer::DrawPoint(const b2Vec2& p1, float size, const b2Color& color)
	{
	}

	void DebugBox2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon(vertexCount);
		sf::Vector2f center;
		for (int i = 0; i < vertexCount; i++)
		{
			//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
			sf::Vector2f transformedVec = World2Screen(vertices[i], cam);
			polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
		}																								   // they still show up though.. but less frequently
		polygon.setOutlineThickness(-1.f);
		polygon.setFillColor(sf::Color::Transparent);
		polygon.setOutlineColor(DebugBox2DRenderer::GLColorToSFML(color));

		Game::Get().renderTexture.draw(polygon);
	}

	void DebugBox2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon(vertexCount);
		for (int i = 0; i < vertexCount; i++)
		{
			//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
			sf::Vector2f transformedVec = World2Screen(vertices[i], cam);
			polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
		}																								   // they still show up though.. but less frequently
		polygon.setOutlineThickness(-1.f);
		polygon.setFillColor(DebugBox2DRenderer::GLColorToSFML(color, 60));
		polygon.setOutlineColor(DebugBox2DRenderer::GLColorToSFML(color));

		Game::Get().renderTexture.draw(polygon);
	}

	void DebugBox2DRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
	{
		sf::CircleShape circle(radius * zoom);
		circle.setOrigin(radius * zoom, radius * zoom);
		circle.setPosition(World2Screen(center, cam));
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(-1.f);
		circle.setOutlineColor(DebugBox2DRenderer::GLColorToSFML(color));

		Game::Get().renderTexture.draw(circle);
	}

	void DebugBox2DRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
	{
		sf::CircleShape circle(radius * zoom);
		circle.setOrigin(radius * zoom, radius * zoom);
		circle.setPosition(World2Screen(center, cam));
		circle.setFillColor(DebugBox2DRenderer::GLColorToSFML(color, 60));
		circle.setOutlineThickness(1.f);
		circle.setOutlineColor(DebugBox2DRenderer::GLColorToSFML(color));

		b2Vec2 endPoint = center + radius * axis;
		sf::Vertex line[2] =
		{
			sf::Vertex(World2Screen(center, cam), DebugBox2DRenderer::GLColorToSFML(color)),
			sf::Vertex(World2Screen(endPoint, cam), DebugBox2DRenderer::GLColorToSFML(color)),
		};

		Game::Get().renderTexture.draw(circle);
		Game::Get().renderTexture.draw(line, 2, sf::Lines);
	}

	void DebugBox2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(World2Screen(p1,cam), DebugBox2DRenderer::GLColorToSFML(color)),
			sf::Vertex(World2Screen(p2,cam), DebugBox2DRenderer::GLColorToSFML(color))
		};

		Game::Get().renderTexture.draw(line, 2, sf::Lines);
	}

	void DebugBox2DRenderer::DrawTransform(const b2Transform& xf)
	{
		float lineLength = 0.4f;

		/*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
		b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
		sf::Vertex redLine[] =
		{
			sf::Vertex(World2Screen(xf.p,cam), sf::Color::Red),
			sf::Vertex(World2Screen(xAxis,cam), sf::Color::Red)
		};

		// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
		// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
		/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
		b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
		sf::Vertex greenLine[] =
		{
			sf::Vertex(World2Screen(xf.p,cam), sf::Color::Green),
			sf::Vertex(World2Screen(yAxis,cam), sf::Color::Green)
		};

		Game::Get().renderTexture.draw(redLine, 2, sf::Lines);
		Game::Get().renderTexture.draw(greenLine, 2, sf::Lines);
	}
}
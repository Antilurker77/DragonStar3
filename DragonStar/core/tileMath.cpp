// ================================================================
//
// tileMath.cpp
//
// ================================================================

#include "tileMath.hpp"

#include <iostream>
#include "settings.hpp"

double TileMath::Distance(sf::Vector2i start, sf::Vector2i end) {
	double result = 0.0;

	int xdist = abs(start.x - end.x);
	int ydist = abs(start.y - end.y);

	if (xdist == ydist) {
		result = 1.41 * static_cast<double>(xdist);
	}
	else {
		result = static_cast<double>(abs(xdist - ydist)) + static_cast<double>(std::min(xdist, ydist)) * 1.41;
	}

	return result;
}

sf::Vector2i TileMath::Closest(sf::Vector2i location, std::vector<sf::Vector2i>& area) {
	sf::Vector2i result = location;
	if (std::find(area.begin(), area.end(), location) == area.end()) {
		double lowestDistance = std::numeric_limits<double>::max();
		sf::Vector2i closestTile;
		for (auto t : area) {
			double checkDistance = abs(TileMath::Distance(location, t));
			if (checkDistance < lowestDistance) {
				lowestDistance = checkDistance;
				closestTile = t;
			}
		}
		result = closestTile;
	}
	return result;
}

sf::Vector2i TileMath::PixelToTile(sf::Vector2i location) {
	sf::Vector2i result(location.x / settings.TileSizeInt, location.y / settings.TileSizeInt);
	return result;
}

std::vector<sf::Vector2i> TileMath::Neighboors(sf::Vector2i location) {
	std::vector<sf::Vector2i> result {
		{ location.x + 1, location.y },
		{ location.x + 1, location.y - 1 },
		{ location.x + 1, location.y + 1 },
		{ location.x - 1, location.y },
		{ location.x - 1, location.y - 1 },
		{ location.x - 1, location.y + 1 },
		{ location.x, location.y - 1 },
		{ location.x, location.y + 1 }
	};
	return result;
}

std::vector<sf::Vector2i> TileMath::Offset(std::vector<sf::Vector2i>& area, sf::Vector2i offset) {
	std::vector<sf::Vector2i> result;
	result.reserve(area.size());

	for (auto& tile : area) {
		sf::Vector2i t = tile;
		t.x += offset.x;
		t.y += offset.y;
		result.push_back(t);
	}

	return result;
}

std::vector<sf::Vector2i> TileMath::Rotate(std::vector<sf::Vector2i>& area, sf::Vector2i center, double degrees) {
	std::vector<sf::Vector2i> result;
	degrees = 3.141592654 * degrees / 180.0;
	double s = std::sin(degrees);
	double c = std::cos(degrees);

	result.reserve(area.size());

	for (auto& tile : area) {
		tile.x -= center.x;
		tile.y -= center.y;

		double x = tile.x * c - tile.y * s;
		double y = tile.x * s + tile.y * c;

		sf::Vector2i rotatedTile{ static_cast<int>(std::round(x)), static_cast<int>(std::round(y)) };
		rotatedTile.x += center.x;
		rotatedTile.y += center.y;

		result.push_back(rotatedTile);
	}

	return result;
}

double TileMath::AdjacentDegree(sf::Vector2i center, sf::Vector2i tile) {
	double result = 0.0;

	if (tile.x > center.x && tile.y == center.y) {
		result = 90.0;
	}
	else if (tile.x == center.x && tile.y > center.y) {
		result = 180.0;
	}
	else if (tile.x < center.x && tile.y == center.y) {
		result = 270.0;
	}

	return result;
}

std::vector<sf::Vector2i> TileMath::AreaOfEffect(sf::Vector2i center, int radius) {
	std::vector<sf::Vector2i> result;

	int maxDistance = radius / 100;

	for (int x = center.x - maxDistance; x <= center.x + maxDistance; x++) {
		for (int y = center.y - maxDistance; y <= center.y + maxDistance; y++) {
			int distanceCheck = static_cast<int>(std::round(Distance(center, { x, y }) * 100.0));
			if (distanceCheck <= radius) {
				result.push_back({ x, y });
			}
		}
	}

	return result;
}

std::vector<sf::Vector2i> TileMath::Line(sf::Vector2i start, sf::Vector2i end, bool negativeOffset) {
	std::vector<sf::Vector2i> result;
	//std::cout << "[" << start.x << ", " << start.y << "] to [" << end.x << ", " << end.y << "] (" << negativeOffset << ")\n";
	
	// https://www.redblobgames.com/grids/line-drawing.html
	int diagonalDistance = std::max(abs(end.x - start.x), abs(end.y - start.y));
	result.reserve(static_cast<size_t>(diagonalDistance + 1));
	for (int i = 0; i <= diagonalDistance; i++) {
		double t = 0.0;
		//double offset = std::numeric_limits<double>::epsilon() * 10.0;
		double offset = 0.00001;
		if (negativeOffset) {
			offset *= -1.0;
		}
		if (diagonalDistance != 0) {
			t = static_cast<double>(i) / static_cast<double>(diagonalDistance);
		}
		double startX = static_cast<double>(start.x);
		double startY = static_cast<double>(start.y);
		double endX = static_cast<double>(end.x);
		double endY = static_cast<double>(end.y);

		int pointX = static_cast<int>(std::round(startX + t * (endX - startX) + offset));
		int pointY = static_cast<int>(std::round(startY + t * (endY - startY) + offset));

		result.push_back(sf::Vector2i(pointX, pointY));
	}

	/*
	if (start.x == end.x) {
		for (int i = std::min(start.y, end.y); i <= std::max(start.y, end.y); i++) {
			result.push_back({ start.x, i });
		}
	}
	else if (start.y == end.y) {
		for (int i = std::min(start.x, end.x); i <= std::max(start.x, end.x); i++) {
			result.push_back({ i, start.y });
		}
	}
	else {
		// for symmetry
		sf::Vector2i startCalc = start;
		sf::Vector2i endCalc = end;

		bool mirrorX = false;
		bool mirrorY = false;

		// mirror points so that line is always going down-right
		if (start.x > end.x) {
			mirrorX = true;
			endCalc.x += abs(start.x - end.x) * 2;
		}
		if (start.y > end.y) {
			mirrorY = true;
			endCalc.y += abs(start.y - end.y) * 2;
		}

		// https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
		const bool steep = abs(endCalc.y - startCalc.y) > abs(endCalc.x - startCalc.x);
		if (steep) {
			std::swap(startCalc.x, startCalc.y);
			std::swap(endCalc.x, endCalc.y);
		}
		if (startCalc.x > endCalc.x) {
			std::swap(startCalc.x, endCalc.x);
			std::swap(startCalc.y, endCalc.y);
		}

		const double dx = static_cast<double>(endCalc.x - startCalc.x);
		const double dy = static_cast<double>(abs(endCalc.y - startCalc.y));

		double error = dx / 2.0;
		const int yStep = (startCalc.y < endCalc.y) ? 1 : -1;
		int y = startCalc.y;

		const int maxX = endCalc.x;

		for (int x = startCalc.x; x < maxX; x++) {
			if (steep) {
				result.push_back({ y, x });
			}
			else {
				result.push_back({ x, y });
			}
			error -= dy;
			if (error < 0.0) {
				y += yStep;
				error += dx;
			}
		}

		// unmirror points
		if (mirrorX) {
			for (size_t i = 0; i < result.size(); i++) {
				if (result[i] != start) {
					result[i].x -= abs(result[i].x - start.x) * 2;
				}
			}
		}
		if (mirrorY) {
			for (size_t i = 0; i < result.size(); i++) {
				if (result[i] != start) {
					result[i].y -= abs(result[i].y - start.y) * 2;
				}
			}
		}
	}
	*/

	/*
	// https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
	const bool steep = abs(end.y - start.y) > abs(end.x - start.x);
	if (steep) {
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}
	if (start.x > end.x) {
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	const double dx = static_cast<double>(end.x - start.x);
	const double dy = static_cast<double>(abs(end.y - start.y));

	double error = dx / 2.0;
	const int yStep = (start.y < end.y) ? 1 : -1;
	int y = start.y;

	const int maxX = end.x;

	for (int x = start.x; x < maxX; x++) {
		if (steep) {
			result.push_back({ y, x });
		}
		else {
			result.push_back({ x, y });
		}
		error -= dy;
		if (error < 0.0) {
			y += yStep;
			error += dx;
		}
	}
	*/
	return result;
}
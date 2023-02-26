#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "cell.hpp"
#include "matrix.hpp"
#include "field.hpp"

sf::Vector2i CalculateTile(sf::Vector2i position, sf::Vector2i tileDimentions);

Matrix<int> TextureMatrix(Field const& field);

int CalculateTexture(Field const& field, int i, int j);

int CalculateVisibleTexture(Field const& field, int i, int j);

#endif
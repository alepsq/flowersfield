#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "matrix.hpp"

class TileMap : public sf::Drawable, public sf::Transformable {
 public:
  bool load(std::string& texture_file, sf::Vector2i tileMapSize,
            const int* tilesType, unsigned int width, unsigned int heigth) {
    if (!m_texture.loadFromFile(texture_file)) return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * heigth * 4);

    for (unsigned int i = 0; i < width; ++i)
      for (unsigned int j = 0; j < heigth; ++j) {
        int tileNumber = tilesType[i + j * width];

        int textureX = tileNumber % (m_texture.getSize().x / tileMapSize.x);
        int textureY = tileNumber / (m_texture.getSize().x / tileMapSize.x);

        sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(i * tileMapSize.x, j * tileMapSize.y);
        quad[1].position =
            sf::Vector2f((i + 1) * tileMapSize.x, j * tileMapSize.y);
        quad[2].position =
            sf::Vector2f((i + 1) * tileMapSize.x, (j + 1) * tileMapSize.y);
        quad[3].position =
            sf::Vector2f(i * tileMapSize.x, (j + 1) * tileMapSize.y);

        // define its 4 texture coordinates
        quad[0].texCoords =
            sf::Vector2f(textureX * tileMapSize.x, textureY * tileMapSize.y);
        quad[1].texCoords = sf::Vector2f((textureX + 1) * tileMapSize.x,
                                         textureY * tileMapSize.y);
        quad[2].texCoords = sf::Vector2f((textureX + 1) * tileMapSize.x,
                                         (textureY + 1) * tileMapSize.y);
        quad[3].texCoords = sf::Vector2f(textureX * tileMapSize.x,
                                         (textureY + 1) * tileMapSize.y);
      }
    return true;
  }

  bool load(std::string& texture_file, sf::Vector2i tileMapSize,
            Matrix<int> matrix) {
    const int* tilesType = &matrix(1, 1);
    unsigned int width = matrix.GetLength();
    unsigned int heigth = matrix.GetHeight();
    return load(texture_file, tileMapSize, tilesType, width, heigth);
  }

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &m_texture;

    target.draw(m_vertices, states);
  }

  sf::VertexArray m_vertices;
  sf::Texture m_texture;
};

#endif
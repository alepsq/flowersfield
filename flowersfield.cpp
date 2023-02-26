#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

#include "TileMap.hpp"
#include "cell.hpp"
#include "field.hpp"
#include "matrix.hpp"
#include "texture.hpp"

int main() {
  std::string textureFile{"texture.png"};

  sf::Vector2i fieldDimentions{0, 0};
  sf::Vector2i const tileDimentions{32, 32};
  int n_bombs{0};

  std::cout << "Inserire numero di righe" << '\n';
  std::cin >> fieldDimentions.y;
  if (!std::cin.good()) {
    throw std::runtime_error("error in rows selection");
  }
  std::cout << "Inserire numero di colonne" << '\n';
  std::cin >> fieldDimentions.x;
  if (!std::cin.good()) {
    throw std::runtime_error("error in columns selection");
  }
  std::cout <<"Inserire numero di bombe"<<'\n';
  std::cin >> n_bombs;
  if (!std::cin.good()) {
    throw std::runtime_error("error in number of bombs selection");
  }

  unsigned const display_width = tileDimentions.x * fieldDimentions.x;
  unsigned const display_height = tileDimentions.y * fieldDimentions.y;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "minesweeper",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setPosition(sf::Vector2i(100, 30));

  Field field{fieldDimentions.y, fieldDimentions.x, n_bombs};
  TileMap tiles;

  while (window.isOpen()) {
    sf::Vector2i mouseTile =
        CalculateTile(sf::Mouse::getPosition(window), tileDimentions);

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonReleased:
          if (IsInRange(field.GetMatrix(), mouseTile.y, mouseTile.x)) {
            switch (event.mouseButton.button) {
              case sf::Mouse::Left:
                field.evolve_sx(mouseTile.y, mouseTile.x);
                break;
              case sf::Mouse::Right:
                field.evolve_dx(mouseTile.y, mouseTile.x);
                break;
              default:
                break;
            }
            break;
          }
        default:
          break;
      }
    }

    if (!tiles.load(textureFile, tileDimentions, TextureMatrix(field)))
      return -1;
    window.clear();
    window.draw(tiles);
    window.display();
  }
}
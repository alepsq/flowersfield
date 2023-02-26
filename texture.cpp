#include "texture.hpp"

sf::Vector2i CalculateTile(sf::Vector2i position, sf::Vector2i tileDimentions) {
  int row = position.y / tileDimentions.y + 1;
  int column = position.x / tileDimentions.x + 1;

  return {column, row};
}

Matrix<int> TextureMatrix(Field const& field) {
  int const n_row{field.GetMatrix().GetHeight()};
  int const n_column{field.GetMatrix().GetLength()};
  Matrix<int> intMatrix(n_row, n_column);
  for (int i = 1; i <= n_row; ++i)
    for (int j = 1; j <= n_column; ++j) {
      intMatrix(i, j) = CalculateTexture(field, i, j);
    }
  return intMatrix;
}

int CalculateTexture(Field const& field, int i, int j) {
  Matrix<Cell> const& matrix = field.GetMatrix();
  int texture;
  switch (matrix(i, j).GetStatus()) {
    case cell_status::visible:
      texture = CalculateVisibleTexture(field, i, j);
      break;
    case cell_status::hidden:
      texture = 10;
      break;
    default:
      throw std::runtime_error("unknown cell status detected");
      break;
  }
  return texture;
}

int CalculateVisibleTexture(Field const& field, int i, int j) {
  Matrix<Cell> const& matrix = field.GetMatrix();
  switch (matrix(i, j).GetType()) {
    case cell_type::flower:
      switch (field.near_bombs(i, j)) {
        case 0:
          return 0;
          break;
        case 1:
          return 1;
          break;
        case 2:
          return 2;
          break;
        case 3:
          return 3;
          break;
        case 4:
          return 4;
          break;
        case 5:
          return 5;
          break;
        case 6:
          return 6;
          break;
        case 7:
          return 7;
          break;
        case 8:
          return 8;
          break;
        default:
          throw std::runtime_error(
              "cell with more than 8 neighbouring bombs found");
          break;
      }
      break;
    case cell_type::bomb:
      return 9;
      break;
    default:
      throw std::runtime_error("unknown cell type detected");
      break;
  }
}
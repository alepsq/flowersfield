#ifndef FIELD_HPP
#define FIELD_HPP

#include <algorithm>
#include <random>
#include <stdexcept>

#include "cell.hpp"
#include "matrix.hpp"

class RandomIntGenerator {
 public:
  RandomIntGenerator(int lower, int upper)
      : distribution(lower, upper), engine(device()) {}

  int get() { return distribution(engine); }

 private:
  std::random_device device;
  std::uniform_int_distribution<int> distribution;
  std::default_random_engine engine;
};

class Field {
 public:
  Field(int height, int length) : field_{height, length} {}

  Field(int height, int length, int n_bombs) : Field(height, length) {
    if (n_bombs < 0 || n_bombs > length * height)
      throw std::out_of_range("number of bombs selected is invalid");
    RandomIntGenerator randomRow_{1, height};
    RandomIntGenerator randomColumn_{1, length};
    while (n_bombs != 0) {
      int row = randomRow_.get();
      int column = randomColumn_.get();
      if (!IsBomb(field_(row, column))) {
        --n_bombs;
        field_(row, column).SetType(cell_type::bomb);
      }
    }
  }

  Field(Matrix<Cell> matrix) : Field(matrix.GetHeight(), matrix.GetLength()) {
    field_ = matrix;
  }

  bool evolve_sx(int y, int x);
  bool evolve_dx(int y, int x);

  Matrix<Cell> const& GetMatrix() const { return field_; }

  int near_bombs(int y, int x) const;

 private:
  Matrix<Cell> field_;
};

#endif
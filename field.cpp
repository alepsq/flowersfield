#include "field.hpp"

#include <algorithm>

#include "cell.hpp"
#include "matrix.hpp"

int Field::near_bombs(int y, int x) const {
  int counter = 0;
  int n_row = field_.GetHeight();
  int n_column = field_.GetLength();

  for (int i = std::max(y - 1, 1); i <= std::min(y + 1, n_row); ++i) {
    for (int j = std::max(x - 1, 1); j <= std::min(x + 1, n_column); ++j) {
      if (IsBomb(field_(i, j)) && (i != y || j != x)) ++counter;
    }
  }
  return counter;
}

bool Field::evolve_sx(int y, int x) {
  Cell& currentCell = field_(y, x);

  if (!IsHidden(currentCell)) {
    return true;
  }

  if (IsHiddenBomb(currentCell)) {
    field_.for_all([](Cell& cell) {
      if (cell.GetType() == cell_type::bomb)
        cell.SetStatus(cell_status::visible);
    });
    return false;
  }

  currentCell.SetStatus(cell_status::visible);

  if (near_bombs(y, x) == 0) {
    int n_row = field_.GetHeight();
    int n_column = field_.GetLength();

    for (int i = std::max(y - 1, 1); i <= std::min(y + 1, n_row); ++i) {
      for (int j = std::max(x - 1, 1); j <= std::min(x + 1, n_column); ++j) {
        if (i != y || j != x) evolve_sx(i, j);
      }
    }
  }
  return true;
}

bool Field::evolve_dx(int y, int x) {
  Cell& currentCell = field_(y, x);
  if (!IsHidden(currentCell)) {
    return true;
  }

  if (IsHiddenBomb(currentCell)) {
    currentCell.SetStatus(cell_status::visible);
    return true;
  }

  field_.for_all([](Cell& cell) {
    if (cell.GetType() == cell_type::bomb) cell.SetStatus(cell_status::visible);
  });

  return false;
}

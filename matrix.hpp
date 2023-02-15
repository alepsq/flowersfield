#include <stdexcept>
#include <vector>

template <typename T>

class Matrix {
    public:
    Matrix(int rows, int columns) : n_row_{rows}, n_column_{columns} {
    vector_.resize(rows * columns);
  }

  T& operator()(int row, int column) {
    CheckRange(row, column);
    return vector_[CalculateIndex(row, column)];
  }
  void SetElement(int row, int column, T value) {
    CheckRange(row, column);
    vector_[CalculateIndex(row, column)] = value;
  }

 private:
  std::vector<T> vector_;
  int n_row_;
  int n_column_;
  void CheckRange(int row, int column) {
    if (row > n_row_ || column > n_column_)
      throw std::out_of_range("matrix is out of range");
  }
  int CalculateIndex(int row, int column) { return n_row_* column + row; }
};
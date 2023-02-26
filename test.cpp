#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "cell.hpp"
#include "doctest.h"
#include "field.hpp"
#include "matrix.hpp"

TEST_CASE("matrix") {
  SUBCASE("constructor") {
    CHECK_NOTHROW(Matrix<double>{2, 2});
    CHECK_NOTHROW(Matrix<char>{20, 40});
    CHECK_NOTHROW(Matrix<Cell>{100, 200});
    CHECK_THROWS(Matrix<int>{-15, 23});
  }
  SUBCASE("getters") {
    Matrix<int> matrix{4, 3};
    CHECK(matrix.GetHeight() == 4);
    CHECK(matrix.GetLength() == 3);
  }
  SUBCASE("set element and get element") {
    Matrix<char> matrix{6, 8};
    CHECK_NOTHROW(matrix(1, 2) = 'b');
    CHECK(matrix(1, 2) == 'b');
    CHECK_THROWS(matrix(8, 6));
  }
  SUBCASE("copy matrix") {
    Matrix<int> matrix_1{20, 20};
    Matrix<int> matrix_2{20, 19};
    Matrix<int> matrix_3{20, 20};
    matrix_3(15, 10) = 1999;
    matrix_3(10, 1) = 25;
    CHECK_THROWS(matrix_1 = matrix_2);
    CHECK_NOTHROW(matrix_1 = matrix_3);
    CHECK(matrix_1(15, 10) == 1999);
    CHECK(matrix_1(10, 1) == 25);
  }
  SUBCASE("Is in range") {
    Matrix<char> matrix{20, 20};
    CHECK(IsInRange(matrix, 2, 2));
    CHECK(!IsInRange(matrix, 21, 20));
    CHECK(!IsInRange(matrix, -1, 5));
  }
}

TEST_CASE("Cell") {
  SUBCASE("constructors") {
    CHECK_NOTHROW(Cell());
    CHECK_NOTHROW(Cell(cell_type::bomb));
    CHECK_NOTHROW(Cell(cell_type::bomb, cell_status::visible));
  }
  SUBCASE("setters and getters") {
    Cell cell_1;
    Cell cell_2{cell_type::bomb, cell_status::visible};
    CHECK(cell_1.GetStatus() == cell_status::hidden);
    CHECK(cell_2.GetType() == cell_type::bomb);
    CHECK(cell_2.GetStatus() == cell_status::visible);
    CHECK_NOTHROW(cell_1.SetStatus(cell_status::visible));
    CHECK_NOTHROW(cell_1.SetType(cell_type::bomb));
    CHECK(cell_1.GetStatus() == cell_status::visible);
    CHECK(cell_1.GetType() == cell_type::bomb);
  }
  SUBCASE("functions") {
    Cell cell_1(cell_type::bomb);
    Cell cell_2{cell_type::bomb, cell_status::visible};
    CHECK((IsBomb(cell_1) && IsBomb(cell_2)));
    CHECK((IsHidden(cell_1) && !IsHidden(cell_2)));
    CHECK(IsHiddenBomb(cell_1));
    CHECK(!IsHiddenBomb(cell_2));
  }
}

TEST_CASE("Field") {
  SUBCASE("constructor") {
    Field field_1{2, 2};
    Field field_2{2, 3, 5};
    Matrix<Cell> matrix{7, 2};
    Field field_3{matrix};
    CHECK(field_1.GetMatrix().GetHeight() == 2);
    CHECK(field_2.GetMatrix().GetLength() == 3);
    CHECK(field_3.GetMatrix().GetHeight() == 7);
  }

  SUBCASE("evolve") {
    Matrix<Cell> matrix{6, 8};
    matrix(1, 2).SetType(cell_type::bomb);
    matrix(2, 3).SetType(cell_type::bomb);
    matrix(4, 3).SetType(cell_type::bomb);
    matrix(5, 1).SetType(cell_type::bomb);
    Field field{matrix};
    CHECK(field.GetMatrix()(1, 2).GetType()==cell_type::bomb);
        CHECK(field.near_hidden_bombs(2, 2) == 2);
    CHECK(field.evolve_sx(2, 2));
    CHECK(field.evolve_sx(3, 1));
    CHECK(field.evolve_dx(1, 2));

    Matrix<Cell> evolved_matrix{field.GetMatrix()};
    CHECK((evolved_matrix(2, 1).GetType() == cell_type::flower &&
           evolved_matrix(2, 1).GetStatus() == cell_status::visible));
    CHECK((evolved_matrix(2, 2).GetType() == cell_type::flower &&
           evolved_matrix(2, 2).GetStatus() == cell_status::visible));
    CHECK((evolved_matrix(3, 2).GetType() == cell_type::flower &&
           evolved_matrix(3, 2).GetStatus() == cell_status::visible));
    CHECK((evolved_matrix(4, 2).GetType() == cell_type::flower &&
           evolved_matrix(4, 2).GetStatus() == cell_status::visible));
    CHECK((evolved_matrix(4, 1).GetType() == cell_type::flower &&
           evolved_matrix(4, 1).GetStatus() == cell_status::visible));
    CHECK((evolved_matrix(1, 2).GetType() == cell_type::bomb &&
           evolved_matrix(4, 1).GetStatus() == cell_status::visible));
    CHECK(!field.evolve_sx(2, 3));
    evolved_matrix = field.GetMatrix();
    CHECK((evolved_matrix(5, 1).GetType() == cell_type::bomb &&
           evolved_matrix(5, 1).GetStatus() == cell_status::visible));
  }
}

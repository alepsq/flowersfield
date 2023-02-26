#include "cell.hpp"

bool IsBomb(Cell cell) { return cell.GetType() == cell_type::bomb; }
bool IsHidden(Cell cell) { return cell.GetStatus() == cell_status::hidden; }
bool IsHiddenBomb(Cell cell) { return (IsBomb(cell) && IsHidden(cell)); }
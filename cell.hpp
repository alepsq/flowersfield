enum class cell_type { bomb, flower, defused };

enum class cell_status { hidden, visible };

class Cell {
 public:
  Cell() : type_{cell_type::flower}, status_{cell_status::hidden} {}
  Cell(cell_type type) : type_{type}, status_{cell_status::hidden} {}
  Cell(cell_type type, cell_status status) : type_{type}, status_{status} {}
  cell_type GetType() const { return type_; }
  cell_status GetStatus() const { return status_; }
  void SetType(cell_type type) { type_ = type; }
  void SetStatus(cell_status status) { status_ = status; }

 private:
  cell_type type_;
  cell_status status_;
};
export module Board;

export class Board : public Game {
  public:
    bool updateBoard(int row, int col, char changed_char);
    char getState(int row, int col);
};
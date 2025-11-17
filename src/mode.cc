export module Mode;

export class Mode {
  protected:
    Board board;
    std::vector<Player> players;
    int num_players;

  public:
    virtual void operatingGame() = 0;
  
};

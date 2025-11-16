export module Game;

export class Game {
  public:
    bool notifyObservers(Link *link, std::string state);
    void attach(Observers *observer);
    void detach(Observers *observer);
};
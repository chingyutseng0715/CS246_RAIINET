export module Observer;

export class Observer {
  public:
    virtual bool notify() = 0;
};
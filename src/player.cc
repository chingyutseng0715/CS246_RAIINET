export module Player;

export class Player : public Observer {
  public:
    bool notify() override;
    int getDownloadedVirusAmount();
    int getDownloadedDataAmount();
};
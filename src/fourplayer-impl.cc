module FourPlayerMode;

FourPlayerMode::FourPlayerMode() : GameMode{std::make_shared<Board>()} {
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(std::make_shared<Player>());
    }
}

void FourPlayerMode::runGame() {

}

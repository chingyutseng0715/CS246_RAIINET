module TwoPlayerMode;

TwoPlayerMode::TwoPlayerMode() : GameMode{std::make_shared<Board>()} {
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(std::make_shared<Player>());
    }
}

void TwoPlayerMode::runGame() {
    while (true) {
        break; // temporary
    }
}

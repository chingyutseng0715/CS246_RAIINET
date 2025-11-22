module GameMode;

using namespace std;

GameMode::GameMode(Board board, std::vector<Player> players) : board{board}, players{players} {
}

void GameMode::operatingGame() {
    while (true) {
        switch (game_state) {
            case GameState::Menu:
                // run some menu display function
                break;
            case GameState::GameRunning:
                runGame();
                break;
            case GameState::GameOver:
                // run some game over display function, that could potentially reset the game
                break;
        }
    }
}

void GameMode::setGameState(GameState::GameState new_game_state) {
    game_state = new_game_state;
}

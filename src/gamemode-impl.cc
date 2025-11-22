module GameMode;

GameMode::GameMode(Board board, std::vector<Player> players) : board{board}, players{players} {
}

void GameMode::operatingGame() {
    while (true) {
        switch (game_state) {
            case GameState::Menu:
                displayMenu();
                break;
            case GameState::GameRunning:
                runGame();
                break;
            case GameState::GameOver:
                displayGameOver();  // potentially let this or something else reset the game
                break;
        }
    }
}

void GameMode::displayMenu() {

}

void GameMode::displayGameOver() {
    
}

void GameMode::setGameState(GameState::GameState new_game_state) {
    game_state = new_game_state;
}

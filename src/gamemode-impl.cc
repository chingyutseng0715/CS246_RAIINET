module GameMode;

GameMode::GameMode(std::shared_ptr<Board> board) : board{board} {
}

void GameMode::operatingGame() {
    while (true) {
        Player winner;
        switch (game_state) {
            case GameState::Menu:
                displayMenu();
                break;
            case GameState::GameRunning:
                winner = runGame();
                break;
            case GameState::GameOver:
                displayGameOver(winner); // potentially let this or something else reset the game
                break;
        }
    }
}

void GameMode::displayMenu() {
    cout << ASCII_TITLE << endl;
}

void GameMode::displayGameOver(Player winner) {
    
}

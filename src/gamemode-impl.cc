module GameMode;

GameMode::GameMode(std::shared_ptr<Board> board) : board{board} {
}

void GameMode::operatingGame() {
    while (true) {
        switch (game_state) {
            case GameState::Menu:
                displayMenu();
                break;
            case GameState::GameRunning:
                runGame(); // can store the winner enum and use that as a parameter in displayGameOver()
                break;
            case GameState::GameOver:
                displayGameOver();  // potentially let this or something else reset the game
                break;
        }
    }
}

void GameMode::displayMenu() {
    cout << ASCII_TITLE << endl;
}

void GameMode::displayGameOver() {
    
}

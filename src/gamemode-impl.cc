module GameMode;

using std::string;

GameMode::GameMode(std::shared_ptr<Board> board) : board{board} {
}

void GameMode::operatingGame() {
    while (true) {
        PlayerID winner;
        switch (game_state) {
            case GameState::Menu:
                displayMenu();
                game_state = GameState::GameRunning;
                break;
            case GameState::GameRunning:
                winner = runGame();
                game_state = GameState::GameOver;
                break;
            case GameState::GameOver:
                displayGameOver(winner);
                return; // potentially let this or the function above reset the game
                // break;
        }
    }
}

void GameMode::displayMenu() {
    cout << ASCII_TITLE << endl;
    cout << ASCII_INSTRUCTIONS << endl;
    string user_input;
    while (getline(cin, user_input)) {
        if (user_input == "") return;
    }
}

void GameMode::displayGameOver(PlayerID winner) {
    string winner_str;
    switch(winner) {
        case PlayerID::Player1:
            winner_str = ASCII_PLAYER_ONE;
            break;
        case PlayerID::Player2:
            winner_str = ASCII_PLAYER_TWO;
            break;
        case PlayerID::Player3:
            winner_str = ASCII_PLAYER_THREE;
            break;
        case PlayerID::Player4:
            winner_str = ASCII_PLAYER_FOUR;
            break;
        case PlayerID::Nobody:
            winner_str = ASCII_NOBODY;
            break;
    }
    cout << winner_str << endl;
    cout << ASCII_WINNER_MESSAGE_END << endl;
    // maybe add something to reset the game
}

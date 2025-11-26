module GameMode;

using std::string, std::cin, std::cout, std::endl, std::ifstream, std::istringstream, std::unique_ptr, std::shared_ptr, std::invalid_argument;

GameMode::GameMode(std::unique_ptr<Board> board) : board{std::move(board)} {
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
                return;
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
}

bool GameMode::conductPlayerTurn(shared_ptr<Player> current_player_ptr, bool &ability_used) {
    while (true) {
        // Read a line from input
        string line;
        bool valid_line;
        if (using_file) {
            valid_line = static_cast<bool>(getline(sequence_file, line)); // getline() doesn't return a bool
        } else {
            valid_line = static_cast<bool>(getline(cin, line)); // getline() doesn't return a bool
        }

        // Check whether a line couldn't be read
        if (!valid_line) {
            // Return to standard input if EOF has been reached while reading a file
            if (using_file && sequence_file.eof()) {
                using_file = false;
                continue;
            } else { // Otherwise, EOF has been reached on standard input, so terminate the game
                return false;
            }
        }

        istringstream iss{line};
        string cmd;

        if (!(iss >> cmd)) continue; // Skip empty lines

        // Parse the command
        if (cmd == "abilities") {
            current_player_ptr->displayAbility(cout);
            continue;

        } else if (cmd == "board") {
            current_player_ptr->printPlayerView(cout);
            continue;

        } else if (cmd == "ability") {
            if (ability_used) throw invalid_argument("An ability has already been played this turn.");
            int ability_ID;
            if (!(iss >> ability_ID) || ability_ID < 1 || ability_ID > 5) {
                throw invalid_argument("Invalid ability ID.");
            }
            string ability_command;
            if (!getline(iss, ability_command)) throw invalid_argument("Ability command not provided.");
            current_player_ptr->usingAbility(ability_ID, ability_command);
            ability_used = true;
            continue;

        } else if (cmd == "move") {
            string move_command;
            if (!getline(iss, move_command)) throw invalid_argument("Move command not provided.");
            current_player_ptr->movingLink(move_command);
            return true;

        } else if (cmd == "sequence") {
            string sequence_file_name;
            if (!(iss >> sequence_file_name)) throw invalid_argument("File name not provided.");
            sequence_file = ifstream(sequence_file_name);
            if (!sequence_file) throw invalid_argument("File does not exist.");
            using_file = true;
            continue;

        } else if (cmd == "quit") {
            return false;

        } else {
            throw invalid_argument("Invalid command.");

        }
    }
}

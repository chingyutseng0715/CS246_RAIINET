module TwoPlayerMode;

using std::string, std::ifstream, std::istringstream, std::shared_ptr, std::make_shared, std::invalid_argument;

const string PLAYER1 = "Player 1"; // CHANGE to enums later
const string PLAYER2 = "Player 2";

TwoPlayerMode::TwoPlayerMode(const ProcessedInput &input) : 
    GameMode{make_shared<TwoPlayerBoard>()} {
    ability_orders = input.ability_orders;
    link_orders = input.link_orders;
    players.emplace_back(make_shared<Player>(PLAYER1, board, ability_orders[0]));
    players.emplace_back(make_shared<Player>(PLAYER2, board, ability_orders[1]));
    
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        // players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, ability_orders[i]));
        board->addPlayer(players[i], link_orders[i]);
    }
}

PlayerID TwoPlayerMode::runGame() {
    // Start the game with Player 1 having the first turn
    PlayerID current_player = PlayerID::Player1;
    shared_ptr<Player> current_player_ptr = players[0];

    while (true) {
        bool ability_used = false;

        // Return false upon EOF or 'quit' and true upon a successful 'move'
        if (!conductPlayerTurn(current_player, current_player_ptr, ability_used)) {
            return PlayerID::Nobody;
        }

        // Return the current player if they have downloaded 4 data
        if (current_player_ptr->getDownloadedDataAmount() == 4) {
            return current_player;
        }

        // Return the opposing player if the current player has downloaded 4 viruses
        if (current_player_ptr->getDownloadedVirusAmount() == 4) {
            return (current_player == PlayerID::Player1) ? PlayerID::Player2 : PlayerID::Player1;
        }

        // Change which player's turn it is
        switch (current_player) {
            case PlayerID::Player1:
                current_player = PlayerID::Player2;
                current_player_ptr = players[1];
                break;
            case PlayerID::Player2:
                current_player = PlayerID::Player1;
                current_player_ptr = players[0];
                break;
        }
    }
}

// maybe add a playerCount param if I move this func to GameMode
bool TwoPlayerMode::conductPlayerTurn(PlayerID current_player, // prolly move this func to GameMode since 4-play impl is same
                                      shared_ptr<Player> current_player_ptr, // remove current_player if it isn't used
                                      bool &ability_used) {
    while (true) {
        // Read a line from input
        string line;
        bool valid_line;
        if (using_file) {
            valid_line = getline(sequence_file, line);
        } else {
            valid_line = getline(cin, line);
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
            current_player_ptr->usingAbility(ability_ID, ability_command)
            ability_used = true;
            continue;

        } else if (cmd == "move") {
            string link_char;
            string direction;
            if (!(iss >> link_char >> direction)) {
                throw invalid_argument("Missing or invalid arguments.");
            }
            if (/*CHECK FOR INVALID LINKS*/) {
                throw invalid_argument("Invalid link.");
            }
            if (direction != "up" && direction != "down" && direction != "left" && direction != "right") {
                throw invalid_argument("Invalid direction.");
            }
            current_player_ptr->movingLink(link_char, direction);
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

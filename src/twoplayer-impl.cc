module TwoPlayerMode;

TwoPlayerMode::TwoPlayerMode(std::string ability1_order, std::string ability2_order, 
                             std::string link1_order, std::string link2_order) : 
    GameMode{std::make_shared<TwoPlayerBoard>()} {
    ability_orders.emplace_back(ability1_order);
    ability_orders.emplace_back(ability2_order);
    link_orders.emplace_back(link1_order);
    link_orders.emplace_back(link2_order);
    players.emplace_back(std::make_shared<Player>(PLAYER1, board, ability_orders[0]));
    players.emplace_back(std::make_shared<Player>(PLAYER2, board, ability_orders[1]));
    
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        board->addPlayer(players[i], link_orders[i]);
    }
}

Winner TwoPlayerMode::runGame() {
    Player current_turn = Player::Player1;
    std::shared_ptr<Player> current_player = players[0];
    while (true) {
        if (!conductPlayerTurn(current_turn, current_player)) return; // If statement is true upon EOF or 'quit' command

        if (current_player->getDownloadedDataAmount() == 4) {
            return current_turn;
        }
        if (current_player->getDownloadedVirusAmount() == 4) {
            return current_turn == Player::Player1 ? Player::Player2 : Player::Player1; // Returns the other player
        }

        if (current_turn == Player::Player1) {
            current_turn = Player::Player2;
            current_player = players[1];
        } else if (current_turn == Player::Player2) {
            current_turn = Player::Player1;
            current_player = players[0];
        }
    }
}

bool conductPlayerTurn(Player current_turn, std::shared_ptr<Player> current_player) {
    std::string line;
    bool abilityUsed = false;
    while (getline(cin, line)) {
        istringstream iss{line};
        std::string cmd;
        if (!(iss >> cmd)) continue;

        if (cmd == "abilities") {
            // print the abilities of current_player
        } else if (cmd == "board") {
            // print the board from the perspective of current_player
        } else if (cmd == "ability") {
            if (abilityUsed) {
                throw std::invalid_argument("An ability has already been played.");
            }
            int ability_ID;
            if (!(iss >> ability_ID) || ability_ID < 1 || ability_ID > 1) {
                throw std::invalid_argument("Invalid ability ID.");
            }
            // identify the ability and use iss to fetch the remaining info for the ability, and input it to a function
        } else if (cmd == "move") {
            char link_char;
            std::string direction;
            if (!(iss >> link >> direction)) {
                throw std::invalid_argument("Missing or invalid arguments.");
            }
            if (PLAYER1_VALID_LINKS.find(link) == PLAYER1_VALID_LINKS.npos) {
                throw std::invalid_argument("Invalid link.");
            }
            if (direction != "up" && direction != "down" && direction != "left" && direction != "right") {
                throw std::invalid_argument("Invalid direction.");
            }
            current_player->movingLink(link_char, direction);
            return true;
        }
        if (cmd == "sequence") {
            std::string command_sequence_file;
            if (!(iss >> command_sequence_file)) {
                throw std::invalid_argument("Invalid file name.");
            }
            // INCLUDE OTHER FILE CHECKS (SUCH AS FILE DOESN'T EXIST OR EMPTY) AND SET ITS CONTENTS AS A LIST OF COMMANDS
        }
        if (cmd == "quit") {
            return false;
        }
    }
    return false; // change???
}

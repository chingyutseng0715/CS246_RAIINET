module TwoPlayerMode;

using std::string, std::shared_ptr, std::make_shared, std::ifstream, std::invalid_argument;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";

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

Winner TwoPlayerMode::runGame() {
    Player current_turn = Player::Player1;
    shared_ptr<Player> current_player = players[0];
    
    istream *input = &cin;
    bool using_file = false;
    while (true) {
        bool ability_used = false;
        conductPlayerTurn(current_turn, current_player, input, ability_used, using_file); // Returns false upon EOF or 'quit' command

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

bool conductPlayerTurn(Player current_turn, shared_ptr<Player> current_player, 
                       istream *&in, bool &ability_used, bool &using_file) {
    string line;
    while (getline(*in, line)) {
        istringstream iss{line};
        string cmd;
        
        if (!(iss >> cmd)) continue; // skips blank lines

        if (cmd == "abilities") {
            // print the abilities of current_player
        } else if (cmd == "board") {
            // print the board from the perspective of current_player
        } else if (cmd == "ability") {
            if (ability_used) {
                throw invalid_argument("An ability has already been played.");
            }
            int ability_ID;
            if (!(iss >> ability_ID) || ability_ID < 1 || ability_ID > 5) {
                throw invalid_argument("Invalid ability ID.");
            }
            // identify the ability and use iss to fetch the remaining info for the ability, and input it to a function
            ability_used = true;
        } else if (cmd == "move") {
            char link_char;
            string direction;
            if (!(iss >> link_char >> direction)) {
                throw invalid_argument("Missing or invalid arguments.");
            }
            if (PLAYER1_VALID_LINKS.find(link_char) == PLAYER1_VALID_LINKS.npos) {
                throw invalid_argument("Invalid link.");
            }
            if (direction != "up" && direction != "down" && direction != "left" && direction != "right") {
                throw invalid_argument("Invalid direction.");
            }
            current_player->movingLink(link_char, direction);
            return true;
        } else if (cmd == "sequence") {
            string sequence_file_name;
            if (!(iss >> sequence_file_name)) {
                throw invalid_argument("File name not provided.");
            }
            sequence_file = if_stream(sequence_file_name);
            if (!sequence_file) throw invalid_argument("File does not exist.");
            using_file = true;
            in = &sequence_file;
            continue;
        } else if (cmd == "quit") {
            return false;
        } else {
            throw invalid_argument("Invalid command.");
        }
    }
    if (in->eof() && using_file) {
        in = &cin;
        using_file = false;
        return true;
    }
    return false; // change???
}

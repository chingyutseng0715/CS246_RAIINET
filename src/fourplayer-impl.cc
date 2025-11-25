module FourPlayerMode;

using std::string, std::shared_ptr, std::make_shared, std::ifstream, std::invalid_argument;

const string PLAYER1 = "Player 1";
const string PLAYER2 = "Player 2";
const string PLAYER3 = "Player 3";
const string PLAYER4 = "Player 4";

FourPlayerMode::FourPlayerMode(const ProcessedInput &input) : 
    GameMode{make_shared<FourPlayerBoard>()} {
    ability_orders = input.ability_orders;
    link_orders = input.link_orders;
    players.emplace_back(make_shared<Player>(PLAYER1, board.get(), ability_orders[0]));
    players.emplace_back(make_shared<Player>(PLAYER2, board.get(), ability_orders[1]));
    players.emplace_back(make_shared<Player>(PLAYER3, board.get(), ability_orders[2]));
    players.emplace_back(make_shared<Player>(PLAYER4, board.get(), ability_orders[3]));

    for (int i = 0; i < NUM_PLAYERS; ++i) {
        // players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, ability_orders[i]));
        board->addPlayer(players[i].get(), link_orders[i]);
    }
}

PlayerID FourPlayerMode::runGame() {
    // Start the game with Player 1 having the first turn
    PlayerID current_player = PlayerID::Player1;
    shared_ptr<Player> current_player_ptr = players[0];

    while (true) {
        bool ability_used = false;

        // Return false upon EOF or 'quit' and true upon a successful 'move'
        if (!conductPlayerTurn(current_player_ptr, ability_used)) {
            return PlayerID::Nobody;
        }

        // Return the current player if they have downloaded 4 data
        if (current_player_ptr->getDownloadedDataAmount() == 4) {
            return current_player;
        }

        // Remove the current player from if the game if they have downloaded 4 viruses
        if (current_player_ptr->getDownloadedVirusAmount() == 4) {
            eliminatedPlayers[current_player] = true;
            --remaining_players;
        }

        // Check if 3 players have lost, leaving the last player to win
        if (remaining_players == 1) {
            for (auto &player : eliminatedPlayers) {
                if (!player.second) return player.first;
            }
        }

        // Change which player's turn it is
        do {
            switch (current_player) {
                case PlayerID::Player1:
                    current_player = PlayerID::Player2;
                    current_player_ptr = players[1];
                    break;
                case PlayerID::Player2:
                    current_player = PlayerID::Player3;
                    current_player_ptr = players[2];
                    break;
                case PlayerID::Player3:
                    current_player = PlayerID::Player4;
                    current_player_ptr = players[3];
                    break;
                case PlayerID::Player4:
                    current_player = PlayerID::Player1;
                    current_player_ptr = players[0];
                    break;
            }
        } while (eliminatedPlayers[current_player]);
    }
}

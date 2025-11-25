module TwoPlayerMode;

using std::string, std::shared_ptr, std::make_shared;

const string PLAYER1 = "Player 1"; // CHANGE to enums later
const string PLAYER2 = "Player 2";

TwoPlayerMode::TwoPlayerMode(const ProcessedInput &input) : 
    GameMode{make_shared<TwoPlayerBoard>()} {
    ability_orders = input.ability_orders;
    link_orders = input.link_orders;
    players.emplace_back(make_shared<Player>(PLAYER1, board.get(), ability_orders[0])); // Is .get() here fine??? It means every copied ptr of Board is a raw ptr!!!!!
    players.emplace_back(make_shared<Player>(PLAYER2, board.get(), ability_orders[1]));
    
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        // players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, ability_orders[i]));
        board->addPlayer(players[i].get(), link_orders[i]);
    }
}

PlayerID TwoPlayerMode::runGame() {
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

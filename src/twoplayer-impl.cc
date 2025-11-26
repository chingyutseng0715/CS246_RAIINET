module TwoPlayerMode;

using std::string, std::cout, std::to_string, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared;

TwoPlayerMode::TwoPlayerMode(const ProcessedInput &input) : 
    GameMode{make_unique<TwoPlayerBoard>()} {
	for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, input.ability_orders[i]));
        board->addPlayer(players[i].get(), input.link_orders[i]);
    }
}

PlayerID TwoPlayerMode::runGame() {
    // Start the game with Player 1 having the first turn
    PlayerID current_player = PlayerID::Player1;
    shared_ptr<Player> current_player_ptr = players[0];

    while (true) {
        bool ability_used = false;
        current_player_ptr->printPlayerView(cout);

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

module TwoPlayerMode;

using std::string, std::cout, std::to_string, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared;

TwoPlayerMode::TwoPlayerMode(const ProcessedInput &input) : 
    GameMode{make_unique<TwoPlayerBoard>()} {
	for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board.get(), input.ability_orders[i]));
        board->addPlayer(players[i].get(), input.link_orders[i]);
    }
}

PlayerID TwoPlayerMode::runGame() { // INEFFICIENT, CHANGE LATER (make it similar to four-player-impl.)
    // Start the game with Player 1 having the first turn
    PlayerID current_player = PlayerID::Player1;
    shared_ptr<Player> current_player_ptr = players[0];
    PlayerID opposing_player = PlayerID::Player2;
    shared_ptr<Player> opposing_player_ptr = players[1];

    while (true) {
        bool ability_used = false;
        current_player_ptr->printPlayerView(cout);

        // Return false upon EOF or 'quit' and true upon a successful 'move'
        if (!conductPlayerTurn(current_player_ptr, ability_used)) {
            return PlayerID::Nobody;
        }

        // Return the current player if they have downloaded 4 data or the opponent has downloaded 4 viruses
        if (current_player_ptr->getDownloadedDataAmount() == DATA_DOWNLOADS_TO_WIN || 
            opposing_player_ptr->getDownloadedVirusAmount() == VIRUS_DOWNLOADS_TO_LOSE) {
            current_player_ptr->printPlayerView(cout);
            return current_player;
        }

        // Return the opposing player if they have downloaded 4 data or the current player has downloaded 4 viruses
        if (opposing_player_ptr->getDownloadedDataAmount() == DATA_DOWNLOADS_TO_WIN || 
            current_player_ptr->getDownloadedVirusAmount() == VIRUS_DOWNLOADS_TO_LOSE) {
            opposing_player_ptr->printPlayerView(cout);
            return opposing_player;
        }

        // Change which player's turn it is
        switch (current_player) {
            case PlayerID::Player1:
                current_player = PlayerID::Player2;
                current_player_ptr = players[1];
                opposing_player = PlayerID::Player1;
                opposing_player_ptr = players[0];
                break;
            case PlayerID::Player2:
                current_player = PlayerID::Player1;
                current_player_ptr = players[0];
                opposing_player = PlayerID::Player2;
                opposing_player_ptr = players[1];
                break;
        }
    }
}

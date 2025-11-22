module FourPlayerMode;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";
const std::string PLAYER3 = "Player 3";
const std::string PLAYER4 = "Player 4";

FourPlayerMode::FourPlayerMode(std::string ability1_order, std::string ability2_order,
				               std::string ability3_order, std::string ability4_order,
					           std::string link1_order, std::string link2_order,
					           std::string link3_order, std::string link4_order) : 
    GameMode{std::make_shared<FourPlayerBoard>()} {
    ability_orders.emplace_back(ability1_order);
    ability_orders.emplace_back(ability2_order);
    ability_orders.emplace_back(ability3_order);
    ability_orders.emplace_back(ability4_order);
    link_orders.emplace_back(link1_order);
    link_orders.emplace_back(link2_order);
    link_orders.emplace_back(link3_order);
    link_orders.emplace_back(link4_order);
    players.emplace_back(std::make_shared<Player>(PLAYER1, board, ability_orders[0]));
    players.emplace_back(std::make_shared<Player>(PLAYER2, board, ability_orders[1]));
    players.emplace_back(std::make_shared<Player>(PLAYER3, board, ability_orders[2]));
    players.emplace_back(std::make_shared<Player>(PLAYER4, board, ability_orders[3]));

    for (int i = 0; i < NUM_PLAYERS; ++i) {
        board->addPlayer(players[i], link_orders[i]);
    }
}

void FourPlayerMode::runGame() {

}

export module Player;

import <iostream>;
import <memory>;
import <map>;
import <vector>;
import <string>;
import Constants;
import Observer;
import Board;
import Link;
import Ability;
import LinkBoost;
import Firewall;
import Download;
import Scan;
import Polarize;
import Upgrade; 
import Theft;
import Obstacle;
import HTVirus;

export class Player : public Observer {
	int downloaded_virus_amount;
    int downloaded_data_amount;
	int ability_amount; // the remained unused ability amount
	bool lose;
	bool win;
	Board *board;
	std::vector<std::unique_ptr<Ability>> abilities;
	std::vector<Link *> owned_links;
	std::vector<Link *> downloaded_links;
	public:
		// Constructor
		Player(std::string name, Board *board, std::string abilitychosen = DEFAULT_ABILITY_ORDER);

		// getAbilityAmount() return the ability amount
		int getAbilityAmount();

		// getAbility(ability_id) return an Ability * for the ability stored on abilities with the given ability_id
		Ability * getAbility(int ability_id);

		// movable() return true if the player can still move a link. Otherwise, return false and 
		//   set lose to true
		bool movable();

		// getUsableAbilityAmount() return the amount of usable abilities
		int getUsableAbilityAmount();

		// isWin() return true if the player won, and false otherwise
		bool isWin();

		// isLose() return true if the player lost, and false otherwise
		bool isLose();

		// download(link_char) download the link with symbol link_char, checking whether the
		//   link was infected and if the player won/lost
		void download(char link_char) override;

		// addLink(link_char) add the link with symbol link_char as one of the owned_links
		void addLink(char link_char) override;

		// addAbility(ability_char) create and store the ability with symbol ability_char in abilities
		void addAbility(char ability_char) override;

		// removeAbility() remove the first unused ability and return it's ability character
		char removeAbility() override;

		// usingAbility(ability_id, command) use the ability with the given ability_id and 
		//   coresponding command
		void usingAbility(int ability_id, std::string command);

		// moveLink(command) move the link based on the given command
		void movingLink(std::string command);

		// displayAbility(os) display each ability to the ostream os
		void displayAbility(std::ostream &os);

		// printPlayerView(os) print the player's view of the board to the ostream os
		void printPlayerView(std::ostream &os);

		// printPlayer(os, hidden) print the number of downloaded links and link status of the
		//   player to the ostream os and hidden status
		void printPlayer(std::ostream &os, bool hidden);
};

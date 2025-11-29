module Player;

import <iostream>;
import <sstream>;
import <memory>;
import <map>;
import <vector>;
import <stdexcept>;
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

Player::Player(std::string name, Board *board, std::string abilitychosen) : Observer{name},
	downloaded_virus_amount{0}, downloaded_data_amount{0}, ability_amount{0}, lose{false}, win{false}, board{board} {
	char input;
	std::istringstream iss{abilitychosen};
	while (iss >> input) {
		addAbility(input);
	}
}

int Player::getAbilityAmount() { return ability_amount; }

Ability * Player::getAbility(int ability_ID) { 
	if (ability_ID >= 1 && ability_ID <= static_cast<int>(abilities.size())) {
		return abilities[ability_ID - 1].get();
	} else {
		return nullptr;
	}
}

bool Player::movable() {
	for (Link *link: owned_links) { // if any link is movable, return true
		if (!link->isDownloaded() && board->movable(link->getSymbol())) {
			return true;
		}
	}
	lose = true; // if no links are movable, the player loses
	return false;
}

int Player::getUsableAbilityAmount() {
	int count = 0; // counts the ability that one player can use
	for (size_t i = 0; i < abilities.size(); ++i) {
		Ability *ability = getAbility(i + 1);
		if (ability->isUsed()) {
			continue;
		} 
		switch (ability->getName()[0]) {
        	case 'L': // Link-boost
        	case 'P': // Polarize
        	case 'U': // Upgrade
				for (Link *link: owned_links) {
					if (!link->isDownloaded()) {
						++count; // can be used as long as you have a link on the board
						break;
					}
				}
            	break;
        	case 'O': // Obstacle
            	if (board->getObstacleTick() == 0) {
                	++count; // can be used only when there is no other obstacles placed
            	} // it is really impossible to be unable to place it physically, thus no checking on this
				break;
        	case 'H': // HTVirus
            	for (Link *link: owned_links) {
                	if (link->isVirus() && !link->isDownloaded()) {
                    	++count; // can used only when you have virus on the board
                    	break;
                	}
            	}
            	break;
        	default:
				++count; // other abilities can be used as long as the game keeps going
            	break;
    	}
	}
	return count;
}

bool Player::isWin() {
	return win;
}

bool Player::isLose() {
	return lose;
}

void Player::download(char link_char) {
	Link* link = board->getLink(link_char);
	link->Download();
	if (link->isInfected()) { // the download process for a infected virus
		if (downloaded_data_amount == 0) { // if no data downloaded
			for (Link *owned_link : owned_links) {
				if (!owned_link->isVirus() && !owned_link->isDownloaded()) {
					owned_link->setType(LinkType::Virus); // change a data on the board to virus
					break;
				}
			}
		} else {
			for (Link *downloaded_link: downloaded_links) {
				if (!downloaded_link->isVirus()) { // change all the downloaded data to virus
					downloaded_link->setType(LinkType::Virus);
					downloaded_data_amount -= 1;
					downloaded_virus_amount += 1;
				}
			}
		}
		downloaded_virus_amount += 1;		
	} else if (link->isVirus()) {
		downloaded_virus_amount += 1;
	} else {
		downloaded_data_amount += 1;
	}
	downloaded_links.emplace_back(link);
	
	if (downloaded_data_amount >= DATA_DOWNLOADS_TO_WIN) {
		win = true; // check the winning conditions
	}
	if (downloaded_virus_amount >= VIRUS_DOWNLOADS_TO_LOSE) {
		lose = true; // check the losing conditions
	}
}

void Player::addLink(char link_char) {
	owned_links.emplace_back(board->getLink(link_char));
}

void Player::addAbility(char ability_char) {
	switch (ability_char) {
		case 'L':
			abilities.emplace_back(std::make_unique<LinkBoost>(this, board));
			break;
		case 'F':
			abilities.emplace_back(std::make_unique<Firewall>(this, board));
			break;
		case 'D':
			abilities.emplace_back(std::make_unique<Download>(this, board));
			break;
		case 'S':
			abilities.emplace_back(std::make_unique<Scan>(this, board));
			break;
		case 'P':
			abilities.emplace_back(std::make_unique<Polarize>(this, board));
			break;
		case 'U':
			abilities.emplace_back(std::make_unique<Upgrade>(this, board));
			break;
		case 'T':
			abilities.emplace_back(std::make_unique<Theft>(this, board));
			break;
		case 'O':
			abilities.emplace_back(std::make_unique<Obstacle>(this, board));
			break;
		case 'H':
			abilities.emplace_back(std::make_unique<HTVirus>(this, board));
			break;
		default:
			throw std::invalid_argument("Invalid ability symbol.");
			break;
	}
	ability_amount += 1;
}

char Player::removeAbility() {
	Ability *ability = nullptr;
	for (size_t i = 0; i < abilities.size(); ++i) {
		if (!abilities[i].get()->isUsed()) { // find the first unused ability
			ability = abilities[i].get();
			break;
		}
	}
	if (ability == nullptr) {
		return NULL_ABILITY; // if no unused ability, return a state represents nothing removed
	}
	ability->markUsed(); // mark as used to represent removed
	ability_amount -= 1;
	return ability->getName()[0]; // return the type of the ability
}

void Player::usingAbility(int ability_ID, std::string command) {
	Ability *ability = getAbility(ability_ID);
	if (ability->isUsed()) {
		throw std::invalid_argument("Ability used.");
	}
	ability->operatingAbility(command); // use the ability
	ability_amount -= 1;
}

void Player::movingLink(std::string command) {
	std::istringstream iss{command};
	char link_char;
	std::string direction;
	if (!(iss >> link_char >> direction)) {
        throw std::invalid_argument("Invalid moving command.");
    }
	Link *link = board->getLink(link_char);
	if (link && link->getPlayer() == this) { // check if the link exists and belongs to the player
		board->updateLink(link_char, direction);
	} else {
		throw std::invalid_argument("You cannot move a link that is non-exist or belongs to another player.");
	}
}

void Player::displayAbility(std::ostream &os) {
	for (size_t i = 0; i < abilities.size(); ++i) {
		os << "(ID: " << i + 1 << ") " << abilities[i]->getName() << *getAbility(i + 1) << std::endl;
	}
	os << std::endl;
}

void Player::printPlayerView(std::ostream &os) {
	printPlayer(os, false);
	board->printBoard(os, this);
	os << std::endl;
}

void Player::printPlayer(std::ostream &os, bool hidden) {
	os << name << ":" << std::endl;
    os << "Downloaded: " << downloaded_data_amount << "D, " << downloaded_virus_amount << "V" << std::endl;
    os << "Abilities: " << ability_amount << std::endl;
    for (size_t i = 0; i < owned_links.size() / 2; ++i) {
        owned_links[i]->printLink(os, hidden);
    }
    os << std::endl;
    for (size_t i = owned_links.size() / 2; i < owned_links.size(); ++i) {
        owned_links[i]->printLink(os, hidden);
    }
	os << std::endl;		
}

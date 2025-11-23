import <iostream>;
import GameMode;
import TwoPlayerMode;
import FourPlayerMode;

using namespace std;

const std::string DEFAULT_ABILITY_ORDER = "LFDSP";
const std::string DEFAULT_LINK_ORDER = "V1V2V3V4D1D2D3D4";
const std::string AVAILABLE_ABILITIES = "LFDSP"; //add theft and other abilities

int main(int argc, char *argv[]) {
	// assume graphics do not exist yet
	std::string ability1_order = DEFAULT_ABILITY_ORDER;
	std::string ability2_order = DEFAULT_ABILITY_ORDER;
	std::string link1_order = DEFAULT_LINK_ORDER;
	std::string link2_order = DEFAULT_LINK_ORDER;

	bool ability1_order_set = true;
	bool ability2_order_set = true;
	bool link1_order_set = true;
	bool link2_order_set = true;
	bool graphics_set = true;

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			if (std::string(argv[i]) == "-ability1" && !ability1_order_set) {
				std::string order = std::string(argv[i + 1]);
				int order_length = order.length();
				if (order_length != 5) {
					throw std::invalid_argument("Invalid number of abilities.");
				}
				for (int i = 0; i < order_length; ++i) {
					if (AVAILABLE_ABILITIES.find(order[i]) == AVAILABLE_ABILITIES.npos) {
						throw std::invalid_argument("Listed ability does not exist.");
					}
				}
				ability1_order = order;
				++i;
				continue;
			}
			if (std::string(argv[i]) == "-ability2" && !ability2_order_set) {
				
			}
			if (std::string(argv[i]) == "-link1" && !link1_order_set) {

			}
			if (std::string(argv[i]) == "-link1" && !link2_order_set) {

			}
			if (std::string(argv[i]) == "-graphics" && !graphics_set) {
				// Code to enable graphics to be added
			}
			throw std::invalid_argument("Invalid command-line arguments.");
		}
	}

	std::unique_ptr<GameMode> RAIInet = 
		std::make_unique<TwoPlayerMode>(ability1_order, ability2_order, 
										link1_order, link2_order);
	RAIInet->operatingGame();
}

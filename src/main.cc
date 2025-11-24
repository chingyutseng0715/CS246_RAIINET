import <memory>;
import GameMode;
import TwoPlayerMode;
import FourPlayerMode;
import CommandLineProcessor;

const int PLAYERS = 2; // Client can change to 4

int main(int argc, char *argv[]) {
	// std::string ability1_order, ability2_order, link1_order, link2_order;
	CommandLineProcessor processor;
	ProcessedInput input = processor.processCommands(argc, argv, PLAYERS);

	std::unique_ptr<GameMode> RAIInet;
	switch (PLAYERS) {
		case 2:
			// RAIInet = std::make_unique<TwoPlayerMode>(ability1_order, ability2_order, link1_order, link2_order);
			RAIInet = std::make_unique<TwoPlayerMode>(input);
		case 4:
			RAIInet = std::make_unique<TwoPlayerMode>(input);
	}
	RAIInet->operatingGame();
}

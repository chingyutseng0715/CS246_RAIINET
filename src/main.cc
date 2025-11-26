import <memory>;
import GameMode;
import TwoPlayerMode;
import FourPlayerMode;
import CommandLineProcessor;

const int PLAYERS = 2; // Client can change to 4

int main(int argc, char *argv[]) {
	ProcessedInput input = processCommands(argc, argv, PLAYERS);

	std::unique_ptr<GameMode> RAIInet;
	switch (PLAYERS) {
		case 2:
			RAIInet = std::make_unique<TwoPlayerMode>(input);
			break;
		case 4:
			RAIInet = std::make_unique<FourPlayerMode>(input);
			break;
	}
	RAIInet->operatingGame();
}

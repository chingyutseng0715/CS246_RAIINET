import <memory>;
import GameMode;
import TwoPlayerMode;
import FourPlayerMode;
import CommandLineProcessor;

int main(int argc, char *argv[]) {
	ProcessedInput input = processCommands(argc, argv);

	std::unique_ptr<GameMode> RAIInet;
	switch (input.num_players) {
		case 2:
			RAIInet = std::make_unique<TwoPlayerMode>(input);
			break;
		case 4:
			RAIInet = std::make_unique<FourPlayerMode>(input);
			break;
	}
	RAIInet->operatingGame();
}

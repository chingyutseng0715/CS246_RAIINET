import <memory>;
import GameMode;
import CommandLineProcessor;

int main(int argc, char *argv[]) {
	ProcessedInput input = processCommands(argc, argv);

	GameMode RAIInet(input);
	RAIInet.operatingGame();
}

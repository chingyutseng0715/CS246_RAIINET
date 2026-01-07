
---

# CS246 project - RAllnet (ignore the following contents for now)

This is our CS246 project, aiming to build a board game(RAIINET), using CS246's object-oriented approach. It has two game modes:  two players/ four players. Each player trys to download as much data and as less virus in order to win the game. 

---

## Table of Contents

* [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)

---

## Installation

### Prerequisites

* C++20, g++-14 compiler, Linux with X11 graphics enabled

### Steps

1. **Clone the repository:**

   ```bash
   git clone https://github.com/chingyutseng0715/CS246_RAIINET
   ```

2. **Navigate to the project directory:**

   ```bash
   cd CS246_RAIINET/src
   ```

3. **Compile the files:**
   
   ```bash
   make
   ```

4. **Run the application:**

   ```bash
   ./RAllnet
   ```

---

## Usage

The following are the command used to operate the game.

### Command line
Use the following command
```bash
./RAIInet <arguments>
```
The followings are the rules for arguments
* ```-players <N>``` specifies the number of players. <N> is the number of players which can be either 2 or 4. If not specified, the default players would be 2.

* ```-ability1 <ABILITYSTRING>``` specifies the abilities for player 1 (this is a list of the 5 abilities player 1 will use). If not specified, use the default set of abilities (Link boost, Firewall, Download, Scan, Polarize in that order). The abilities are given by a string consisting of the first letter of each ability. The available letters are given here.

* ```-ability2 <ABILITYSTRING>``` is as above but for the second player. 

* ```-link1``` specifies the order of links player 1 receives. The string should list what each link a, b, ..., h should be. For example, the example board in the display section can be made with-p1order V1D4V3V2D3V4D2D1. If this argument is not specified, your program should use the ordering V1V2V3V4D1D2D3D4. •

* ```-link2``` is as above but for the second player. 

* ```-graphics``` should enable your graphical interface.


### Stardard input

---

## Contributing

We welcome contributions! If you'd like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Open a pull request to merge your changes.

Make sure to follow the code style and include tests (if applicable).

---

## License

This project is licensed under the [MIT License](LICENSE) - see the [LICENSE](LICENSE) file for details.

---

## Contact

For any questions, feel free to contact:

* **Name**: Your Name
* **Email**: [your.email@example.com](mailto:your.email@example.com)
* **GitHub**: [@yourusername](https://github.com/yourusername)

---

You can modify and adapt this template based on your project’s specific needs!

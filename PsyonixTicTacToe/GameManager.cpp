#include <iostream>
#include <limits>
#include "TicTacToe.h"

TicTacToe initialize() {
	//Initialize board and loop until valid input is recieved
	int N, M, K;
	do {
		std::cout << "Please enter game rules (n m k)" << std::endl;
		std::cin >> N >> M >> K;
		if (std::cin.fail() || N < 2 || M < 2 || K < 2) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please try again!" << std::endl;
		}
		else { break; }
	} while (true);
	return TicTacToe(N, M, K);
}

bool processWinner(char winner) {
	//Check winner and print appropriate message. Ask to play again and return answer
	if (winner == 'D') {
		std::cout << "Game ended in a draw! Play again? (Y/N)" << std::endl;
	}
	else {
		if (winner == 'X') {
			std::cout << "Player X has won! Play again? (Y/N)" << std::endl;
		}
		else {
			std::cout << "Player O has won! Play again? (Y/N)" << std::endl;
		}
	}
	char again;
	std::cin >> again;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return (again == 'Y') ? true : false;
}

bool processUndo(TicTacToe& ttt) {
	//Clear input buffer and ask to Undo. Return if successful- and print message if invalid request.
	char undo;
	std::cout << "Undo last move? Y if yes, any key if no." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> undo;
	if (undo == 'Y') {
		if (ttt.undo()) { return true; }
		std::cout << "No moves to undo!" << std::endl;
	}
	return false;
}

char processMove(TicTacToe& ttt) {
	//Clear input buffer and ask for Move until valid response is given. Return board status (C for continute or X/O/D for win/draw)
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int n, m;
	do {
		std::cout << "Player " << ttt.getPlayer() << " enter coordinates of move (n, m)" << std::endl;
		std::cin >> n >> m;
		if (!std::cin.fail() && ttt.move(n, m)) { return ttt.checkWin(n, m); }
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid Input!" << std::endl;
	} while (true);
}

char processGame(TicTacToe& ttt) {
	//Main game loop
	while (true) {
		ttt.print();
		if (!processUndo(ttt)) {
			char winner = processMove(ttt);
			if (winner != 'C') {
				ttt.print();
				return winner;
			}
		}
	}
}

void gameLoop() {
	while (true) {
		TicTacToe ttt = initialize();
		char winner = processGame(ttt);
		if (!processWinner(winner)) { break; }
	}
}
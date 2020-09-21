#include <iostream>
#include <limits>
#include "TicTacToe.h"

TicTacToe initialize() {
	int N, M, K;
	do {
		std::cout << "Please enter game rules (n m k)" << std::endl;
		std::cin >> N >> M >> K;
		if (std::cin.fail() || N<=0 || M<=0 || K<=0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please try again!" << std::endl;
		}
		else { break; }
	} while (true);
	return TicTacToe(N, M, K);
}

bool processWinner(char winner) {
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
	return (again=='Y') ? true : false;
}

bool processUndo(TicTacToe& ttt) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char undo;
	do {
		std::cout << "Undo last move? Y if yes, any key if no." << std::endl;
		std::cin >> undo;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input!" << std::endl;
		}
		else { break; }
	} while (true);
	if (undo == 'Y') {
		if (ttt.undo()) { return true; }
		std::cout << "No moves to undo!" << std::endl;
	}
	return false;
}

char processMove(TicTacToe& ttt) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int n, m;
	do {
		std::cout << "Player " << ttt.getPlayer() << " enter coordinates of move (n, m)" << std::endl;
		std::cin >> n >> m;
		if (!std::cin.fail() && ttt.move(n,m)) { return ttt.checkWin(n, m); }
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid Input!" << std::endl;
	} while (true);
}

char processGame(TicTacToe& ttt) {
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

int main() {
	while (true) {
		TicTacToe ttt = initialize();
		char winner = processGame(ttt);
		if (!processWinner(winner)) { break; }
	}
}
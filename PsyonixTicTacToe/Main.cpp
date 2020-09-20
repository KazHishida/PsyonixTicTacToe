#include <iostream>
#include "TicTacToe.h"

TicTacToe initialize() {
	int N, M, K;
	std::cout << "Please enter game rules (n m k)" << std::endl;
	std::cin >> N >> M >> K;
	return TicTacToe(N, M, K);
}

char processMoves(TicTacToe& ttt) {
	while (true) {
		std::cout << "Enter coordinates of next move (n m)" << std::endl;
		int n, m;
		std::cin >> n >> m;
		ttt.move(n, m);
		ttt.print();
		if (ttt.checkWin(n, m) != 'C') {
			return ttt.checkWin(n, m);
		}
	}
}

bool processEnd(char winner) {
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

int main() {
	TicTacToe ttt = initialize();
	bool cont = true;
	while (cont) {
		char winner = processMoves(ttt);
		cont = processEnd(winner);
	}
}

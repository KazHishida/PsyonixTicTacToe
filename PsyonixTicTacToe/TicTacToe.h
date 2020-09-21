#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <iostream>
#include <utility>
class Board {
public:
	Board(int N, int M);
	int getN();
	int getM();
	char get(int n, int m);
	void place(int n, int m, char player);
private:
	std::vector<std::vector<char>> board;
};
class TicTacToe {
	public:
		TicTacToe(int N, int M, int K);
		void print();
		bool move(int n, int m);
		char checkWin(int n, int m);
		bool undo();
		char getPlayer();
	private:
		Board board;
		int K;
		char player;
		std::vector<std::pair<int, int>> moves;
};
#endif
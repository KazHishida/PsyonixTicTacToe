#include "TicTacToe.h"


Board::Board(int N, int M) : board(N, std::vector<char>(M, ' ')) { }
int Board::getN() { return board.size(); }
int Board::getM() {	return board[0].size(); }
char Board::get(int n, int m) { return (n < getN() && m < getM() && m>=0 && n>=0) ? board[n][m] : 'e'; } //Will return 'e' for error if invalid
void Board::place(int n, int m, char player) { board[n][m] = player; }

TicTacToe::TicTacToe(int n, int m, int k) : board(n, m), K(k), player('X') {}
bool TicTacToe::move(int n, int m) {
	if (board.get(n, m) == ' ') {
		board.place(n, m, player);
		player = (player == 'X') ? 'O' : 'X'; //Swap player
		moves.push_back(std::make_pair(n, m));
		return true;
	}
	return false;
}
bool TicTacToe::undo() {
	if (moves.size() > 0) {
		std::pair<int, int> move = moves.back();
		board.place(move.first, move.second, ' ');
		player = (player == 'X') ? 'O' : 'X'; //Swap player
		moves.pop_back();
		return true;
	}
	return false;
}
char TicTacToe::getPlayer() {
	return player;
}
void TicTacToe::print() {
	for (int n = 0; n < board.getN(); ++n) {
		for (int m = 0; m < board.getM()-1; ++m) {
			std::cout<<board.get(n, m)<<"|";
		}
		std::cout << board.get(n, board.getM() - 1);
		if (n != board.getN() - 1) {
			std::cout << std::endl;
			for (int i = 0; i < board.getM()-1; ++i) {
				std::cout << "--";
			}
			std::cout << "-" << std::endl;
		}
		else {
			std::cout << std::endl;
		}
	}
}
char TicTacToe::checkWin(int n, int m) {
	/*Check for win by starting at most recent position, since that is the only way
	* a win can occur. Then check horizontal, vertical, and both diagonals by iterating
	* forwards and backwards to check for consecutive players. If K consecutive are
	* counted, then return winner. This could have been written more elegantly,
	* but is written to run in O(K).
	*/
	int toWin = K - 1;
	char winner = (player == 'X') ? 'O' : 'X';
	//Check horizontally
	for (int i = 1; i < K; ++i) {
		if (board.get(n, m + i) == winner) { --toWin; }
		else { break; }
	}
	for (int i = 1; i < K; ++i) {
		if (board.get(n, m - i) == winner) { --toWin; }
		else { break; }
	}
	if (toWin) { toWin = K - 1; }
	else { return winner; }
	//Check vertically
	for (int i = 1; i < K; ++i) {
		if (board.get(n + i, m) == winner) { --toWin; }
		else { break; }
	}
	for (int i = 1; i < K; ++i) {
		if (board.get(n - i, m) == winner) { --toWin; }
		else { break; }
	}
	if (toWin) { toWin = K - 1; }
	else { return winner; }
	//Check forward diag
	for (int i = 1; i < K; ++i) {
		if (board.get(n - i, m + i) == winner) { --toWin; }
		else { break; }
	}
	for (int i = 1; i < K; ++i) {
		if (board.get(n + i, m - i) == winner) { --toWin; }
		else { break; }
	}
	if (toWin) { toWin = K - 1; }
	else { return winner; }
	//Check backward diag
	for (int i = 1; i < K; ++i) {
		if (board.get(n + i, m + i) == winner) { --toWin; }
		else { break; }
	}
	for (int i = 1; i < K; ++i) {
		if (board.get(n - i, m - i) == winner) { --toWin; }
		else { break; }
	}
	if (toWin) { toWin = K - 1; }
	else { return winner; }
	//Make sure board isn't full, signifying a draw
	for (int n = 0; n < board.getN(); ++n) {
		for (int m = 0; m < board.getM(); ++m) {
			if (board.get(n, m) == ' ') {
				return 'C';
			}
		}
	}
	return 'D';
}
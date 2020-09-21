#include "TicTacToe.h"
//Helper functions
char swapPlayer(char curPlayer) { return (curPlayer == 'X') ? 'O' : 'X'; }

//Defining Board
Board::Board(int N, int M) : board(N, std::vector<char>(M, ' ')) { }
int Board::getN() { return board.size(); }
int Board::getM() {	return board[0].size(); }
char Board::get(int n, int m) { return (n < getN() && m < getM() && m>=0 && n>=0) ? board[n][m] : 'e'; } //Will return 'e' for error if invalid
void Board::place(int n, int m, char player) { board[n][m] = player; }

//Defining TicTacToe
TicTacToe::TicTacToe(int n, int m, int k) : board(n, m), K(k), player('X') {}
char TicTacToe::getPlayer() { return player; }
bool TicTacToe::move(int n, int m) {
	//Place move, process player change, and add to moves stack for undo's
	if (board.get(n, m) == ' ') {
		board.place(n, m, player);
		player = swapPlayer(player);
		moves.push(std::make_pair(n, m));
		return true;
	}
	return false;
}
bool TicTacToe::undo() {
	//Undo move, process player change, and remove from move stack
	if (moves.size() > 0) {
		std::pair<int, int> move = moves.top();
		board.place(move.first, move.second, ' ');
		player = swapPlayer(player);
		moves.pop();
		return true;
	}
	return false;
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
	* counted, then return winner.
	*/
	char winner = (player == 'X') ? 'O' : 'X';
	int toWinHor = K - 1, toWinVer = K - 1, toWinLDiag = K - 1, toWinRDiag = K - 1;
	bool hor = true, ver = true, lDiag = true, rDiag = true;
	//Check for increasing consecutive values
	for (int i = 1; i < K; ++i) {
		if (hor && board.get(n, m + i) == winner) { --toWinHor; }
		else { hor = false; }
		if (ver && board.get(n + i, m) == winner) { --toWinVer; }
		else { ver = false; }
		if (lDiag && board.get(n + i, m - i) == winner) { --toWinLDiag; }
		else { lDiag = false; }
		if (rDiag && board.get(n + i, m + i) == winner) { --toWinRDiag; }
		else { rDiag = false; }
	}
	//Reset and check for decreasing consecutive values
	hor = ver = lDiag = rDiag = true;
	for (int i = 1; i < K; ++i) {
		if (hor && board.get(n, m - i) == winner) { --toWinHor; }
		else { hor = false; }
		if (ver && board.get(n - i, m) == winner) { --toWinVer; }
		else { ver = false; }
		if (lDiag && board.get(n - i, m + i) == winner) { --toWinLDiag; }
		else { lDiag = false; }
		if (rDiag && board.get(n - i, m - i) == winner) { --toWinRDiag; }
		else { rDiag = false; }
	}
	if (!toWinHor || !toWinVer || !toWinLDiag || !toWinRDiag) { return winner; }
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
#pragma once
#include "Move.h"
#include <stack>

enum _Move{legal, illegal, no_move};

enum _Direction { _left, _right, _up, _down, left_up, left_down, right_up, right_down };

class Board {
public:
	//constructor
	Board(int to_win); // to_win is the winner

	//Confirm the move
	void Play(const Move &next_step);  // pre: player must be legal
	_Move IsValid(const Move & step) const;
	void Change_it(const Move & start, int change_to);

	//Evaluate and win?
	void count();
	int Winner();
	int Evaluate();

	// Find the next_step
	bool Legal_move(std::stack<Move> & moves) const;

	bool Done();
	void Print() const;
	bool Better(int value, int old_value) const;//比较两个值那个对先手有利
	int Worst_case() const;
	int Moves_done();
	void Skip();

private:
	int board[10][10]; // 合法的走法是[1-8][1-8]
	int move_done;
	int board_used;
	int winner; // move_done % 2 + 1 为 winner
	int player_one; // winner
	int player_two;
};
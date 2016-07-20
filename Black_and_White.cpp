// Black_and_White.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Board.h"
#include <stack>
#include <iostream>

using namespace std;

int Look_ahead(Board & game, Move & recommanded, int depth = 2)
{
	if (game.Done() || depth <= 0)
		return game.Evaluate();
	stack<Move> next_step;
	bool moved = game.Legal_move(next_step);
	int value, best_value = game.Worst_case();
	while (!next_step.empty())
	{
		Move do_it, replay;
		do_it = next_step.top();
		Board new_game = game;
		new_game.Play(do_it);
		//new_game.Print();
		value = Look_ahead(new_game,replay, depth - 1);
		if (game.Better(value,best_value)) {
			best_value = value;
			recommanded = do_it;
		}
		next_step.pop();
	}
	if (!moved)
		game.Skip();
	return best_value;
}

int main()
{
	Board Config(1);
	Move recommended;
	int x, y;
	int wanted_depth = 2;
	do
	{
		Config.Print();
		cout << "Your turn:" << endl;
		cout << "X:";
		cin >> x;
		cout << "Y:";
		cin >> y;
		Move first(y, x);
		if (Config.IsValid(first) != legal)
		{
			cout << "The step is invalid! Please try again." << endl;
		}
		else
		{
			Config.Play(first);
			Config.Print();
			break;
		}
	} while (1);
	while (!Config.Done())
	{
		Look_ahead(Config, recommended, wanted_depth);
		Config.Play(recommended);
		cout << "Computer:" << endl;
		Config.Print();
		if (Config.Done())break;
		do
		{
			stack<Move> can;
			Config.Legal_move(can);
			if (can.size() == 0)
			{
				cout << "Unfortunatly, you have no place to go. Your turn is skipped!" << endl;
				Config.Skip();
				break;
			}
			cout << "Your turn:" << endl;
			cout << "X:";
			cin >> x;
			cout << "Y:";
			cin >> y;
			Move me(y, x);
			if (Config.IsValid(me) != legal)
			{
				cout << "The step is invalid! Please try again." << endl;
			}
			else
			{
				Config.Play(me);
				Config.Print();
				break;
			}
		} while (1);
		if (Config.Moves_done() + wanted_depth > 64)
			wanted_depth--;
	}
	if (Config.Winner() == 1) cout << "Game over with computer win." << endl;
	else if (Config.Winner() == 2) cout << "Game over with you win." << endl;//impossible
	else cout << "Game over with a draw." << endl;//only when you go (1,1) at first step.
    return 0;
}


#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board(int to_win):move_done(4),winner(to_win),player_two(0),player_one(0),board_used(4)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			board[i][j] = 0;
	board[4][4] = board[5][5] = 1;
	board[4][5] = board[5][4] = 2;
}

void Board::Play(const Move & next_step)
{
	board[next_step.x][next_step.y] = move_done % 2 + 1;
	Change_it(next_step, move_done % 2 + 1);
	board_used++;
	move_done++;
}

_Move Board::IsValid(const Move & step) const
{
	if (board[step.x][step.y] == 0)
	{
		int player = move_done % 2 + 1;
		int x = step.x, y = step.y;
		bool first_time = true;
		// 检查行
		for (int j = y + 1; j < 9; j++) // right
		{
			if (first_time) 
			{
				first_time = false;
				if (board[x][j] == player)
					break;
				if (board[x][j] == 0)
					break;
			}
			else 
			{
				if (board[x][j] == player)
					return legal;
				else if (board[x][j] == 0)
					break;
			}
			
		}
		first_time = true;
		for (int j = y - 1; j > 0; j--) // left
		{
			if (first_time)
			{
				first_time = false;
				if (board[x][j] == player)
					break;
				else if (board[x][j] == 0)
					break;
			}
			else
			{
				if (board[x][j] == player)
					return legal;
				else if (board[x][j] == 0)
					break;
			}			
		}
		
		// 检查列
		first_time = true;
		for (int i = x + 1; i < 9; i++)// down
		{
			if (first_time)
			{
				first_time = false;
				if (board[i][y] == player)
					break;
				else if (board[i][y] == 0)
					break;
			}
			else
			{
				if (board[i][y] == player)
					return legal;
				else if (board[i][y] == 0)
					break;
			}
		}
		first_time = true;
		for (int i = x - 1; i < 9; i--)// up
		{
			if (first_time)
			{
				first_time = false;
				if (board[i][y] == player)
					break;
				else if (board[i][y] == 0)
					break;
			}
			else
			{
				if (board[i][y] == player)
					return legal;
				else if (board[i][y] == 0)
					break;
			}
		}

		// 检查对角线
		int temp_x = x - 1, temp_y = y - 1;

		// 左上
		first_time = true;
		while (temp_x > 0 && temp_y > 0)
		{
			if (first_time)
			{
				first_time = false;
				if (board[temp_x][temp_y] == player)
					break;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			else
			{
				if (board[temp_x][temp_y] == player)
					return legal;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			temp_x--;
			temp_y--;
		}

		// 右上
		temp_x = x - 1;
		temp_y = y + 1;
		first_time = true;
		while (temp_x > 0 && temp_y < 9)
		{
			if (first_time)
			{
				first_time = false;
				if (board[temp_x][temp_y] == player)
					break;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			else
			{
				if (board[temp_x][temp_y] == player)
					return legal;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			temp_x--;
			temp_y++;
		}

		// 左下
		temp_x = x + 1;
		temp_y = y - 1;
		first_time = true;
		while (temp_x < 9 && temp_y > 0)
		{
			if (first_time)
			{
				first_time = false;
				if (board[temp_x][temp_y] == player)
					break;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			else
			{
				if (board[temp_x][temp_y] == player)
					return legal;
				else if (board[temp_x][temp_y] == 0)
					break;
			}			
			temp_x++;
			temp_y--;
		}

		// 右下
		temp_x = x + 1;
		temp_y = y + 1;
		first_time = true;
		while (temp_x < 9 && temp_y < 9)
		{
			if (first_time)
			{
				first_time = false;
				if (board[temp_x][temp_y] == player)
					break;
				else if (board[temp_x][temp_y] == 0)
					break;
			}
			else
			{
				if (board[temp_x][temp_y] == player)
					return legal;
				else if (board[temp_x][temp_y] == 0)
					break;
			}			
			temp_x++;
			temp_y++;
		}
	}
	return illegal;
}

void Board::Change_it(const Move & start, int change_to)
{
	int x = start.x, y = start.y;
	bool first_time = true;
	// 检查行
	for (int j = y + 1; j < 9; j++) // right
	{
		if (first_time)
		{
			first_time = false;
			if (board[x][j] == change_to)
				break;
			if (board[x][j] == 0)
				break;
		}
		else
		{
			if (board[x][j] == change_to)
			{
				for (int k = y + 1; k < j; k++) {
					board[x][k] = change_to;
				}
				break;
			}
			else if (board[x][j] == 0)
				break;
		}

	}
	first_time = true;
	for (int j = y - 1; j > 0; j--) // left
	{
		if (first_time)
		{
			first_time = false;
			if (board[x][j] == change_to)
				break;
			else if (board[x][j] == 0)
				break;
		}
		else
		{
			if (board[x][j] == change_to)
			{
				for (int k = y - 1; k > j; k--) {
					board[x][k] = change_to;
				}
				break;
			}
			else if (board[x][j] == 0)
				break;
		}
	}

	// 检查列
	first_time = true;
	for (int i = x + 1; i < 9; i++)// down
	{
		if (first_time)
		{
			first_time = false;
			if (board[i][y] == change_to)
				break;
			else if (board[i][y] == 0)
				break;
		}
		else
		{
			if (board[i][y] == change_to)
			{
				for (int k = x + 1; k < i; k++) {
					board[k][y] = change_to;
				}
				break;
			}
			else if (board[i][y] == 0)
				break;
		}
	}
	first_time = true;
	for (int i = x - 1; i < 9; i--)// up
	{
		if (first_time)
		{
			first_time = false;
			if (board[i][y] == change_to)
				break;
			else if (board[i][y] == 0)
				break;
		}
		else
		{
			if (board[i][y] == change_to)
			{
				for (int k = x - 1; k > i; k--) {
					board[k][y] = change_to;
				}
				break;
			}
			else if (board[i][y] == 0)
				break;
		}
	}

	// 检查对角线
	int temp_x = x - 1, temp_y = y - 1;

	// 左上
	first_time = true;
	while (temp_x > 0 && temp_y > 0)
	{
		if (first_time)
		{
			first_time = false;
			if (board[temp_x][temp_y] == change_to)
				break;
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		else
		{
			if (board[temp_x][temp_y] == change_to)
			{
				int t_x = x - 1, t_y = y - 1;
				while (t_x > temp_x && t_y > temp_y)
				{
					board[t_x][t_y] = change_to;
					t_x--;
					t_y--;
				}
				break;
			}
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		temp_x--;
		temp_y--;
	}

	// 右上
	temp_x = x - 1;
	temp_y = y + 1;
	first_time = true;
	while (temp_x > 0 && temp_y < 9)
	{
		if (first_time)
		{
			first_time = false;
			if (board[temp_x][temp_y] == change_to)
				break;
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		else
		{
			if (board[temp_x][temp_y] == change_to)
			{
				int t_x = x - 1, t_y = y + 1;
				while (t_x > temp_x && t_y < temp_y)
				{
					board[t_x][t_y] = change_to;
					t_x--;
					t_y++;
				}
				break;
			}
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		temp_x--;
		temp_y++;
	}

	// 左下
	temp_x = x + 1;
	temp_y = y - 1;
	first_time = true;
	while (temp_x < 9 && temp_y > 0)
	{
		if (first_time)
		{
			first_time = false;
			if (board[temp_x][temp_y] == change_to)
				break;
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		else
		{
			if (board[temp_x][temp_y] == change_to)
			{
				int t_x = x + 1, t_y = y - 1;
				while (t_x < temp_x && t_y > temp_y)
				{
					board[t_x][t_y] = change_to;
					t_x++;
					t_y--;
				}
				break;
			}
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		temp_x++;
		temp_y--;
	}

	// 右下
	temp_x = x + 1;
	temp_y = y + 1;
	first_time = true;
	while (temp_x < 9 && temp_y < 9)
	{
		if (first_time)
		{
			first_time = false;
			if (board[temp_x][temp_y] == change_to)
				break;
			else if (board[temp_x][temp_y] == 0)
				break;
		}
		else
		{
			if (board[temp_x][temp_y] == change_to)
			{
				int t_x = x + 1, t_y = y + 1;
				while (t_x < temp_x && t_y < temp_y)
				{
					board[t_x][t_y] = change_to;
					t_x++;
					t_y++;
				}
				break;
			}
			else if (board[temp_x][temp_y] == 0)
				break;
		}		
		temp_x++;
		temp_y++;
	}
}

void Board::count()
{
	player_one = player_two = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (board[i][j] == winner)
				player_one++;
			else if (board[i][j] != 0)
				player_two++;
		}
	}
}

int Board::Winner()
{
	count();
	if (player_two < player_one)
		return 2;
	if (player_two > player_one)
		return 1;
	else
		return 0;
}

int Board::Evaluate()
{
	if (Winner() == winner) return (64 - move_done);
	if (Winner() == 0) return 0;
	return move_done - 64;
}

bool Board::Done()
{
	return (board_used == 64);
}

void Board::Print() const
{
	string coordinate[] = { "    1  2  3  4  5  6  7  8" , "1  ","2  " ,"3  " ,"4  " ,"5  " ,"6  " ,"7  ","8  " };
	cout << coordinate[0] << endl;
	for (int i = 1; i < 9; i++)
	{
		cout << coordinate[i];
		for (int j = 1; j < 9; j++)
		{
			cout << " ";
			if (board[i][j] == 0)
				cout << "_";
			else
				cout << board[i][j];
			cout << " ";
		}
		cout << endl;
	}
}

bool Board::Better(int value, int old_value) const
{
	if ((move_done % 2 + 1) != winner) return value < old_value;
	else
		return value > old_value;
}

int Board::Worst_case() const
{
	if ((move_done % 2 + 1) == winner) return -65;
	else return 65;
}

bool Board::Legal_move(std::stack<Move>& moves) const
{
	bool moved = false;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			Move try_it = Move(i, j);
			if (IsValid(try_it) == legal)
			{
				moved = true;
				moves.push(try_it);
			}
		}
	}
	return moved;
}

int Board::Moves_done()
{
	return move_done;
}

void Board::Skip()
{
	move_done++;
}

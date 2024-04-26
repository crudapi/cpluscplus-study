// CMakeSnakeProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSnakeProject.h"

#include <list>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>//随机数
#include <chrono>//日期时间
#include <cassert>

using namespace std;

// 游戏的任意位置 只有三种情况：什么也没有；蛇的身体；食物
enum class MatrixValueEnum
{
	NOTHING = '0', SNAKE_BODY = '1', FOOD = '2'
};

class Model
{
public:
	size_t GetRow(void) { return m_playBoard.size(); }
	size_t GetCol(void) { return m_playBoard.at(0).size(); }
	void EatFood(pair<int, int> nextPosition)
	{
		//new snake head
		m_snakeBody.push_front(nextPosition);
		//直接吃掉，尾巴不用移动
		m_playBoard[nextPosition.first][nextPosition.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY);
	}
	bool PushFoodAt(int row, int col)
	{
		bool result = false;
		if (m_playBoard[row][col] == static_cast<char>(MatrixValueEnum::NOTHING))
		{
			m_playBoard[row][col] = static_cast<char>(MatrixValueEnum::FOOD);
			result = true;
		}
		return result;
	}
	// 判断 (i,j) 处是否是一个食物
	bool ExistFood(int row, int col) const
	{
		//返回 坐标(i,j)处是否是有蛇的食物可以吃
		//(8) your code

		return m_playBoard[row][col] == static_cast<char>(MatrixValueEnum::FOOD);
	}
	void IncreaseOnlyBody(pair<int, int> nextPosition)
	{
		m_snakeBody.push_front(nextPosition);
	}
	void AppendToBoard(const vector<char>& lineData)
	{
		m_playBoard.push_back(lineData);
	}
	//撞到墙壁或者蛇自己的身体就结束游戏
	bool IsGameOver(int go_to_row, int go_to_col) const
	{
		//判断游戏是否已经结束了
		// go_to_row go_to_col 是蛇的头打算要去的目的地，这个目的地会导致gomeover
		// 比如超出了游戏界面（下标越界）
		// 比如撞到了蛇的身体
		//(5) your code ： row out of range, col out of range, snake body ahead
		size_t row = m_playBoard.size();
		size_t col = m_playBoard.at(0).size();
		if (go_to_row >= row || go_to_col >= col || go_to_row < 0 || go_to_col < 0)
		{
			return true;
		}
		else if (m_playBoard[go_to_row][go_to_col] == static_cast<char>(MatrixValueEnum::SNAKE_BODY)) {
			return true;
		}

		return false;
	}
	// 计算蛇的头移动一次后的新坐标
	std::pair<int, int> GetNextPosition(int step_row, int step_column) const
	{
		//根据蛇的头的位置，以及一个移动的向量 (i,j) 得到蛇头部打算要去的新目的地的坐标
		auto oldPosition = GetCurrentPosition();
		//(7) your code
		auto newRow = oldPosition.first + step_row;
		auto newColumn = oldPosition.second + step_column;
		return std::make_pair(newRow, newColumn);
	}
	// 获取蛇的头的坐标
	std::pair<int, int> GetCurrentPosition(void) const
	{
		//返回蛇 的头的坐标，是m_snakeBody的第一个元素的值
		//（6） your code : snake body 's front element
		auto front = m_snakeBody.front();
		return front;
	}
	void MoveOneStepTo(pair<int, int> nextPosition)
	{
		//snake tail move to snake new head
		//new snake head
		//尾巴移动 
		auto head = nextPosition;
		auto tail = m_snakeBody.back();
		m_playBoard[tail.first][tail.second] = static_cast<char>(MatrixValueEnum::NOTHING);
		m_playBoard[head.first][head.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY);
		m_snakeBody.push_front(head);
		m_snakeBody.pop_back();
	}
	// 在界面上生成一个新的食物给蛇吃
	void CreateFood(void)
	{
		// 生成一个新的食物给蛇来吃
		// 随机生成一个新的位置，但是这个位置可能已经是蛇的身体了
		// 所以，需要用一个循环不断的重复在一个新生成的随机位置放置食物
		// 直到放置成功为止
		do
		{
			auto seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 g(seed);  // mt19937 is a standard mersenne_twister_engine
			//生成新的随机的坐标
			//随机数的用法：https://blog.csdn.net/calmreason/article/details/72655060
			//(9) your code
			int row = g() % GetRow();
			int col = g() % GetCol();

			// 在新坐标处放置一个食物，记得检查可以放才能放
			// 一旦放好，记得退出循环，让程序继续执行
			//(10) your code : push food at row, col. if ok , break this loop.
			if (m_playBoard[row][col] != static_cast<char>(MatrixValueEnum::SNAKE_BODY)) {
				PushFoodAt(row, col);
				break;
			}
		} while (true);
	}
	//this function help your find bug easyly
	void ShowBoardForTest(ostream& os) const
	{
		for (size_t row = 0; row < m_playBoard.size(); row++)
		{
			for (size_t col = 0; col < m_playBoard[row].size(); col++)
			{
				auto element = m_playBoard[row][col];
				os << element << " ";
			}
			os << std::endl;
		}
	}
	void ShowGame(ostream& os) const
	{
		auto headPosition = m_snakeBody.front();
		for (size_t row = 0; row < m_playBoard.size(); row++)
		{
			for (size_t col = 0; col < m_playBoard[row].size(); col++)
			{
				auto element = m_playBoard[row][col];
				//打印蛇的头，其实这个位置的内存值是蛇的身体;存储的时候部分蛇的头和身的身体
				//，只有显示的时候才通过在队列中的位置区分
				if (row == headPosition.first && col == headPosition.second)
				{
					os << "@" << " ";
				}
				//打印食物，内存中的 '2' 打印成 $
				else if (element == static_cast<char>(MatrixValueEnum::FOOD))
				{
					os << "$" << " ";
				}
				//打印空白，内存中的 '0' 打印成 '_'
				else if (element == static_cast<char>(MatrixValueEnum::NOTHING))
				{
					os << "_" << " ";
				}
				// snake body
				else if (element == static_cast<char>(MatrixValueEnum::SNAKE_BODY))
				{
					os << "#" << " ";
				}
				else
				{
					assert(false);
				}
			}
			os << std::endl;
		}
	}
public:
	vector<vector<char>> m_playBoard;// 整个游戏的数据（二维数组）
	list<pair<int, int>> m_snakeBody;// 蛇的身体数据
};

class Control
{
public:
	// 用户输入一个字符（e/s/f/d），决定将蛇的头部往哪个方向移动
	// 移动蛇的头的坐标(x,y) = (x,y) + (row_step, column_step)
	bool GoAhead(char userInputDirection)
	{
		switch (userInputDirection)
		{
		case 'w':
		case 'W':
			//行往上移动的逻辑：往上移动 1 行（最上面的第一行的行号为 0，看文章中的图），列不移动 
			return GoAhead(/*row_step*/-1, /*column_step*/0);
		case 'a':
		case 'A':
			return GoAhead(0, -1);//类比往上移动的逻辑
		case 'd':
		case 'D':
			return GoAhead(0, +1);//类比往上移动的逻辑
		case 's':
		case 'S':
			return GoAhead(+1, 0);//类比往上移动的逻辑
		default:
			return true;
		}
	}
	bool LoadPlayDataFromFile(istream& fin)
	{
		std::string line;
		std::getline(fin, line);
		std::istringstream iss(line);// 字符串流 https://zhuanlan.zhihu.com/p/441027904
		int row_count = 0, column_count = 0;
		//读取行数和列数
		//(1) your code
		//read board size : row and col . 
		//see https://blog.csdn.net/calmreason/article/details/126686679
		iss >> row_count >> column_count;

		for (int row = 0; row < row_count; row++)
		{
			std::vector<char> lineData;
			std::getline(fin, line);
			std::istringstream lineDataIss(line);
			for (int column = 0; column < column_count; column++)
			{
				char element;
				//读取一个元素
				// (2) your code
				//  read data from istringstream , and store it to line data
				//  see : https://blog.csdn.net/calmreason/article/details/126736091
				lineDataIss >> element;
				lineData.push_back(element);

				//将组成蛇的头1存放到蛇m_snakeBody容器中，蛇一开始没有身体，只有一个蛇头
				//判断两个char相等即可
				if (element == '1')
				{
					//(3) your code   IncreaseOnlyBody
					pair<int, int> snakePair(row, column);
					m_model.m_snakeBody.push_back(snakePair);
				}
			}
			//将第一行数据存放到二维数组中，作为第一维的一个元素（子数组）
			//(4) your code : AppendToBoard  lineData
			m_model.m_playBoard.push_back(lineData);
		}
		if (m_model.m_snakeBody.empty())
		{
			cout << "snake body is empty! init game failed." << endl;
			assert(false);
			return false;
		}
		return true;
	}
	//行值移动的步长 row_step，列值移动的步长 column_step
	//往上是行之减小的方向，往下是行值增加的方向；列是往左列值减小，往右列值增大
	bool GoAhead(int row_step, int column_step)
	{
		//m_model内部存储了当前位置 currentPosition
		// nextPosition = currentPostion + (row_step, column_step)
		auto nextPosition = m_model.GetNextPosition(row_step, column_step);
		// 首先判断游戏是否已经结束
		if (m_model.IsGameOver(nextPosition.first, nextPosition.second))
		{
			return false;
		}
		// 判断nextPosition 处是否有食物
		// 如果有食物，就吃掉这个食物
		// 并生成一个新的食物
		if (m_model.ExistFood(nextPosition.first, nextPosition.second))
		{
			// (11) your code
			// EatFood at nextPosition
			m_model.EatFood(nextPosition);
			// create one food use CreateFood
			m_model.CreateFood();

		}
		// 如果 nextPosition 处没有食物，就移动蛇的身体
		else
		{
			// (12) your code 
			// MoveOneStepTo nextPosition
			m_model.MoveOneStepTo(nextPosition);
		}

		return true;
	}

	Model m_model;
};

class Snake
{

public:
	// 从文件中加载界面数据，存放到内部容器中，再根据容器内容绘制界面
	bool LoadPlayDataFromFile(const std::string& file)
	{
		std::ifstream fin(file);
		if (!fin)
		{
			std::cout << "can not open file " << file << endl;
			return false;
		}
		auto result = m_control.LoadPlayDataFromFile(fin);

		return result;
	}
	// 开始游戏
	void Play(void);
private:

	// 打印贪吃蛇游戏，将界面和内存之间的数据对应起来
	// 界面     内存
	// '_'  <== '0'
	// '$'  <== '2'
	// '#'  <== '1'
	// '@'  <== '1'
	void PrintMatrix(void) const
	{
		//test code, remove it while your code is finished.
		m_control.m_model.ShowBoardForTest(cout);

		m_control.m_model.ShowGame(cout);
	}

private:
	Control m_control;
};

void Snake::Play(void)
{
	//游戏一直进行，直到 Game Over ，才会退出。
	while (true)
	{
		/*清屏，这不是C++的一部分，是系统调用。
		  这个语句执行的快慢与代码无关，与控制台用户自己设置的缓冲区大小有关。
		*/
		system("cls");
		//输出游戏界面：棋盘
		PrintMatrix();
		//输出提示语
		std::cout << "direction: W(up) A(left) S(down) D(right)\n";
		std::cout << "$: food\n";
		std::cout << "@: snake head\n";
		std::cout << "#: snake tail\n";

		char direction;
		std::cin >> direction;
		//往前走一步，如果判断无法往前走到用户指定的位置，就退出程序（比如，蛇咬到了自己、撞到了墙壁）
		if (!m_control.GoAhead(direction))
		{
			std::cout << "Game Over!" << std::endl;
			break;
		}
	}
}


int main(int argc, char** argv)
{
	//创建游戏对象
	Snake snake;
	//读取文本文件，加载游戏数据
	if (snake.LoadPlayDataFromFile("data.txt"))
	{
		snake.Play();//整个游戏都在这个函数里
	}
	else//加载文件失败，退出程序
	{
		cout << "LoadPlayDataFromFile data.txt failed!" << endl;
		assert(false);

	}

	return 0;
}
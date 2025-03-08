#include <iostream>
#include "Button.h"
#include <new>
#include <stdlib.h>

//using namespace std;

bool CheckIMatching(bool IsExist[][10], int x0, int y0, int x1, int y1) {
//Checking I moving
	if (x0 == x1) {
		if (y0 > y1) std::swap(y0, y1);
		for (int i = y0 + 1;i < y1;++i) 
			if (IsExist[x1][i] == false) return false;
			//Phần tử còn tồn tại gọi là false còn không tồn tại gọi là true
	}
	else if (y0 == y1) {
		if (x0 > x1) std::swap(x0, x1);
		for (int i = x0 + 1;i < x1;++i)
			if (IsExist[i][y1] == false) return false;
			//Phần tử còn tồn tại gọi là false còn không tồn tại gọi là true
	}
	if (x1 != x0 && y1 != y0) return false;
	return true;
}

bool checkLMatching(bool IsExist[][10], int x0, int y0, int x1, int y1){
//Checking L Moving
	if (x0 == x1 || y0 == y1)	return false;
	if (IsExist[x0][y1] == false && IsExist[x1][y0] == false)	return false;
	if (IsExist[x0][y1])
		if (CheckIMatching(IsExist, x0, y0, x0, y1) && CheckIMatching (IsExist, x1, y1, x0, y1) && IsExist[x0][y1])	return true;
	if (IsExist[x1][y0])
		if (CheckIMatching(IsExist, x1, y0, x0, y0) && CheckIMatching (IsExist, x1, y0, x1, y1) && IsExist[x1][y0])	return true;
	return false;
}

bool checkUMatching(bool IsExist[][10], int x0, int y0, int x1, int y1, int ROWS, int COLS){
//Checking U Moving
	if (x0 == x1 && y0 == y1)	return false;

	if (x0 == 0 && x1 == 0)	return true;
	if (y0 == 0 && y1 == 0)	return true;
	if (x0 == ROWS-1 && x1 == ROWS-1)	return true;
	if (y0 == COLS-1 && y1 == COLS-1)	return true;

	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (x0 == 0)
		if (CheckIMatching(IsExist, x1, y1, 0, y1) && IsExist[0][y1])	return true;
	if (x0 < x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (x0 == ROWS-1)
		if (CheckIMatching(IsExist, x1, y1, ROWS-1, y1) && IsExist[ROWS-1][y1])	return true;
	
	if (y0 > y1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y0 == 0)	
		if (CheckIMatching(IsExist, x1, y1, x1, 0) && IsExist[x1][0])	return true;
	if (y0 < y1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y0 == COLS-1)
		if (CheckIMatching(IsExist, x1, y1, x1, COLS-1) && IsExist[x1][COLS-1])	return true;

	if (CheckIMatching(IsExist, x0, y0, 0, y0) && CheckIMatching(IsExist, x1, y1, 0, y1) && IsExist[0][y0] && IsExist[0][y1])	return true;
	if (CheckIMatching(IsExist, x0, y0, x0, 0) && CheckIMatching(IsExist, x1, y1, x1, 0) && IsExist[x0][0] && IsExist[x1][0])	return true;
	if (CheckIMatching(IsExist, x0, y0, ROWS-1, y0) && CheckIMatching(IsExist, x1, y1, ROWS-1, y1) && IsExist[ROWS-1][y0] && IsExist[ROWS-1][y1])	return true;
	if (CheckIMatching(IsExist, x0, y0, x0, COLS-1) && CheckIMatching(IsExist, x1, y1, x1, COLS-1) && IsExist[x0][COLS-1] && IsExist[x1][COLS-1])	return true;
	
	if (x0 == x1){
		for (int i = x0-1; i>=0; i--)
			if (IsExist[i][y0] && IsExist[i][y1]){
				if (CheckIMatching(IsExist, i, y0, i, y1))	return true;
			}
			else break;
		for (int i = x0+1; i < ROWS; i++)
			if (IsExist[i][y0] && IsExist[i][y1]){
				if (CheckIMatching(IsExist, i, y0, i, y1))	return true;
			}
			else break;
		return false;
	}

	if (y0 == y1){
		for (int i = y0-1; i>=0; i--)
			if (IsExist[x0][i] && IsExist[x1][i]){
				if (CheckIMatching(IsExist, x0, i, y0, i))	return true;
			}
			else break;
		for (int i = y0+1; i<COLS; i++)
			if (IsExist[x0][i] && IsExist[x1][i]){
				if (CheckIMatching(IsExist, x0, i, y0, i))	return true;
			}
			else break;
		return false;
	}

	if (y0 > y1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (x0 == x1+1 || x0 == x1-1){
		for (int i = y0-1; i>=0; i--)
			if (IsExist[x0][i] && IsExist[x1][i]){
				if (CheckIMatching(IsExist, x1, i, x1, y1))	return true;
				else i = -5;
			}
			else break;
	}

	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y0 == y1-1 || y0 == y1+1){
		for (int i = x0-1; i>=0; i--)
			if (IsExist[i][y1] && IsExist[i][y0]){
				if (CheckIMatching(IsExist, x1, y1, i, y1))	return true;
			}
			else break;
	}


	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int i = x0-1; i>=0; i--){
		if (IsExist[i][y0]){
			if (CheckIMatching(IsExist, i, y0, i, y1) && IsExist[i][y1] &&  CheckIMatching(IsExist, i, y1, x1, y1))	{
				return true;
			}
		}
		else break;
	}
	if (x0 < x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int i = x0+1; i < ROWS; i++){
		if (IsExist[i][y0]){
			if (CheckIMatching(IsExist, i, y0, i, y1) && IsExist[i, y1] && CheckIMatching(IsExist, i, y1, x1, y1))	{
				return true;
			}
		}
		else break;
	}

	if (y0 > y1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int i = y0-1; i>=0; i--){
		if (IsExist[x0, i]){
			if (CheckIMatching(IsExist, x0, i, x1, i) && IsExist[x1][i] && CheckIMatching(IsExist, x1, i, x1, y1)){
				return true;
			}
		}
		else break;
	}
	if (y0 < y1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int i = y0+1; i < COLS; i++){
		if (IsExist[x0, i]){
			if (CheckIMatching(IsExist, x0, i, x1, i) && IsExist[x1][i] && CheckIMatching(IsExist, x1, i, x1, y1)){
				return true;
			}
		}
		else break;
	}
	return false;
}

bool CheckZMatching(bool IsExist[][10], int x0, int y0, int x1, int y1) {
//Checking Z Moving
	if (x0==x1 || y0 == y1) return false;

	if (x0 < x1)
	{
		for (int i = x0 + 1; i < x1; ++i)
		{
			if (CheckIMatching(IsExist, x0, y0, i + 1, y0) == true && CheckIMatching(IsExist, i, y0 - 1, i, y1 + 1) == true && CheckIMatching(IsExist, i - 1, y1, x1, y1) == true) return true;
		}
	}

	if (x0 > x1)
	{
		for (int i = x0 - 1; i > x1; i--)
		{
			if (CheckIMatching(IsExist, x0, y0, i - 1, y0) == true && CheckIMatching(IsExist, i, y0 + 1, i, y1 - 1) == true && CheckIMatching(IsExist, i + 1, y1, x1, y1) == true) return true;
		}
	}

	if (y0 > y1)
	{
		for (int i = y0 - 1; i > y1; i--)
		{
			if (CheckIMatching(IsExist, x0, y0, x0, i - 1) == true && CheckIMatching(IsExist, x0 - 1, i, x1 + 1, i) == true && CheckIMatching(IsExist, x1, i + 1, x1, y1) == true) return true;
		}
	}

	if (y0 < y1)
	{
		for (int i = y0 + 1; i < y1; ++i)
		{
			if (CheckIMatching(IsExist, x0, y0, x0, i + 1) == true && CheckIMatching(IsExist, x0 - 1, i, x1 + 1, i) == true && CheckIMatching(IsExist, x1, i - 1, x1, y1) == true) return true;
		}
	}

	return false;
}

bool checkAll(bool IsExist[][10], int x0, int y0, int x1, int y1, int Rows, int Cols){
//Check ALl (includes UIZL Moving)
	if (CheckIMatching(IsExist, x0, y0, x1, y1))	return true;
	if (checkUMatching(IsExist, x0, y0, x1, y1, Rows, Cols))	return true;
	if (checkLMatching(IsExist, x0, y0, x1, y1))	return true;
	if (CheckZMatching(IsExist, x0, y0, x1, y1))	return true;
	return false;
}

bool check_couple(Button A, Button B){
//Check the same
	std::string Aa = A.text.getString();
	std::string Bb = B.text.getString();
	if (Aa == Bb)	
		return true;
	else	return false;
}

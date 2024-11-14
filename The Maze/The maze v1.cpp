//==============================================================
// Filename :The maze
// Authors :Ivan Ooijevaar & Marlin Sliman
// Version :1
// License :
// Description :code that constructs a maze and makes an x symbol traverse it
//==============================================================
#include <iostream>
#include <array>
#include <string>

const size_t size = 12;		//select size of maze, square maze so only 1 variable needed
void printMaze(std::array<std::array<std::string, size>, size>&);	//initialize printmaze function to take in the maze
void locateX(std::array<std::array<std::string, size>, size>);	//initialize locateX function
void traverseMaze(std::array<std::array<std::string, size>, size>);
int x = 0;
int y = 0;
char right = 'l';		//define right-hand side for the x
int main() {
	//create the maze consisting of an array with an array of columns, the size specified above determines the grouping of the maze
	std::array<std::array<std::string, size>, size> maze = {	
		"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#",
		"#", ".", ".", ".", "#", ".", ".", ".", ".", ".", ".", "#",
		".", ".", "#", ".", "#", ".", "#", "#", "#", "#", ".", "#",
		"#", "#", "#", ".", "#", ".", ".", ".", ".", "#", ".", "#",
		"#", ".", ".", ".", ".", "#", "#", "#", ".", "#", ".", "x",
		"#", "#", "#", "#", ".", "#", ".", "#", ".", "#", ".", "#",
		"#", ".", ".", "#", ".", "#", ".", "#", ".", "#", ".", "#",
		"#", "#", ".", "#", ".", "#", ".", "#", ".", "#", ".", "#",
		"#", ".", ".", ".", ".", ".", ".", ".", ".", "#", ".", "#",
		"#", "#", "#", "#", "#", "#", ".", "#", "#", "#", ".", "#",
		"#", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "#",
		"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"
		};	//using spaces for visual maze constructing
	
	printMaze(maze);	//use the function to print the starting maze
	//locateX(maze);
	traverseMaze(maze);
}

void printMaze(std::array<std::array<std::string, size>, size> & o) {//function to print the maze

	for (auto &row : o) {//automatically make correct variable row and keep incrementing adress until all rows are printed

		for (auto &figure : row) {//automatically make correct variable figure and keep incrementing adress until all figures are printed

			std::cout << figure << ' ';
		}
		std::cout << std::endl;
	}
}

void locateX(std::array<std::array<std::string, size>, size> l) {//function that finds the coordinates of the symbol x

	for (int p = 0; p < size; p++) {//step trough the rows

		for (int q = 0; q < size; q++) {//step trough the values of the rows, looking at each value
			
			if (l[p][q] == "x") {		//if the coordinate contains the x, say so, and display the coordinates
				//std::cout << "X located\n";
				//std::cout << p << ' ' << q << std::endl;	
				x = p;	//store location of the x
				y = q;
				break;
			}
		}	
	}
}

void traverseMaze(std::array<std::array<std::string, size>, size> i) {
	
	
	locateX(i);		//find point
	if (i[x][y - 1] == "." and right == 'l') {//if there is an open space to the right-hand side of the x, move the x
		i[x][y - 1] = "x";	//move x
		i[x][y] = ".";
		y = y - 1;
		right = 'u';	//"rotate" the x (change its right-hand side)
		std::cout << "Moving left\n";
	}
	else if (i[x - 1][y] == "." and right == 'u') {
		i[x - 1][y] = "x";
		i[x][y] = ".";
		x = x - 1;
		right = 'r';
		std::cout << "Moving up\n";
	}
	else if (i[x][y + 1] == "." and right == 'r') {
		i[x][y + 1] = "x";
		i[x][y] = ".";
		y = y + 1;
		right = 'd';
		std::cout << "Moving right\n";
	}
	else if (i[x + 1][y] == "." and right == 'd') {
		i[x + 1][y] = "x";
		i[x][y] = ".";
		x = x + 1;
		right = 'l';
		std::cout << "Moving down\n";
	}
	else {		//if no way was found, "rotate" the x (change its right-hand side)
		if (right == 'r') {
			right = 'u';
		}
		else if (right == 'u') {
			right = 'l';
		}
		else if (right == 'l') {
			right = 'd';
		}
		else {
			right = 'r';
		}
	}

	
	
	printMaze(i); //print maze
	std::cout << right << std::endl;		//print direction of right-hand side
	if (x == 0 or x == 11 or y == 0 or y == 11) {//if you are at an edge of the maze
		std::cout << "You made it out of the maze!\n";
	}
	else {
		traverseMaze(i);
	}
}
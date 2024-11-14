//==============================================================
// Filename :The maze
// Authors :Ivan Ooijevaar & Marlin Sliman
// Version :2
// License :
// Description :code that constructs a maze and makes an x symbol traverse it
//==============================================================
#include <iostream>
#include <array>
#include <string>

const size_t size = 12;		//select size of maze, square maze so only 1 variable needed
void printMaze(const std::array<std::array<std::string, size>, size>&);	//initialize printmaze function to take in the maze
void locateX(const std::array<std::array<std::string, size>, size>);	//initialize locateX function
void traverseMaze(std::array<std::array<std::string, size>, size>);	//initialize traverseMaze function
int x = 0;
int y = 0;
char right = 'l';		//define right-hand side for the x
char front = 'd';		//define front side(right side is dominant and should be started with
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
	std::cout << std::endl;		//add extra empty line for visibility
	traverseMaze(maze);	//start recursion loop
}

void printMaze(std::array<std::array<std::string, size>, size>& o) {//function to print the maze

	for (auto const & row : o) {//automatically make correct variable row and keep incrementing adress until all rows are printed

		for (auto const & figure : row) {//automatically make correct variable figure and keep incrementing adress until all figures are printed

			std::cout << figure << ' ';
		}
		std::cout << std::endl;
	}
}

void locateX(const std::array<std::array<std::string, size>, size> l) {//function that finds the coordinates of the symbol x

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

void traverseMaze(std::array<std::array<std::string, size>, size> i) {	//function to traverse the maze


	locateX(i);		//find point
	//these if statements check for an open space on the right-hand side of the x symbol(l = left, u = up, d - down, r = right w.r.t. the maze)
	if (i[x][y - 1] == "." and right == 'l') {//if there is an open space to the right-hand side of the x, move the x
		i[x][y - 1] = "x";	//move the x
		i[x][y] = ".";		//replace former loction of the x
		y = y - 1;			//indicate new location, useful for win condition
		right = 'u';	//"rotate" the x (change its right-hand side and front direction)
		front = 'l';
		std::cout << "Moving left\n";
	}
	else if (i[x - 1][y] == "." and right == 'u') {
		i[x - 1][y] = "x";
		i[x][y] = ".";
		x = x - 1;
		right = 'r';
		front = 'u';
		std::cout << "Moving up\n";
	}
	else if (i[x][y + 1] == "." and right == 'r') {
		i[x][y + 1] = "x";
		i[x][y] = ".";
		y = y + 1;
		right = 'd';
		front = 'r';
		std::cout << "Moving right\n";
	}
	else if (i[x + 1][y] == "." and right == 'd') {
		i[x + 1][y] = "x";
		i[x][y] = ".";
		x = x + 1;
		right = 'l';
		front = 'd';
		std::cout << "Moving down\n";
	}
	//from here the if statements see if the x can move forward
	else if (i[x][y - 1] == "." and front == 'l') {//if you can walk forward, do so
		i[x][y - 1] = "x";	//move the x
		i[x][y] = ".";		//replace former x
		y = y - 1;
		
		std::cout << "Moving left\n";
	}
	else if (i[x - 1][y] == "." and front == 'u') {
		i[x - 1][y] = "x";
		i[x][y] = ".";
		x = x - 1;
		
		std::cout << "Moving up\n";
	}
	else if (i[x][y + 1] == "." and front == 'r') {
		i[x][y + 1] = "x";
		i[x][y] = ".";
		y = y + 1;
		
		std::cout << "Moving right\n";
	}
	else if (i[x + 1][y] == "." and front == 'd') {
		i[x + 1][y] = "x";
		i[x][y] = ".";
		x = x + 1;

		std::cout << "Moving down\n";
	}
	else {		//if no way to move was found, "rotate" the x (change its right-hand side)
		std::cout << "rotating" << std::endl;		//print direction of right-hand side
		if (right == 'r') {
			right = 'u';
			front = 'l';
		}
		else if (right == 'u') {
			right = 'l';
			front = 'd';
		}
		else if (right == 'l') {
			right = 'd';
			front = 'r';
		}
		else if(right == 'd'){
			right = 'r';
			front = 'u';
		}
		else {	//just in case, this should not do anything normally
			std::cout << "ERROR\n";
		}
	}


	std::cout << std::endl;		//add extra empty line for visibility
	printMaze(i); //print maze
	std::cout << std::endl;		//add extra empty line for visibility
	if (x == 0 or x == 11 or y == 0 or y == 11) {//if you are at an edge of the maze
		std::cout << "You made it out of the maze!\n";
	}
	else {
		traverseMaze(i);
	}
}
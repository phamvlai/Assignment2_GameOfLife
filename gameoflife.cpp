#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>



using namespace std;

#define CLASSIC 0
#define DOUGHTNUT 1
#define MIRROR 2

//Grid Class to conduct the game of life.
class Grid{
private:
	int width,height;
	int **grid;
	int boundaryMode;
public:
	Grid(int w,int h,int mode,double popDensity = 0){
		width = w;	//Width of the grid.
		height = h;	//Height of the grid
		boundaryMode = mode;	//Type of Grid
		grid = new int*[height];
		// Nested for loop to create the 2D array
		for (int i = 0; i < height; ++i)
		{
			grid[i] = new int[width];
			for (int j = 0; j < width; ++j)
			{
				if(((double) rand() / (RAND_MAX))  < popDensity){
					grid[i][j] = 1;
				}
				else{
					grid[i][j] = 0;
				}
			}
		}
	}
	//Set the value of the cell
	void setCell(int i,int j,int val){
		grid[i][j] = val;
	}
	//Print out the grid
	void print(){
		for (int j = 0; j < width; ++j){
			cout << "-";
		}
		cout << endl;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if(grid[i][j] == 0){
					cout << "-";
				}
				else{
					cout << "*";
				}
			}
			cout << endl;
		}
		for (int j = 0; j < width; ++j){
			cout << "-";
		}
		cout << endl;
	}
	//Function to count the neighbors.
	int countNeighbour(int i,int j){
		int count = 0;
		//Used switch to change boundary mode accordingly.
		switch(boundaryMode){
			case CLASSIC:
				if( i - 1 >= 0){
					count += grid[i-1][j];
					if(j + 1 < width){
						count += grid[i-1][j+1];
					}
					if(j - 1 >= 0){
						count += grid[i-1][j-1];
					}
				}
				if(i + 1 < height){
					if(j - 1 >= 0){
						count += grid[i+1][j-1];
					}
					count += grid[i+1][j];
					if(j + 1 < width){
						count += grid[i+1][j+1];
					}
				}
				if(j + 1 < width){
					count += grid[i][j+1];
				}
				if(j - 1 >= 0){
					count += grid[i][j-1];
				}
				return count;
				break;
			case DOUGHTNUT:
				if( i - 1 >= 0){
					count += grid[i-1][j];
					if(j + 1 < width){
						count += grid[i-1][j+1];
					}
					else{
						count += grid[i-1][0];
					}
					if(j - 1 >= 0){
						count += grid[i-1][j-1];
					}
					else{
						count += grid[i-1][width - 1];
					}
				}
				else{
					count += grid[height-1][j];
					if(j + 1 < width){
						count += grid[height-1][j+1];
					}
					else{
						count += grid[height-1][0];
					}
					if(j - 1 >= 0){
						count += grid[height-1][j-1];
					}
					else{
						count += grid[height - 1][width - 1];
					}
				}
				if(i + 1 < height){
					if(j - 1 >= 0){
						count += grid[i+1][j-1];
					}
					else{
						count += grid[i+1][width - 1];
					}
					count += grid[i+1][j];
					if(j + 1 < width){
						count += grid[i+1][j+1];
					}
					else{
						count += grid[i+1][0];
					}
				}
				else{
					if(j - 1 >= 0){
						count += grid[0][j-1];
					}
					else{
						count += grid[0][width - 1];
					}
					count += grid[0][j];
					if(j + 1 < width){
						count += grid[0][j+1];
					}
					else{
						count += grid[0][0];
					}
				}
				if(j + 1 < width){
					count += grid[i][j+1];
				}
				else{
					count += grid[i][0];
				}
				if(j - 1 >= 0){
					count += grid[i][j-1];
				}
				else{
					count += grid[i][width - 1];
				}
				return count;
				break;
			case MIRROR:
				if( i - 1 >= 0){
					count += grid[i-1][j];
					if(j + 1 < width){
						count += grid[i-1][j+1];
					}
					else{
						count += grid[i-1][j];
					}
					if(j - 1 >= 0){
						count += grid[i-1][j-1];
					}
					else{
						count += grid[i-1][j];
					}
				}
				else{
					count += grid[i][j];
					if(j + 1 < width){
						count += grid[i][j+1];
					}
					else{
						count += grid[i][j];
					}
					if(j - 1 >= 0){
						count += grid[i][j-1];
					}
					else{
						count += grid[i][j];
					}
				}
				if(i + 1 < height){
					if(j - 1 >= 0){
						count += grid[i+1][j-1];
					}
					else{
						count += grid[i+1][j];
					}
					count += grid[i+1][j];
					if(j + 1 < width){
						count += grid[i+1][j+1];
					}
					else{
						count += grid[i+1][j];
					}
				}
				else{
					if(j - 1 >= 0){
						count += grid[i][j-1];
					}
					else{
						count += grid[i][j];
					}
					count += grid[i][j];
					if(j + 1 < width){
						count += grid[i][j+1];
					}
					else{
						count += grid[i][j];
					}
				}
				if(j + 1 < width){
					count += grid[i][j+1];
				}
				else{
					count += grid[i][j];
				}
				if(j - 1 >= 0){
					count += grid[i][j-1];
				}
				else{
					count += grid[i][j];
				}
				return count;
				break;
		}
		return 0;
	}
	bool same(int **newgrid){
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if(grid[i][j] != newgrid[i][j]){
					return false;
				}
			}
		}
		return true;
	}
	//Implementing the rules of the game.
	bool update(){
		int **newgrid = new int*[height];
		for (int i = 0; i < height; ++i)
		{
			newgrid[i] = new int[width];
			for (int j = 0; j < width; ++j)
			{
				newgrid[i][j] = grid[i][j];
			}
		}
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				int n = countNeighbour(i,j);
				if(n < 2){
					newgrid[i][j] = 0;
				}
				else if(n == 3){
					if(newgrid[i][j] == 0){
						newgrid[i][j] = 1;
					}
				}
				else if(n >= 4){
					newgrid[i][j] = 0;
				}
			}
		}
		if(same(newgrid)){
			return false;
		}
		grid = newgrid;
		return true;
	}
};

//Used to read in the file.
Grid *fromFile(string filename,int mode){
	ifstream file(filename.c_str());
	int w,h;
	char c;
	file >> h;
	file >> w;
	Grid *grid = new Grid(w,h,mode);
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			file >> c;
			if(c == 'X'){
				grid->setCell(i,j,1);
			}
			else{
				grid->setCell(i,j,0);
			}
		}
	}
	return grid;
}
int askBoundaryMode(){
	int bMode = -1;
	while(true){
		cout << "Choose boundary mode : \n";
		cout << "0. CLASSIC\n";
		cout << "1. DOUGHNUT\n";
		cout << "2. MIRROR\n";
		cin >> bMode;
		if(cin.fail()){
			cout << "Invalid value.";
		}
		else if(bMode < 0 || bMode > 2){
			cout << "Invalid Boundary mode.\n";
		}
		else{
			break;
		}
	}
	return bMode;
}
//Askes the user for population density.
double askPopDensity(){
	double popDensity = 0;
	while(true){
		cout << "Enter population density between 0 and 1: ";
		cin >> popDensity;
		if(popDensity < 0 || popDensity > 1){
			cout << "Invalid Population density.\n";
		}
		else{
			break;
		}
	}
	return popDensity;
}
Grid* chooseGrid(){
	int choice;
	cout << "Choose Only One:\n";
	cout << "1. Randomly create grid" << endl;
	cout << "2. Load from file" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;
	string filename;
	Grid *grid;
	int w,h,bMode;
	double popDensity;
	if(choice == 3){
		exit(0);
	}
	else if(choice == 1){
		cout << "Enter width : ";
		cin >> w;
		if(cin.fail()){
			cout << "Invalid value.\n";
			exit(0);
		}
		cout << "Enter height : ";
		cin >> h;
		if(cin.fail()){
			cout << "Invalid value.\n";
			exit(0);
		}
		bMode = askBoundaryMode();
		popDensity = askPopDensity();
		grid = new Grid(w,h,bMode,popDensity);
	}
	else if(choice == 2){
		cout << "Enter filename : ";
		cin >> filename;
		ifstream inFile(filename.c_str());
		if(!inFile){
			cout << "Unable to open file.\n";
			exit(0);
		}
		bMode = askBoundaryMode();
		grid = fromFile(filename,bMode);
	}
	else{
		cout << "Invalid value.\n";
		exit(0);
	}
	return grid;
}

//main arguement to run the program
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Grid *grid = chooseGrid();
	int pause = 0;
	//Keeps the user in a loop until a correct choice is entered.
	while(true){
		cout << "Please enter 1 or 2:\n";
		cout << "1. To pause in between generations\n";
		cout << "2. Do not pause in between generations\n";
		cin >> pause;
		if(cin.fail()){
			cout << "Invalid value.\n";
		}
		else if(pause != 1 && pause != 2){
			cout << "Invalid input\n";
		}
		else{
			break;
		}
	}
	//Do while loop to update the grid with a pause or not.
	do{
		system("clear");
		grid->print();
		if(pause == 1){
			//Pauses the game until something is entered
		cout << "\nPress the Enter key to continue....\n";
    cin.ignore();
    cin.get();
		}
	}while(grid->update());
	cout << "Press 'enter' to exit";
	cin.get();
	return 0;
}

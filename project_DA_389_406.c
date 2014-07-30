//E/10/389 E/10/406
#include <stdio.h>
#include <stdlib.h>

typedef struct sMaze maze;

//ADT for storing maze
struct sMaze{
char ** str;
int x;
int y;
};



maze readMaze(char *);
void printMaze(maze);
int solveMaze(maze,int,int);
maze trackO(maze);


int main(int argc,char *argv[])
{
	if( argv[1] != NULL)
	{
	//readinng maze
	maze getMaze = readMaze(argv[1]);
	//printing maze
	printMaze(getMaze);
	printf("\n");
	
	//get the start point
	maze m = trackO(getMaze);
	
	//solve the maze and if there is a solution.], printing it
	if(solveMaze(getMaze,m.x,m.y))
	{
		printMaze(getMaze);
	}
	}
	return 0;
}

//Reading maze from file
maze readMaze(char *fileName)
{	
	//open file
	FILE *file = fopen(fileName, "r");
	char **str;
	int x,y;
	
	if( file != NULL)
	{
		fscanf(file,"%d %d\n",&y,&x);
		//printf("%d %d",x,y);
		str = malloc(sizeof(char *) * y);
		int i;
		for(i=0;i<y;i++)
		{	//reading file line by line and storing in 2D array pointer
			str[i] = malloc(sizeof(char) * x);
			fscanf(file,"%s\n",str[i]);
		}
	}
	fclose(file);
	//Storing the result in to inMaze struct
	maze inMaze;
	inMaze.str = str;
	inMaze.x = x;
	inMaze.y = y;
	
	return inMaze;
}

void printMaze(maze outMaze)
{
	int i;
	for(i = 0;i<outMaze.y;i++)
	{
		//printing maze line by line
		printf("%s\n",outMaze.str[i]);
	}
}

//solving the maze
int solveMaze(maze inMaze,int x,int y)
{
	
	//chek if x,y out of bound
	if( x < 0 || x > inMaze.x || y < 0 || y > inMaze.y)
		return 0;
	
	//check if the end
	if(inMaze.str[y][x] == '*')
		return 1;
	
	//check if the next pixcel is a wall
	if(inMaze.str[y][x] != '.' && inMaze.str[y][x] != 'o')
		return 0;
		
	if(inMaze.str[y][x] != 'o')
		inMaze.str[y][x] = 'X';
	
	//check the 4 side pixcels
	if( solveMaze(inMaze,x,y-1) )
		return 1;
	if( solveMaze(inMaze,x+1,y) )
		return 1;
	if( solveMaze(inMaze,x-1,y) )
		return 1;
	if( solveMaze(inMaze,x,y+1) )
		return 1;
	if(inMaze.str[y][x] != 'o')
		inMaze.str[y][x] = '.';
	
	return 0;
}

//getting the cordinates of starting point
maze trackO(maze inMaze)
{
	int i,j;
	maze pointO;
	
	for(i = 0; i < inMaze.y; i++)
	{
		for(j = 0; j < inMaze.x; j++)
		{
			if(inMaze.str[i][j] == 'o')
			{
				pointO.x = j;
				pointO.y = i;
				return pointO;
			}
		}
	}
	
	pointO.x = -1;
	pointO.y = -1;
	return pointO;
}
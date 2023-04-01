#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;


void mydata(); //function to print the information of the developer
void makearray (char[][5], char[][5], int ROW); // function to initialize the arrays and randomly add 10 Rocks and 5 Exits
void display (const char[][5],int ROW);// function to display the array 
void lavaraise(char[][5], char[][5],int, int&); // function that increases the lava when called
bool user(char[][5], char[][5],int, int&, int&); // function that takes the input from the user and checks whether the coordinate has X, R, L or E

int main ()
{
    const int ROW = 10; // ROW of the array
    const int COLUMN = 5; // Column of the array
    srand (time (0));
    int line = ROW-1; // variable that keeps the lava position
    mydata();
  char Originalgame[ROW][COLUMN], Displaygame[ROW][COLUMN];
  makearray (Originalgame, Displaygame, ROW);
    int chance = 10 ;  // initializing chance 10 for user to predict the exit coordinate
  //  lavaraise(Originalgame,Displaygame,ROW, line);
    
  //display (Originalgame,ROW);       // FIXME_BEFORE_SUBMIT
  display (Displaygame, ROW);        

    while (chance > 0 ){  // while loop runs until chance becomes less than 0
        user(Originalgame, Displaygame, ROW, line, chance) ;
        
    }
    
    if (chance < 1){
    cout <<"Out of tries" << endl;
    cout <<"You lost the Game. " << endl<< endl; 
    cout <<"The original game is " << endl;
    display(Originalgame, ROW);
    
    }
    
  return 0;
}






void mydata(){
    // Displaying the Header
    // this function contains no parameter and prints the information about the department, student's name, euid and email

cout << "+-----------------------------------------------+"<<endl;
cout << "|       Computer Science and Engineering        |" << endl;
cout << "|        CSCE 1030 - Computer Science I         |" << endl;
cout << "|  Asim Timsina    at0733    at0733@my.unt.edu  |" << endl;
cout << "+-----------------------------------------------+ " << endl << endl ; 

}

void display (const char array[][5], int ROW)
{
    // this is a void function with the parameter constant array and ROW
    // this function prints the array with in a grid format, along with the numeric headers. 
  cout << "  0 1 2 3 4 " << endl;
  for (int i = 0; i < ROW; i++)
    {
      cout << i << " ";
      for (int j = 0; j < 5; j++)
	{
	  cout << array[i][j] << " ";
	}
      cout << endl;
    }
}

void makearray (char Originalgame[][5], char Displaygame[][5], int ROW)
{
    // this is a void function with the parameter two arrays and ROW
    // this function initialize two arrays with empty spaces and also 10 Rocks and 5 exits in Originalgame array
  int tempx, tempy; // tempx and tempy are temp int that contains randomly generated x and y coordinate for ROcks and Exits
  for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < 5; j++)
	{
	  Originalgame[i][j] = 'X';
	}
    }
  for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < 5; j++)
	{
	  Displaygame[i][j] = 'X';
	}
    }

  for (int i = 0; i < 10; i++)
    {

      tempx = rand () % 10; // randomly generating x coordinate between 0 and 9 for Rocks
      tempy = rand () % 5;// randomly generating y coordinate between 0 and 4 for Rocks

      if (Originalgame[tempx][tempy] == 'X')
	    Originalgame[tempx][tempy] = 'R';
      else
	i--;
    }
    
        for (int i = 0; i < 5; i++)
    {

      tempx = rand () % 10;// randomly generating x coordinate between 0 and 9 for Exits
      tempy = rand () % 5;// randomly generating y coordinate between 0 and 4 for Exits

      if (Originalgame[tempx][tempy] == 'X')
	Originalgame[tempx][tempy] = 'E';
      else
	i--;
    }
}

void lavaraise(char Originalgame[][5], char Displaygame[][5],int ROW, int& line){
     // this is a void function with the parameter  two arrays  ROW and line that keeps the no of lava already present
    // this function updates the Lava 'L' in each slot in a row starting from the bottom row 
          for(int i = 0; i < 5 ; i++){
            Displaygame[line][i]='L';
            Originalgame[line][i]='L';
        }
        line -- ;
    
}

bool user(char Originalgame[][5], char Displaygame[][5],int ROW, int& line, int& chance){
    // this is a bool function with the parameter  two arrays  ROW and line that keeps the no of lava already present and the chance 
    /* this function takes the x and y coordinate from the user and checks the bound
        if the coordinate is inside the bound the function checks whether the coordinate contains exits, rocks , empty
        space or lava and proceed according to it
        */
        
     cout << chance <<" chance remaining" << endl; 
    cout << "Enter the x and y coordinate ";
    int userx,usery ;
    cin >> userx >> usery ;
    
  //  cout << userx << usery << Originalgame[userx][usery] << endl ;  // FIXME_BEFORE_SUBMIT
    
    if ((userx >=0) && (userx <10) && (usery >=0) && (usery <5))
    {
    if ((Originalgame[userx][usery]=='X')) // if the coordinate contains Empty slot
    {
      cout <<"You found an empty tile! The Lava rises!" << endl << endl; 
      lavaraise(Originalgame, Displaygame,ROW, line );
       display (Displaygame, ROW);    
      chance --;
      
    }
    
     else if (Originalgame[userx][usery]=='R') // if the coordinate contains Rock
    {
        cout <<"You found a Rock, ouch! Please try again." << endl  << endl ;  
       display (Displaygame, ROW);    
        chance --;
    }
    else if (Originalgame[userx][usery]=='L') // if the coordinate contains Lava
    {
        cout <<"You found the LAVA! You lose an extra guess!"<< endl << endl;
        chance -= 2 ;
        lavaraise(Originalgame, Displaygame,ROW, line );
      display (Displaygame, ROW);    
    }
    else if (Originalgame[userx][usery]=='E')  // if the coordinate contains Exit
    {
        cout <<"You found the Exit! GOOD JOB! YOU WON!" << endl << endl;
       //terminate();
       // exit (EXIT_FAILURE);
        exit (1);
    }
    }
    else   // // if the coordinate is outside the bound
    
        {
            cout <<"Your position is outside the bounds of the game!"<<endl << endl;
            chance -- ;
            return false ;
        }
}

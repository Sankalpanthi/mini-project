#include<iostream>
#include<string>
using namespace std;
int checkwin();
string p1,p2;
char grid[3][3];
int j; //it will store player's turn
void choice()
{
	cout<<"Who will play first, "<<p1<<" or "<< p2<<"?"<<endl;
	//we will input a new name and check if it is the first player or the second
	string n;
	getline(cin,n);
	//if its none of the two we will print an error
	if((n!=p1)&&(n!=p2))
	{
		cout<<n<<" is not a registered player."<<endl;
		choice();
	}
	else
    {
        if(n==p1)
		    j=1;
	    else
		    j=-1;
    }
}
void  board()
{
    //we will print this board after every turn
	cout<<"THE BOARD:"<<endl;
	for(int i=0;i<3;i++)
    {
        cout<<" "<<grid[i][0]<<" | "<<grid[i][1]<<" | "<<grid[i][2]<<endl;
        cout<<"-----------"<<endl;
    }
}
void play()
{
	int r,c;
	int i=-1; //used for storing the result of the game
	while(i==-1)
	{
	    cout<<"Player of current turn: ";
		if(j==1)
			cout<<p1<<endl;
		else
			cout<<p2<<endl;
        cout<<"Choose a row number (0 to 2):"<<endl;
		cin>>r;
		if(r>2||r<0)
		{
			cout<<r<<" is not a valid row."<<endl;
			continue; //for restarting again from the while loop if the entered row is incorrect
		}
		cout<<"Choose a column number (0 to 2):"<<endl;
		cin>>c;
		if(c>2||c<0)
		{
			cout<<c<<" is not a valid column."<<endl;
			continue; //for restarting again from the while loop if the entered column is incorrect
		}
		//execution of the move
		if(grid[r][c]=='.')
			grid[r][c]=((j+1)?'X':'O');
		else
		{
			cout<<"Error! Position already occupied!"<<endl;
			continue;
		}
		j*=-1; //to change player's turn after every move
		board();
		i=checkwin(); //i will hold the value of the result
	}
    cout<<"Game is over:"<<endl;
    if(i==1)
        cout<<p1<<" wins!"<<endl;
    else if(i==2)
        cout<<p2<<" wins!"<<endl;
	else
		cout<<"It is a tie!"<<endl;
}



int checkwin()
{
    //here we will return value based upon following:
    //if p1 wins return 1
    //if p2 wins return 2
    //if no one has won and some positions are remaining return -1
    //if no one has won and no positions are remaining return 0(for draw)
	//for horizontal
	for(int i=0;i<3;i++)
    {
        if((grid[i][0]==grid[i][1]) && (grid[i][1]==grid[i][2]))
        {
            if(grid[i][0]=='X')
                return 1;
            else if(grid[i][0]=='O')
                return 2;
        }
    }
	//for diagonal
	if(((grid[0][0]==grid[1][1]) && (grid[1][1]==grid[2][2])) || ((grid[0][2]==grid[1][1]) && (grid[1][1]==grid[2][0])))
    {
        if(grid[1][1]=='X')
            return 1;
        else if(grid[1][1]=='O')
            return 2;
    }
	//for vertical
	for(int i=0;i<3;i++)
    {
        if((grid[0][i]==grid[1][i]) && (grid[1][i]==grid[2][i]))
        {
            if(grid[0][i]=='X')
                return 1;
            else if(grid[0][i]=='O')
                return 2;
        }
    }
	for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[i][j]=='.')
                return -1;
    return 0;
}
int main()
{
    int t=1;
    char opt; //will store if the players wish to play the game again or not
	//initializing the grid
	for (int i=0;i<3;i++)
	{
	    for(int j=0;j<3;j++)
		    grid[i][j]='.';
	}
    //taking input for both the players
    cout<<"Enter a name for the X player:"<<endl;
	getline(cin,p1);
	cout<<"Enter a name for the O player:"<<endl;
	getline(cin,p2);
	//calling the appropriate functions for the execution of the game
    choice();
    board();
    play();
    while(t==1)
    {
        cout<<"Would you like to play again? (Y/N)"<<endl;
        cin>>opt;
        cin.ignore();
        if(opt=='Y')
            main();
        else if(opt=='N')
            cout<<"Come back again soon!"<<endl;
        else
        {
            cout<<opt<<" is not a valid answer."<<endl;
            continue;
        }
        t=0;
    }
}


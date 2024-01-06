# include <iostream>
# include <vector>
# define n 9
using namespace std;

// Show the final result

void Show(vector <vector <int> > &board)
{
    for (int i = 0; i < n; i++) 
    {
        cout<<"\t\t";
        if(i == 3 || i == 6)
        {
            cout<<"_____________________"<<endl;
            cout<<"\t\t";
        }
		for (int j = 0; j < n; j++)
        {
            
            if(j == 3 || j == 6)
                cout<<"|";

            cout<<board[i][j]<<" ";
        }
        cout<<endl;
	}
}

// To check if the input number in the row and column is valid or not
bool isSafe(vector <vector <int> > &board, int row, int col)
{

    int k = board[row][col];

    // check the rows
    for(int i=0; i<n; i++) 
    {
        if(i == row)
            continue;
        if(board[i][col] == k)
            return false;
    }

    // check the columns
    for(int i=0; i<n; i++)
    {
        if(i == col)
            continue;
        if(board[row][i] == k)
            return false;
    }

    // check the 3x3 sub grid
    int start_row = 3 * (row / 3);
    int start_col = 3 * (col / 3);

    for(int i = start_row; i < start_row+3; i++)
    {
        for(int j = start_col; j<start_col+3; j++)
        {
            if(i == row && j == col)
                continue;

            if(board[i][j] == k)
                return false;
        }
    }
    return true;
}

// Recursive function to solve the sudoku
bool SolveBoard(vector <vector <int> > &board, int col, int k, int i)
{   
    if(col == n)
    {
        i++;
        col = 0;
        k=1;
    }    

    if(i == n && col == n)
        return true;

    for( ;i<n; )
    {
        if(board[i][col] == 0)
        {
            if(k > n)
            {
                board[i][col] = 0;
                    return false;
            }
            
            else
                board[i][col] = k++;

            while(!isSafe(board,i,col))
            {
               board[i][col] = k++;
            
                if(board[i][col] > n)
               {
                    board[i][col] = 0;
                    return false;
               }
            }

                if(!SolveBoard(board, col+1, 1, i))
                {
                    board[i][col] = 0;
                    return SolveBoard(board,col,k,i); // backtracking
                }
        }
        else{
            if(col == n-1)
            {
               col = 0;
               i++;
            }
            else  
            {
                col++;
            }
        }
    }
    return true;
}


int main()
{
    vector <vector <int> >board(n, vector<int>(n,0));

    int row = 0,column,number;
    string numbers;
    char ch;

    cout<<"DISCLAIMER :- If the block is empty, then enter 0."<<endl<<endl;

    do
    {
        cout<<"Enter the values of all columns of "<<(row+1)<<" row "<<endl;
        for(int i=0; i<9; i++)
        {
            cin>>number;

            if(number != 0)
                board[row][i] = number;
        }
    
    }while(++row < 9); 

    cout<<"\n\n\t\t\tRESULT IS :\n" <<endl;

    if(!SolveBoard(board, 0, 1, 0))
        cout<<"No Solution exist"<<endl;
    
    else 
       Show(board);
    
    cout <<"\n\nEXECUTION IS OVER." << endl;
    cin.ignore();

    system("pause");

}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X ='X';
const char O = '0';

const char empty = ' ';

const char tie = 'T';
const char NoOne = 'N';

void instuctions()
{
    cout<<"Welcome to the ultimate man-machime snowdown: Tic-Tac-Toe."<<endl;
    cout<<" 0 | 1 | 2\n";
    cout<<"----------\n";
    cout<<" 3 | 4 | 5\n";
    cout<<"----------\n";
    cout<<" 6 | 7 | 8\n";
}

char askYesNo (string question)
{
    char response;
    do
    {
        cout<<question<<" (y/n): ";
        cin>>response;
    }while (response!= 'y' && response!= 'n');
        return response;
}

int askNumber(string question, int hight, int low=0)
{
    int number;
    do
    {
        cout<<question<<" ("<<low<<" - "<<hight<<" ): ";
        cin>>number;
    }while(number>hight || number <low);
    return number;
}

char humanPiece()
{
    char go_first = askYesNo("Do you require he first move?");
    if(go_first=='y')
    {
        cout<<"Then take the first move. You will need it.\n";
        return X;
    }
    else
    {
        cout<<"You bravert will be your undoing...I will go first.\n";
        return O;
    }
}

char opponent (char piece)
{
    if(piece==X)
        return O;
    else return X;
}

void displayBoard(const vector<char> &board)
{
    cout<<"\n\t"<<board[0]<<" | "<<board[1]<<" | "<<board[2];
    cout<<"\n\t"<<"----------";
    cout<<"\n\t"<<board[3]<<" | "<<board[4]<<" | "<<board[5];
    cout<<"\n\t"<<"----------";
    cout<<"\n\t"<<board[6]<<" | "<<board[7]<<" | "<<board[8];
    cout<<"\n\t";
}

char winner (const vector <char> &board)
{
    //усі можливі виграшні ряди
    const int WINNING_ROWS[8][3]={
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6} };

    const int TOTAL_ROWS = 8;
    //якщо в одному з виграшних рядів вже є три однакові значення
    //і не дорівнюють Empty - то є переможець

    for(int row=0;row<TOTAL_ROWS;++row)
    {
        if      (
         (board[WINNING_ROWS[row][0]] != empty)
                &&
         (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]])
                &&
         (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])
                )
            return board[WINNING_ROWS[row][0]]; //повертає символ, що виграв
    }

    //оскільки переможець цикло не визначився, перевіряєм чи є ніччя
    //тобто чи залишились на полі пусті клітки
    //count - функція з STL перевіряє чи є заданий символ  в списку
    if(count(board.begin(),board.end(),empty)==0)
        return tie;
    //якщо немає ні переможця, ні ніччиї - то ігра йде далі
    return NoOne;
}

inline bool isLegal(int move, const vector<char> &board)
{
    return (board[move]==empty);
}

int humanMove(const vector <char> &board, char human)
{
    int move = askNumber("Where wiil you move?", (board.size()-1));
    while(!isLegal(move,board))
    {
        cout<<"That square is already occupied\n";
        move= askNumber("Where will you move?",(board.size()-1));
    }
    cout<<"Fine...\n";
    return move;
}

int computerMove(vector <char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;


//якщо комп'ютер може виграти наступним ходом, то він зробить цей хід
    while(!found&&move<board.size())
    {
        if (isLegal(move,board))
        {
            board[move]=computer;
            found=winner(board)==computer;
            board[move]= empty;
        }
        if (!found)
            ++move;
    }


//якщо людина може перемогти наступним ходом, то тре блокувати цей хід
    if(!found)
    {
        move=0;
        char human=opponent(computer);
        while(!found &&move<board.size())
        {
            if (isLegal(move,board))
            {
                board[move]= human;
                found=winner(board)==human;
                board[move]==empty;
            }
            if(!found)
                ++move;
        }
    }


//-----найкраза з клітинок що залишилась
    if(!found)
    {
        move=0;
        unsigned int i=0;
        const int BEST_MOVES[]={4,0,2,6,8,1,3,5,7};
        //вибрати оптимальну свобідну клітку
        while(!found && i<board.size())
        {
            move=BEST_MOVES[i];
            if(isLegal(move,board))
                found=true;
            ++i;
        }
    }

cout<<"I shall take square number "<<move<<endl;
return move;
}

void announceWinner(char winner, char computer, char human)
{
    if(winner==computer)
    cout<<"You loose";
    else if(winner=human)
        cout<<"You win";
    else
        cout<<"It is tie";

    cout<<endl;
}

int main()
{
    int move;
    const int NUM_SQUARES = 9;

    vector<char> board(NUM_SQUARES, empty); //дошка з 9 елементів, пуста

    instuctions();

    char human= humanPiece();
    char computer= opponent(human);

    char turn= X;

    displayBoard(board);

    while(winner(board)==NoOne)
    {
        if(turn==human)
        {
            move = humanMove(board,human);
            board[move]=human;
        }
        else
        {
            move = computerMove(board,computer);
            board[move]=computer;
        }
        displayBoard(board);
        turn=opponent(turn);
    }

    announceWinner(winner(board),computer,human);
}

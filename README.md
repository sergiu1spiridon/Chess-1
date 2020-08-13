# Hashtable-AI controlled Chess Game
Contributors:

* [Matei Octavian-Mihai](https://github.com/tavisit)
* [Spiridon Sergiu-Mihai](https://github.com/sergiu1spiridon)

### Nota Bene

If you have a question about the code or the hypotheses we made, do not hesitate to post a comment in the comment section below.
If you also have a suggestion on how this notebook could be improved, please reach out.

## Table of Contents
1. [Basic information about project](#chapter_1)
2. [Chess rules](#chapter_2)
3. [Structure of the AI](#chapter_3)
   1. [Overview](#subchapter_1)
   2. [Hashtable structure](#subchapter_2)
      1. Basic information
      2. Heap structure and use
      3. Hashtable structure and use
   3. [Random structure](#subchapter_3)
      1. Basic information
      2. Pieces movement builder
6. [Application Behaviour](#chapter_4)
7. [Conclusion](#chapter_5)

# <a name="chapter_1">Basic information about project</a>

The program is implemented in C using the main structure and data types offered by this, so no additional libraries or dependencies are required

If you use a UNIX based operating system, call the program from the terminal as ```chess```
If you use Windows, start the application from ```chess.exe```

# <a name="chapter_2">Chess rules</a>

Chess is a two-player strategy board game played on a checkered board with 64 squares arranged in an 8×8 square grid. Played by millions of people worldwide, chess is believed to be derived from the Indian game chaturanga sometime before the 7th century. Chaturanga is also the likely ancestor of the East Asian strategy games xiangqi (Chinese chess), janggi (Korean chess), and shogi (Japanese chess). Chess reached Europe via Persia and Arabia by the 9th century, due to the Umayyad conquest of Hispania. The pieces assumed their current properties in Spain in the late 15th century, and the modern rules were standardized in the 19th century.
The stardard board is the following:
![Chess Table](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Chess_Board.svg/1200px-Chess_Board.svg.png)
Each player begins with 16 pieces:
* one king
* one queen
* two rooks
* two knights
* two bishops
* eight pawns

Each piece type moves differently, with the most powerful being the queen and the least powerful the pawn. The objective is to checkmate the opponent's king by placing it under an inescapable threat of capture. To this end, a player's pieces are used to attack and capture the opponent's pieces, while supporting one another. During the game, play typically involves exchanging pieces for the opponent's similar pieces, and finding and engineering opportunities to trade advantageously or to get a better position. The game will finish if one of the players resigns or if one of them performs the action of checkmate which represents the inability of the other player to move any piece without entering a check or leaving one.

# <a name="chapter_3">Structure of the AI</a>

The AI is structured in two main parts:
1. The hashtable that extract the best next move from its structure
2. The random structure that moves the pieces in a pseudo-random manner

## <a name="subchapter_1">Overview</a>
This program uses a series of structure that ensure a smooth and rigorous run:
* structures that pinpoint the location and type of the pieces
```c
typedef struct Point
{
    int posX;
    int posY;
    int posX_initial;
    int posY_initial;
    unsigned char typePiece;
}coord;
typedef struct pieceCoordonate
{
	char piece;
	int x;
	int y;
}pieceCoordonate;
```
* hashtable structure and its components
```c
// the heap is the building block of the hashtable
typedef struct HeapNode {
    unsigned char* key;
    int score;
}HeapNode;

typedef struct Heap {
	int size;
	HeapNode **myHeap;
}Heap;

// the list of collisions in the hashtable
typedef struct InfoNode{
    unsigned char* key;
    Heap* heap;
    int score;
    unsigned char **parents;
    int numberOfParents;
}InfoNode;

typedef struct Node
{
	InfoNode *info;
	struct Node *next;
}Node;

typedef struct List
{
    Node* head;
    Node* tail;
    int size;
}List;
```
**All these** make possible the construction of the hashtable structure
```c
// the hashtable structure
typedef struct hashtable {
	List **bucket;
	int size;
	unsigned long (*hashFunction)(unsigned char*);
}hashtable;
```

In order to fill up the hashtable, the current state of the chess matrix will be parsed as a string and transformed according to the following hash function:
```C
 unsigned long hashfct(unsigned char *str) {
	unsigned int hash = 0;
	int c = *str;

	while (c) {
	    hash += c;
		c = *str++;
	}

	return hash;
}
```
The hashtable algorithm is designed to learn from the player and rank the states in order to finally defeat the user. If a state is not registered in the hashtable, the algorithm will take a random approach in order to make the game playable in any condition.

## <a name="subchapter_2">Hashtable Structure</a>  



## <a name="subchapter_3">Random Structure</a>

### Basic information

The algorithm takes the current chess table and produces the next state according to some rules and probabilities.
The algorithm takes all the possible moves from all its pieces and selects one according to the following table of value( the most valuable pieces will have a better probability of movement).

**Types of games**
The game is structured in 3 main parts:
* Early game which represents the portion of the game from the start to the moment when at most 16 pieces were moved
* Middle game ends when when the total number of pieces is less or than 8
* End game ends with a checkmate

|Piece      |EarlyGame|MiddleGame|EndGame|
|-----------|---------|----------|-------|
|P/p(pawn)  |    01   |    01    |   01  |
|H/h(knight)|    03   |    04    |   05  |
|B/b(bishop)|    03   |    04    |   05  |
|R/r(rook)  |    05   |    06    |   07  |
|Q/q(queen) |    09   |    10    |   13  |
|K/k(king)  |    01   |    01    |   01  |

### Objective
The objective of the algorithm is to produce a move that will not result in a check. The main function that searches for AI check's has the following definition:
```c
bool isNotInCheckAI(unsigned char**currentMatrix)
```
It relies on the behaviour and mathematical priciples of the other pieces, that return a boolean value for each one of them.

### Pieces movement builder

The algorithm works in 3 stages to ensure a predictible and human-like behaviour.

#### First stage

The AI locates all the pieces on the board with a simple matrix parsing and appends to the pieceCoord the initial coordonates of its pieces
```C
for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(matrix[i][j]==piece)
            {
                // insert the location of the piece into the return value
                pieceCoord[nrOfPieces] = malloc(sizeof(coord));
                pieceCoord[nrOfPieces]->posX = j;
                pieceCoord[nrOfPieces]->posX_initial = j;
                pieceCoord[nrOfPieces]->posY = i;
                pieceCoord[nrOfPieces]->posY_initial = i;
                pieceCoord[nrOfPieces]->typePiece = piece;
                nrOfPieces++;

            }
        }
    }
```

#### Second stage

The AI chooses a series of possible movements from the pieces though the function ```switchPieces``` and for each piece, their respective behaviour function will be called, each unique, but the main components of each one are:

**The** allocation of memory for the next move and loading of the initial position
```c
coord* returnValue = malloc(sizeof(coord));
NULL_PARAM_STRUCT_VALIDATION(returnValue)

returnValue->posX = posX;
returnValue->posX_initial = posX;
returnValue->posY = posY;
returnValue->posY_initial = posY;     
returnValue->typePiece = piece_type;

int * possibleMovement = malloc(sizeof(int)*9);
int sizePossible = 0;
```
**The** search of a possible move with the help of the standard function ```strcmp(enemy_pieces)```

**The** random part of the algorithm, where the seed is set by **sizePossible** and then, a new position will be returned in the ```switchPieces```, in order to be processed again with the same random procedure

#### Third stage

In the variable ```allPieces```, there will be some valid moves, some unchanged moves, so a search and delete of the duplicates is neccessary. If the number of moves gathered from this procedure becomes 0, then the AI cant' find any possible move without getting in check, so the algorithm returns ```NULL```, an indicator of the player's win. If the algorithm returns some possible moves, one will be randomly selected and returned by the main random AI function.
```c
for(int i=0;i<nrOfMoves;i++)
{
    if( allPieces[i]->posY == allPieces[i]->posY_initial &&
        allPieces[i]->posX == allPieces[i]->posX_initial)
    {
        for(int j=i;j<nrOfMoves-1;j++)
            allPieces[j] = allPieces[j+1];
        nrOfMoves--;
        i--;
    }
}
if(nrOfMoves == 0)
{
    return NULL;
}
```

#### The AI's pieces

The code for the **Knight** required special care from the development point of view, because it only has 8 possible moves in a 'L' shape. The function that dictates it's movements is:
```c
// relative positions on the knight's move
int xValues[8] = {-1,-2,-2,-1,1,2,2,1};
int yValues[8] = {2,1,-1,-2,-2,-1,1,2};

// itterate the possible moves and get the list of the ones that are possible
for(int i=0;i<8;i++)
{
    // conditions on the possible moves
    if(posY+yValues[i] < 0 || posY+yValues[i] > 7 ||
       posX+xValues[i] < 0 || posX+xValues[i]> 7 )
        continue;
    if(strchr(userPieces,(char)(matrix[posY+yValues[i]][posX+xValues[i]])))
        {
            returnValue->posX += xValues[i];
            returnValue->posY += yValues[i];
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix,'H')))
            {
               possibleMovement[sizePossible++] = i;
            }  
            returnValue->posX -= xValues[i];
            returnValue->posY -= yValues[i];
        }
}
```
The code for the **Queen** is a conglomeration of 4 possible states, because the queen inherits the behaviour of the **Rook** and **Bishop**, so on one hand, the code for these two is clearer, the queen has the ability to override and move on the vertical, horizontal lines, but also on diagonals:
```c
case 'Q':
  for(prob = 0;prob<pieceValue[4][typeGame];prob++)
  {
      allPieces[currentNrOfPieces] = malloc(sizeof(coord));

      allPieces[currentNrOfPieces]->typePiece = 'Q';
      allPieces[currentNrOfPieces] = mainDiagonalMove( currentPieceLocation->posX,
                                                  currentPieceLocation->posY,
                                                  matrix,'Q');
      if(allPieces[currentNrOfPieces]!=NULL)
          currentNrOfPieces++;
      allPieces[currentNrOfPieces] = malloc(sizeof(coord));

      allPieces[currentNrOfPieces]->typePiece = 'Q';
      allPieces[currentNrOfPieces] = secondaryDiagonalMove(currentPieceLocation->posX,
                                                      currentPieceLocation->posY,
                                                      matrix,'Q');
      if(allPieces[currentNrOfPieces]!=NULL)
          currentNrOfPieces++;
      allPieces[currentNrOfPieces] = malloc(sizeof(coord));

      allPieces[currentNrOfPieces]->typePiece = 'Q';
      allPieces[currentNrOfPieces] = horizontalMove(currentPieceLocation->posX,
                                                  currentPieceLocation->posY,
                                                  matrix,'Q');
      if(allPieces[currentNrOfPieces]!=NULL)
          currentNrOfPieces++;
      allPieces[currentNrOfPieces] = malloc(sizeof(coord));

      allPieces[currentNrOfPieces]->typePiece = 'Q';
      allPieces[currentNrOfPieces] = verticalMove( currentPieceLocation->posX,
                                              currentPieceLocation->posY,
                                              matrix,'Q');
      if(allPieces[currentNrOfPieces]!=NULL)
          currentNrOfPieces++;
  }
```
Although the algorithm won't be an expert player, it will be the best training ground for the hashtable component that relies on random and unnexpected behaviour

# <a name="chapter_4">Application Behaviour</a>



# <a name="chapter_5">Conclusion</a>


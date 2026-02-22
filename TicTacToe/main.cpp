#include <bits/stdc++.h>
using namespace std;

class IObserver{
    public:
    virtual void update(string msg)=0;
    virtual ~IObserver(){}
};

class ConsoleNotifier: public IObserver{
    public:
    void update(string msg) override{
        cout << msg << endl;
    }
};

class Symbol{
    char mark;
    public:
    Symbol(char m){
        mark=m;
    }
    char getMark(){
        return mark;
    }
};

class Player{
    int id;
    string name;
    Symbol *s;
    int score;
    public:
    Player(int id,string name,Symbol *s){
        this->id=id;
        this->name=name;
        this->s=s;
        score=0;
    }
    Symbol* getSymbol(){
        return s;
    }
    void incrementScore(){
        score++;
    }
};

class Board{
    vector<vector<Symbol*>>grid;
    int size;
    Symbol *emptyCell;
    public:    
    Board(int s){
        size=s;
        emptyCell=new Symbol('-');
        grid=vector<vector<Symbol*>>(s,vector<Symbol*>(s,emptyCell));
    }
    int getSize(){
        return size;
    }
    bool isCellEmpty(int r,int c){
        if(r<0 or c<0 or r>=size or c>=size) return 0;
        return grid[r][c]==emptyCell;
    }
    bool placeMark(int r,int c,Symbol s){
        if(!isCellEmpty(r,c)) return 0;
        if(isCellEmpty(r,c)){
            grid[r][c]=new Symbol(s.getMark());
        }
        return 1;
    }
    Symbol* getCell(int r,int c){
        if(r<0 or c<0 or r>=size or c>=size) return nullptr;
        return grid[r][c];
    }
    void displayBoard(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                cout << grid[i][j]->getMark() << " ";
            }
            cout << endl;
        }
    }
};

class Rules{
    public:
    virtual bool isValidMove(Board *b,int r,int c)=0;
    virtual bool checkWin(Board *b,Symbol *s)=0;
    virtual bool checkDraw(Board *b)=0;
};

class StandardRules:public Rules{
    public:
    bool isValidMove(Board *b,int r,int c) override{
        return b->isCellEmpty(r,c);
    }
    bool checkWin(Board *b,Symbol *s) override{
        //logic to check win of symbol s in board b
        int size=b->getSize();
        //check rows
        for(int i=0;i<size;i++){
            bool win=true;
            for(int j=0;j<size;j++){
                if(b->getCell(i,j)->getMark()!=s->getMark()){
                    win=false;
                    break;
                }
            }
            if(win) return 1;
        }
        //check columns
        for(int j=0;j<size;j++){
            bool win=true;
            for(int i=0;i<size;i++){
                if(b->getCell(i,j)->getMark()!=s->getMark()){
                    win=false;
                    break;
                }
            }
            if(win) return 1;
        }
        //check diagonals
        bool win=true;
        for(int i=0;i<size;i++){
            if(b->getCell(i,i)->getMark()!=s->getMark()){
                win=false;
                break;
            }
        }
        if(win) return 1;
        win=true;
        for(int i=0;i<size;i++){
            if(b->getCell(i,size-1-i)->getMark()!=s->getMark()){
                win=false;
                break;
            }
        }
        return win;
    }
    bool checkDraw(Board *b) override{
        for(int i=0;i<b->getSize();i++){
            for(int j=0;j<b->getSize();j++){
                if(b->isCellEmpty(i,j)) return 0;
            }
        }
        return 1;
    }
};

class Game{
    Board* board;
    deque<Player*>players;
    Rules* rules;
    vector<IObserver*>Observers;
    bool gameOver;
    public:
    Game(int size){
        board=new Board(size);
        rules=new StandardRules();
        gameOver=false;
    }
    void addPlayer(Player* p){
        players.push_back( p);
    }
    void addObserver(IObserver* observer){
        Observers.push_back(observer);
    }
    void notify(string msg){
        for(auto obs:Observers){
            obs->update(msg);
        }
    }
    void play(){
        int turn=0;
        while(!gameOver){
            Player* currentPlayer=players[turn%players.size()];
            notify("Player " + string(1, currentPlayer->getSymbol()->getMark()) + "'s turn");
            //logic to get move from player and play
            int r,c;
            cin >> r >> c;
            if(rules->isValidMove(board,r,c)){
                board->placeMark(r,c,*currentPlayer->getSymbol());
                board->displayBoard();
                if(rules->checkWin(board,currentPlayer->getSymbol())){
                    notify("Player " + string(1, currentPlayer->getSymbol()->getMark()) + " wins!");
                    currentPlayer->incrementScore();
                    gameOver=true;
                }
                else if(rules->checkDraw(board)){
                    notify("Game is a draw!");
                    gameOver=true;
                }
                turn++;
            }
            else{
                notify("Invalid move! Try again.");
            }
        }
    }
};

enum GameType{
    STANDARD
};

class GameFactory{
    public:
    static Game* createGame(GameType type,int size){
        if(type==STANDARD){
            return new Game(size);
        }
        return nullptr;
    }
};

int main(){
    Game* game=GameFactory::createGame(STANDARD,3);
    ConsoleNotifier* consoleNotifier=new ConsoleNotifier(); 
    game->addObserver(consoleNotifier);
    Player* p1=new Player(1,"Player 1",new Symbol('X'));
    Player* p2=new Player(2,"Player 2",new Symbol('O'));
    game->addPlayer(p1);
    game->addPlayer(p2);
    game->play();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class BoardEntity{
    int start;
    int end;
    public:
    BoardEntity(int start, int end){
        this->start = start;
        this->end = end;
    }
    int getStart(){
        return start;
    }
    int getEnd(){
        return end;
    }
};

class Snake:public BoardEntity{
    public:
    Snake(int start,int end): BoardEntity(start,end){}
};

class Ladder:public BoardEntity{
    public:
    Ladder(int start, int end) : BoardEntity(start,end){}
};

class Rule{
    Board* board;
    int n;
    public:
    Rule(Board* board, int n){
        this->board = board;
        this->n = n;
    }
    int newPos(int curr,int roll){
        int val=curr+roll;
        if(val>n) return val;
        else if(val==n) return n;
        else{
            BoardEntity* entity = board->getEntity(val);
            if(entity!=nullptr){
                return entity->getEnd();
            }
            return val;
        }
    }
};

class Board{
    int size;
    unordered_map<int, BoardEntity*> entities;
    public:
    Board(int size){
        this->size = size;
    }
    int getSize(){
        return size;
    }
    void addEntity(BoardEntity* entity){
        entities[entity->getStart()] = entity;
    }
    BoardEntity* getEntity(int position){
        if(entities.find(position) != entities.end()){
            return entities[position];
        }
        return nullptr;
    }
};

class Player{
    string name;
    int position;
    public:
    Player(string name){
        this->name = name;
        this->position = 0;
    }
    string getName(){
        return name;
    }
    int getPosition(){
        return position;
    }
    void setPosition(int position){
        this->position = position;
    }
};

class Die{
    int n;
    public:
    Die(int n){
        this->n = n;
    }
    int roll(){
        return rand() % n + 1;
    }
};

class Game{
    Board board;
    deque<Player> players;
    Die die;
    public:
    Game(Board board, Die die):board(board), die(die){}
    void addPlayer(Player player){
        players.push_back(player);
    }
    void start(){
        while(!players.empty()){
            Player currentPlayer = players.front();
            players.pop_front();
            int rollValue = die.roll();
            cout << currentPlayer.getName() << " rolled a " << rollValue << endl;
            static Rule rule(&board, board.getSize());
            int newPosition = rule.newPos(currentPlayer.getPosition(), rollValue);
            cout << currentPlayer.getName() << " moved to position " << newPosition << endl;
            if(newPosition == board.getSize()){
                cout << currentPlayer.getName() << " wins!" << endl;
                break;
            }
            currentPlayer.setPosition(newPosition);
            players.push_back(currentPlayer);
        }
    }
};

int main(){
    Player p1("Player 1");
    Player p2("Player 2");
    Board board(100);
    Game game(board, Die(6));
    board.addEntity(new Snake(14,7));
    board.addEntity(new Snake(98,65));
    board.addEntity(new Ladder(4,25));
    board.addEntity(new Ladder(33,70));
    game.addPlayer(p1);
    game.addPlayer(p2);
    game.start();
}
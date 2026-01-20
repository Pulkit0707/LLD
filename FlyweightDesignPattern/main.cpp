#include <bits/stdc++.h>
using namespace std;

class AsteroidFlyweight{
    //Intrinsic Properties
    int l,w,h;
    string c,t,m;
    public:
    AsteroidFlyweight(int l,int w,int h,string c,string t,string m){
        this->l=l;
        this->w=w;
        this->h=h;
        this->c=c;
        this->t=t;
        this->m=m;
    }
    void render(int px,int py,int vx,int vy){
        cout<<"Rendering color "<<c<<" texture "<<t<<" material "<<m<<" px "<<px<<" py "<<py<<" vx "<<vx<<" vy "<<endl;
    }
    static size_t getMemory(){
        return sizeof(int)*3+sizeof(string)*3+32*3;
    }
};

class AsteroidFactory{
    static unordered_map<string,AsteroidFlyweight*>flyweights;
    public:
    static AsteroidFlyweight* getAsteroid(int l,int w,int h,string c,string t,string m){
        string key=to_string(l)+"|"+to_string(w)+"|"+to_string(h)+"|"+c+"|"+t+"|"+m;
        if(flyweights.find(key)==flyweights.end()){
            flyweights[key]=new AsteroidFlyweight(l,w,h,c,t,m);
        }
        return flyweights[key];
    }
    static int getCount(){
        return flyweights.size();
    }
    static size_t getTotalMemory(){
        return flyweights.size()*AsteroidFlyweight::getMemory();
    }
    static void cleanup(){
        flyweights.clear();
    }
};

unordered_map<string,AsteroidFlyweight*>AsteroidFactory::flyweights;

class AsteroidContext{
    //Extrinsic Properties
    int vx,vy,px,py;
    AsteroidFlyweight*flyweight;
    public:
    AsteroidContext(int vx,int vy,int px,int py,AsteroidFlyweight*fl){
        flyweight=fl;
        this->vx=vx;
        this->vy=vy;
        this->px=px;
        this->py=py;
    }
    void render(){
        flyweight->render(px,py,vx,vy);
    }
    void update(){
        px+=vx;
        py+=vy;
    }
    static size_t getMemory(){
        return sizeof(int)*3+sizeof(string)*3+32*3;
    }
};

class Game{
    vector<AsteroidContext*>asteroids;
    public:
    void spawn(int cnt){
        cout<<"Spawning"<<cnt<<"asteroids"<<endl;
        vector<string>colors={"R","B","G"};
        vector<string>textures={"S","M","H"};
        vector<string>materials={"I","S","W"};
        int sizes[]={25,35,45};
        for(int i=0; i<cnt; i++){
            int type=i%3;
            AsteroidFlyweight*flyweight=AsteroidFactory::getAsteroid(
                sizes[type],sizes[type],sizes[type]*10,colors[type],textures[type],materials[type]
            );
            asteroids.push_back(new AsteroidContext(
                2, 3, 100*i+50, 200*i+30, flyweight
            ));
        }
        cout<<"Created "<<asteroids.size()<<" objects"<<endl;
    }
    void renderAll(){
        cout<<"First 5 are"<<endl;
        for(int i=0; i<min(5,(int)asteroids.size()); i++) asteroids[i]->render();
    }
    int getCount(){
        return asteroids.size();
    }
    size_t calculateMemory(){
        size_t contextMemory=asteroids.size()*AsteroidContext::getMemory();
        size_t flyweightMemory=AsteroidFactory::getTotalMemory();
        return contextMemory+flyweightMemory;
    }
};

int main(){
    int cnt=1000000;
    Game*game=new Game();
    game->spawn(cnt);
    game->renderAll();
    size_t totalMemory=game->calculateMemory();
    cout<<"total memory "<<totalMemory;
    return 0; 
}
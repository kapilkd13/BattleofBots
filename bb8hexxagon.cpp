    #include <bits/stdc++.h>
#include<chrono>

    const double MAX = 10000;
    const double MIN = -10000;

    //using namespace std;



    typedef struct move{
    int ini_x,ini_y,fin_x,fin_y;
    bool isJump;
    double movescore;

    }move;

    move finalMove;


int Depth=2;
std::vector<move> globalvec;
std::chrono::time_point<std::chrono::system_clock> start, endpt;

bool compareByScore(const move &a, const move &b)
{
    return a.movescore > b.movescore;
}

    bool validCoord(int x,int y)
    {

    return(x<6&&x>-1&&y<7&&y>-1);


    }


    bool issafeBox(int fin_x,int fin_y,int id,int grid[][7])
    {
    bool safe=true;
    if(fin_y%2){

    if(validCoord(fin_x,fin_y+1)&&(grid[fin_x][fin_y+1]==0||grid[fin_x][fin_y+1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x+1,fin_y+1)&&(grid[fin_x+1][fin_y+1]==0||grid[fin_x+1][fin_y+1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x+1,fin_y)&&(grid[fin_x+1][fin_y]==0||grid[fin_x+1][fin_y]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x+1,fin_y-1)&&(grid[fin_x+1][fin_y-1]==0||grid[fin_x+1][fin_y-1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x,fin_y-1)&&(grid[fin_x][fin_y-1]==0||grid[fin_x][fin_y-1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x-1,fin_y)&&(grid[fin_x-1][fin_y]==0||grid[fin_x-1][fin_y]==((id%2)+1)))
    safe=false;
    }

    else{
    if(validCoord(fin_x-1,fin_y+1)&&(grid[fin_x-1][fin_y+1]==0||grid[fin_x-1][fin_y+1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x,fin_y+1)&&(grid[fin_x][fin_y+1]==0||grid[fin_x][fin_y+1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x+1,fin_y)&&(grid[fin_x+1][fin_y]==0||grid[fin_x+1][fin_y]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x,fin_y-1)&&(grid[fin_x][fin_y-1]==0||grid[fin_x][fin_y-1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x-1,fin_y-1)&&(grid[fin_x-1][fin_y-1]==0||grid[fin_x-1][fin_y-1]==((id%2)+1)))
    safe=false;

    else if(validCoord(fin_x-1,fin_y)&&(grid[fin_x-1][fin_y]==0||grid[fin_x-1][fin_y]==((id%2)+1)))
    safe=false;
    }
    return safe;
    }
    //returns grid score



    bool issolidsafeBox(int fin_x,int fin_y,int id,int grid[][7])
    {
    bool safe=true;
    if(fin_y%2){

    if(validCoord(fin_x,fin_y+1)&&(grid[fin_x][fin_y+1]==0))
    safe=false;

    else if(validCoord(fin_x+1,fin_y+1)&&(grid[fin_x+1][fin_y+1]==0))
    safe=false;

    else if(validCoord(fin_x+1,fin_y)&&(grid[fin_x+1][fin_y]==0))
    safe=false;

    else if(validCoord(fin_x+1,fin_y-1)&&(grid[fin_x+1][fin_y-1]==0))
    safe=false;

    else if(validCoord(fin_x,fin_y-1)&&(grid[fin_x][fin_y-1]==0))
    safe=false;

    else if(validCoord(fin_x-1,fin_y)&&(grid[fin_x-1][fin_y]==0))
    safe=false;
    }

    else{
    if(validCoord(fin_x-1,fin_y+1)&&(grid[fin_x-1][fin_y+1]==0))
    safe=false;

    else if(validCoord(fin_x,fin_y+1)&&(grid[fin_x][fin_y+1]==0))
    safe=false;

    else if(validCoord(fin_x+1,fin_y)&&(grid[fin_x+1][fin_y]==0))
    safe=false;

    else if(validCoord(fin_x,fin_y-1)&&(grid[fin_x][fin_y-1]==0))
    safe=false;

    else if(validCoord(fin_x-1,fin_y-1)&&(grid[fin_x-1][fin_y-1]==0))
    safe=false;

    else if(validCoord(fin_x-1,fin_y)&&(grid[fin_x-1][fin_y]==0))
    safe=false;
    }
    return safe;
    }

    void getSpreadedGrid(int grid[][7], int id,int ini_x,int ini_y,int fin_x,int fin_y )
    {
    if(grid[ini_x][ini_y]==id)
    if(grid[fin_x][fin_y]==0)
    {grid[fin_x][fin_y]=id;

    if(fin_y%2){

    if(validCoord(fin_x,fin_y+1)&&grid[fin_x][fin_y+1]==((id%2)+1))
    grid[fin_x][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y+1)&&grid[fin_x+1][fin_y+1]==((id%2)+1))
    grid[fin_x+1][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y)&&grid[fin_x+1][fin_y]==((id%2)+1))
    grid[fin_x+1][fin_y]=id;

    if(validCoord(fin_x+1,fin_y-1)&&grid[fin_x+1][fin_y-1]==((id%2)+1))
    grid[fin_x+1][fin_y-1]=id;

    if(validCoord(fin_x,fin_y-1)&&grid[fin_x][fin_y-1]==((id%2)+1))
    grid[fin_x][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y)&&grid[fin_x-1][fin_y]==((id%2)+1))
    grid[fin_x-1][fin_y]=id;
    }

    else{
    if(validCoord(fin_x-1,fin_y+1)&&grid[fin_x-1][fin_y+1]==((id%2)+1))
    grid[fin_x-1][fin_y+1]=id;

    if(validCoord(fin_x,fin_y+1)&&grid[fin_x][fin_y+1]==((id%2)+1))
    grid[fin_x][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y)&&grid[fin_x+1][fin_y]==((id%2)+1))
    grid[fin_x+1][fin_y]=id;

    if(validCoord(fin_x,fin_y-1)&&grid[fin_x][fin_y-1]==((id%2)+1))
    grid[fin_x][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y-1)&&grid[fin_x-1][fin_y-1]==((id%2)+1))
    grid[fin_x-1][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y)&&grid[fin_x-1][fin_y]==((id%2)+1))
    grid[fin_x-1][fin_y]=id;
    }
    /*
     for(int i=0;i<6;i++)
      {for(int j=0;j<7;j++)
      {
      printf("%d",grid[i][j]);
      }
      printf("\n");
     // printf("value scanned\n");
      }
      printf("%d %d %d %d %d\n\n", id, ini_x, ini_y, fin_x, fin_y);
    */
    }


    }

    void getJumpedGrid(int grid[][7], int id,int ini_x,int ini_y,int fin_x,int fin_y )
    {
    if(grid[ini_x][ini_y]==id)
    if(grid[fin_x][fin_y]==0)
    {grid[ini_x][ini_y]=0;
    grid[fin_x][fin_y]=id;

    if(fin_y%2){

    if(validCoord(fin_x,fin_y+1)&&grid[fin_x][fin_y+1]==((id%2)+1))
    grid[fin_x][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y+1)&&grid[fin_x+1][fin_y+1]==((id%2)+1))
    grid[fin_x+1][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y)&&grid[fin_x+1][fin_y]==((id%2)+1))
    grid[fin_x+1][fin_y]=id;

    if(validCoord(fin_x+1,fin_y-1)&&grid[fin_x+1][fin_y-1]==((id%2)+1))
    grid[fin_x+1][fin_y-1]=id;

    if(validCoord(fin_x,fin_y-1)&&grid[fin_x][fin_y-1]==((id%2)+1))
    grid[fin_x][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y)&&grid[fin_x-1][fin_y]==((id%2)+1))
    grid[fin_x-1][fin_y]=id;
    }

    else{
    if(validCoord(fin_x-1,fin_y+1)&&grid[fin_x-1][fin_y+1]==((id%2)+1))
    grid[fin_x-1][fin_y+1]=id;

    if(validCoord(fin_x,fin_y+1)&&grid[fin_x][fin_y+1]==((id%2)+1))
    grid[fin_x][fin_y+1]=id;

    if(validCoord(fin_x+1,fin_y)&&grid[fin_x+1][fin_y]==((id%2)+1))
    grid[fin_x+1][fin_y]=id;

    if(validCoord(fin_x,fin_y-1)&&grid[fin_x][fin_y-1]==((id%2)+1))
    grid[fin_x][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y-1)&&grid[fin_x-1][fin_y-1]==((id%2)+1))
    grid[fin_x-1][fin_y-1]=id;

    if(validCoord(fin_x-1,fin_y)&&grid[fin_x-1][fin_y]==((id%2)+1))
    grid[fin_x-1][fin_y]=id;
    }
    }


    }

    void getChangedGrid(int grid[][7],int id,move v)
    {if(v.isJump)
    getJumpedGrid(grid,id,v.ini_x,v.ini_y,v.fin_x,v.fin_y);
    else
    getSpreadedGrid(grid,id,v.ini_x,v.ini_y,v.fin_x,v.fin_y);
    }


    //pass empty cell coord
    bool isSpreadPossible(int grid[][7],int ini_x,int ini_y,int id)
    {
    if(grid[ini_x-1][ini_y]==id)
    return true;

    if(grid[ini_x][ini_y-1]==id)
    return true;


    if(grid[ini_x][ini_y+1]==id)
    return true;

    if(grid[ini_x+1][ini_y-1]==id)
    return true;

    if(grid[ini_x+1][ini_y]==id)
    return true;

    if(grid[ini_x+1][ini_y+1]==id)
    return true;
    return false;

    }

    bool isJumpPossible(int grid[][7],int ini_x,int ini_y,int id)
    {
    if(grid[ini_x-1][ini_y]==id)
    return true;

    if(grid[ini_x][ini_y-1]==id)
    return true;


    if(grid[ini_x][ini_y+1]==id)
    return true;

    if(grid[ini_x+1][ini_y-1]==id)
    return true;

    if(grid[ini_x+1][ini_y]==id)
    return true;

    if(grid[ini_x+1][ini_y+1]==id)
    return true;
    return false;


    }


     void getPossibleSpread(int grid[][7],int ini_x,int ini_y,int id,std::vector<move>&movevec)
    {

    std::vector<move> moves;

    if(grid[ini_x][ini_y]==id)
    {
    if(ini_y%2){
    if(validCoord(ini_x-1,ini_y)&&grid[ini_x-1][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y;
    m->isJump=false;

    movevec.push_back(*m);
    }

    if(validCoord(ini_x,ini_y-1)&&grid[ini_x][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y-1;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x,ini_y+1)&&grid[ini_x][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y+1;
    m->isJump=false;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x+1,ini_y-1)&&grid[ini_x+1][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y-1;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x+1,ini_y)&&grid[ini_x+1][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x+1,ini_y+1)&&grid[ini_x+1][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y+1;
    m->isJump=false;
    movevec.push_back(*m);
    }


    }
    else{

    if(validCoord(ini_x-1,ini_y)&&grid[ini_x-1][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y;
    m->isJump=false;

    movevec.push_back(*m);
    }

    if(validCoord(ini_x-1,ini_y+1)&&grid[ini_x-1][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y+1;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x,ini_y+1)&&grid[ini_x][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y+1;
    m->isJump=false;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x+1,ini_y)&&grid[ini_x+1][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x,ini_y-1)&&grid[ini_x][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y-1;
    m->isJump=false;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x-1,ini_y-1)&&grid[ini_x-1][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y-1;
    m->isJump=false;
    movevec.push_back(*m);
    }



    }
    }

    }




    //get possible jump
    void getPossibleJump(int grid[][7],int ini_x,int ini_y,int id,std::vector<move>&movevec)
    {

    if(grid[ini_x][ini_y]==id)
    {
    if(ini_y%2){
    if(validCoord(ini_x,ini_y+2)&&grid[ini_x][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }
    if(validCoord(ini_x+1,ini_y+2)&&grid[ini_x+1][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }
    if(validCoord(ini_x+2,ini_y+1)&&grid[ini_x+2][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+2;
    m->fin_y=ini_y+1;
    m->isJump=true;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x+2,ini_y)&&grid[ini_x+2][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+2;
    m->fin_y=ini_y;
    m->isJump=true;
    movevec.push_back(*m);}


    if(validCoord(ini_x+2,ini_y-1)&&grid[ini_x+2][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+2;
    m->fin_y=ini_y-1;
    m->isJump=true;
    movevec.push_back(*m);

    }

    if(validCoord(ini_x+1,ini_y-2)&&grid[ini_x+1][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x,ini_y-2)&&grid[ini_x][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x-1,ini_y-2)&&grid[ini_x-1][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x-1,ini_y-1)&&grid[ini_x-1][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y-1;
    m->isJump=true;
    movevec.push_back(*m);
    }



    if(validCoord(ini_x-2,ini_y)&&grid[ini_x-2][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-2;
    m->fin_y=ini_y;
    m->isJump=true;
    movevec.push_back(*m);
    }



    if(validCoord(ini_x-1,ini_y+1)&&grid[ini_x-1][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y+1;
    m->isJump=true;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x-1,ini_y+2)&&grid[ini_x-1][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }}
    else{
    if(validCoord(ini_x,ini_y+2)&&grid[ini_x][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }
    if(validCoord(ini_x+1,ini_y+2)&&grid[ini_x+1][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }
    if(validCoord(ini_x+1,ini_y+1)&&grid[ini_x+1][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y+1;
    m->isJump=true;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x+2,ini_y)&&grid[ini_x+2][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+2;
    m->fin_y=ini_y;
    m->isJump=true;
    movevec.push_back(*m);}


    if(validCoord(ini_x+1,ini_y-1)&&grid[ini_x+1][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y-1;
    m->isJump=true;
    movevec.push_back(*m);

    }

    if(validCoord(ini_x+1,ini_y-2)&&grid[ini_x+1][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x+1;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x,ini_y-2)&&grid[ini_x][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x-1,ini_y-2)&&grid[ini_x-1][ini_y-2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y-2;
    m->isJump=true;
    movevec.push_back(*m);
    }

    if(validCoord(ini_x-2,ini_y-1)&&grid[ini_x-2][ini_y-1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-2;
    m->fin_y=ini_y-1;
    m->isJump=true;
    movevec.push_back(*m);
    }



    if(validCoord(ini_x-2,ini_y)&&grid[ini_x-2][ini_y]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-2;
    m->fin_y=ini_y;
    m->isJump=true;
    movevec.push_back(*m);
    }



    if(validCoord(ini_x-2,ini_y+1)&&grid[ini_x-2][ini_y+1]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-2;
    m->fin_y=ini_y+1;
    m->isJump=true;
    movevec.push_back(*m);
    }


    if(validCoord(ini_x-1,ini_y+2)&&grid[ini_x-1][ini_y+2]==0)
    {move *m=new move;
    m->ini_x=ini_x;
    m->ini_y=ini_y;
    m->fin_x=ini_x-1;
    m->fin_y=ini_y+2;
    m->isJump=true;
    movevec.push_back(*m);
    }
    }
    }

    }

    //spreadmoves
    void getSpreadMoveList(int grid[][7],int id,std::vector<move>&movevec)
    {//vector<move>  spreadmove;

    for(int i=0;i<6;i++)
    {for(int j=0;j<7;j++)
    {
    if(grid[i][j]==id)
    {
    getPossibleSpread(grid,i,j,id,movevec);
    //printf("getspread");
    //spreadmove.insert(spreadmove.end(),movelist.begin(),movelist.end());
    }
    }}
    //return spreadmove;
    }

    //jumpmoves
    void getJumpMoveList(int grid[][7],int id,std::vector<move>&movevec)
    {//vector<move>  jumpmove;
    for(int i=0;i<6;i++)
    {for(int j=0;j<7;j++)
    {
    if(grid[i][j]==id){
    getPossibleJump(grid,i,j,id,movevec);

    //jumpmove.insert(jumpmove.end(),movelist.begin(),movelist.end());
    }
    }}
    //return jumpmove;
    }


    //generate move list
     void getMoveList(int grid[][7],int id,std::vector<move>&movevec)
    {//printf("getmove");
    getSpreadMoveList(grid,id,movevec);
    getJumpMoveList(grid,id,movevec);

    //return spreadmove;

    //spreadmove.insert(spreadmove.end(),jumpmove.begin(),jumpmove.end());
    //return spreadmove;


    }

   double getGridScore(int grid[][7], int id)
    {int score=0;//,count0=0,countpl=0,countoppo=0;
/*
      std::vector<move> movevec3;

    getMoveList(grid,((id%2)+1),movevec3);
    if(movevec3.empty())
    {for(int i=0;i<6;i++)
    {for(int j=0;j<7;j++)
    {
    if(grid[i][j]==id)
     countpl++;
      else if(grid[i][j]==((id%2)+1))
    countoppo++;
    }}
    if(countpl>countoppo)
    return 1000;
    else if(countoppo>countpl)
     return -1000;
    }*/
    for(int i=0;i<6;i++)
    {for(int j=0;j<7;j++)
    {
    if(grid[i][j]==id)
    {if(issafeBox(i,j,id,grid))
    score+=2;
//else if(issafeBox(i,j,id,grid))
  //  score+=0.5;
    //else
    score+=5;
    }
    else if(grid[i][j]==((id%2)+1))
    {if(issafeBox(i,j,((id%2)+1),grid))
    score-=2;
  // else
   //if(issafeBox(i,j,((id%2)+1),grid))
    //score-=0.3;
    //else
    score-=5;
    }
    else{


    }
    }

    }
    return score;

    }


    // Returns optimal value for current player (Initially called
    // for root and maximizer)
    double minimax(int depth, int grid[][7], bool maximizingPlayer,int id, double alpha, double beta,bool firstTurn)
    {  // typedef Iter = std::vector<move>::const_iterator;
        // Terminating condition. i.e leaf node is reached
//double time=(std::clock()-start)/do
    //printf("minmax in");

  //  std::cout << "f(42) = " << fibonacci(42) << '\n';

    endpt = std::chrono::system_clock::now();


//clock code set duration here
if( std::chrono::duration<double>(endpt-start).count()>0.95)
        {
             finalMove=globalvec.front();
           printf("%d %d\n",finalMove.ini_x,finalMove.ini_y);
             printf("%d %d\n",finalMove.fin_x,finalMove.fin_y);

             printf("%d\n",Depth);
             int s=0;
              for (std::vector<move>::iterator it = globalvec.begin(); it!=globalvec.end(); ++it) {s++;
               printf("%lf\n",it->movescore);
                 printf("%d %d\n",it->ini_x,it->ini_y);
             printf("%d %d\n",it->fin_x,it->fin_y);
  }               printf("total size %d\n",s);
           exit(0);
}
        if (depth == 1)
        {
       // printf("%d ",getGridScore(grid,id));
            return getGridScore(grid,id);
    }


    //maximizing cond starts
        if (maximizingPlayer)
        {
            double best = MIN;
         //   return 1;


if(firstTurn)
{
firstTurn=false;
 if(globalvec.empty())
    return getGridScore(grid,id);
    //std::random_shuffle(movevec.begin(), movevec.end());
    for (std::vector<move>::iterator it = globalvec.begin(); it!=globalvec.end(); ++it) {
    int i=0;
    int gridcpy[6][7];
    std::copy(&grid[0][0], &grid[0][0]+6*7,&gridcpy[0][0]);

    getChangedGrid(gridcpy,id,*it);
                double val = minimax(depth-1,gridcpy ,false, id, alpha, beta,firstTurn);
                it->movescore=val;

                best = std::max(best, val);

                alpha = std::max(alpha, best);

                // Alpha Beta Pruning
                if (beta <= best)
                    break;
                    i++;
            }
            return best;
 }  else
 { std::vector<move> movevec;
getMoveList(grid,id,movevec);
            // Recur for left and right children

    if(movevec.empty())
    return getGridScore(grid,id);
    //std::random_shuffle(movevec.begin(), movevec.end());
    for (std::vector<move>::iterator it = movevec.begin(); it!=movevec.end(); ++it) {
    int i=0;
    int gridcpy[6][7];
    std::copy(&grid[0][0], &grid[0][0]+6*7,&gridcpy[0][0]);
    //memcpy(gridcpy, grid, sizeof(grid));
/*
    for(int i=0;i<6;i++)
      {for(int j=0;j<7;j++)
      {
      printf("%d",gridcpy[i][j]);
      }
      printf("\n");
     // printf("value scanned\n");
      }
      printf("%d %d %d  %d\n\n",   it->ini_x,   it->ini_y,   it->fin_x,   it->fin_y);

*/

    getChangedGrid(gridcpy,id,*it);
                double val = minimax(depth-1,gridcpy ,false, id, alpha, beta,firstTurn);
                it->movescore=val;
      /*          printf("after change \n");
    for(int i=0;i<6;i++)
      {for(int j=0;j<7;j++)
      {
      printf("%d",gridcpy[i][j]);
      }
      printf("\n");

     // printf("value scanned\n");
      }*/
   // printf(" value %f\n\n",val);
              //  if(best<val&&depth==0)
              //  finalMove=*it;
                best = std::max(best, val);

                alpha = std::max(alpha, best);

                // Alpha Beta Pruning
                if (beta <= best)
                    break;
                    i++;
            }
            return best;
            }
        }
        else
        {
            double best = MAX;

            // Recur for left and right children
          std::  vector<move> movevec2;

    getMoveList(grid,((id)%2)+1,movevec2);
    if(movevec2.empty())
    return getGridScore(grid,id);
    //std::random_shuffle(movevec2.begin(), movevec2.end());
    for (std::vector<move>::iterator it2 = movevec2.begin(); it2!=movevec2.end(); ++it2) {

    int j=0;
    int gridcpy[6][7];
    std::copy(&grid[0][0], &grid[0][0]+6*7,&gridcpy[0][0]);
    getChangedGrid(gridcpy,((id)%2)+1,*it2);
                double val = minimax(depth-1, gridcpy,true, id, alpha, beta,firstTurn);
                best = std::min(best, val);
                beta = std::min(beta, best);

                // Alpha Beta Pruning
                if (best <= alpha)
                    break;
                    j++;
            }
            return best;
        }
    }

    int main()
    { start = std::chrono::system_clock::now();

      int grid[6][7];
      for(int i=0;i<6;i++)
      {for(int j=0;j<7;j++)
      {
      scanf("%d",&grid[i][j]);
      }
     // printf("value scanned\n");
      }
      int movenumber,id;
      scanf("%d %d",&movenumber,&id);
  getMoveList(grid,id,globalvec);

  while(1){
 double value= minimax(Depth, grid, true, id, MIN, MAX,true);
 std::sort(globalvec.begin(), globalvec.end(), compareByScore);
  /*finalMove=globalvec.front();
           printf("%d %d\n",finalMove.ini_x,finalMove.ini_y);
             printf("%d %d\n",finalMove.fin_x,finalMove.fin_y);
               int s=0;
              for (std::vector<move>::iterator it = globalvec.begin(); it!=globalvec.end(); ++it) {s++;
               printf("%lf\n",it->movescore);

  }
exit(0);
 */
 Depth+=2;
  }



        return 0;
    }


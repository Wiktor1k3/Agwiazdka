#include <iostream>
#include <fstream>
#include <math.h>
#include <float.h>

#define rozmiar 20
#define pozX 2
#define pozY 2
#define celX 16
#define celY 16

using namespace std;

float otw[rozmiar][rozmiar];
int ruch[rozmiar][rozmiar];
int zamk[rozmiar][rozmiar];
int droga[rozmiar][rozmiar];
int rodzice[rozmiar][rozmiar];

int podX,podY;

void sciezka(int sX, int sY)
{
    droga[sX][sY]=3;
    if(sX==pozX && sY==pozY){
        cout<< "\nDroga:\n";
        for(int i=0;i<rozmiar;i++){
            for(int j=0;j<rozmiar;j++){
                cout<<droga[i][j]<<"  ";
            }
            cout<<"\n";
    }
        return;
    }

    if(rodzice[sX][sY]==4){
        sciezka(sX-1,sY);
        }
    if(rodzice[sX][sY]==3){
        sciezka(sX+1,sY);
    }
    if(rodzice[sX][sY]==2){
        sciezka(sX,sY+1);
    }
    if(rodzice[sX][sY]==1){
        sciezka(sX,sY-1);
        }
}


void test(int X, int Y){
    if(X==celX && Y==celY){
        sciezka(X,Y);
        return;
    };
    int k=0;
    podX=X;
    podY=Y;

    if(zamk[X][Y]!=1 && zamk[X][Y]!=5){
        zamk[X][Y]=1;
        if(X<rozmiar-1 && zamk[X+1][Y]!=5 && zamk[X+1][Y]!=1){
            rodzice[X+1][Y]=4;
            ruch[X+1][Y]=ruch[X][Y]+1;
            otw[X+1][Y]=ruch[X][Y]+1+sqrt(pow(X+1-celX,2)+pow(Y-celY,2));
        }
        else{k=k+1;}
        if(Y>0 && zamk[X][Y-1]!=5 && zamk[X][Y-1]!=1){
            rodzice[X][Y-1]=2;
            ruch[X][Y-1]=ruch[X][Y]+1;
            otw[X][Y-1]=ruch[X][Y]+1+sqrt(pow(X-celX,2)+pow(Y-1-celY,2));
        }
        else{k=k+1;}
        if(X>0 && zamk[X-1][Y]!=5 && zamk[X-1][Y]!=1){
            rodzice[X-1][Y]=3;
            ruch[X-1][Y]=ruch[X][Y]+1;
            otw[X-1][Y]=ruch[X][Y]+1+sqrt(pow(X-1-celX,2)+pow(Y-celY,2));
        }
        else{k=k+1;}
        if( Y<rozmiar-1 && zamk[X][Y+1]!=5 && zamk[X][Y+1]!=1){
            rodzice[X][Y+1]=1;
            ruch[X][Y+1]=ruch[X][Y]+1;
            otw[X][Y+1]=ruch[X][Y]+1+sqrt(pow(X-celX,2)+pow(Y+1-celY,2));
        }
        else{k=k+1;}


    }

    float najmniejszy = FLT_MAX;
    int najY,najX;
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            if (zamk[i][j]!=1 && zamk[i][j]!=5 && otw[i][j]>0){
                if(otw[i][j]<=najmniejszy){
                    najmniejszy=otw[i][j];
                    najX=i;
                    najY=j;
                }
            }
        }
    }
    if(najmniejszy==FLT_MAX){
        cout<<"Nie ma drogi";
        return;
    }

    test(najX,najY);


}

int main()
{

    ruch[pozX][pozY]=0;

    fstream plik;
    plik.open("grid.txt",ios :: in);
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            plik>>zamk[i][j];
        }
    }

    for(int i=0;i<rozmiar;i++){
        for(int j=0; j<rozmiar;j++){
            droga[i][j]=zamk[i][j];
            }
    }
    cout<< "\nPodstawa:\n";
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            cout<<zamk[i][j]<<"  ";
            }
        cout<<"\n";
    }

   test(pozX,pozY);
    return 0;
}

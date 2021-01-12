/*Victor de Oliveira Ogata 111838
Gaspar Afonso Rocha 112203*/
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define SRAND_VALUE 1985
#define MAX_THREADS 4
#define GRID_SIZ 2048
using namespace std;

int getNeighbors(int *New_Grid, int i, int j){
    int Alive_C_num = 0;
    int x=-1;
    while(x<2){
        if(x!=0){
            if(New_Grid[(((i+x+GRID_SIZ)%GRID_SIZ)*GRID_SIZ)+((j-1+GRID_SIZ)%GRID_SIZ)]){
                Alive_C_num = Alive_C_num + 1;
            }
            if(New_Grid[(((i+x+GRID_SIZ)%GRID_SIZ)*GRID_SIZ)+((j+GRID_SIZ)%GRID_SIZ)]){
                Alive_C_num = Alive_C_num + 1;
            }
            if(New_Grid[(((i+x+GRID_SIZ)%GRID_SIZ)*GRID_SIZ)+((j+1+GRID_SIZ)%GRID_SIZ)]){
                Alive_C_num = Alive_C_num + 1;
            }
        }
        else{
            if(New_Grid[(((i+x+GRID_SIZ)%GRID_SIZ)*GRID_SIZ)+((j-1+GRID_SIZ)%GRID_SIZ)]){
                Alive_C_num = Alive_C_num + 1;
            }
            if(New_Grid[(((i+x+GRID_SIZ)%GRID_SIZ)*GRID_SIZ)+((j+1+GRID_SIZ)%GRID_SIZ)]){
                Alive_C_num = Alive_C_num + 1;
            }
        }
        x++;
    }
    return Alive_C_num;
}

int main(){
    int Gen=0;
    srand(SRAND_VALUE);

    int *Grid = (int *)malloc(GRID_SIZ * GRID_SIZ * sizeof(int)); 
    int *New_Grid = (int *)malloc(GRID_SIZ * GRID_SIZ * sizeof(int));
    
    for(int i = 0; i<GRID_SIZ; i++) {
        for(int j = 0; j<GRID_SIZ; j++) {
            Grid[(i*GRID_SIZ)+j]= rand() % 2;
        }
    }

    omp_set_num_threads(MAX_THREADS);

    struct timeval inicio, final2;
    gettimeofday(&inicio, NULL);

    while (Gen<4){ 
        if(Gen%100==0){
            cout << "Keep alive " << Gen << "\n";
        }

        for(int a =0; a < GRID_SIZ/2; a++){
            for(int b = 0; b < GRID_SIZ; b++){
                New_Grid[(a*GRID_SIZ)+b] = Grid[(a*GRID_SIZ)+b];
                New_Grid[((GRID_SIZ-1-a)*GRID_SIZ)+b] = Grid[((GRID_SIZ-1-a)*GRID_SIZ)+b];
            }
        }

        #pragma omp parallel default(none) shared(Grid,New_Grid)
        {
            #pragma omp for
            for(int a = 0; a < GRID_SIZ; a++){
                for(int b = 0; b < GRID_SIZ; b++){
                    
                    int Cells_Alive = getNeighbors(New_Grid,a,b);

                    if(Cells_Alive < 2 || Cells_Alive >3){
                        Grid[(a*GRID_SIZ)+b] = 0;
                    }
                    else if(Cells_Alive == 3){
                        Grid[(a*GRID_SIZ)+b] = 1;
                    }
                }
            }
        }

        Gen = Gen +1;
    }

    gettimeofday(&final2, NULL);
    int time = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);
    cout << " Tempo Decorrido: " << time << "ms\n";

    int Cells=0;
    #pragma omp parallel default(none) shared(Grid) reduction (+:Cells)
    {
        #pragma omp for
        for(int a = 0; a < GRID_SIZ; a++){
            for(int b = 0; b < GRID_SIZ; b++){
                if (Grid[(a*GRID_SIZ)+b]){
                        Cells += 1;
                }
            }
        }
    }
    
    gettimeofday(&final2, NULL);
    time = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);
    cout << " Tempo Decorrido: " << time << "ms\n";

    cout<< " Celulas vivas: " << Cells << endl;
}
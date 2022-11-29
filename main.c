#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void criaPopulacao(int tamCromossomo, int **populacao){
    srand((unsigned)time(NULL));

    for(int cromossomo = 0; cromossomo < 300; cromossomo++){
        for(int i = 0; i < tamCromossomo; i++){
            int numAleat = 1+(rand()%30);
            if(i == 0){
                populacao[cromossomo][i] = populacao[cromossomo][tamCromossomo] = numAleat;
            }else{
                //verifico se o número já não existe no cromossomo
                int j = 0;
                while(j < i){
                    if(populacao[cromossomo][j] == numAleat){
                        numAleat = 1+(rand()%30);
                        j = 0;
                    }else{
                        j++;
                    }
                }
                populacao[cromossomo][i] = numAleat;
            }
        }
    }
}

void calculaDistancia(int numCidades, float **distanciaCidades, int *coordenadasX, int *coordenadasY){
    for(int i = 0; i < numCidades; i++){
        for(int j = 0; j < numCidades; j++){
            if(i != j){
                float aux = pow((coordenadasX[j]-coordenadasX[i]),2)+ pow((coordenadasY[j]-coordenadasY[i]),2);
                distanciaCidades[i][j] = distanciaCidades[j][i] = sqrt(aux);
            }
        }
    }
}

int main()
{
    //leitura do arquivo com dados do mapa
    FILE *arquivo;
    arquivo = fopen("Testes/tspcit30.txt", "rt");
    char *result;
    if(arquivo == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    int linha = 0, numCidades = 0;
    //guarda coordenadas das cidades
    int *coordenadasX, *coordenadasY;


    while(linha<=numCidades){
        if(linha == 0){
            result = fscanf(arquivo,"%d",&numCidades);
            coordenadasX = (int*)malloc(numCidades*sizeof(int));
            coordenadasY = (int*)malloc(numCidades*sizeof(int));
        }else{
            result = fscanf(arquivo,"%d%d",&coordenadasX[linha-1],&coordenadasY[linha-1]);
        }
        linha++;
    }

    //só para conferir se gravou corretamente
    for(int i = 1; i<= numCidades; i++){
        printf("cidade %d: (%d, %d)\n",i,coordenadasX[i-1],coordenadasY[i-1]);
    }

    float **distanciaCidades = (float**)malloc(numCidades*sizeof(float*));
    for(int i = 0; i < numCidades; i++){
        distanciaCidades[i] = (float*)malloc(numCidades*sizeof(float));
        for(int j = 0; j < numCidades; j++){
            distanciaCidades[i][j] = 0;
        }
    }

    calculaDistancia(numCidades, distanciaCidades, coordenadasX, coordenadasY);
    //imprime só para conferir
    for(int i = 0; i < numCidades; i++){
        for(int j = 0; j < numCidades; j++){
            if(i != j)
                printf("distancia da cidade %d para a cidade %d: [%f]\n",i+1,j+1,distanciaCidades[i][j]);
        }
    }

    //cria população
    int **populacao = (int**)malloc(300*sizeof(int*));
    for(int i = 0; i < 300; i++){
        populacao[i] = (int*)malloc((numCidades+1)*sizeof(int));
    }

    criaPopulacao(numCidades, populacao);

    //imprime a população
    for(int i = 0; i<300; i++){
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",populacao[i][j]);
        }
        printf("\n");
    }

    /*
    passos seguintes:
    - calcular dist�ncia de todas as cidades
    - calcular fitness de cada individuo
    -fazer a sele��o dos individuos com torneio de tamanho 2
    - fazer crossover e muta��o, que tem taxas de 0.8 e 0.1, respectivamente
    - aplicar crit�rio de parada
    */

    return 0;
}

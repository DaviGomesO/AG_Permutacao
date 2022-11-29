#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void sorteiaCromossomo(int intervaloMax){
    int *cromossomo = (int*)malloc((intervaloMax+1)*sizeof(int));
    srand((unsigned)time(NULL));

    for(int i = 0; i < intervaloMax; i++){
        int numAleat = 1+(rand()%30);
        if(i == 0){
            cromossomo[i] = cromossomo[intervaloMax] = numAleat;
        }else{
            cromossomo[i] = numAleat;
        }
    }

    for(int i = 0; i < intervaloMax; i++){
        printf("%d\n",cromossomo[i]);
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

    //s� para conferir se gravou corretamente
    for(int i = 1; i<= numCidades; i++){
        printf("cidade %d: (%d, %d)\n",i,coordenadasX[i-1],coordenadasY[i-1]);
    }

    //cria popula��o
    int **populacao = (int**)malloc(300*sizeof(int*));
    for(int i = 0; i < 300; i++){
        populacao[i] = (int*)malloc((numCidades+1)*sizeof(int));
    }

    //criar popula��o aleatoriamente
    sorteiaCromossomo(numCidades);

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

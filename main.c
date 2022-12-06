#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void criaPopulacao(int tamCromossomo, int **populacao, int tamPop){
    srand((unsigned)time(NULL));

    for(int cromossomo = 0; cromossomo < tamPop; cromossomo++){
        for(int i = 0; i < tamCromossomo; i++){
            int numAleat = (rand()%tamCromossomo);
            if(i == 0){
                populacao[cromossomo][i] = populacao[cromossomo][tamCromossomo] = numAleat;
            }else{
                //verifico se o número já não existe no cromossomo
                int j = 0;
                while(j < i){
                    if(populacao[cromossomo][j] == numAleat){
                        numAleat = (rand()%tamCromossomo);
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

void fitness(int **populacao, float **distanciaCidades, int numCidades, float *fitnessPop, int tamPop){
    for(int aux = 0; aux < tamPop; aux++){
        float aptidaoIndividuo = 0;
        int i = 0;
        while(i < numCidades-1){
            aptidaoIndividuo += distanciaCidades[populacao[aux][i]][populacao[aux][i+1]];
            //printf("\n%dx%d: %f",populacao[aux][i]+1,populacao[aux][i+1]+1,distanciaCidades[populacao[aux][i]][populacao[aux][i+1]]);
            i++;
        }
        int j = 0;
        aptidaoIndividuo += distanciaCidades[populacao[aux][i]][populacao[aux][j]];
        //printf("\n%dx%d: %f",populacao[aux][i]+1,populacao[aux][i+1]+1,distanciaCidades[populacao[aux][i]][populacao[aux][j]]);

        fitnessPop[aux] = aptidaoIndividuo;
        //printf("\nFitness da sequencia: %f\n", aptidaoIndividuo);
    }
}

void insertion_sort(int **populacao, float *fitnessPop, int tamPop, int numCidades){
    int i, j;
    float valor;

    for(i = 1; i < tamPop; i++){
        valor = fitnessPop[i];
        for(j = i-1; j >= 0 && valor > fitnessPop[j]; j--){
            fitnessPop[j+1] = fitnessPop[j];
            for(int gene = 0; gene <= numCidades; gene++){
                int aux = populacao[j+1][gene];
                populacao[j+1][gene] = populacao[j][gene];
                populacao[j][gene] = aux;
            }
        }
        fitnessPop[j+1] = valor;
    }

    //como queremos o menor valor, vou ordenar de forma crescente
    float *vetAux = (float*)malloc(tamPop*sizeof(float));
    int **matAux = (int**)malloc(tamPop*sizeof(int*));
    for(i = 0; i < tamPop; i++){
        matAux[i] = (int*)malloc((numCidades+1)*sizeof(int));
    }

    int contAux = tamPop-1;
    for(i = 0; i < tamPop; i++){
        for(j = 0; j <= numCidades; j++){
            matAux[i][j] = populacao[contAux][j];
        }
        vetAux[i] = fitnessPop[contAux];
        contAux--;
    }

    for(i = 0; i < tamPop; i++){
        for(j = 0; j <= numCidades; j++){
            populacao[i][j] = matAux[i][j];
        }
        fitnessPop[i] = vetAux[i];
    }
}

int torneio(int **populacao, int numCromossomos, int tamanhoTorneio)
{
    int melhor = 0;
    int aux = 0;

    for (int i = 0; i < tamanhoTorneio; i++)
    {
        aux = rand() % numCromossomos;

        if (melhor == 0)
            melhor = aux;
        else if (aux < melhor)
            melhor = aux;
    }

    return melhor;
}

void crossover(int **populacao, int **novaGeracao, int numCromossomos, int numCidades)
{
    for (int geraFilho = 0; geraFilho < 50; geraFilho++)
    {
        srand((unsigned)time(NULL));
        int tamanhoTorneio = 2;
        int numTorneio_01;
        int numTorneio_02;

        // Gerando Pais
        int *pai_01 = (int *)malloc((numCidades+1) * sizeof(int));
        int *pai_02 = (int *)malloc((numCidades+1) * sizeof(int));

        // Gerando Filhos
        int *filho_01 = (int *)malloc((numCidades+1) * sizeof(int));
        int *filho_02 = (int *)malloc((numCidades+1) * sizeof(int));

        int corte = 1 + (rand() % numCidades);

        // Escolhendo o Pai 01 e Pai 02
        numTorneio_01 = torneio(populacao, numCromossomos, tamanhoTorneio);
        numTorneio_02 = torneio(populacao, numCromossomos, tamanhoTorneio);
        for (int j = 0; j <= numCidades; j++){
            pai_01[j] = populacao[numTorneio_01][j] + 1;
            pai_02[j] = populacao[numTorneio_02][j] + 1;
        }

        // Gerando os filhos a partir dos pais
        for (int i = 0; i < corte; i++)
        {
            filho_01[i] = pai_01[i];
            filho_02[i] = pai_02[i];
        }

        for (int j = corte; j <= numCidades; j++)
        {
            filho_01[j] = pai_02[j];
            filho_02[j] = pai_01[j];
        }

        filho_01[numCidades] = filho_01[0];
        filho_02[numCidades] = filho_02[0];

        // Adicionando valores na matriz de nova geracao
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("Filhos %d: \n" , geraFilho);
        for (int j = 0; j <= numCidades; j++)
        {
            novaGeracao[numCromossomos][j] = filho_01[j];
            novaGeracao[numCromossomos + 1][j] = filho_02[j];
        }
        numCromossomos = numCromossomos + 2;


        // Imprimendo valores

        // printf("Pai 01:\n");
        // for(int j = 0; j <= 100; j++) printf("[%d]", populacao[numTorneio_01][j] + 1);
        // printf("\nnumTorneio_01: %d", numTorneio_01);
        // printf("\npopulacao[%d][0]: %d", numTorneio_01, populacao[numTorneio_01][0] + 1);
        // printf("\n-------------------------------------------------------------------------------------\n");

        // printf("Pai 02:\n");
        // for(int j = 0; j <= 100; j++) printf("[%d]", populacao[numTorneio_02][j] + 1);
        // printf("\nnumGenesAleatorio02: %d", numTorneio_02);
        // printf("\npopulacao[%d][100]: %d", numTorneio_02, populacao[numTorneio_02][100] + 1);
        // printf("\n-------------------------------------------------------------------------------------\n");

        /*
        printf("Filho 01:\n");
        for(int i = 0; i <= numCidades; i++) {
            printf("[%d]", filho_01[i]);
        }
        printf("\n-------------------------------------------------------------------------------------\n");

        printf("Filho 02:\n");
        for(int i = 0; i <= numCidades; i++) {
            printf("[%d]", filho_02[i]);
        }
        printf("\n-------------------------------------------------------------------------------------\n");
        */
    }

    printf("Nova geracao:\n");
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j <= numCidades; j++)
        {
            printf("[%d]", novaGeracao[i][j]);
        }
        printf("\n");
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
    int tamPop = 300;
    int **populacao = (int**)malloc(tamPop*sizeof(int*));
    for(int i = 0; i < tamPop; i++){
        populacao[i] = (int*)malloc((numCidades+1)*sizeof(int));
    }

    criaPopulacao(numCidades, populacao, tamPop);

    //imprime a população
    for(int i = 0; i<tamPop; i++){
        printf("cromossomo %d", i+1);
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",populacao[i][j]+1);
        }
        printf("\n");
    }

    //calcula o fitness de cada cromossomo
    float *fitnessPop = (float*)malloc(tamPop*sizeof(float));
    fitness(populacao, distanciaCidades, numCidades, fitnessPop, tamPop);

    for(int i = 0; i < tamPop; i++){
        printf("\nfitness do cromossomo %d: %f",i+1, fitnessPop[i]);
    }

    //ordena para prevalecer o elitismo
    insertion_sort(populacao, fitnessPop, tamPop, numCidades);

    for(int i = 0; i<tamPop; i++){
        printf("cromossomo %d", i+1);
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",populacao[i][j]+1);
        }
        printf("\n");
    }

    for(int i = 0; i < tamPop; i++){
        printf("\nfitness do cromossomo %d: %f",i+1, fitnessPop[i]);
    }

    int **novaGeracao = (int **)malloc(400 * sizeof(int *));
    for (int i = 0; i < 400; i++)
    {
        novaGeracao[i] = (int *)malloc((numCidades + 1) * sizeof(int));
    }

    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j <= numCidades; j++)
        {
            novaGeracao[i][j] = populacao[i][j];
        }
    }


    crossover(populacao, novaGeracao, tamPop, numCidades);

    /*
    passos seguintes:
    -fazer a sele��o dos individuos com torneio de tamanho 2
    - fazer crossover e muta��o, que tem taxas de 0.8 e 0.1, respectivamente
    - aplicar crit�rio de parada
    */

    return 0;
}

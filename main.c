#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>

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

void fitness(int **populacao, float **distanciaCidades, int numCidades, float *fitnessPop, int tamPop, int posInicial){
    for(int aux = posInicial; aux < tamPop; aux++){
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

int conferirCromossomo(int *filho, int **populacao, int tamPop, int numCidades){
    //confere se o cromossomo criado já está na população
    for(int i = 0; i < tamPop; i++){
        int cont = 0;
        for(int j = 0; j <= numCidades; j++){
            if(filho[j] == populacao[i][j]){
                cont++;
            }
        }

        if(cont > numCidades){
            printf("\ncromossomo ja esta na populacao");
            return -1;
        }
    }
    return 0;
}

int conferirRestricao(int *filho, int numCidades){
    for(int i = 1; i <  numCidades; i++){
        for(int j = 0; j < i; j++){
            //printf("\n%d = %d", filho[i], filho[j]);
            if(filho[i] == filho[j]) return 0;
        }
    }
    return 1;
}

void crossover(int **populacao, int **novaGeracao, int numCromossomos, int numCidades)
{
    int aux = numCromossomos;
    srand((unsigned)time(NULL));
    for (int geraFilho = 0; aux < 400; geraFilho++)
    {
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
            pai_01[j] = populacao[numTorneio_01][j];
            pai_02[j] = populacao[numTorneio_02][j];
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

        /*
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("Filhos %d: \n" , geraFilho);

        printf("filho");
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",filho_01[j]+1);
        }
        printf("\n");
        printf("filho");
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",filho_02[j]+1);
        }
        printf("\n");
        */

        //conferir se os filhos atendem as restrições
        int confereFilho1 = conferirRestricao(filho_01, numCidades);
        int confereFilho2 = conferirRestricao(filho_02, numCidades);

        //conferir se os filhos já estão na população
        //confereFilho1 += conferirCromossomo(filho_01,populacao,numCromossomos,numCidades);
        //confereFilho2 += conferirCromossomo(filho_02,populacao,numCromossomos,numCidades);

        //se os dois filhos passarem das restrições, adiciona os dois
        if(confereFilho1+confereFilho2 == 2){
            //printf("\nAceita os dois!");
            for (int j = 0; j <= numCidades; j++)
            {
                novaGeracao[aux][j] = filho_01[j];
                novaGeracao[aux + 1][j] = filho_02[j];
            }
            aux = aux + 2;
        }else if(confereFilho1+confereFilho2 == 1){
            // se passar somente 1 filho, adiciona o mesmo, provavelmente nunca ocorre
            //printf("\nAceita apenas um");
            if(confereFilho1 == 1){
                for (int j = 0; j <= numCidades; j++)
                {
                    novaGeracao[aux][j] = filho_01[j];
                }
                aux++;
            }else if(confereFilho2 == 1){
                for (int j = 0; j <= numCidades; j++)
                {
                    novaGeracao[aux][j] = filho_02[j];
                }
                aux++;
            }
        }else{
            //printf("\nNao aceita nenhum dos dois");
        }
    }
}

void mutacao(int **populacao, int **novaGeracao, int numCromossomos, int numCidades){
    int aux = numCromossomos;
    srand((unsigned)time(NULL));

    for (int geraFilho = 0; aux < 400; geraFilho++)
    {
        int *pai = (int *)malloc((numCidades+1) * sizeof(int));
        int *filho = (int *)malloc((numCidades+1) * sizeof(int));

        //escolhendo o pai
        int tamanhoTorneio = 2;
        int numTorneio;
        numTorneio = torneio(populacao, numCromossomos, tamanhoTorneio);
        for (int j = 0; j <= numCidades; j++){
            pai[j] = populacao[numTorneio][j];
        }

        //escolhendo duas posições para fazer a troca, evitando trocar a cidade inicial
        int pos1 = 1 + (rand() % numCidades);
        int pos2 = 1 + (rand() % numCidades);
        //int pos3 = 1 + (rand() % numCidades);
        //int pos4 = 1 + (rand() % numCidades);

        //fazendo a troca
        for(int i = 0; i <= numCidades; i++){
            filho[i] = pai[i];
        }
        filho[pos1] = pai[pos2];
        filho[pos2] = pai[pos1];
        //filho[pos3] = pai[pos4];
        //filho[pos4] = pai[pos3];

        //conferindo se esse novo cromossomo passa nas restrições
        int confereFilho = conferirRestricao(filho, numCidades);
        //confereFilho1 += conferirCromossomo(filho_01,populacao,numCromossomos,numCidades);

        if(confereFilho == 1){
            //printf("\nAceita o filho!");
            for (int j = 0; j <= numCidades; j++)
            {
                novaGeracao[aux][j] = filho[j];
            }
            aux++;
        }else{
            //printf("\nNao aceita o filho");
        }

        /*printf("\npai -");
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",pai[j]+1);
        }
        printf("\nposicoes alteradas %d e %d", pos1+1, pos2+2);
        printf("\nfilho -");
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",filho[j]+1);
        }*/
    }
}

void elitismo(int tamCromossomo, int numCidades, int **populacao, int **novaGeracao, int *fitnessPop, int *fitnessNG){
    for(int i = 0; i<tamCromossomo; i++){
        for(int j = 0; j <= numCidades; j++){
            populacao[i][j] = novaGeracao[i][j];
        }
        fitnessPop[i] = fitnessNG[i];
    }
}

int main()
{
    clock_t tem = clock(); //armazena tempo de execução
    //leitura do arquivo com dados do mapa
    FILE *arquivo;
    FILE *resultados;
    arquivo = fopen("Testes/tspcit30.txt", "rt");
    resultados = fopen("Testes/Resultados/resultado teste para mapa com 30 cidades.txt", "wt");
    char *result;
    if(arquivo == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    if(resultados != NULL)
        printf("Arquivo de resultados criado com sucesso!!\n");
    else{
        printf("Problemas na criacao do arquivo\n");
        return 1;
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
    /*for(int i = 0; i<tamPop; i++){
        printf("cromossomo %d", i+1);
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",populacao[i][j]+1);
        }
        printf("\n");
    }*/

    //calcula o fitness de cada cromossomo
    float *fitnessPop = (float*)malloc(tamPop*sizeof(float));
    fitness(populacao, distanciaCidades, numCidades, fitnessPop, tamPop, 0);

    /*for(int i = 0; i < tamPop; i++){
        printf("\nfitness do cromossomo %d: %f",i+1, fitnessPop[i]);
    }*/

    //ordena para prevalecer o elitismo
    insertion_sort(populacao, fitnessPop, tamPop, numCidades);

    /*for(int i = 0; i<tamPop; i++){
        printf("cromossomo %d", i+1);
        for(int j = 0; j <= numCidades; j++){
            printf("[%d]",populacao[i][j]+1);
        }
        printf("\n");
    }

    for(int i = 0; i < tamPop; i++){
        printf("\nfitness do cromossomo %d: %f",i+1, fitnessPop[i]);
    }*/

    printf("\nMelhor cromossomo inicial:\n");
    fprintf(resultados,"Melhor cromossomo inicial:\n");
    for(int i = 0; i <= numCidades; i++){
        printf("[%d]",populacao[0][i]+1);
        fprintf(resultados,"[%d]",populacao[0][i]+1);
    }
    printf("\nFitness: %f", fitnessPop[0]);
    fprintf(resultados,"\nFitness: %f", fitnessPop[0]);

    //aplicando gerações dos novos cromossomos
    srand((unsigned)time(NULL));
    float txCrossover = 0.8, txMutacao = 0.1;
    int periodoSemConvergencia = 0;
    for(int geracoes = 0; geracoes <= 1000; geracoes++){
        if(periodoSemConvergencia == 50){
            printf("\nGeracao %d\nPAROU!!!", geracoes);
            fprintf(resultados,"\nParou na %d geração, devido ao critério de parada, que é o de 50 gerações sem convergir o melhor cromossomo.", geracoes);
            break;
        }
        float melhorSolucao = fitnessPop[0];

        float *fitnessNG = (float*)malloc(400 * sizeof(float));
        int **novaGeracao = (int **)malloc(400 * sizeof(int *));
        for (int i = 0; i < 400; i++)
        {
            novaGeracao[i] = (int *)malloc((numCidades + 1) * sizeof(int));
            fitnessNG[i] = 0;
        }

        for (int i = 0; i < 300; i++)
        {
            for (int j = 0; j <= numCidades; j++)
            {
                novaGeracao[i][j] = populacao[i][j];
            }
            fitnessNG[i] = fitnessPop[i];
        }

        float aplicaCrossover = rand()%101;
        aplicaCrossover = aplicaCrossover/100;
        if(aplicaCrossover <= txCrossover){

            crossover(populacao, novaGeracao, tamPop, numCidades);

            //calcular o fitness desses novos filhos
            fitness(novaGeracao, distanciaCidades, numCidades, fitnessNG, 400, tamPop);
            /*printf("Nova geracao:\n");
            for (int i = 0; i < 400; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", novaGeracao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessNG[i]);
            }*/

            insertion_sort(novaGeracao,fitnessNG,400,numCidades);

            /*for (int i = 0; i < 400; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", novaGeracao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessNG[i]);
            }*/

            //aplicar elitismo pegando os primeiros 300 elementos da nova geração
            elitismo(tamPop,numCidades,populacao,novaGeracao,fitnessPop,fitnessNG);

            /*for (int i = 0; i < 300; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", populacao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessPop[i]);
            }*/
        }

        float aplicaMutacao = rand()%101;
        aplicaMutacao = aplicaMutacao/100;
        if(aplicaMutacao <= txMutacao){
            //mutação
            mutacao(populacao, novaGeracao, tamPop, numCidades);

            //calcular o fitness desses novos filhos
            fitness(novaGeracao, distanciaCidades, numCidades, fitnessNG, 400, tamPop);
            /*printf("Nova geracao:\n");
            for (int i = 0; i < 400; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", novaGeracao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessNG[i]);
            }*/

            insertion_sort(novaGeracao,fitnessNG,400,numCidades);

            /*for (int i = 0; i < 400; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", novaGeracao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessNG[i]);
            }*/

            //aplicar elitismo pegando os primeiros 300 elementos da nova geração
            elitismo(tamPop,numCidades,populacao,novaGeracao,fitnessPop,fitnessNG);

            /*for (int i = 0; i < 300; i++)
            {
                printf("\ncromossomo %d", i+1);
                for (int j = 0; j <= numCidades; j++)
                {
                    printf("[%d]", populacao[i][j]+1);
                }
                printf("\nfitness: %f",fitnessPop[i]);
            }*/
        }

        //critério de parada
        //verifica se o melhor cromossomo da população se alterou
        if(melhorSolucao == fitnessPop[0]){
            periodoSemConvergencia++;
        }else{
            periodoSemConvergencia = 0;
        }
    }


    printf("\nMelhor cromossomo final:\n");
    fprintf(resultados,"\nMelhor cromossomo final:\n");
    for(int i = 0; i <= numCidades; i++){
        printf("[%d]",populacao[0][i]+1);
        fprintf(resultados,"[%d]",populacao[0][i]+1);
    }
    printf("\nFitness: %f", fitnessPop[0]);
    fprintf(resultados,"\nFitness: %f", fitnessPop[0]);

    /*
    passos seguintes:
    - fazer testes - 10 para cada instância obs: quantidade de gerações
    */

    tem = clock() - tem; //tempo final - tempo inicial
    int minutos = (((double)tem)/(CLOCKS_PER_SEC/1000))/60000;
    int segundos = (((((double)tem)/(CLOCKS_PER_SEC/1000))/60000)-minutos)*60;

    fprintf(resultados,"\nTempo de execucao: ~ %d minutos e %d segundos", minutos, segundos);

    fclose(resultados);
    fclose(arquivo);
    return 0;
}

# Algoritmo Genético para o problema da Permutação

<h3>Resumo da aplicação</h3>

<div id="main">
  <p>A aplicação inicia importando a instância, em seguida faz a leitura dos dados que estão dispostos no arquivo, onde na primeira linha se encontra o número correspondente a quantidade de cidades da instância, e após a primeira linha, os dados são dispostos na primeira coluna para a coordanada geográfica X e na segunda coluna para a coordenada geográfica Y. Após a leitura dos dados, é feito o cálculo da distância entre as cidades.</p>
  <p>O calculo consiste em verificar para cada cidade a distância dela para as demais cidadesl, e guarda esses valores em uma matriz criada exclusivamente para armazenar as distâncias.</p>
  <p>Na sequência faz-se a <a href="#criaPopulacao">criação da população</a>, e em seguida faz-se o <a href="#fitness">cálculo da aptidão (fitness)</a> de cada índividuo/cromossomo gerado na população inicial.</p>
  <p>Para auxiliar no elitismo, faz-se a ordenação da população de acordo com o valor de fitness, a ordenação ocorre por meio do algoritmo de Insertion Sort, no qual o mesmo ordena os valores de fitness e a população em ordem crescente.</p>
  <p>Adiante, essa população irá passar por um <a href="#geracoes">período de gerações</a> onde a mesma estará sujeita as transformações de <a href="#">Crossover</a>, que tem taxa de crossover igual a 0.8, e a <a href="#">Mutação</a> que tem a taxa de mutação com valor igual a 0.1 para ser aplicada.</p>
</div>

<div id="criaPopulacao">
  <p>A criação da população se caracteriza no formato aleatório, onde cada criomossomo é criado da seguinte forma:</p>
  <ul>
    <li>Escolhe a cidade inicial de forma aleatória, e aloca a mesma na posição inicial e na posição final do índividuo;</li>
    <li>Em seguida escolhe-se numéros aleatórios entre 1 e o número de cidades;</li>
    <li>Aloca esses números aleatórios nos genes do índividuo, de tal forma que esses números não tenha sido alocado em posições anteriores do vetor. Garantindo a restrição "(i) a de cada cidade a ser visitada apareça em alguma posição da rota;" </li>
    <li>Repete-se o processo até preencher a população</li>
  </ul>
</div>

<div id="fitness">
  <p>A função de fitness consiste em percorrer cada individuo da população passada por parâmetro, e vai adicionando ao valor de fitness do índividuo a medida em que percorre o índividuo, consultando na matriz de distâncias qual o valor de distância a partir da sequência apresentada pelo índividuo, e adicionando o valor a variável de aptidão. Ainda, esse valor de aptidão é armazenado em um vetor excludivo para os fitness de cada índividuo, sendo alocados na posição correspondente em que os mesmos aparecem na população.</p>
</div>

<div id="geracoes">
  <p>Nas gerações são criadas uma população auxiliar com tamanho para alocar 400 individuos, e um vetor auxiliar para os valores de fitness, onde esses irão auxiliar no processo de elitismo para a escolha dos 300 melhores índividuos.</p>
  <p>A população auxiliar recebe os 300 individuos da população principal, assim como o vetor de fitness auxiliar recebe os 300 valores correspondentes.</p>
  <p>Basicamente, após passar pelo processo de Crossover e de Mutação, cria-se novos índividuos e para não perdê-los, alocamos esse individuos na população auxiliar e ordena-se de acordo com os valores de fitness do vetor de fitness auxiliar com os valores da população principal e dos novos índividuos alocados.</p>
  <p>Ainda, é feito a verificação de condição de parada, na qual consulta se o período em que a melhor solução não se altera é igual a 50 gerações.</p>
</div>

<hr/>

### Atualizações:
##### (28/11)
- Ler dados do arquivo em txt (Quantidade de cidades e coordenadas de cada cidades);
- Cria vetor de população com 300 individuos do tamanho de acordo com o número de cidades;
- Cria população aleatoriamente com a função criaPopulacao(), de tal forma que cada cromossomo não tenha repetição de números (obs: apenas no último que informa que da última cidade visitada retorna para a primeira).

##### (29/11)
- Calcula a distância entre as cidades e aloca em uma matriz de tamanho nxn;
- Calcula agora o fitness de cada individuo da população.

#### (06/12)
- Aplicado a ordenação, para fins elitista;
- Faz o torneio entre dois cromossomos da população, escolhendo a melhor solução, no caso a de menor distância;
- Faz o Crossover pegando genes de um pai até um certo corte, e genes de outro pai do corte em diante;
- Aplica o processo de gerações a partir das transformações de crossover;
- Aplica o elitismo;
- Verifica se o cromossomo gerado no crossover atende a restrição.

#### (07/12)
- Criado a mutação que escolhe duas posições do pai, e faz a troca entre essas duas posições no filho;
- Guarda informações do melhor cromossomo em um arquivo txt;
- Armazena informações sobre o tempo de execução;
- Aplicado as taxas de crossover e mutação.

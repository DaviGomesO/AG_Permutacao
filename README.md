# Algoritmo Genético para o problema da Permutação

<h3>Resumo da aplicação</h3>

<div id="main">
  <p>A aplicação inicia importando a instância, em seguida faz a leitura dos dados que estão dispostos no arquivo, onde na primeira linha se encontra o número correspondente a quantidade de cidades da instância, e após a primeira linha, os dados são dispostos na primeira coluna para a coordanada geográfica X e na segunda coluna para a coordenada geográfica Y. Após a leitura dos dados, é feito o cálculo da distância entre as cidades.</p>
  <p>O calculo consiste em verificar para cada cidade a distância dela para as demais cidadesl, e guarda esses valores em uma matriz criada exclusivamente para armazenar as distâncias.</p>
  <p>Na sequência faz-se a <a href="#criaPopulacao">criação da população</a>, e em seguida faz-se o <a href"#fitness">cálculo da aptidão(fitness)</a> de cada índividuo/cromossomo gerado na população inicial.</p>
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
  <p>Essa função percorre cada individuo da população passada por parâmetro, e vai adicionando ao valor de fitness do índividuo a medida em que percorre o índividuo, consultando na matriz de distâncias qual o valor de distância a partir da sequência apresentada pelo índividuo, e adicionando o valor a variável de aptidão. Ainda, esse valor de aptidão é armazenado em um vetor excludivo para os fitness de cada índividuo, sendo alocados na posição correspondente em que os mesmos aparecem na população.</p>
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

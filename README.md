# Algoritmo Genético para o problema da Permutação

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
- Guarda informações do melhor cromossomo em um arquivo txt.

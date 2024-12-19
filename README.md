Bibliotecas adicionadas

As únicas bibliotecas usadas são “<iostream>”, padrão para entrada e saída de
dados, e “<ctime>”, importante nos processos de randomização baseados no tempo.

Inicialização da matriz

Inicialmente, foi plantada a semente de randomização usando a função “srand”
com base no tempo local do computador, oferecido pela biblioteca “<ctime>”. Isso será
útil nos processos que trabalham com aleatoriedade no programa.

As variáveis “comp” e “larg” receberão respectivamente o número de linhas e o
número de colunas da matriz m, que será a vizinhança analisada. Na primeira
formação da matriz, ela será totalmente preenchida com o valor 0 e será impressa no
terminal.

PREENCHIMENTO DA MATRIZ

Agora, será definida a proporção de agentes dos tipos 1 e 2 na matriz,
representando características antagônicas entre eles, e quantas células
permanecerão com o valor 0, indicando as casas vazias da vizinhança. Para isso, foi
criada a variável total, que recebe o produto de “comp” e “larg”, que é igual ao número
de células da matriz m. Primeiramente, 10% desse valor será reservado para casas
vazias na variável “casasVazias”. O restante, alocado na variável “casasOcupadas”,
metade será de agentes do tipo 1 e a outra metade de agentes do tipo 2.


Antes de preencher a matriz com os valores reservados, as variáveis inteiras
“contagem1” e “contagem2” são inicializadas com o valor 0, para que assim, dentro 
do laço de repetição duplo, a estrutura condicional opere controlando a quantidade de
elementos de cada tipo que será alocado no “array” bidimensional. Dessa forma, os
elementos estão dispostos de forma ordenada na matriz.

REALOCANDO OS AGENTES ALEATORIAMENTE

O Modelo de Segregação Social de Schelling trabalha com os agentes
dispostos aleatoriamente na vizinhança, portanto, é preciso realocar os elementos da
matriz em posições aleatórias. Para facilitar nesse processo, um “array”
unidimensional, chamado linear, do tamanho da variável total será criado, e os
elementos da matriz m serão passados para ele.

Depois, começando pelo elemento da última posição do “array” até o primeiro,
será escolhida uma outra posição aleatória para que os elementos alternem seus
lugares. Após esse processo ser feito com todos os elementos, eles são “devolvidos”
para a matriz bidimensional m, e ela é impressa no terminal. Agora, essa é a matriz
que será trabalhada no programa.

OBSERVANDO A SEGREGAÇÃO

Nesse momento, a função “limiteTolerancia()” será chamada.

Se o usuário informar um valor entre 1 e 8, esse valor será retornado para o
“main()” dentro da variável “tolerancia”. Caso contrário, “limitetolerancia()” será
operada novamente até que seja dada entrada a um valor válido. Como cada agente
é rodeado por no máximo outros oito, esse é o máximo aceito como limite de
tolerância.

Também foi criada a variável booleana “matrizAlterada” e a inteira repetições,
que serão usadas a seguir na estrutura do-while.

Início repetição “do-while”

Aqui, “false” foi atribuída a “matrizAlterada”, ou seja, a estrutura de repetição
“do-while” será interrompida quando não houver mudança na situação dessa variável.
Outra forma de interromper as iterações é caso ela exceda o limite de 200 repetições,
por meio da condicional que usa repetições para contar esse número.

Em seguida a matriz será impressa novamente. Na primeira vez, não haverá
nenhuma alteração, pois nenhum requisito de mudança foi avaliado ainda. A partir da
segunda iteração, a matriz será impressa com uma nova formação de grupo. Um
grupo será um conjunto de agentes do tipo 1 insatisfeitos, localizados cada um em
uma casa rodeada por uma quantidade acima do limite de tolerância de agentes do
tipo 2, que se mudam para casas vazias (representadas por 0).

VERIFICAÇÃO DA VIZINHANÇA DE MOORE

Agora, para cada agente do tipo 1, serão analisados os seus vizinhos,
inicializando a variável “contagemDiferentes” em 0, de acordo a Vizinhança de Moore,
em que cada elemento da grade é vizinho dos outros oito ao redor dele. Para isso,
quando o laço duplo de repetição for estiver apontando para um agente do tipo 1, será
percorrido de -1 a 1 horizontal e verticalmente por meio de outra estrutura de repetição
com as variáveis “deslocaLinha” e “deslocaColuna”, para verificar se o vizinho é um
agente do tipo 2. Quando ambas recebem o valor 0, a casa é ignorada porque é a do
próprio agente a ser analisado.


Os elementos dispostos nas bordas da matriz, por natureza não têm oito
vizinhos para serem contados. Porém, por se tratar da Vizinhança de Moore, a
estrutura da matriz, mesmo que bidimensional, será considerada como se fosse uma
esfera, em que não haja um limite que separe a parte de dentro da parte de fora dela.
Assim, todos os elementos terão oito outros como vizinhos e isso será feito pela
função “indiceToroidal()”.


No main(), os parâmetros recebidos por “indiceToroidal()” são i +
“deslocaLinha/Coluna” e “comp/larg”. Eles são, respectivamente, passados para fora
do “main()” como índice e limite. O retorno dessa função chega pela variável
“ajusteLinha/Coluna” e representa qual elemento esse deslocamento corresponde
como vizinho do agente analisado. Ainda no exemplo de uma matriz 10x10, vamos
considerar o elemento da linha 9, coluna 9 (último elemento da matriz) para encontrar
seu vizinho inferior direito.

int main() {
int ajusteLinha = indiceToroidal(9 + 1, 10);
int ajusteLinha = indiceToroidal(9 + 1, 10);
}
int indiceToroidal(10, 10) {
return (10 % 10 + 10) % 10;
(0 + 10) % 10;
10 % 10;
0;
}

Logo, o vizinho inferior direito do agente 9,9 está localizado na posição 0,0.
Sendo assim, a variável “contagemDiferentes” é incrementada em uma unidade a
cada vez que um vizinho do tipo 2 é encontrado.

REALOCAÇÃO DOS VIZINHOS INSATISFEITOS
Quando “contagemDiferentes” excede “tolerancia”, o seguinte procedimento é
iniciado:


É criado um “array” para armazenar todas as posições das casas vazias, para
que os agentes insatisfeitos possam se mudar. A escolha da casa de destino é feita
aleatoriamente usando mais uma vez a função “rand()”. Quando a troca é feita, o valor
de “matrizAlterada” é trocado para “true”, forçando que a estrutura continue a ser
repetida.

IMPRESSÃO FINAL DA MATRIZ

Finalmente, quando não houver mais agentes insatisfeitos, a matriz final é
impressa, sendo essa a vizinhança em que grupos foram formados e a segregação
claramente exposta.

Figura 18: Versão final da matriz

18
Dessa forma, o código passa por todos esses processos e na etapa final, depois
do usuário colocar o seu limite de tolerância, é mostrado para ele os grupos que foram
formados a partir da condição estabelecida. Assim, o modelo de Schelling foi
representado a partir de algoritmos e estruturas de dados.

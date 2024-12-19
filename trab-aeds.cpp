#include <iostream>
#include <ctime> //usada para os processos que trabalham com aleatoriedade (baseada no tempo local do pc)
using namespace std;

//função para conexao das bordas da matriz
int indiceToroidal(int indice, int limite) {
    return (indice % limite + limite) % limite;
}

//função de entrada do limite de tolerancia, que só aceita entre valores entre 1 e 8
int limiteTolerancia() {
    int tolerancia;
    while (true) {
        cout << "Qual sera o limite de tolerancia da vizinhanca? (1 a 8): ";
        cin >> tolerancia;
        if (tolerancia >= 1 && tolerancia <= 8) {
            return tolerancia;
        }
        cout << "Limite invalido. Tente novamente.\n";
    }
}

int main() {
    srand(time(0)); //semente da geração de numeros aleatorios

    //definiçao do tamanho da matriz
    int comp, larg;
    cout << "Informe o numero de linhas da matriz: ";
    cin >> comp;
    cout << "Informe o numero de colunas da matriz: ";
    cin >> larg;

    //inicializaçao da matriz com o valor 0 para todas as casas
    int m[comp][larg];
    for(int i = 0; i<comp; i++) {
        for(int j = 0; j<larg; j++) {
            m[i][j] = 0;
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    //proporção de distribuição dos valores em cada casa
    int total = comp * larg; //numero de celulas da matriz
    int casasVazias = 10.0/100 * (total);
    int casasOcupadas = (total) - casasVazias;
    int tipo1 = casasOcupadas / 2;
    int tipo2 = casasOcupadas - tipo1;

    //distribuiçao ORDENADA dos valores
    int contagem1 = 0;
    int contagem2 = 0;
    for(int i = 0; i<comp; i++) {
        for(int j = 0; j<larg; j++) {    
            if (contagem1 < tipo1) {
                m[i][j] = 1;
                contagem1++;
            } else if (contagem2 < tipo2) {
                m[i][j] = 2;
                contagem2++;
            }
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    //colocando os valores da matriz num array unidimensional para 
    //facilitar na "bagunça" dos elementos
    int linear[total];
    int posicao = 0;
    for (int i = 0; i < comp; i++) {
        for (int j = 0; j < larg; j++) {
            linear[posicao++] = m[i][j];
        }
    }

    //mudando as posiçoes dos valores
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(linear[i], linear[j]); //troca os valores de posição
    }

    //voltando os elementos para um array bidimensional
    posicao = 0;
    for (int i = 0; i<comp; i++) {
        for (int j = 0; j<larg; j++) {
            m[i][j] = linear[posicao++];
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    //verificando os vizinhos
    int tolerancia = limiteTolerancia();
    bool matrizAlterada;
    int repeticoes = 0;

    do {
        matrizAlterada = false;
        repeticoes++;
        if (repeticoes > 200) {
            cout << "Satisfacao global nao alcancada após 200 mudanças." << endl;
            break;
        }
        
        //matriz apos mudança
        cout << endl;
        cout << "Formacao de grupos numero " << repeticoes << endl;
        for (int i = 0; i < comp; i++) {
            for (int j = 0; j < larg; j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;

        for (int i = 0; i < comp; i++) {
            for (int j = 0; j < larg; j++) {
                if (m[i][j] == 1) {
                    int contagemDiferentes = 0;

                    //conta diferentes entre os 8 vizinhos (vizinhança de Moore)
                    for (int deslocaLinha = -1; deslocaLinha <= 1; deslocaLinha++) {
                        for (int deslocaColuna = -1; deslocaColuna <= 1; deslocaColuna++) {
                            if (deslocaLinha == 0 && deslocaColuna == 0) continue; //ignora a célula que está sendo analisada

                            int ajusteLinha = indiceToroidal(i + deslocaLinha, comp);
                            int ajusteColuna = indiceToroidal(j + deslocaColuna, larg);

                            if (m[ajusteLinha][ajusteColuna] != 1 && m[ajusteLinha][ajusteColuna] != 0) {
                                contagemDiferentes++;
                            }
                        }
                    }

                    //identificando as casas vazias e reservando para serem usadas
                    if (contagemDiferentes > tolerancia) {
                        int casasVazias[total][2]; // Array para armazenar as posições das casas 0
                        int contadorVazias = 0;
                        for (int x = 0; x < comp; x++) {
                            for (int y = 0; y < larg; y++) {
                                if (m[x][y] == 0) {
                                    casasVazias[contadorVazias][0] = x;
                                    casasVazias[contadorVazias][1] = y;
                                    contadorVazias++;
                                }
                            }
                        }

                        //"escolher" uma casa 0 aleatória entre as reservadas e trocando os elementos
                        if (contadorVazias > 0) {
                            int escolha = rand() % contadorVazias;
                            int destinoX = casasVazias[escolha][0];
                            int destinoY = casasVazias[escolha][1];

                            swap(m[i][j], m[destinoX][destinoY]);
                            matrizAlterada = true;
                            //impressão das mudanças realizadas
                            cout << "(" << i << ", " << j << ") => (" << destinoX << ", " << destinoY << ")" << endl; 
                        }
                    }
                }
            }
        }
    } while (matrizAlterada);

    cout << endl;

    //impressão da matriz pronta
    cout << "Versao final da matriz: " << endl;
    for (int i = 0; i < comp; i++) {
        for (int j = 0; j < larg; j++) {
            cout << m[i][j] << " ";
        } 
        cout << endl;
    }

    return 0;
}

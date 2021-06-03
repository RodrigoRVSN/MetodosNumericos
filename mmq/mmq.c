/* 
Rodrigo Victor          RA: 200897

-------------------------- Método dos Minímos Quadrados -------------------------------------------------------------------------------

	O método dos mínimos quadrados tem como objetivo criar a melhor equação de reta ou parábola para a realização do ajuste com os variáveis pontos existentes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaFloat(float **p, int tam);
void coletaPontos(int qtd, float *x, float *y);
void verificaGrau(int qtd, float *x, float *y, float *u);
void calculaReta(int qtd, float *x, float *y, float *u);
void mostraU(int qtd, float *u);
void calculaEscalarReta(int qtd, float *produtoEscalar, float *u, float *y);
void mostraEscalar(int qtd, float *produtoEscalar);
void calculaGauss(int qtd, float *produtoEscalar);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Início que pede a quantidade de pontos, coleta os pontos e verifica o grau da equacao (reta ou parabola) em loop */

int main()
{
    int qtd;
    float *x = NULL, *y = NULL, *u = NULL;
    char opc = 's';
    system("color 0A");
    do
    {
        system("cls");
        printf("Digite quantos pontos possui: ");
        fflush(stdin); // limpa buffer do teclado
        scanf("%d", &qtd);
        alocaFloat(&x, qtd);
        alocaFloat(&y, qtd);
        alocaFloat(&u, qtd);
        coletaPontos(qtd, x, y);
        verificaGrau(qtd, x, y, u);
        printf("\nDeseja informar outra tabela? (S/N)");
        fflush(stdin);
        scanf("%c", &opc);
    } while (opc != 'n' && opc != 'N');
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Coleta valores de x e y no ponteiro alocado dinamicamente */

void coletaPontos(int qtd, float *x, float *y)
{
    int i;
    for (i = 0; i < qtd; i++)
    {
        printf("\nDigite o valor de X [%d]: ", i);
        fflush(stdin);
        scanf("%f", x + i); // + i usado para andar o endereço do ponteiro para cada iteração do for
        printf("Digite o valor de Y [%d]: ", i);
        fflush(stdin);
        scanf("%f", y + i);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* funcao pra direcionar o calculo para uma reta ou uma parabola, em loop para salvar os dados.*/

void verificaGrau(int qtd, float *x, float *y, float *u)
{
    char opc;
    int opcGrau;
    do
    {
        printf("\n\nDigite 1 para reta\nDigite 2 para parabola\n");
        fflush(stdin);
        scanf("%d", &opcGrau);
        if (opcGrau == 1)
            calculaReta(qtd, x, y, u);
        //else if(opcGrau == 2)
        //calculaParabola()
        //else
        printf("\n\nDeseja efetuar outro ajuste com mesmos valores? (S/N): ");
        fflush(stdin);
        scanf("%c", &opc);
    } while (opc != 'n' && opc != 'N');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* responsavel por calcular os vetores u0 e u1 quando é uma reta. */

void calculaReta(int qtd, float *x, float *y, float *u)
{
    float valorX = 0;
    int linha, coluna;
    float *produtoEscalar = NULL;
    alocaFloat(&produtoEscalar, qtd);

    for (linha = 0; linha < qtd; linha++) // percorre as linhas dos vetores u para salvar 3 linhas e 2 colunas
    {
        valorX = *(x + linha); // auxiliar para pegar os dados do ponteiro x
        for (coluna = 0; coluna < 2; coluna++)
        {
            *(u + (linha * qtd + coluna)) = pow(valorX, coluna); // faz a potencia do número x de acordo com o numero da coluna e guarda em u
        }
    }

    mostraU(qtd, u);
    calculaEscalarReta(qtd, produtoEscalar, u, y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcao que calcula o produto escalar da reta de acordo com os vetores U*/

void calculaEscalarReta(int qtd, float *produtoEscalar, float *u, float *y)
{
    int coluna, linha, colEscalar, linEscalar;
    float aux = 0;
    for (colEscalar = 0; colEscalar < 3; colEscalar++)
    { // foram utilizados 2 for para incrementar ao mesmo tempo a tabela do produto escalar e dos vetores u
        for (linEscalar = 0; linEscalar < 2; linEscalar++)
        {
            if ((colEscalar == 0 && linEscalar == 1) || (colEscalar == 1 && linEscalar == 0))
            { // se for o [0] [1] ou [1] [0] em que ocorre a  multiplicacao mutua, logo obtem-se o mesmo valor, porem em endereço diferentes
                for (coluna = 0; coluna < 2; coluna++)
                {
                    aux = 0;
                    for (linha = 0; linha < qtd; linha++)
                    { // auxiliar pega o valor de u proximo ou anterior (operador ternario) e incrementa os produtos na auxiliar
                        aux += (coluna == 0) ? *(u + (linha * qtd + coluna)) * *(u + (linha * qtd + coluna + 1)) : *(u + (linha * qtd + coluna)) * *(u + (linha * qtd + coluna - 1));
                    }
                }
                *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux; // coloca em tal endereco do for escalar o aux calculado após o incremento
            }

            else if ((colEscalar == 0 && linEscalar == 0) || (colEscalar == 1 && linEscalar == 1))
            { // se for [0] [0] ou [1] [1] realiza a somatoria do produto consigo mesmo conforme o andamento da linha.
                aux = 0;
                for (linha = 0; linha < qtd; linha++)
                {
                    aux += *(u + (linha * qtd + colEscalar)) * *(u + (linha * qtd + colEscalar));
                }
                *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux; //coloca em tal endereco do for escalar o aux calculado apos o incremento
            }

            else
            { // se for da ultima coluna, que utiliza o y
                if (colEscalar == 2 && linEscalar == 0)
                { // se for a primeira linha
                    for (coluna = 0; coluna < 2; coluna++)
                    { // agora o incremento e a somatoria do produto de u com y
                        aux = 0;
                        for (linha = 0; linha < qtd; linha++)
                        {
                            aux += *(u + (linha * qtd)) * *(y + linha);
                        }
                    }
                    *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux;
                }

                else
                { // se for a segunda linha
                    for (coluna = 0; coluna < 2; coluna++)
                    {
                        aux = 0;
                        for (linha = 0; linha < qtd; linha++)
                        {
                            aux += *(u + (linha * qtd + coluna)) * *(y + linha);
                        }
                    }
                    *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux;
                }
            }
        }
    }
    mostraEscalar(qtd, produtoEscalar);
    calculaGauss(qtd, produtoEscalar);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcao em que se calcula o pivo, m21, os coeficientes com o metodo de gauss e imprime a funcao */

void calculaGauss(int qtd, float *produtoEscalar)
{
    int colEscalar, linEscalar;
    float pivo = *(produtoEscalar + (0 * qtd + 0)); // primeiro endereco
    float m = *(produtoEscalar + (1 * qtd + 0)) / *(produtoEscalar + (0 * qtd + 0)); // divide l2 por l1
    float coefAngular, coefLinear;

    for (colEscalar = 0; colEscalar < 3; colEscalar++)
    {
        for (linEscalar = 0; linEscalar < 2; linEscalar++)
        { // anda a tabela de produto escalar
            if (linEscalar == 1)
            { // se estiver na linha 1 (0, 1) substitui a segunda linha inteira com a subtracao da linha 2 com a linha 1 e seu produto com m
                *(produtoEscalar + (1 * qtd + colEscalar)) = *(produtoEscalar + (1 * qtd + colEscalar)) - *(produtoEscalar + (0 * qtd + colEscalar)) * m;
            }
        }
    }
    coefAngular = *(produtoEscalar + (1 * qtd + 2)) / *(produtoEscalar + (1 * qtd + 1)); // coef angular e a ultima coluna da linha 2 dividida pela linha 2 da coluna 2
    coefLinear = (*(produtoEscalar + (0 * qtd + 2)) - *(produtoEscalar + (0 * qtd + 1)) * coefAngular) / *(produtoEscalar + (0 * qtd + 0)); // subtracao da ultima coluna da linha 1 pela segunda coluna da linha 1 e posterior divisao pelo da linha 1 e coluna 1
    printf("\n\n\n\t-------------- MATRIZ TRIANGULAR SUPERIOR --------------");
    mostraEscalar(qtd, produtoEscalar);
    printf("\n\n\n------------------------\n\na1: %.3f\na0: %.3f\n\nA equacao que se qualifica para esses criterios: f(x)= %.2f + %.2f*x", coefAngular, coefLinear, coefLinear, coefAngular);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Mostra os valores de U */

void mostraU(int qtd, float *u)
{
    int linha, coluna;

    printf("\n\n\n\t\t-------------- U --------------\n");
    for (linha = 0; linha < qtd; linha++)
    {
        printf("\n");
        for (coluna = 0; coluna < 2; coluna++)
        {
            printf("\t\t%.3f\t", *(u + (linha * qtd + coluna)));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Mostra o produto escalar a partir dos vetores U */

void mostraEscalar(int qtd, float *produtoEscalar)
{
    int linha, coluna;
    printf("\n\n\n\t\t-------------- ESCALAR --------------\n");

    for (linha = 0; linha < 2; linha++)
    {
        printf("\n");
        for (coluna = 0; coluna < 3; coluna++)
        {
            printf("\t%.3f\t", *(produtoEscalar + (linha * qtd + coluna)));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Aloca o float */

void alocaFloat(float **p, int tam)
{
    if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
    {
        exit(1);
    }
}

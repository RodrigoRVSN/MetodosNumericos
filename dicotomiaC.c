#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Inicializa as funções, passando os respectivos parametros.
 */

void alocaInt(int **p, int tam);
void alocaFloat(float **p, int tam);
void recebeParametros(int *coef, int *expo, int qtd);
void media(float *a, float *b, float *media, float int1, float int2, int iteracao);
void calculaFuncaoA(int *coef, int *expo, float *pA, float *pFuncA, int qtd);
void calculaFuncaoB(int *coef, int *expo, float *pB, float *pFuncB, int qtd);
void calculaFuncaoMedia(int *coef, int *expo, float *pMedia, float *pFuncMedia, int qtd, int i);
void intervaloParaPonteiro(float *a, float *b, float int1, float int2);
void mostra(float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, int max);
void verificaPar(float *pFuncA, float *pMedia, float *pFuncB, int qtd, float *pA, float *pB, float *pFuncMedia);
void verificaSeTemRaiz(float *pFuncA, float *pFuncB);
void ciclo(float *coef, float *expo, int qtd, float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, float criterio);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Declarando as variáveis e passa as chamadas das funções para o processamento. */

int main()
{
    int qtd;
    float criterio, intervalo1, intervalo2;
    float *pMedia = NULL, *pA = NULL, *pB = NULL, *pFuncA = NULL, *pFuncB = NULL, *pFuncMedia = NULL;
    int *pCoef = NULL, *pExpo = NULL;
    printf("\nDigite a quantidade de termos da equacao (max 10): ");
    scanf("%d", &qtd);
    alocaInt(&pCoef, qtd);
    alocaInt(&pExpo, qtd);
    alocaFloat(&pA, qtd);
    alocaFloat(&pMedia, qtd);
    alocaFloat(&pB, qtd);
    alocaFloat(&pFuncA, qtd);
    alocaFloat(&pFuncMedia, qtd);
    alocaFloat(&pFuncB, qtd);
    recebeParametros(pCoef, pExpo, qtd);
    printf("\n\nDigite o inicio do intervalo e o final: ");
    scanf("%f %f", &intervalo1, &intervalo2);
    intervaloParaPonteiro(pA, pB, intervalo1, intervalo2); //converte o intervalo 1 e 2 em ponteiro na iteracao 0
    media(0, 0, pMedia, intervalo1, intervalo2, 0);
    printf("\n\nDigite a criterio: ");
    scanf("%f", &criterio);
    calculaFuncaoA(pCoef, pExpo, pA, pFuncA, qtd);
    calculaFuncaoB(pCoef, pExpo, pB, pFuncB, qtd);
    verificaSeTemRaiz(pFuncA, pFuncB);
    calculaFuncaoMedia(pCoef, pExpo, pMedia, pFuncMedia, qtd, 0);
    ciclo(pCoef, pExpo, qtd, pA, pMedia, pB, pFuncA, pFuncMedia, pFuncB, criterio);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Recebe os parametros atraves do scanner.
 */
void recebeParametros(int *coef, int *expo, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
    {
        printf("\n\nDigite o coeficiente %i e o expoente %i: ", i + 1, i + 1);
        scanf("%d %d", coef + i, expo + i);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equação e usa o laço do for para iterar n vezes de acordo com o erro.
 */
void calculaFuncaoA(int *coef, int *expo, float *pA, float *pFuncA, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
    {
        *pFuncA += *(coef + i) * pow(*(pA), *(expo + i));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equação e usa o laço do for para iterar n vezes de acordo com o erro.
 */
void calculaFuncaoB(int *coef, int *expo, float *pB, float *pFuncB, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
    {
        *pFuncB += *(coef + i) * pow(*(pB), *(expo + i));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equação e usa o laço do for para iterar n vezes de acordo com o erro.
 */
void calculaFuncaoMedia(int *coef, int *expo, float *pMedia, float *pFuncMedia, int qtd, int i)
{
    int j;
    for (j = 0; j < qtd; j++)
    {
        *(pFuncMedia + i) += *(coef + j) * pow(*(pMedia + i), *(expo + j));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Faz uma validação para saber onde estão acontecendo as trocas de sinais.

Altera os valores dos pontos medios e a partir do resultado obtem se um novo intervalo
 */
void verificaPar(float *pFuncA, float *pMedia, float *pFuncB, int qtd, float *pA, float *pB, float *pFuncMedia)
{
    float a = *(pFuncA + qtd) * *(pFuncMedia + qtd);
    float b = *(pFuncB + qtd) * *(pFuncMedia + qtd);
    if (a < 0)
    {
        *(pFuncB + qtd + 1) = *(pFuncMedia + qtd);
        *(pFuncA + qtd + 1) = *(pFuncA + qtd);
        *(pB + qtd + 1) = *(pMedia + qtd);
        *(pA + qtd + 1) = *(pA + qtd);
    }
    else if (b < 0)
    {
        *(pFuncA + qtd + 1) = *(pFuncMedia + qtd);
        *(pFuncB + qtd + 1) = *(pFuncB + qtd);
        *(pA + qtd + 1) = *(pMedia + qtd);
        *(pB + qtd + 1) = *(pB + qtd);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Chama as funções, onde processará enquanto o módulo do erro(Na linha que está sendo processada) for maior que o criterio (erro informado pelo exercicio).
 */
void ciclo(float *coef, float *expo, int qtd, float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, float criterio)
{

    int i = 0;

    while (fabs(*(funcMedia + i)) > criterio)
    {
        verificaPar(funcA, m, funcB, i, a, b, funcMedia);
        media(a, b, m, 0, 0, i + 1);
        calculaFuncaoMedia(coef, expo, m, funcMedia, qtd, i + 1);
        i++;
    }
    mostra(a, m, b, funcA, funcMedia, funcB, i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica se há raiz na equação(produto maior que 0), pelo contrario encerra o programa.
 */
void verificaSeTemRaiz(float *pFuncA, float *pFuncB)
{
    float produto = *pFuncA * *pFuncB;
    if (produto > 0)
    {
        printf("Nao existe raiz real no intervalo informado! O programa ira fechar.");
        system("pause");
        exit(1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/* calcula media, sendo a partir da validação que as variaveis são diferentes de 0.
 */
void media(float *a, float *b, float *media, float int1, float int2, int iteracao)
{
    if (int1 != 0 && int2 != 0)
        *(media + 0) = (int1 + int2) / 2;
    else
    {
        *(media + iteracao) = ((*(a + iteracao)) + (*(b + iteracao))) / 2;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void intervaloParaPonteiro(float *a, float *b, float int1, float int2)
{
    *(a + 0) = int1;
    *(b + 0) = int2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Faz alocação para o int */

void alocaInt(int **p, int tam)
{
    if ((*p = (int *)realloc(*p, tam * sizeof(int))) == NULL)
        exit(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Faz alocação para o float */

void alocaFloat(float **p, int tam)
{
    if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
        exit(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Exibe a tabela com os resultados, a raiz e o erro.
 */
void mostra(float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, int max)
{
    int z;
    printf("\n\na\t\tm\t\tb\t\tf(a)\t\tf(m)\t\tf(b)\n\n");
    for (z = 0; z <= max; z++)
        printf("\n%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n\n", *(a + z), *(m + z), *(b + z), *(funcA + z), *(funcMedia + z), *(funcB + z));
    printf("\n\nA raiz e %.3f e o erro e de %.3f", *(m + max), *(funcMedia + max));
}

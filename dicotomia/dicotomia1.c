/* 
Abner J. Moura			RA: 190914
Rodrigo Victor          RA: 200897

----------------------------------------------------DICOTOMIA-------------------------------------------------------------------------------

	O processo de dicotomia, destinado a achar a raiz da equacao, basicamente verifica em pares quais sao os valores que dao seguimento para 
elaboracao do exercicio

*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaInt(int **p, int tam);
void alocaFloat(float **p, int tam);
void recebeParametros(int *coef, int *expo, int qtd);
void intervaloParaPonteiro(float *a, float *b, float int1, float int2);
void media(float *a, float *b, float *media, float int1, float int2, int iteracao);
void calculaFuncaoA(int *coef, int *expo, float *pA, float *pFuncA, int qtd);
void calculaFuncaoB(int *coef, int *expo, float *pB, float *pFuncB, int qtd);
void ciclo(int *coef, int *expo, int qtd, float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, float criterio, float k);
void calculaFuncaoMedia(int *coef, int *expo, float *pMedia, float *pFuncMedia, int qtd, int i);
void verificaSeTemRaiz(float *pFuncA, float *pFuncB);
void verificaPar(float *pFuncA, float *pMedia, float *pFuncB, int qtd, float *pA, float *pB, float *pFuncMedia);
void mostra(float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, int max, float k);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Declarando as variaveis e passa as chamadas das funcoes para o processamento. */

int main()
{
    int qtd;
    float criterio, intervalo1, intervalo2, k;
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
    recebeParametros(pCoef, pExpo, qtd); // recebe coeficiente e expoente em ponteiro
    printf("\n\nDigite o inicio do intervalo e o final: ");
    scanf("%f %f", &intervalo1, &intervalo2);
    printf("\n\nDigite a criterio: ");
    scanf("%f", &criterio);
    intervaloParaPonteiro(pA, pB, intervalo1, intervalo2); //converte o intervalo 1 e 2 em ponteiro na iteracao 0
    media(0, 0, pMedia, intervalo1, intervalo2, 0); // calcula a primeira media
    calculaFuncaoA(pCoef, pExpo, pA, pFuncA, qtd); // calcula fa na primeira iteracao
    calculaFuncaoB(pCoef, pExpo, pB, pFuncB, qtd); // calcula fb na primeira iteracao
    verificaSeTemRaiz(pFuncA, pFuncB); // verifica se valores informados possuem raiz
    calculaFuncaoMedia(pCoef, pExpo, pMedia, pFuncMedia, qtd, 0); //calcula fm na primeira iteracao, as restantes sao feitas no ciclo
    k=(log10(intervalo2-intervalo1)-log10(criterio))/log10(2); // calcula k iteracoes
    ciclo(pCoef, pExpo, qtd, pA, pMedia, pB, pFuncA, pFuncMedia, pFuncB, criterio, k); // inicia ciclo de repeticao de verificacoes
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Recebe os parametros atraves do scanner.*/
 
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

/* Faz alocacao para o int */

void alocaInt(int **p, int tam)
{
    if ((*p = (int *)realloc(*p, tam * sizeof(int))) == NULL)
        exit(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Faz alocacao para o float */

void alocaFloat(float **p, int tam)
{
    if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
        exit(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//funcao usada para converter os primeiros intervalos em ponteiro, para facilitar ao criar a tabela mostra.

void intervaloParaPonteiro(float *a, float *b, float int1, float int2)
{
    *(a + 0) = int1;
    *(b + 0) = int2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equacao e usa o laco do for para iterar n vezes de acordo com o erro.
Executada apenas uma vez*/
 
void calculaFuncaoA(int *coef, int *expo, float *pA, float *pFuncA, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
        *pFuncA += *(coef + i) * pow(*(pA), *(expo + i));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equacao e usa o laco do for para iterar n vezes de acordo com o erro.
Executada apenas uma vez*/

void calculaFuncaoB(int *coef, int *expo, float *pB, float *pFuncB, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
        *pFuncB += *(coef + i) * pow(*(pB), *(expo + i));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica se ha raiz na equacao(produto maior que 0), pelo contrario encerra o programa.
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Usando a biblioteca math, calcula o resultado da equacao e usa o laco do for para iterar n vezes de acordo com o erro.
*/
 
void calculaFuncaoMedia(int *coef, int *expo, float *pMedia, float *pFuncMedia, int qtd, int i)
{
    int j;
    for (j = 0; j < qtd; j++)
        *(pFuncMedia + i) += *(coef + j) * pow(*(pMedia + i), *(expo + j));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Chama as funcoes, onde processara enquanto o modulo de fm (na linha que esta sendo processada) for maior que o criterio
em (erro informado pelo exercicio). */
 
void ciclo(int *coef, int *expo, int qtd, float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, float criterio, float k)
{
    int i = 0;
    while (fabs(*(funcMedia + i)) > criterio) // se o valor em modulo de fm for > que criterio continua o ciclo
    {
        verificaPar(funcA, m, funcB, i, a, b, funcMedia);
        media(a, b, m, 0, 0, i + 1);
        calculaFuncaoMedia(coef, expo, m, funcMedia, qtd, i + 1);
        i++;
    }
    mostra(a, m, b, funcA, funcMedia, funcB, i, k);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Faz uma validacao para saber onde estao acontecendo as trocas de sinais.
Altera os valores dos pontos medios e a partir do resultado obtem se um novo intervalo */

void verificaPar(float *pFuncA, float *pMedia, float *pFuncB, int qtd, float *pA, float *pB, float *pFuncMedia)
{
    float a = *(pFuncA + qtd) * *(pFuncMedia + qtd);
    float b = *(pFuncB + qtd) * *(pFuncMedia + qtd);
    if (a < 0)          // se fa * fm for negativo
    {
        *(pFuncB + qtd + 1) = *(pFuncMedia + qtd);
        *(pFuncA + qtd + 1) = *(pFuncA + qtd);
        *(pB + qtd + 1) = *(pMedia + qtd);
        *(pA + qtd + 1) = *(pA + qtd);
    }
    else if (b < 0)     // se fb * fm for negativo
    {
        *(pFuncA + qtd + 1) = *(pFuncMedia + qtd);
        *(pFuncB + qtd + 1) = *(pFuncB + qtd);
        *(pA + qtd + 1) = *(pMedia + qtd);
        *(pB + qtd + 1) = *(pB + qtd);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

/* calcula media, sendo a partir da valida��o que as variaveis s�o diferentes de 0. */
 
void media(float *a, float *b, float *media, float int1, float int2, int iteracao)
{
    if (int1 != 0 && int2 != 0)
        *(media + 0) = (int1 + int2) / 2; //se for a primeira iteracao, calcula media normalmente no primeiro modulo.
    else
        *(media + iteracao) = ((*(a + iteracao)) + (*(b + iteracao))) / 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Exibe a tabela com os resultados, a raiz, o erro e k.
 */
 
void mostra(float *a, float *m, float *b, float *funcA, float *funcMedia, float *funcB, int max, float k)
{
    int z;
    printf("\n\na\t\tm\t\tb\t\tf(a)\t\tf(m)\t\tf(b)\n\n");
    for (z = 0; z <= max; z++)
        printf("\n%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n\n", *(a + z), *(m + z), *(b + z), *(funcA + z), *(funcMedia + z), *(funcB + z));
    printf("\n\nA raiz e %.3f e o erro e de %.3f", *(m+max), *(funcMedia+max));
    printf("\n\nO valor de k e: %f", k);
}

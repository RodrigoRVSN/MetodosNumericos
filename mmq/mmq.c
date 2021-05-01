/* 
Rodrigo Victor          RA: 200897

------------------------------------------------Método dos Minímos Quadrados-------------------------------------------------------------------------------

	O .
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaFloat(float **p, int tam);
void coletaPontos(int qtd, float *x, float *y);
void calculaReta(int qtd, float *x, float *y, float *u);
void calculaEscalarReta(int qtd, float *produtoEscalar, float *u, float *y);
void mostraEscalar(int qtd, float *produtoEscalar);
void mostraU(int qtd, float *u);
void verificaGrau(int qtd, float *x, float *y, float *u);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

int main()
{
    system("cls");
    int qtd;
    float *x = NULL, *y = NULL, *u = NULL;
    printf("\nDigite quantos pontos possui:\n");
    fflush(stdin); // limpa buffer do teclado
    scanf("%d", &qtd);
    alocaFloat(&x, qtd);
    alocaFloat(&y, qtd);
    alocaFloat(&u, qtd);
    coletaPontos(qtd, x, y);
    verificaGrau(qtd, x, y, u);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

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

/*  */

void calculaReta(int qtd, float *x, float *y, float *u)
{
    float valorX = 0;
    int linha, coluna;
    float *produtoEscalar = NULL;
    alocaFloat(&produtoEscalar, qtd);

    for (linha = 0; linha < qtd; linha++)
    {
        valorX = *(x + linha);
        for (coluna = 0; coluna < 2; coluna++)
        {
            *(u + (linha * qtd + coluna)) = pow(valorX, coluna);
        }
    }

    mostraU(qtd, u);
    calculaEscalarReta(qtd, produtoEscalar, u, y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

void calculaEscalarReta(int qtd, float *produtoEscalar, float *u, float *y)
{
    int coluna, linha, colEscalar, linEscalar;
    float aux = 0;
    for (colEscalar = 0; colEscalar < 3; colEscalar++)
    {
        for (linEscalar = 0; linEscalar < 2; linEscalar++)
        {
            if ((colEscalar == 0 && linEscalar == 1) || (colEscalar == 1 && linEscalar == 0))
            {
                for (coluna = 0; coluna < 2; coluna++)
                {
                    aux = 0;
                    for (linha = 0; linha < qtd; linha++)
                    {
                        aux += (coluna == 0) ? *(u + (linha * qtd + coluna)) * *(u + (linha * qtd + coluna + 1)) : *(u + (linha * qtd + coluna)) * *(u + (linha * qtd + coluna - 1));
                        //printf("\nPara %.3f bens aux %.3f esc %d", *(u + (linha * qtd + coluna)), aux, colEscalar);
                    }
                }
                *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux;
            }

            else if ((colEscalar == 1 && linEscalar == 1) || (colEscalar == 0 && linEscalar == 0))
            {
                aux = 0;
                for (linha = 0; linha < qtd; linha++)
                {
                    aux += *(u + (linha * qtd + colEscalar)) * *(u + (linha * qtd + colEscalar));
                }
                *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux;
            }

            else
            {
                if (colEscalar == 2 && linEscalar == 0)
                {
                    for (coluna = 0; coluna < 2; coluna++)
                    {
                        aux = 0;
                        for (linha = 0; linha < qtd; linha++)
                        {
                            aux += *(u + (linha * qtd)) * *(y + linha);
                        }
                    }
                    *(produtoEscalar + (linEscalar * qtd + colEscalar)) = aux;
                }

                else
                {
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
    // *(produtoEscalar + (linha * qtd + coluna))
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

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
    } while (opc != 'n' && opc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

void mostraU(int qtd, float *u)
{
    printf("\n");
    int linha, coluna;

    for (linha = 0; linha < qtd; linha++)
    {
        printf("\n");
        for (coluna = 0; coluna < 2; coluna++)
        {
            printf("%.3f [%d] [%d]\t", *(u + (linha * qtd + coluna)), linha, coluna);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

void mostraEscalar(int qtd, float *produtoEscalar)
{
    int linha, coluna;
    printf("\n\n\n\t\tESCALAR\n");

    for (linha = 0; linha < 2; linha++)
    {
        printf("\n");
        for (coluna = 0; coluna < 3; coluna++)
        {
            printf("%.3f [%d] [%d]\t", *(produtoEscalar + (linha * qtd + coluna)), linha, coluna);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */

void alocaFloat(float **p, int tam)
{
    if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
        exit(1);
}

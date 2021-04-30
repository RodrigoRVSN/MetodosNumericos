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
void calculaU(int qtd, float *x, float *y, float *u);
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
    alocaFloat(&u, (pow(qtd, qtd) + qtd));
    coletaPontos(qtd, x, y);
    calculaU(qtd, x, y, u);
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

void calculaU(int qtd, float *x, float *y, float *u)
{
    float valorX = 0;
    int linha, coluna;
    for (linha = 0; linha < qtd; linha++)
    {
        printf("\n");
        valorX = *(x + linha);
        for (coluna = 0; coluna < qtd; coluna++)
        {
            *(u + (linha * qtd + coluna)) = pow(valorX, coluna);
        }
    }
    mostraU(qtd, u);
    verificaGrau(qtd, x, y, u);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  */


void verificaGrau(int qtd, float *x, float *y, float *u){
    char opc;
    int opcGrau;
    do{
        printf("\n\nDigite 1 para reta\nDigite 2 para parabola\n");
        fflush(stdin);
		scanf("%d", &opcGrau);
        if(opcGrau == 1)
            //calculaReta()
        //else if(opcGrau == 2)
            //calculaParabola()
        //else
        printf("\nDeseja efetuar outro ajuste com mesmos valores? (S/N): ");
        fflush(stdin);
		scanf("%c", &opc);
    } while ( opc != 'n' && opc );
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
        for (coluna = 0; coluna < qtd; coluna++)
        {
            printf("%.3f [%d] [%d]\t", *(u + (linha * qtd + coluna)), linha, coluna);
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

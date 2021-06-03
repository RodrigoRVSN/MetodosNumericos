#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaFloat(float **p, int tam);
void coletaPontos(int qtd, float *x, float *fx);
float verificaMaiorX(float *x, int qtd);
float verificaMenorX(float *x, int qtd, float maior);
void pegaValorDoUsuario(float maior, float menor, float *x, float *fx, int qtd);
float calculaL(int qtd, float xUsuario, float *x, int i, float maior, float menor);
void mostraL(float *l, int qtd);
void calculaFx(float *fx, float *l, int qtd, float xUsuario);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Início do programa em que são informados quantos pontos há na tabela, verifica qual é maior ou menor
e leva para a função que pega o valor de X do usuário. É feita dentro de um Do While para caso o 
usuário queira, pode dar outros pontos para fazer uma nova "tabela" */

int main()
{
	int qtd;
	char opc = 's';
	float *x = NULL, *fx = NULL;
	float maior, menor;
	do
	{
		system("cls"); // limpa tela a cada Do While
		printf("\nDigite quantos pontos possui:\n");
		fflush(stdin); // limpa buffer do teclado
		scanf("%d", &qtd);
		alocaFloat(&x, qtd);
		alocaFloat(&fx, qtd);
		coletaPontos(qtd, x, fx);
		maior = verificaMaiorX(x, qtd);
		menor = verificaMenorX(x, qtd, maior);
		pegaValorDoUsuario(maior, menor, x, fx, qtd);
		printf("\n\n\t\tDeseja continuar a inserir valores? (S/N) ");
		fflush(stdin);
		scanf("%c", &opc);
	} while (opc != 'n' && opc != 'N');
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função usada para preencher a "tabela" com os ponteiros para x e F(x) que estão alocados. */

void coletaPontos(int qtd, float *x, float *fx)
{
	int i;
	for (i = 0; i < qtd; i++)
	{
		printf("\n\nDigite o valor de X [%d]: ", i);
		fflush(stdin);
		scanf("%f", x + i); // + i usado para andar o endereço do ponteiro para cada iteração do for
		printf("Digite o valor de f(X) [%d]: ", i);
		fflush(stdin);
		scanf("%f", fx + i);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica o maior valor de X */

float verificaMaiorX(float *x, int qtd)
{
	int i;
	float maior = *(x + 0); // atribui maior como o primeiro X
	for (i = 0; i < qtd; i++)
	{
		if (*(x + i) > maior) // se o X que acompanha o for for maior que a variável
			maior = *(x + i); //atribui a variável esse X
	}
	return maior;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica menor valor de X */

float verificaMenorX(float *x, int qtd, float maior)
{
	int i;
	float menor = maior; // atribui o maior x para comparar
	for (i = 0; i < qtd; i++)
	{
		if (*(x + i) < menor)
			menor = *(x + i);
	}
	return menor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Nessa função, pede o X para o usuário dentro de um Do While até ele digitar um valor entre o maior 
X e menor X, dentro de um Do While para cada interpolação */

void pegaValorDoUsuario(float maior, float menor, float *x, float *fx, int qtd)
{
	int i;
	float *l = NULL;
	float xUsuario;
	char opc;
	do
	{
		alocaFloat(&l, qtd); // aloca L's
		do					 // verifica se está entre os polos
		{
			printf("\nDigite o ponto X. OBS.: deve estar entre %.2f e %.2f: ", menor, maior);
			fflush(stdin);
			scanf("%f", &xUsuario);
		} while (xUsuario < menor || xUsuario > maior);

		for (i = 0; i < qtd; i++) // calcula o L para cada iteração, sendo L[iteração]
		{
			*(l + i) = calculaL(qtd, xUsuario, x, i, maior, menor);
		}

		mostraL(l, qtd);
		calculaFx(fx, l, qtd, xUsuario);
		printf("\n\nDeseja interpolar outro ponto? (S/N) ");
		fflush(stdin);
		scanf("%c", &opc);
	} while (opc != 'n' && opc != 'N');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Calcula L para cada iteração do for */

float calculaL(int qtd, float xUsuario, float *x, int i, float maior, float menor)
{
	int k, contador = 1;
	float valor = 0, ponte = 0, aux;
	if (qtd == 2) // se for linear (altera o x [indíce] por não poder ser igual ao i)
	{
		if (i == 0) // para a primeira iteração L[0]
			valor = (xUsuario - *(x + 1)) / (*(x + i) - *(x + 1));
		else // L [1]
			valor = (xUsuario - *(x + 0)) / (*(x + i) - *(x + 0));
	}
	else if (qtd > 2) // se não for linear
	{
		for (k = 0; k < (qtd - 1); k++) // for utilizado para calcular o produtório das diferenças, sendo - 1 do total
		{
			contador++;						   //contador entra como 1 e incrementa dentro do for.
			if (k == i && (contador - 2) == 0) // se i e k forem os primeiros termos, L[0]
			{
				aux = *(x + contador); // grava na auxiliar o ponto do próximo X
			}
			else if (k == i) // se forem iguais e não forem o primeiro de todos (L[0] com k = 0)
			{
				aux = *(x + k + 1); // grava o ponto seguinte do ponteiro na auxiliar
				if (qtd > 3)		// se não for quadrática
					contador++;		//incrementa o contador, pois terá que pular o endereço do ponteiro para os próximos itens
			}
			else // se não for igual
			{
				aux = *(x + contador - 2); // grava o auxiliar levando em consideração a iteração do contador caso seja não quadrática
			}
			ponte = (xUsuario - aux) / (*(x + i) - aux); // é realizada a relação das diferenças guardado na ponte, usada como auxiliar para o valor
			if (k == 0) // se for a primeira diferença
			{				   
				valor = ponte; // joga o valor da auxiliar ponte dentro da variável valor
			}
			else
			{
				valor = valor * ponte; // se não for a primeira, realiza o produto da auxiliar com o valor de antes (produtório das diferenças)
			}
		}
	}
	return valor; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Mostra através do for o conteúdo dentro do ponteiro de L, ou seja, mostra os L[indíce] */

void mostraL(float *l, int qtd)
{
	int i;
	for (i = 0; i < qtd; i++)
		printf("\n\tL [%d]: %.3f", i, *(l + i));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Após o cálculo de L, calculo F(x) do X do usuário.*/

void calculaFx(float *fx, float *l, int qtd, float xUsuario)
{
	int i;
	float fxCalculado = 0, produto = 0;
	for (i = 0; i < qtd; i++)
	{
		produto = *(fx + i) * *(l + i); // multiplica F [indíce] pelo L [indíce]
		fxCalculado += produto;			// realiza a somatória de todos os produtos obtidos para apresentar o Y
	}
	printf("\n\n\t\tFx de [%.3f]: %.3f ", xUsuario, fxCalculado);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Realiza alocação dos pontos da tabela e dos L's */

void alocaFloat(float **p, int tam)
{
	if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
		exit(1);
}

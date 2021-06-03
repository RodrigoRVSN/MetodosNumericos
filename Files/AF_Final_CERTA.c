/*
              Grupo 7
Gabriel Fernandes       RA: 200047  
Rodrigo Victor          RA: 200897
Fernando de Carvalho    RA: 200892
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct info_livro{
    char                sigla;                     // [L]ivre, [E]mprestado, [R]eservado
    int                 reg;                       // registro do livro
};

struct info_aluno{
    char                 sigla;
    char                 RA[7];
    int                  dia_ret;                // dia máx=31
    int                  mes_ret;                // mes: fev=28 dias
    int                  dia_dev;                // mes: abril=jun=set=nov=30 dias
    int                  mes_dev;                // os demais = 31 dias
};

typedef struct livro{
    int                 reg;                        // gerado automaticamente
    char                titulo[80];
    char                autor[80];
    struct info_aluno   status[2];      
}livro;

typedef struct aluno{
    char                nome[80];
    char                RA[7];
    int                 emprestado;                  // qtdede livros emprestados ?Max= 3
    int                 reservado;                  // qtde de livros reservados ?Max =1
    struct info_livro   tabela[4];
}aluno;

void aloca_Aluno(aluno **p_aluno, int tam);
void aloca_Livro(livro **p_livro, int tam);
void cadastra_Aluno(aluno *p_aluno);
int validarRA(char *ra);
void cadastra_Livro(livro *p_livro,int tam);
void mostra_livros(livro *p_livro, int opcao_livro);
int parcial_livros_status(livro *p_livro);
void mostra_alunos(aluno *p_aluno, int opcao_aluno);
void mostra_status_livros(livro *p_livro);
void mostra_status_aluno(aluno *p_aluno);
long int verifica_livros();
long int verifica_alunos();
void grava_livro(livro *p_livro, char *str, int pos);
void grava_aluno(aluno *p_aluno,char *str, int pos);
void emprestimo_e_reserva(aluno *p_aluno,livro *p_livro);
void empresta(aluno *p_aluno, livro *p_livro, int pos_alu);
void se_livro_livre(aluno *p_aluno,livro *p_livro);
void reserva(aluno *p_aluno, livro *p_livro, int pos_liv, int pos_alu);
int calendario(int mes);
int dia_da_devolucao(int dia, int max);
int mes_da_devolucao(int dia, int max, int mes);
void devolucao(aluno *p_aluno, livro *p_livro);
int pos_RA(aluno *p_aluno);
int calcularDias(livro *p_livro, int dia, int mes);
void se_reservado_empresta(aluno *p_aluno,livro *p_livro);
void deleta(livro *p_livro, aluno *p_aluno);
void minuscula(char *p);
int busca(livro *p_livro);
void deleta_reservado(livro *p_livro, aluno *p_aluno);
void deleta_emprestimo(livro *p_livro, aluno *p_aluno);

int main(){
    int op_menu, op_cadastro, op_aluno, op_livro;
    long int cont_livro;
    livro *plivro=NULL;
    aluno *paluno=NULL;
    aloca_Aluno(&paluno, 1);
    aloca_Livro(&plivro, 1);

    do
    {
        system("cls");
        system("color 02");
        printf("\n\t\t\t\t\t\tMENU\n\n\n\t[1] Cadastro\n\t[2] Consulta do aluno\n\t[3] Consulta do livro\n\t[4] Emprestimo ou reserva\n\t[5] Status dos livros\n\t[6] Status dos alunos\n\t[7] Devolver\n\t[8] Deletar um livro\n\t[0] Finalizar\n\n\n\t\tQual deseja escolher?   ");
        scanf("%d",&op_menu);
        fflush(stdin);

        switch(op_menu){

            case 1:
                system("cls");
                printf("\n\t\t\t\tO que deseja cadastrar?\n\n\n[1] Para aluno\n[2] Para livro\n\n");
                scanf("%d",&op_cadastro);
                fflush(stdin);

                if(op_cadastro==1)
                {
                   printf("\n\tA opcao escolhida foi a de cadastrar um aluno.\n\n");
                   cadastra_Aluno(paluno);
                }//cadastro do aluno

                else if(op_cadastro==2)
                {
                    printf("\n\tA opcao escolhida foi a de cadastrar um livro.\n\n");
                    cont_livro = verifica_livros();
                    cadastra_Livro(plivro,cont_livro);
                }//cadastro do livro
                else
                    printf("\nOpcao invalida.");
                break;

            case 2:
                system("cls");
                printf("\n\t\t\t\tCONSULTA DO ALUNO\n\n\n[1] Para consulta total\n[2] Para consulta parcial\n\n");
                scanf("%d", &op_aluno);
                fflush(stdin);
                mostra_alunos(paluno, op_aluno);
                break;

            case 3:
                system("cls");
                printf("\n\t\t\t\tCONSULTA DE LIVROS\n\n\n[1] Para consultar todos os livros\n[2] Para procurar pelo titulo\n[3] Para procurar pelo registro\n[4] Para procurar pelo status\n\n");
                scanf("%d",&op_livro);
                fflush(stdin);
                mostra_livros(plivro, op_livro);
                break;

            case 4:
                system("cls");
                printf("\t\t\tEmprestimo ou reserva de livros");
                emprestimo_e_reserva(paluno, plivro);
                break;

            case 5:
                system("cls");
                mostra_status_livros(plivro);
                break;
            
            case 6:
                system("cls");
                mostra_status_aluno(paluno);
                break;

            case 7:
                system("cls");
                devolucao(paluno, plivro);
                break;

            case 8:
                system("cls");
                deleta(plivro,paluno);
                break;

        }//switch case da opcao do menu
        system("pause");
    }while(op_menu!=0);
    return 0;
}//main

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void aloca_Aluno(aluno **p_aluno, int tam){
    if((*p_aluno=(aluno*)realloc(*p_aluno,tam*sizeof(aluno)))==NULL)
        exit(1);
}//aloca aluno

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void aloca_Livro(livro **p_livro, int tam){
    if((*p_livro=(livro*)realloc(*p_livro,tam*sizeof(livro)))==NULL)
        exit(1);
}//aloca livro

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cadastra_Livro(livro *p_livro,int tam){
    int aux_arr;
    aux_arr=busca(p_livro);
    if(aux_arr!=-1)
        tam=aux_arr;
    p_livro->reg=tam+1;
    printf("\nDigite o titulo do livro do registro %d: ",p_livro->reg);
    gets(p_livro->titulo);
    fflush(stdin);
    
    minuscula(&(p_livro->titulo));
    
    printf("\nDigite o autor do livro %s: ", p_livro->titulo);
    gets(p_livro->autor);
    fflush(stdin);
    (p_livro->status+0)->sigla = 'L';
    strcpy((p_livro->status+0)->RA, "000000");
    (p_livro->status+0)->mes_ret = 0;
    (p_livro->status+0)->mes_dev = 0;
    (p_livro->status+0)->dia_ret = 0;
    (p_livro->status+0)->dia_dev = 0;
    (p_livro->status+1)->sigla = 'L';
    strcpy((p_livro->status+1)->RA,"000000");
    (p_livro->status+1)->mes_ret = 0;
    (p_livro->status+1)->mes_dev = 0;
    (p_livro->status+1)->dia_ret = 0;
    (p_livro->status+1)->dia_dev = 0;
    if(aux_arr==-1)  
        grava_livro(p_livro,"ab",1);		
    else
        grava_livro(p_livro,"rb+",tam);
}//cadastra os livros

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cadastra_Aluno(aluno *p_aluno){
    int i, flag;
    char aux_RA[7];
    do {
	printf("\nDigite o nome: ");
    gets(p_aluno->nome);
    fflush(stdin);
    printf("\nDigite o RA: ");
    
	gets(p_aluno->RA);
    fflush(stdin);
    
    p_aluno->emprestado = 0;
    p_aluno->reservado = 0;
    (p_aluno->tabela+0)->sigla = 'L';
    (p_aluno->tabela+1)->sigla = 'L';
    (p_aluno->tabela+2)->sigla = 'L';
    (p_aluno->tabela+3)->sigla = 'L';
    flag = validarRA (p_aluno->RA);
    
    }while ( flag  != 0 );
    
    grava_aluno(p_aluno,"ab",1);
}//cadastra os alunos

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int validarRA(char *ra){
    FILE *fptr = NULL;
    int i, qalu;
    qalu = verifica_alunos();
    aluno *p = NULL;
    aloca_Aluno (&p, 1);

    if (qalu == 0){
        return 0;
    }

    if ((fptr = fopen("aluno.bin","rb"))==NULL)
        printf("\nImpossivel abrir o arquivo, tente novamente");
    
    else{
        for (i = 0; i<qalu; i++){
            fseek(fptr,i*sizeof(aluno),0);
	        fread(p,sizeof(aluno),1,fptr);
	        
            if((strcmp(ra, p->RA)==0))
            {
                printf ("RA ja cadastrado");
                return 1;
            }
			}
			fclose (fptr);
			return 0; 	
        }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_livros(livro *p_livro,int opcao_livro){
    char aux_tit[80];
    int aux_reg,i,achou=0,qliv;
    FILE *fptr = NULL;
    qliv = verifica_livros();
    if((fptr=fopen("livros.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else
    {
        if(opcao_livro == 1)
        {
            for(i=0; i<qliv; i++)
            {
                fseek(fptr,i*sizeof(livro),0);
	            fread(p_livro,sizeof(livro),1,fptr);
                if(strcmp(p_livro->titulo, "@")!=0)
                    printf("\n\nRegistro: %d\nTitulo: %s\nAutor: %s\nStatus [1]: %c\nStatus [2]: %c\n\n\n",p_livro->reg,p_livro->titulo,p_livro->autor,(p_livro->status+0)->sigla,(p_livro->status+1)->sigla);
            }
        }

        else if(opcao_livro==2)
        {
            printf("\nVarredura pelos titulos.\n\nDigite o titulo que procura: ");
            gets(aux_tit);
            fflush(stdin);
            minuscula(&(aux_tit));
            for(i=0; i<qliv; i++)
            {
                fseek(fptr,i*sizeof(livro),0);
	            fread(p_livro,sizeof(livro),1,fptr);
                if((strcmp(aux_tit,p_livro->titulo))==0 && strcmp(p_livro->titulo, "@")!=0)
                {
                    printf("\n\nTitulo: %s\nRegistro: %d\nAutor: %s\nStatus: %c\n",p_livro->titulo,p_livro->reg,p_livro->autor,p_livro->status->sigla);
                    achou=1;
                }
            }
            if(achou!=1)
                printf("\nEste titulo '%s' nao foi encontrado.",aux_tit);
        }

        else if(opcao_livro==3)
        {
            printf("\nVarredura pelo registro.\n\nDigite o registro: ");
            scanf("%d",&aux_reg);
            fflush(stdin);
            for(i=0; i<qliv; i++)
            {
                fseek(fptr,i*sizeof(livro),0);
	            fread(p_livro,sizeof(livro),1,fptr);
                if(aux_reg==p_livro->reg && strcmp(p_livro->titulo, "@")!=0)
                {
                    printf("\n\nRegistro: %d\nTitulo: %s\nAutor: %s\nStatus: %c\n",p_livro->reg,p_livro->titulo,p_livro->autor,p_livro->status->sigla);
                    achou=1;
                }
            }

            if(achou!=1)
                printf("\nRegistro '%d' nao encontrado.",aux_reg);
        }

        else if(opcao_livro==4)
        {
            achou = parcial_livros_status(p_livro);
            if(achou == 0)
                printf("\n\nNenhum livro encontrado.\n");
        }
        else
            printf("\n********************* Opcao invalida.********************\n\n");
        fclose(fptr);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_alunos(aluno *p_aluno, int opcao_aluno){
    char aux_RA[7];
    int i, achou=0,qalu;
    FILE *fptr=NULL;
    qalu = verifica_alunos();
    if((fptr=fopen("aluno.bin","rb"))==NULL)
            printf("\nArquivo nao disponivel...");
    else
    {
        if(opcao_aluno == 1)
        {
            printf("\nConsulta total: ");
            for(i=0; i<qalu; i++)
            {
                fseek(fptr,i*sizeof(aluno),0);
	            fread(p_aluno,sizeof(aluno),1,fptr);
                printf("\nNome: %s\nRA: %s\nLivros emprestados: %i\nLivros reservados: %i\nSituacao: %c\n\n\n", p_aluno->nome, p_aluno->RA, p_aluno->emprestado, p_aluno->reservado, p_aluno->tabela->sigla);
            }
        }
        else if(opcao_aluno == 2)
        {
            printf("\nConsulta parcial\nDigite o RA do aluno: ");
            gets(aux_RA);
            fflush(stdin);
            //minuscula(aux_RA, sizeof(aux_RA));

            for(i=0; i<qalu; i++)
            {
                fseek(fptr,i*sizeof(aluno),0);
	            fread(p_aluno,sizeof(aluno),1,fptr);
                if((strcmp(aux_RA, p_aluno->RA)==0))
                {
                    printf("\nNome: %s\nLivros emprestados: %i\nLivros reservados: %i\nSituacao: %c\n\n\n", p_aluno->nome, p_aluno->emprestado, p_aluno->reservado, p_aluno->tabela->sigla);
                    achou = 1;
                }
            }
            if(achou == 0)
                printf("\nAluno nao encontrado!\n\n\n");
        }

        else
            printf("\n********************* Opcao invalida.********************\n\n");
        fclose(fptr);
    }
}//mostra aluno

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long int  verifica_alunos(){
    long int cont=0;
    FILE *fptr=NULL;
    if((fptr=fopen("aluno.bin","rb"))==NULL)
        return cont;
    else
    {
        fseek(fptr,0,2);
        cont=ftell(fptr)/sizeof(aluno);
        fclose(fptr);
        return cont;
    }//else
}//verifica alunos

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long int verifica_livros(){
    long int cont=0; 
    FILE *fptr=NULL;
    if((fptr=fopen("livros.bin","rb"))==NULL)
        return cont;
    else
    {
        fseek(fptr,0,2);
        cont=ftell(fptr)/sizeof(livro);
        fclose(fptr);
        return cont;
    }//else
}//verifica livros

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void grava_aluno(aluno *p_aluno,char *str, int pos){
    FILE *fptr=NULL;

    if((fptr=fopen("aluno.bin", str))==NULL)
        printf("\nErro ao abrir o arquivo\n");
    else
    {
        if(strcmp(str,"rb+")==0)
            fseek(fptr,pos*sizeof(aluno),0);
            fwrite(p_aluno,sizeof(aluno),1,fptr);
    }//else
    fclose(fptr);
}//grava aluno

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void grava_livro(livro *p_livro, char *str, int pos){
    FILE *fptr=NULL;

    if((fptr=fopen("livros.bin",str))==NULL)
        printf("\nErro ao abrir o arquivo\n");
    else
    {
        if(strcmp(str,"rb+")==0)
            fseek(fptr,pos*sizeof(livro),0);
            fwrite(p_livro,sizeof(livro),1,fptr);

    }//else
    fclose(fptr);
}//grava livros

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void emprestimo_e_reserva(aluno *p_aluno, livro *p_livro){

    char aux_RA[7];
    int i, cont_alunos = verifica_alunos(), cont_livros = verifica_livros, continua=0, pos_alu=0, pos_liv=0;
    FILE *fptr=NULL;
    pos_alu=pos_RA(p_aluno);
        if(p_aluno->emprestado < 3)
            empresta(p_aluno, p_livro, pos_alu);
        else
            empresta(p_aluno, p_livro, pos_alu);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void empresta(aluno *p_aluno, livro *p_livro, int pos_alu){
    char aux_liv [80];
    int i, cont_livro=0, achou=0, pos_liv=0, continua=1;
    FILE *fptr=NULL,*fptrl=NULL;
    printf("\nDigite o titulo do livro que deseja pegar emprestado para o/a %s, RA [%s]:\n",p_aluno->nome,p_aluno->RA);
    gets(aux_liv);
    fflush(stdin);
    minuscula(&aux_liv);
    cont_livro = verifica_livros();
    int cont_alunos = verifica_alunos();

    if((fptrl=fopen("livros.bin","rb"))==NULL)
            printf("\nArquivo nao disponivel...");
    else{        
        for(i=0; i<cont_livro; i++)
        {
            fseek(fptrl,i*sizeof(livro),0);
	        fread(p_livro,sizeof(livro),1,fptrl);
            if((strcmp(aux_liv, p_livro->titulo))==0)
            {   
                pos_liv=i;
                printf("\nO(a) '%s' possui %d livros emprestados [limite de 3].",p_aluno->nome,p_aluno->emprestado);
                if(p_aluno->emprestado==3 && p_aluno->reservado==0)
                    achou = 1;
                
                else if(((p_livro->status+0)->sigla) == 'L' && p_aluno->emprestado<3){
                    se_livro_livre(p_aluno,p_livro);
                    achou = 2;
                }

                else if(((p_livro->status+0)->sigla) == 'E' && p_aluno->reservado==0)
                {
                    if(((p_livro->status+1)->sigla) == 'R')
                        printf("\nEste livro esta emprestado e reservado.");
                    else
                        reserva(p_aluno, p_livro,pos_liv,pos_alu);
                    
                    achou = 3;
                }
            }
            if(achou!=0)
                cont_livro=i;
        }
        if(achou!=1)
                grava_livro(p_livro,"rb+",pos_liv);
        fclose(fptrl);
        
    }

    if((fptr=fopen("aluno.bin","rb"))==NULL) 
            printf("\nArquivo nao disponivel...");
    else{
        if (achou==1){  
            printf("\nSera feita a reserva do livro '%s' para o '%s', pois ja obteve o numero maximo de 3 livros emprestados. ",p_livro->titulo,p_aluno->nome);
            reserva(p_aluno, p_livro,pos_liv,pos_alu);
            grava_aluno(p_aluno,"rb+",pos_alu);
            grava_livro(p_livro,"rb+",pos_liv);
            continua=2;
            }
        else if (achou==2 || achou==3){
            grava_aluno(p_aluno,"rb+",pos_alu);
        }
        fclose(fptr);
    }
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void se_livro_livre(aluno *p_aluno,livro *p_livro){

    int mes=0, max=0, dia=0, dev_dia=0, dev_mes=0;
        do{
            printf("\nDigite o mes: \n[1] Janeiro \n[2] Fevereiro \n[3] Marco\n[4] Abril\n[5] Maio\n[6] Junho\n[7] Julho\n[8] Agosto\n[9] Setembro\n[10] Outubro\n[11] Novembro\n[12] Dezembro\n");
            scanf("%d",&mes);
            fflush(stdin);
            max = calendario(mes);
        }while(mes<1 || mes>12);
            (p_livro->status+0)->mes_ret=mes;           //mes retirada

        do{
            printf("\nDigite o dia da retirada: ");
            scanf("%d",&dia);
            fflush(stdin);
        }while(dia<1 || dia>max);
            (p_livro->status+0)->dia_ret=dia;           //dia retirada

            dev_dia=dia_da_devolucao(dia,max);
            dev_mes=mes_da_devolucao(dia,max,mes);
            (p_livro->status+0)->dia_dev=dev_dia;  
            (p_livro->status+0)->mes_dev=dev_mes;           //devolucao            
            (p_livro->status+0)->sigla = 'E';
            strcpy((p_livro->status+0)->RA,p_aluno->RA);

            if(p_aluno->emprestado == 0)
            {
                (p_aluno->tabela+0)->sigla = 'E';
                (p_aluno->tabela+0)->reg = p_livro->reg;
            }
                
            else if(p_aluno->emprestado == 1)
            {
                (p_aluno->tabela+1)->sigla = 'E';
                (p_aluno->tabela+1)->reg = p_livro->reg;
            } 
            
            else if(p_aluno->emprestado == 2)
            {
                (p_aluno->tabela+2)->sigla = 'E';
                (p_aluno->tabela+2)->reg = p_livro->reg;
            }
            p_aluno->emprestado++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reserva(aluno *p_aluno, livro *p_livro, int pos_liv, int pos_alu)
{
    FILE *fptr = NULL, *fptra=NULL;
    
    int i, j, cont_livros, cont_alunos;

            if((p_livro->status+1)->sigla == 'L'){
                (p_livro->status+1)->sigla = 'R';
                strcpy((p_livro->status+1)->RA, p_aluno->RA);
                cont_livros=i;
            }
            if((p_aluno->tabela+3)->sigla == 'R')
                printf("\nO aluno ja reservou seu limite de livros [1]");
            else if((p_aluno->tabela+3)->sigla != 'R')
            {
                (p_aluno->tabela+3)->sigla = 'R';
                (p_aluno->tabela+3)->reg = p_livro->reg;
                p_aluno->reservado++; 
                printf("\nLivro reservado.\n");  
            }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int calendario(int mes){
    int max;
    if(mes==2)
        max=28;
    else if(mes==4 || mes==6 || mes==9 || mes==11)
        max=30;
    else
        max=31;
    return max;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int dia_da_devolucao(int dia, int max){
    int dia_dev,aux,i;
    if((max-dia)>=7)
        dia_dev=dia+7;
    else {
        for(i=0;dia<max;i++)
            dia++;     
        aux=7-i;
        dia_dev=0+aux;
    }
    return dia_dev;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mes_da_devolucao(int dia, int max, int mes){
    int mes_dev;
    if((max-dia)>=7)
        mes_dev=mes;
    else{
        if(mes+1==13)
            mes_dev=1;
        else
            mes_dev=mes+1;
    }
    return mes_dev;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_status_livros(livro *p_livro){
    int i,j;
    long int qtd_liv = verifica_livros();
    FILE *fptr = NULL;
    if((fptr=fopen("livros.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
            for(i=0; i<qtd_liv; i++){
                printf("\n\n\n\t\t\t\t\tTABELA DO LIVRO [%d]:\n",i+1);
                printf("___________________________________________________________________________________________________________________________");
                printf("\n\n\t|Reg| |Sigla|   |RA|\t|Retirada|\t|Devolucao|\t|Autor|       |Titulo|\n");
                printf("___________________________________________________________________________________________________________________________");
                fseek(fptr,i*sizeof(livro),0);
	            fread(p_livro,sizeof(livro),1,fptr);
             
                for(j=0;j<2;j++){
                    printf("\n(%d)|\t|%d|   |%c|     |%s|\t|%d||%d|\t\t|%d||%d|           |%s|       |%s|\n", j+1, p_livro->reg,(p_livro->status+j)->sigla,(p_livro->status+j)->RA,(p_livro->status+j)->dia_ret,(p_livro->status+j)->mes_ret,(p_livro->status+j)->dia_dev,(p_livro->status+j)->mes_ret,p_livro->autor,p_livro->titulo);
                    printf("--------------------------------------------------------------------------------------------------------------------------");
                }

            }
            
        fclose(fptr);
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_status_aluno(aluno *p_aluno){
    int i,j;
    long int qtd_alu = verifica_alunos();
    FILE *fptr = NULL;
    if((fptr=fopen("aluno.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
        for(i=0; i<qtd_alu; i++){
            printf("\n\n\n\t\tTABELA DOS ALUNOS NUM.: %d\n\n",i+1);
            printf("______________________________________________________________");
            printf("\n\n\t|Nome|\t|RA|\t|Emp|\t|Res|\t|Sigla|\t|Reg|\n");
            printf("______________________________________________________________");
            fseek(fptr,i*sizeof(aluno),0);
	        fread(p_aluno,sizeof(aluno),1,fptr);
            for(j=0;j<4;j++){
                printf("\n(%d) |\t |%s|\t|%s|\t |%d|\t |%d|\t |%c|\t |%d|\n", j+1, p_aluno->nome, p_aluno->RA, p_aluno->emprestado, p_aluno->reservado, (p_aluno->tabela+j)->sigla, (p_aluno->tabela+j)->reg);
                printf("------------------------------------------------------------");
            }
        }
        fclose(fptr);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void devolucao(aluno *p_aluno, livro *p_livro){
    int pos_alu=0, pos_liv=0, qtdliv, i, j, dia, mes, max, dias_calculados, multa, continua;
    char aux_tit[80];
    FILE *fptr=NULL, *fptrA=NULL;
    pos_alu = pos_RA(p_aluno);
    qtdliv = verifica_livros(); 

    if((fptr=fopen("livros.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");

    else{ 
        printf("\nDigite o livro que sera devolvido: ");
        gets(aux_tit);
        fflush(stdin);
        
		minuscula (&aux_tit);
        
        for(i=0; i<qtdliv; i++)
        {
            pos_liv=i;
            fseek(fptr,i*sizeof(livro),0);
	        fread(p_livro,sizeof(livro),1,fptr);
            if(strcmp(aux_tit, p_livro->titulo)==0)
            {
                if(strcmp((p_livro->status+0)->RA, p_aluno->RA) == 0 && (p_livro->status+0)->sigla == 'E')
                {  
                    do{
                        printf("\nDigite o mes: \n[1] Janeiro \n[2] Fevereiro \n[3] Marco\n[4] Abril\n[5] Maio\n[6] Junho\n[7] Julho\n[8] Agosto\n[9] Setembro\n[10] Outubro\n[11] Novembro\n[12] Dezembro\n");
                        scanf("%d",&mes);
                        fflush(stdin);
                    }while(mes>12 || mes<1); 
                    max = calendario(mes);
                    do{
                        printf("\nDigite que dia e hoje (O mes %d vai ate o dia %d): ",mes,max);
                        scanf("%d",&dia); 
                        fflush(stdin);
                    }while(dia<1 || dia>max);
                    dias_calculados = calcularDias(p_livro,dia,mes);
                    if (dias_calculados < 0)
                        printf("\nDevolvido antes do dia.");
                        
                    else if (dias_calculados == 0 )
                        printf("\nRetornado no dia limite.");
                        
                    else{
                        multa = dias_calculados*3;
                        printf("\nO livro foi entregue %d dias atrasados, deve-se pagar R$ %d,00.",dias_calculados,multa);
                    }
                    if((p_livro->status+1)->sigla=='R'){

                        (p_livro->status+0)->sigla = 'E';
                        strcpy((p_livro->status+0)->RA, (p_livro->status+1)->RA);
                        (p_livro->status+0)->dia_ret = dia;
                        (p_livro->status+0)->mes_ret = mes;
                        (p_livro->status+0)->dia_dev = dia_da_devolucao(dia, max);
                        (p_livro->status+0)->mes_dev = mes_da_devolucao(dia, max, mes);
                        

                        (p_livro->status+1)->sigla = 'L';
                        strcpy((p_livro->status+1)->RA,"000000");
                        (p_livro->status+1)->dia_ret = 0;
                        (p_livro->status+1)->mes_ret = 0;
                        (p_livro->status+1)->dia_dev = 0;
                        (p_livro->status+1)->mes_dev = 0;
                        for(j=0;j<3;j++){
                            if(p_livro->reg==(p_aluno->tabela+j)->reg){
                                (p_aluno->tabela+j)->sigla = 'L';
                                (p_aluno->tabela+j)->reg = 0;
                                p_aluno->emprestado--;
                            }
                        }
                              
                        continua = 1; 
                    }

                    else{
                        (p_livro->status+0)->sigla='L';
                        p_aluno->emprestado--;
                        strcpy((p_livro->status+0)->RA,"000000");
                        (p_livro->status+0)->dia_ret = 0;
                        (p_livro->status+0)->mes_ret = 0;
                        (p_livro->status+0)->dia_dev = 0;
                        (p_livro->status+0)->mes_dev = 0;
                        for(j=0;j<3;j++){
                            if(p_livro->reg==(p_aluno->tabela+j)->reg){
                                (p_aluno->tabela+j)->sigla='L';
                                (p_aluno->tabela+j)->reg=0;
                            }
                        }
                        continua = 2;
                    }
                    grava_livro(p_livro,"rb+",pos_liv);
                }
                else
                    printf("\nLivro encontrado. Porem nao esta emprestado para este RA.\n");
            }
        }
    }

    if((fptrA=fopen("aluno.bin","rb"))==NULL) 
            printf("\nArquivo nao disponivel...");
    else{
        if (continua==1 || continua==2){
            grava_aluno(p_aluno,"rb+",pos_alu);
            if(continua==1)
                se_reservado_empresta(p_aluno,p_livro);
        } 
        fclose(fptrA); 
    }
        mostra_status_aluno(p_aluno);
        mostra_status_livros(p_livro);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pos_RA(aluno *p_aluno){

    char aux_RA[7];
    int i, cont_alunos = verifica_alunos(), cont_livros = verifica_livros(), pos_alu=0;
    FILE *fptr=NULL;
    printf("\n\nDigite o RA: ");
    gets(aux_RA);
    fflush(stdin);
    if(cont_livros==0)
        printf("\nNao ha livros.");
    else{
        if((fptr=fopen("aluno.bin","rb"))==NULL)
            printf("\nArquivo nao disponivel...");
        else{
            for(i=0; i<cont_alunos; i++)
            {
                fseek(fptr,i*sizeof(aluno),0);
	            fread(p_aluno,sizeof(aluno),1,fptr);
                if((strcmp(aux_RA, p_aluno->RA))==0)
                {
                    pos_alu = i;
                    cont_alunos=i;
                }
            }
            fclose(fptr);
        }
    }
    return pos_alu;
}      

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int calcularDias(livro *p_livro, int dia, int mes){
    int dias_calculados, dia_max_mes, qtde_mes, dias_de_meses_inteiros=0, i;
    
    printf("\n Livro: %s mes digitado: %d mes da devolucao: %d",p_livro->titulo,mes,(p_livro->status+0)->mes_dev);
    
    if(mes == ((p_livro->status+0)->mes_dev) && dia >= ((p_livro->status+0)->dia_dev))
        dias_calculados = dia - ((p_livro->status+0)->dia_dev);
    
    else if(mes > ((p_livro->status+0)->mes_dev)){
        qtde_mes = mes - (p_livro->status+0)->mes_dev; //Quantidade de meses inteiros atrasados
        if(qtde_mes>1){
            for(i=1; i<qtde_mes; i++)
            {
                dias_de_meses_inteiros += calendario(mes+i); //Soma a quantidade exata de dias passados nos meses inteiros
            }
        }
        dia_max_mes = calendario(mes-1); //Quantidade de dias existentes no mes estipulado de devolucao (não o dia real de devolucao)
        dias_calculados = dia + (dia_max_mes - ((p_livro->status+0)->dia_dev)) + dias_de_meses_inteiros; //Dias de atraso
    }

    else
        dias_calculados = -1;

    return dias_calculados;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void se_reservado_empresta(aluno *p_aluno, livro *p_livro)
{
    int i, j, cont_alu = verifica_alunos(), pos_alu;
    FILE *fptr=NULL;
    if((fptr=fopen("aluno.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
        for(i=0;i<cont_alu;i++)
        { 
            fseek(fptr,i*sizeof(aluno),0);
	        fread(p_aluno,sizeof(aluno),1,fptr);
            if((p_aluno->tabela+3)->reg == p_livro->reg){
                pos_alu=i;
                for(j=0;j<3;j++){
                    if((p_aluno->tabela+j)->sigla == 'L'){
                        p_aluno->emprestado++;
                        (p_aluno->tabela+j)->reg = p_livro->reg;
                        (p_aluno->tabela+j)->sigla = 'E';
                        j=3;
                    }
                }
                (p_aluno->tabela+3)->sigla = 'L';
                (p_aluno->tabela+3)->reg = 0;
                p_aluno->reservado--;
            }
        }
    }
    grava_aluno(p_aluno, "rb+", pos_alu);
    fclose(fptr); 
}   

void deleta(livro *p_livro, aluno *p_aluno){

    int i,j,qreg=0,aux_reg=0, pos_liv=0, continua=0, next=0, qalu=0;
    char aux_titulo[80];
    FILE *fptr=NULL, *fptra=NULL;
    qreg = verifica_livros();
    qalu = verifica_alunos();
    if((fptr=fopen("livros.bin","rb"))==NULL)
        printf("\nErro\n\n");
    else
    {
        printf("\nDigite o titulo do livro a ser deletado: ");
        gets(aux_titulo);
        fflush(stdin);
        
        minuscula (&aux_titulo);
        
            for(i=0;i<qreg;i++)
            {
	            fseek(fptr,i*sizeof(livro),0);
	            fread(p_livro,sizeof(livro),1,fptr);
                if(strcmp(p_livro->titulo,aux_titulo)==0){
                    printf("\nLivro '%s' com registro [%d]",p_livro->titulo,p_livro->reg);
                    continua++;
                }
            }
        if(continua!=0)
        {
        printf("\nDigite o registro que deseja ser alterado: ");
        scanf("%d",&aux_reg);
        fflush(stdin);
            for(j=0;j<qreg;j++)
            {
	        fseek(fptr,j*sizeof(livro),0);
	        fread(p_livro,sizeof(livro),1,fptr);
                if(p_livro->reg==aux_reg){
                    pos_liv=j;
                    if((p_livro->status+0)->sigla=='L')
                        strcpy(p_livro->titulo,"@");
                    else if((p_livro->status+0)->sigla=='E'){
                        printf("\nO livro estava emprestado, entao o RA [%s] deve pagar uma multa de R$ 150,00.",(p_livro->status+0)->RA);
                        strcpy(p_livro->titulo,"@");
                        printf("\n RA [%s] MULTA DE R$ 150,00.",(p_livro->status+0)->RA);
                        deleta_emprestimo(p_livro, p_aluno);
                    }
                    else if((p_livro->status+0)->sigla=='R'){
                        deleta_reservado(p_livro,p_aluno);
                        strcpy(p_livro->titulo,"@");
                    }
                j=qreg;
                }
            }
        }
    grava_livro(p_livro,"rb+",pos_liv);
    fclose(fptr);
  }
}

void deleta_reservado(livro *p_livro, aluno *p_aluno){
    int i, j, cont_alu = verifica_alunos(), pos_alu;
    FILE *fptr=NULL;
    if((fptr=fopen("aluno.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
        for(i=0;i<cont_alu;i++)
        { 
            fseek(fptr,i*sizeof(aluno),0);
	        fread(p_aluno,sizeof(aluno),1,fptr);
            if(p_aluno->RA == (p_livro->status+1)->RA){
                pos_alu=i;  
                p_aluno->reservado--;
                (p_aluno->tabela+3)->reg=0;
                (p_aluno->tabela+3)->sigla='L';
            }
        }
        (p_livro->status+1)->sigla = 'L';
        strcpy((p_livro->status+1)->RA,"000000");
    }
    grava_aluno(p_aluno, "rb+", pos_alu);
    fclose(fptr);
}

void deleta_emprestimo(livro *p_livro, aluno *p_aluno){
    int i, j, cont_alu = verifica_alunos(), pos_alu;
    FILE *fptr=NULL;
    if((fptr=fopen("aluno.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
        for(i=0;i<cont_alu;i++)
        { 
            fseek(fptr,i*sizeof(aluno),0);
	        fread(p_aluno,sizeof(aluno),1,fptr);
            if(p_aluno->RA == (p_livro->status+0)->RA){
                pos_alu=i;
                p_aluno->emprestado--;
                (p_aluno->tabela+0)->reg=0;
                (p_aluno->tabela+0)->sigla='L';
                (p_aluno->tabela+1)->reg=0;
                (p_aluno->tabela+1)->sigla='L';
                (p_aluno->tabela+2)->reg=0;
                (p_aluno->tabela+2)->sigla='L';
            }
        }
        (p_livro->status+0)->sigla = 'L';
        strcpy((p_livro->status+0)->RA,"000000");
    }
    grava_aluno(p_aluno, "rb+", pos_alu);
    fclose(fptr);
}

int	busca(livro *p_livro)
{
    int i,achou=-1,qreg=verifica_livros();
    FILE *fptr=NULL;
    if((fptr=fopen("livros.bin","rb"))==NULL)
        return achou;
    else
    {
        for(i=0;i<qreg;i++)
        {
	    fseek(fptr,i*sizeof(livro),0);
	    fread(p_livro,sizeof(livro),1,fptr);
            if(strcmp(p_livro->titulo,"@")==0){
                achou=i;  
	            i=qreg;
            }
        }
    }
    fclose(fptr); 
return achou;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int parcial_livros_status(livro *p_livro)
{
    int i, j, qliv, achou = 0;
    char stat, aux_stat;
    FILE *fptr = NULL;
    qliv = verifica_livros();
    printf("\nDigite o Status que deseja ver, [L], [E] ou [R]: "); 
    scanf("%c", &aux_stat);
    fflush(stdin);
    stat = toupper (aux_stat);
    if((fptr=fopen("livros.bin","rb"))==NULL)
        printf("\nArquivo nao disponivel...");
    else{
        for(i=0; i<qliv; i++){ 
            fseek(fptr,i*sizeof(livro),0);
            fread(p_livro,sizeof(livro),1,fptr);
            if(stat == 'L' && 'L' == (p_livro->status+0)->sigla && strcmp(p_livro->titulo, "@")!=0) //Printa livros livres
            {
                printf("\n\nTitulo do livro: %s\nRegistro: %d\nAutor: %s\n", p_livro->titulo, p_livro->reg, p_livro->autor);
                achou++;
            }
            
            if(stat == 'E' && 'E' == (p_livro->status+0)->sigla && strcmp(p_livro->titulo, "@")!=0) //Printa livros emprestados
            {
                printf("\n\nTitulo do livro: %s\nRegistro: %d\nAutor: %s\n", p_livro->titulo, p_livro->reg, p_livro->autor);
                achou++;
            }
    
            if(stat == 'R' && 'R' == (p_livro->status+1)->sigla && strcmp(p_livro->titulo, "@")!=0) //Printa livros reservados
            {
                printf("\n\nTitulo do livro: %s\nRegistro: %d\nAutor: %s\n", p_livro->titulo, p_livro->reg, p_livro->autor);
                achou++;
            }
        }
        fclose(fptr);
    }

    if(achou == 0)
        printf("\nNenhum livro encontrado.\n");
        
    return achou;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void minuscula(char *p)
{
    int i;

    for(i=0; i<80; i++)
    {
        *(p+i) = tolower(*(p+i));
    }
}


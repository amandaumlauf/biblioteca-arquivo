/*Biblioteca Pessoal
Função: O programa servirá como uma forma do usuário controlar seu acervo pessoal de livros. 
A partir do menu, o usuário conseguirá cadastrar novos livros, editar, consultar os livros que já possui e ver a quantidade.
Autores: Amanda Umlauf e João Victor Campregher
Data: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define tam 50

FILE *pArq; 

typedef struct biblioteca {
    char nome_livro[500], autor[500], livro_lido[500];
    int pags, num_livro;
}cad;
cad lib[tam];

void cadastrar(); 
void visualizar(); 
void pesquisar(); 
void abrir_arq(); 

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");
	int i, opcao, cont;
  
    i = opcao = cont = 0;

     while (opcao != 6) {
  
        printf("\n\n--------------"
               " BEM-VINDO A SUA BIBLIOTECA "
               "----------------\n");
        printf("\n\n *Utilize os números para navegar no menu* \n");
        printf("\n\n-------------------------\n");
        printf("1. ADICIONAR UM LIVRO NOVO\n ");
        printf("2. MOSTRAR LIVROS CADASTRADOS\n");
        printf("4. REALIZAR BUSCA NOS LIVROS POR AUTOR\n");
        printf("5. VERIFICAR QUANTOS LIVROS TEM NA BIBLIOTECA\n");
        printf("6. SAIR");  

        printf("\n\nESCOLHA UMA DAS OPCOES ACIMA: ");
        scanf("%d", &opcao);
  
        
        switch (opcao) {
  
         
        case 1:
  
            cadastrar();
            system ("pause");
            break;
        
        case 2:
            visualizar();
            break;

        case 4:
            pesquisa();
            break;
  
        case 5:
            printf("\n QUANTIDADE DE LIVROS NA BIBLIOTECA: %d", cont);
            system ("pause");
            break;

        case 6:
            exit(0);
        }
    }
	getchar();
	return 0;
}

void abrir_arq(){
	pArq = fopen("biblioteca.txt", "a");
    if(pArq == NULL){
    printf("Erro na abertura do arquivo!");
    return 1;  
    }
return 0;
}

void cadastrar()
{
    int i;
    int cont;
    abrir_arq("a+");

	for(i=0;i<1;i++)
	{
        getchar();
        printf("INSIRA O NÚMERO DO LIVRO: ");
        scanf("%d", &lib[i].num_livro);
        fflush(stdin);
           
        printf("INSIRA O NOME DO LIVRO: ");
        gets(lib[i].nome_livro);
        fflush(stdin);
  
        printf("INSIRA O NOME DO AUTOR: ");
        gets(lib[i].autor);
        fflush(stdin);
  
        printf("INSIRA O NÚMERO DE PÁGINAS: ");
        scanf("%d", &lib[i].pags);
        fflush(stdin);
  
        printf("VOCÊ JÁ LEU ESSE LIVRO? (INSIRA NO FORMATO: LIDO/LEITURA PENDENTE) ");
        gets(lib[i].livro_lido);
        fflush(stdin);
    
        fwrite(&lib[i],sizeof(cad),1,pArq);
    }
    fclose(pArq);
}

void visualizar()
{
    int i;
	   abrir_arq("r");

	if(pArq == NULL){
		printf("\n\nErro ao abrir!\n");
		exit(0);
		system("pause");
		getchar();
	}
	else{


	int cont = 0;
	int i = 0;
	fseek(pArq,0,SEEK_END);
	cont = ftell(pArq);
	cont = cont/sizeof(cad);
    rewind(pArq);

    for (i = 0; i < cont; i++) {

                printf("\t LIVRO NÚMERO = %d", lib[i].num_livro);
  
                printf("\t NOME DO LIVRO = %s", lib[i].nome_livro);
  
                printf("\t NOME DO AUTOR = %s", lib[i].autor);
  
                printf("\t  QUANTIDADE DE PAGINAS = %d", lib[i].pags);
  
                printf("\t  STATUS DE LEITURA = %s \n", lib[i].livro_lido);
                }

	}
	printf("\n");
	getchar();
	fflush(stdin);    
	system("pause");
}

void pesquisa()
{
	char nome_autor[50];
	int p = 0; 
	int leitura = 1; 
	int ct; 
	abrir_arq("r");
	if(pArq==NULL){
		exit(0);
		system("pause");
	}

	else
    {
    fflush(stdin);
    printf("INSIRA O NOME DO AUTOR: ");
    gets(nome_autor);

    int i, cont;
    i = cont = 0;
    fseek(pArq,0,SEEK_END);
	cont = ftell(pArq);
	cont = cont/sizeof(cad);
	rewind(pArq);

    for (i = 0; i < cont; i++) {
        fread(&lib[i],sizeof(cad),1,pArq);
  
        if (strcmp(nome_autor, lib[i].autor) == 0)
            printf("NOME DO LIVRO: %s  AUTOR: %s  %d PÁGINAS  STATUS: %s",
                    lib[i].nome_livro,
                    lib[i].autor,
                    lib[i].pags,
                    lib[i].livro_lido);
    }

        getchar();
	    system("pause");
}
}
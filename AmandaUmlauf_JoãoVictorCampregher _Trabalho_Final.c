/*Alunos: Amanda Umlauf e Jo�o Victor Campregher
Data: 19/02/2022
Fun��o: O programa serve como uma forma do usu�rio controlar seu acervo pessoal de livros. A partir do menu, o usu�rio consegue cadastrar novos livros, consultar os livros que j� possui, excluir e alterar.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Livro //usamos struct para criar uma estrurura que armazena diversas vari�veis e seus dados em uma variavel especial
{
    int id; 				//
    char nome[50];			//
    char autor[50];			//declara��o de vari�veis da struct
    char status[100];		//
    int pags;				//
};

struct Livro obra; //declara��o de uma vari�vel do tipo livro 
FILE *pArq; // apontando para o arquivo
int tam; 

void menu();                
int cadastrar();
void visualizar();
void pesquisar();           //declara��o de fun��es
void excluirCadastro();
void alterarCadastro();
struct Livro* loadVet();

int main(){ 
    setlocale(LC_ALL, "Portuguese"); //setando a linguagem do programa para portugu�s
    menu();

    return 0;
}

void menu(){
    int opcao;

    while (opcao != 6) { //enquanto op�ao for diferente de 6 o menu ficam em loop de repeti��o

        printf("\n_________\n");    
	    printf("BIBLIOTECA PARTICULAR\n");
        printf("_______\n");
        printf("\n");
        printf("O QUE DESEJA FAZER?\n");
        printf("SELECIONE UMA OP��O:\n");
        printf("\n");
        printf("1. ADICIONAR UM LIVRO NOVO\n");
        printf("2. MOSTRAR LIVROS CADASTRADOS\n");
        printf("3. PESQUISA POR N�MERO DO LIVRO\n");
        printf("4. EXCLUIR CADASTRO\n");
        printf("5. ALTERAR CADASTRO\n");
        printf("6. SAIR\n");
        scanf("%d", &opcao);

        switch (opcao) { //estrutura condicional do tipo "switch case" para coordenar as op��es de execu��o do programa
    
            case 1:
                cadastrar();
                break;
            
            case 2:
                visualizar();
                break;

            case 3:
                pesquisar();
                break;
            
            case 4: 
                excluirCadastro();
                break;
            
            case 5:
            	alterarCadastro();
            	break;
            
            case 6:
                exit(0);
        }
    }
}

int cadastrar(){
    struct Livro* vet=loadVet();
    int i;
    if(tam == -1) //verifica a exist�ncia do arquivo
      printf("Criando arquivo...\n");
    pArq = fopen("biblioteca.txt", "a"); //abre ou cria o arquivo txt
    if(pArq == NULL){
        printf("Erro na abertura do arquivo!"); //verifica se o arquivo abriu corretamente
        exit (1);
    }else{ //se abriu, continua
        printf("INSIRA O N�MERO DO LIVRO: ");
        scanf("%d", &obra.id);
        fflush(stdin);
        for(i=0;i<tam;i++) //para vetor at� o fim do arquivo
          if(vet[i].id == obra.id){ //verifica se existe cadastro com o mesmo n�mero
            printf("J� existe uma obra com este id.\n"); //caso exista, interrompe o cadastro
            return 0;
          }
        //inicia o cadastro
        printf("INSIRA O NOME DO LIVRO: ");
        scanf(" %[^\n]",obra.nome);
        fflush(stdin); //limpa o buffer do teclado

        printf("INSIRA O NOME DO AUTOR: ");
        scanf(" %[^\n]",obra.autor);
        fflush(stdin);
  
        printf("INSIRA O N�MERO DE P�GINAS: ");
        scanf("%d", &obra.pags);
        fflush(stdin);
  
        printf("VOC� J� LEU ESSE LIVRO? (INSIRA NO FORMATO: LIDO/LEITURA PENDENTE) ");
        scanf(" %[^\n]",obra.status);
        fflush(stdin);

        fprintf(pArq, "N�mero: %d\n", obra.id);//imprime as vari�veis no arquivo
        fprintf(pArq, "T�tulo: %s\n", obra.nome);
        fprintf(pArq, "Nome do autor: %s\n", obra.autor);
        fprintf(pArq, "N�mero de p�ginas: %d\n", obra.pags);
        fprintf(pArq, "Status de leitura: %s\n", obra.status);

        fclose(pArq); //fecha o arquivo
    }
    free(vet); //desaloca o espa�o na mem�ria do vet
    return 1; 
} 

void visualizar(){
  struct Livro *vet = loadVet();
  if(tam == 0 || tam == -1) //verifica se existem livros cadastrados (setado no struct Livro* loadVet())
    printf("N�o existem livros cadastrados.\n");
  else{
  	pArq = fopen("biblioteca.txt", "r");
      if(pArq == NULL){
          printf("Erro na abertura do arquivo!");
          exit (1);
      }else{
     		while(!feof (pArq)){ 		//l� o arquivo at� o final
            	fscanf(pArq, "N�mero: %d\n", &obra.id);  	//faz a leitura das vari�veis no arquivo
              	fscanf(pArq, "T�tulo: %[^\n]\n", obra.nome);
              	fscanf(pArq, "Nome do autor: %[^\n]\n", obra.autor);
              	fscanf(pArq, "N�mero de p�ginas: %d\n", &obra.pags);
              	fscanf(pArq, "Status de leitura: %[^\n]\n", obra.status);
  		    	printf("\nN�mero: %d\n", obra.id); 	 //imprime na tela 
              	printf("T�tulo: %s\n", obra.nome);
              	printf("Nome do autor: %s\n", obra.autor);
              	printf("N�mero de p�ginas: %d\n", obra.pags);
              	printf("Status de leitura: %s\n", obra.status);
          }
      }
      fclose(pArq);
    }
  free(vet);
}

void pesquisar(){

    int id;

    pArq = fopen("biblioteca.txt", "r");
    if(pArq == NULL){
        printf("Erro na abertura do arquivo!");
        exit (1);
    }else{
        printf("Informe o n�mero do livro que deseja consultar:");
        scanf("%d", &id);

        while(!feof (pArq)){
            fscanf(pArq, "N�mero: %d\n", &obra.id);
            fscanf(pArq, "T�tulo: %[^\n]\n", obra.nome);
            fscanf(pArq, "Nome do autor: %[^\n]\n", obra.autor);
            fscanf(pArq, "N�mero de p�ginas: %d\n", &obra.pags);
            fscanf(pArq, "Status de leitura: %[^\n]\n", obra.status);
            
            if (id == obra.id){ //compara o id informado com o lido e imprime
                printf("N�mero: %d\n", obra.id);
                printf("T�tulo: %s\n", obra.nome);
                printf("Nome do autor: %s\n", obra.autor);
                printf("N�mero de p�ginas: %d\n", obra.pags);
                printf("Status de leitura: %s\n", obra.status);
            }
        }
    } 
    fclose(pArq); 
}


void excluirCadastro(){

    int codigo, i, aux = 0;
    struct Livro* vet = loadVet();

    if(tam == 0 || tam == -1){
      printf("N�o existem livros cadastrados.\n");
    }
    else{
      printf("Informe o n�mero do livro que deseja excluir:");
      scanf("%d", &codigo);
      
      pArq = fopen("biblioteca.txt", "w");
      if(pArq == NULL){
          printf("Erro na abertura do arquivo!");
          exit (1);
      }else{
          for(i = 0; i < tam; i++){ //para vetor at� o fim do arquivo
            if(vet[i].id != codigo){ //se id for diferente do informado ele escreve no arquivo
              fprintf(pArq, "N�mero: %d\n", vet[i].id);
              fprintf(pArq, "T�tulo: %s\n", vet[i].nome);
              fprintf(pArq, "Nome do autor: %s\n", vet[i].autor);
              fprintf(pArq, "N�mero de p�ginas: %d\n", vet[i].pags);
              fprintf(pArq, "Status de leitura: %s\n", vet[i].status);
            }
            else
              aux = 1; //quando encontrado o informado, seta aux = 1
          }
      }
      fclose(pArq);
    }
    free(vet);
    if(aux == 0) //se n�o for encontrado o id, e portanto aux n�o for setado como 1, imprime livro n�o encontrado
      printf("Livro n�o encontrado.\n");
}

void alterarCadastro(){
  struct Livro* vet = loadVet();
  int id,i, aux = 0;

  if(tam == 0 || tam == -1)
      printf("N�o existem livros cadastrados.\n");
  else{
    printf("Informe o n�mero do livro que deseja editar:");
    scanf("%i",&id);

    for(i = 0; i < tam; i++){ //percorre todos os cadastros
      if(vet[i].id == id){ //se id for igual ao informado
        printf("\nInforma��es atuais do livro:\n"); //imprime informa��es encontradas 
        printf("T�tulo: %s\n", vet[i].nome);
        printf("Nome do autor: %s\n", vet[i].autor);
        printf("N�mero de p�ginas: %d\n", vet[i].pags);
        printf("Status de leitura: %s\n", vet[i].status);
        
        printf("\nINSIRA O NOME DO LIVRO: "); //solicita novas informa��es para as vari�veis
        scanf(" %[^\n]",obra.nome);
        fflush(stdin);
        printf("INSIRA O NOME DO AUTOR: ");
        scanf(" %[^\n]",obra.autor);
        fflush(stdin);
        printf("INSIRA O N�MERO DE P�GINAS: ");
        scanf("%d", &obra.pags);
        fflush(stdin);
        printf("VOC� J� LEU ESSE LIVRO? (INSIRA NO FORMATO: LIDO/LEITURA PENDENTE) ");
        scanf(" %[^\n]",obra.status);
        fflush(stdin);
        aux = 1; //seta aux
        }
    }

    if(aux == 1){ //se informa��es novas cadastradas (aux = 1 setado)
      pArq = fopen("biblioteca.txt", "w");
      if(pArq == NULL){
        printf("Erro na abertura do arquivo!");
        exit (1);
      }else{
        for(i = 0; i < tam; i++){
          if(vet[i].id == id){ //se id for igual ao informado
            fprintf(pArq, "N�mero: %d\n", vet[i].id); //imprime informa��es no arquivo, id, vomo vet e demais como obra (informadas acima)
            fprintf(pArq, "T�tulo: %s\n", obra.nome);
            fprintf(pArq, "Nome do autor: %s\n", obra.autor);
            fprintf(pArq, "N�mero de p�ginas: %d\n", obra.pags);
            fprintf(pArq, "Status de leitura: %s\n", obra.status);
            }else{ //para ids diferentes
              fprintf(pArq, "N�mero: %d\n", vet[i].id); //salva informa��es no arquivo como vet (originais)
              fprintf(pArq, "T�tulo: %s\n", vet[i].nome);
              fprintf(pArq, "Nome do autor: %s\n", vet[i].autor);
              fprintf(pArq, "N�mero de p�ginas: %d\n", vet[i].pags);
              fprintf(pArq, "Status de leitura: %s\n", vet[i].status);
          }
        }
        fclose(pArq);
      }
    }
    else //se aux = 0, livro n�o encontrado
      printf("Livro n�o encontrado.\n"); 
  }
  free(vet);
}


struct Livro* loadVet(){ // essa fun��o aloca um vetor dinamicamente conforme a quantidade de registros tem no arquivo e depois retorna esse vetor com todos os dados contidos no arquivo
  struct Livro *vet = NULL; //seta vet como null
  tam = 0; 

  pArq = fopen("biblioteca.txt", "r");
    if(pArq == NULL){
        printf("Erro na abertura do arquivo!\n");
        tam = -1; //se o arquivo retornar null, seta tam = -1
    }else{
      while(!feof (pArq)){
            fscanf(pArq, "N�mero: %s\n", obra.nome); //leio como string pois fica uma linha em branco no final do arquivo
            if(!feof(pArq)){
              obra.id = atoi(obra.nome); //transforma string em inteiro
              fscanf(pArq, "T�tulo: %[^\n]\n", obra.nome);
              fscanf(pArq, "Nome do autor: %[^\n]\n", obra.autor);
              fscanf(pArq, "N�mero de p�ginas: %d\n", &obra.pags);
              fscanf(pArq, "Status de leitura: %[^\n]\n", obra.status);
              tam++; //cada vez que roda conta +1
              vet = realloc(vet,sizeof(struct Livro) * tam); //realoca o vetor
              vet[tam-1] = obra; //iguala vetor a obra.
            }
      }
  }

  return vet;
}

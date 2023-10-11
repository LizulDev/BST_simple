//Atividade avaliativa de Estrutura de Dados;
//Professor: Guilherme Anzollin;
//Academicos: Luiz Felipe Kaue da Silva (334359), Gerson A. Damazio(396867), Isabela Fernandes (413694).
//Data: 04/10/2023;

//ordem de inserção: se a chave for maior do que a do outro envolvido, fica a direita;
//caso contrário, fica a esquerda;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//estrutura do no ou elemento;
typedef struct Nos{
int chave; 
struct Nos* esq;
struct Nos* dir;
}NOS;

//LIBERAR MEMÓRIA APÓS ENCERRAMENTO.
void liberar_arvore(NOS* raiz) {
    if (raiz == NULL) {
    return; 
}
liberar_arvore(raiz->esq); 
liberar_arvore(raiz->dir); 
    free(raiz); // Liberar o próprio nó
}

//INSERIR novo no na arvore;
void inserir(NOS **raiz, int chave) {    
NOS* novo_no = malloc(sizeof(NOS));
    if (novo_no == NULL) {
printf("ERRO NA ALOCAÇÃO! ENCERRANDO.\n");
    exit(1); 
}
novo_no->chave = chave;
novo_no->esq = NULL;
novo_no->dir = NULL;
    if (*raiz == NULL) {
*raiz = novo_no;
printf("CHAVE %d INSERIDA COM SUCESSO.\n", chave);
} else {
NOS* atual = *raiz;
NOS* no_pai = NULL;
int chave_duplicada = 0;
      while (atual != NULL) {
no_pai = atual;
    if (chave < atual->chave) {
atual = atual->esq;
}else if (chave > atual->chave) {
atual = atual->dir;
} else {
printf("A CHAVE %d JÁ FOI INSERIDA ANTERIORMENTE. TENTE NOVAMENTE!\n", chave);
chave_duplicada = 1;
    break;
}
  }
    if (!chave_duplicada) {
    if (chave < no_pai->chave) {
no_pai->esq = novo_no;
} else {
no_pai->dir = novo_no;
}
printf("CHAVE %d INSERIDA COM SUCESSO.\n", chave);
} else {
free(novo_no);
}
  }
}  

//EXCLUIR NÓ.
void excluir(NOS **raiz, int chave){
    if (*raiz == NULL) {
printf("ÁRVORE VAZIA. NADA A EXCLUIR.\n");
puts("---------------------------------------------------------------");      
    return;
}
NOS * atual  = *raiz;                                 //ponteiros auxiliares para iterar pela arvore;
NOS * no_pai = NULL;                                  //nó pai;
      while (atual != NULL && atual->chave != chave) { //iterando pela arvore;
no_pai = atual;
    if (chave < atual->chave){
atual = atual->esq; 
}else if (chave > atual->chave){
atual = atual->dir;
}
  }
    if (atual == NULL){
printf("CHAVE NÃO ENCONTRADA PARA EXCLUSÃO..\n");
puts("---------------------------------------------------------------");     
return;
}   
    if (atual->esq == NULL){                         //no possui filhos apenas à direita;
    if(no_pai == NULL) {
*raiz = atual->dir;
}else if (atual == no_pai->esq) {
no_pai->esq = atual->dir;
}else{
no_pai->dir = atual->dir;
}
    free(atual);
}else if (atual->dir == NULL) {                    //no possui filhos apenas à esquerda;
    if (no_pai == NULL) {
*raiz = atual->esq;
}else if(atual == no_pai->esq){
no_pai->esq = atual->esq;
}else {
no_pai->dir = atual->esq;
}
    free(atual);
      
}
  }                                            


//BUSCAR CHAVE.
NOS* buscar_chave(NOS* raiz, int chave) {
if (raiz == NULL) {
printf("ARVORE VAZIA. NAO HA CHAVES PARA BUSCAR.\n");
puts("---------------------------------------------------------------");
    return NULL;
}
    if (chave == raiz->chave) {
printf("A CHAVE %d FOI ENCONTRADA.\n", chave);
puts("---------------------------------------------------------------");
    return raiz;
} else if (chave < raiz->chave) {
    if (raiz->esq == NULL) {
printf("A CHAVE %d NAO FOI ENCONTRADA.\n", chave);
puts("---------------------------------------------------------------");
    return NULL;
}
    return buscar_chave(raiz->esq, chave);
} else {
    if (raiz->dir == NULL) {
printf("A CHAVE %d NAO FOI ENCONTRADA.\n", chave);
puts("---------------------------------------------------------------");
    return NULL;
}
    return buscar_chave(raiz->dir, chave);
}
}  

//APOS VERIFICACAO, MOSTRAR CHAVES (INORDER)
void mostrar_em_ordem_recursivo(NOS * raiz2 )
{
  if (raiz2 != NULL){
    mostrar_em_ordem_recursivo(raiz2->esq);
    printf("%i ", raiz2->chave);
    mostrar_em_ordem_recursivo(raiz2->dir);
  }

}


//VERIFICACAO ANTES DE MOSTRAR ARVORE;
void mostrar_em_ordem(NOS* raiz) {
    if(raiz == NULL){ 
   puts("ARVORE VAZIA!\n");
   return;
}
    else {
       mostrar_em_ordem_recursivo(raiz);
    }  
}


int main(void) {
NOS * raiz = NULL;
int chave;  
int opcao = 0;
clock_t inicio_t, fim_t; 
  
      while(opcao != 5){
puts("---------------------------------------------------------------");
printf("MENU DE ESCOLHAS:\n\n");
printf("[1]INSERIR NOVA CHAVE\n");
printf("[2]EXCLUIR CHAVE\n");
printf("[3]BUSCAR CHAVE\n");  
printf("[4]MOSTRAR CHAVES EM ORDEM\n");
printf("[5]SAIR\n\n");  
scanf("%i", &opcao);  
puts("---------------------------------------------------------------");
      switch(opcao) {
//CASO 1 - INSERIR.      
    case 1:
printf("DIGITE O VALOR DA CHAVE:\n\n");
scanf("%i", &chave);
puts("---------------------------------------------------------------");
inicio_t = clock();
inserir(&raiz, chave);  
fim_t = clock();
puts("---------------------------------------------------------------");
printf("TEMPO PARA INSERÇÃO DE CHAVE: %.8lfs\n", (double)(fim_t - inicio_t) / CLOCKS_PER_SEC);
    break;
//CASO 2 - EXCLUIR.        
    case 2:
printf("DIGITE O VALOR DA CHAVE QUE DESEJA EXCLUIR:\n\n");
scanf("%i", &chave);
puts("---------------------------------------------------------------");
inicio_t = clock();
excluir(&raiz, chave);
fim_t = clock();
printf("TEMPO PARA EXCLUSÃO DE CHAVE: %.8lf s\n", (double)(fim_t - inicio_t) / CLOCKS_PER_SEC);
    break;
//CASO 3 - BUSCAR.      
    case 3:
printf("DIGITE O VALOR DA CHAVE PARA BUSCAR:\n\n");
scanf("%i", &chave);
puts("---------------------------------------------------------------");
inicio_t = clock();
NOS* valor = buscar_chave(raiz, chave);
fim_t = clock();
printf("TEMPO PARA BUSCA DE CHAVE: %.8lfs\n", (double)(fim_t - inicio_t) / CLOCKS_PER_SEC);
    break; 
//CASO 4 - MOSTRAR.        
    case 4:
mostrar_em_ordem(raiz);
puts("\n");
    break;
        
    case 5:
printf("SAINDO DO PROGRAMA.\n\n");
puts("---------------------------------------------------------------");
    return 0;
        
    default:
printf("VALOR INVÁLIDO! TENTE NOVAMENTE.\n");
    break;
}
  }  
liberar_arvore(raiz);
raiz = NULL;
}

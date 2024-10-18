#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

typedef struct tipoNo{
  char nome[1024];
  struct tipoNo *filho;
  struct tipoNo *irmao;
  struct tipoNo *pai;
}tipoNo;

typedef struct diretorio{
  tipoNo *raiz;
}diretorio;



void inicializaDir(diretorio *pasta_principal){
  tipoNo *root;

  root = (tipoNo*)malloc(sizeof(tipoNo));
  
  root->filho = NULL;
  root->irmao = NULL;
  root->pai = NULL;
  strcpy(root->nome, "\\root");

  pasta_principal->raiz = root;
}

tipoNo* buscaElemento(tipoNo *pasta, char elemento[1024]){
  
  if(pasta==NULL)
    return NULL;
  
  if(strcmp(pasta->nome, elemento)==0)
    return pasta;

  tipoNo *filho = buscaElemento(pasta->filho, elemento);
  if(filho!=NULL)
    return filho;

  return buscaElemento(pasta->irmao, elemento);
}

void insereNoDir(tipoNo *arquivo, tipoNo *pasta){
  arquivo->irmao = pasta->filho;
  pasta->filho = arquivo; 
}

tipoNo* criaNo(char elemento[1024], tipoNo *pai){
  tipoNo *novo;
  novo = (tipoNo*)malloc(sizeof(tipoNo));

  strcpy(novo->nome, elemento);
  novo->filho = NULL;
  novo->pai = pai;
  novo->irmao = NULL;
  return novo;
}

void removeArquivo(tipoNo* arquivo){
  tipoNo *pai;
  pai = arquivo->pai;
  if(pai->filho == arquivo){
    pai->filho = arquivo->irmao;
  }
  else{
    tipoNo *p;
    p = pai->filho;

    while(p->irmao != arquivo)
      p = p->irmao;

    p->irmao = arquivo->irmao;
  }

  free(arquivo);
}


void moveArquivo(tipoNo* arquivo, tipoNo* novaPasta){
  tipoNo *aux;

  aux = (tipoNo*)malloc(sizeof(tipoNo));
  strcpy(aux->nome, arquivo->nome);
  aux->pai = novaPasta;
  aux->filho = NULL;
  removeArquivo(arquivo);
  insereNoDir(aux, novaPasta);
}

void imprimePre(tipoNo *arv){
    tipoNo *p = arv->filho;
    printf("%s\n",arv->nome);
    while(p!=NULL){
        imprimePre(p);
        p=p->irmao;
    }
}


void imprimeCaminho(tipoNo* buscado){
  tipoNo *p;
  p = buscado;

  while(p->pai != NULL){
    printf("%s ",p->nome);
    p = p->pai;
  }
  printf("%s",p->nome);
}




int main(){
  diretorio pasta_principal;
  int n;
  char *busca, *comando, *elemento, *noPai;

  busca = (char*)malloc(1024*sizeof(char));
  comando = (char*)malloc(1024*sizeof(char));
  elemento = (char*)malloc(1024*sizeof(char));
  noPai = (char*)malloc(1024*sizeof(char));
  scanf("%i",&n);
  scanf("%s",busca);

  inicializaDir(&pasta_principal);

  for(int i=0;i<n;i++){
    scanf("%s %s", comando, elemento);
    if(strcmp("-r", comando)==0){
      tipoNo *arquivo = buscaElemento(pasta_principal.raiz, elemento);
      if(arquivo == NULL){}
      else{
        removeArquivo(arquivo);
      }
    }
    else{
      scanf("%s",noPai);
      if(buscaElemento(pasta_principal.raiz, noPai)==NULL){}
      
      else if(strcmp("-a", comando)==0){
        tipoNo *pasta = buscaElemento(pasta_principal.raiz, noPai);
        tipoNo *arquivo = criaNo(elemento, pasta);
        insereNoDir(arquivo, pasta);
        
    }
      else{
        tipoNo *pasta = buscaElemento(pasta_principal.raiz, noPai);
        tipoNo *arquivo = buscaElemento(pasta_principal.raiz, elemento);
        moveArquivo(arquivo, pasta);
      }
    }
  }

  // imprimePre(pasta_principal.raiz);
  
  tipoNo *buscado;
  buscado = buscaElemento(pasta_principal.raiz, busca);
  if(buscado == NULL)
    printf("Arquivo nao encontrado!");
  else{
    imprimeCaminho(buscado);
  }

  free(busca);
  free(comando);
  free(elemento);
  free(noPai);
  return 0;
}
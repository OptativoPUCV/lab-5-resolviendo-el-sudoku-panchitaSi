#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for (size_t k = 0; k < 9 ; k++){
    unsigned short listaF[10] = {0};
    unsigned short listaC[10] = {0};
    for (size_t i = 0; i < 9 ; i++){
      if (n->sudo[k][i] != 0){
        if (listaF[n->sudo[k][i]] == 1) return 0;
        else{
          listaF[n->sudo[k][i]] = 1;
        }
      }
      if (n->sudo[i][k] != 0){
        if (listaC[n->sudo[i][k]] == 1) return 0;
        else{
          listaC[n->sudo[i][k]] = 1;
        }
      }
    }
  }
  int p;
  for(int k = 0; k < 9 ; k++){
    unsigned short listaSm[10] = {0};
    for(p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      if (n->sudo[i][j] != 0){
        if (listaSm[n->sudo[i][j]] == 1) return 0;
        else listaSm[n->sudo[i][j]] = 1;
      }
    }
  }
  return 1;
}

//1.Cree una función que a partir de un nodo genere una **lista con los nodos adyacentes**:
/*Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. 
Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, 
es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.*/
List* get_adj_nodes(Node* n){
  List* list=createList();
  int fila = -1, col = -1;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        fila = i;
        col = j;
        break;
      }
    }
    if (fila != -1) break;
  }
  
  for (unsigned short num = 1; num < 10 ; num++){
    Node* adj = copy(n);
    adj->sudo[fila][col] = num;
    if (is_valid(adj)) pushBack(list,adj);
  }
  return list;
}


int is_final(Node* n){
  for (size_t k = 0; k < 9; k++){
    for (size_t i = 0; i < 9; i++){
      if (n->sudo[k][i] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila,initial);
  while(top(pila) != NULL){
    Node* actual = top(pila);
    pop(pila);

    if (is_final(actual)) return actual;

    List* lista = get_adj_nodes(actual);
    Node* nodito = first(lista);
    while (nodito != NULL){
      push(pila,nodito);
      nodito = next(lista);
    }

    (*cont)++;
  }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
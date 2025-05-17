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

    return 1;
}

//1.Cree una función que a partir de un nodo genere una **lista con los nodos adyacentes**:
/*Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. 
Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, 
es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.*/
List* get_adj_nodes(Node* n){
  List* list=createList();
  size_t fila = 0;
  size_t col = 0;
  for (fila; fila < 9; fila++){
    for(col; col < 9; col++){
      if (n->sudo[fila][col] == 0) break;
    }
    if (n->sudo[fila][col] == 0) break;
  }

  Node* adj = copy(n);
  for (unsigned short num = 1; num < 10 ; num++){
    adj->sudo[fila][col] = num;
    pushBack(list,adj);
  }
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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
#include<stdio.h>
#include<stdlib.h>
/*########## TREE ##########################################*/
/**/typedef struct naryNode{                              /**/
/*############# 1. naryNode's data  ######################/**/
/*############ 2. Number of Children #####################/**/
/*########### 3. double pointer child array ##############/**/
/*1.*/  int *data;                                        /**/
/*2.*/  int n;                                            /**/
/*3.*/  struct naryNode **child;                          /**/
/**/}naryNode;                                            /**/
/*##########################################################*/

/*############ PROTOTYPES ##################################*/
/**/void traversal(naryNode*);                            /**/
/**/naryNode* findNode(naryNode*, int, naryNode**);       /**/
/**/void countLeaf(naryNode*, int*, int*);                /**/
/**/void existingCheck(naryNode*, int, naryNode**, int*); /**/
/**/void writeFile(naryNode*);                            /**/
/**/int addChild(naryNode*, int*);                        /**/
/**/naryNode *makeNode(int, int*);                        /**/
/**/void *makeInt(int);                                   /**/
/**/naryNode* findDaddy(naryNode*, int, naryNode**);      /**/
/*##########################################################*/
char outputArray[100];
int counterOutput = 0;
/*~~~~~~~~~~~~~~~~~  MAIN PROGRAM ~~~~~~~~~~~~~~~~~*/
int main(int argc, char* argv[]){
  char firstInput[100];
  char secondInput[100];
  scanf("%s", firstInput);
  scanf("%s", secondInput);
  int unique, number, uniqueToAdd, number2, root, many,i;
  int notUnique = 0;
  int count = 0;
/*######################## READING FILES ############################*/
/**/  FILE *fptr = fopen(firstInput, "r");   //for line count      /**/
/**/  FILE *fptr2 = fopen(firstInput, "r");  //for retrieving data /**/
/**/  FILE *fptr3 = fopen(secondInput, "r");                       /**/
/**/  FILE *fptr4 = fopen("output.txt", "w");                      /**/
/*##################### FINISH READING ##############################*/

  while(!feof(fptr)){
    fscanf(fptr, "%d %d\n", &root, &many);
    count++; /* count stores line counter of first input file */
  }
/*### Dinamic memory allocation for first input file  ###*/
/**/  int *uniques, *counts;                           /**/
/**/  counts  = (int*)malloc(count * sizeof(int));     /**/
/**/  uniques  = (int*)malloc(count * sizeof(int));    /**/
/**/  int countUnique = 0;                             /**/
/**/  while(!feof(fptr2)){                             /**/
/**/    fscanf(fptr2, "%d %d\n", &uniqueToAdd, &many); /**/
/**/    uniques[countUnique] = uniqueToAdd;            /**/
/**/    counts[countUnique] = many;                    /**/
/**/    countUnique++;                                 /**/
/**/  }                                                /**/
/*####### Finish reading for first input file ###########*/
  int stopIndex = counts[0]+1;   //stop index when retrieving unique datas
  int willRead = 1;              //how many uniques will be read
  int idex = 0;                  //index counter for each unique data
  int leafsArr[20];              //int array for current leaves
/*#################### Creating Tree, root and child ####################*/
/**/ naryNode *tree = makeNode(counts[0], makeInt(uniques[0]));        /**/
/**/  for(i=0; i<counts[0]; i){                                        /**/
/**/    tree->child[i] = makeNode(0, makeInt(uniques[++i]));           /**/
/**/  }                                                                /**/
/*#######################################################################*/
  int countleafs = 0;  //number of leaves
  countLeaf(tree, &countleafs, leafsArr);
/*######################################### Creating Tree ##########################################*/
/**/  while(stopIndex < count){                                                                   /**/
/**/    for(int j=0; j<counts[willRead] && stopIndex < count ; j++){                              /**/
/**/      struct naryNode *temp = NULL;                                                           /**/
/**/      if(idex == 0){                                                                          /**/
/**/        findNode(tree, leafsArr[0], &temp);                                                   /**/
/**/        addChild(temp, makeInt(uniques[stopIndex]));                                          /**/
/**/      }else{                                                                                  /**/
/**/        findNode(tree, leafsArr[idex%countleafs], &temp);                                     /**/
/**/        addChild(temp, makeInt(uniques[stopIndex]));                                          /**/
/**/      }                                                                                       /**/
/**/      stopIndex++;                                                                            /**/
/**/      idex++;                                                                                 /**/
/**/    }                                                                                         /**/
/**/    willRead++;                                                                               /**/
/**/    idex = 0;                                                                                 /**/
/**/    countleafs = 0;                                                                           /**/
/**/    countLeaf(tree, &countleafs, leafsArr);                                                   /**/
/**/  }                                                                                           /**/
/*##################################################################################################*/
  int *deleted = calloc(10, sizeof(int)) ;
  char command;
  int value;
  int indexDelete = 0;
  char delete = 'd';
  char list = 'l';
  struct naryNode *temp2 = NULL;
  int m;
/*############################# DELETING & LISTING COMMANDS #####################################*/
/**/  while(!feof(fptr3)){                                                                     /**/
/**/    fscanf(fptr3, "%c %d\n", &command, &value);                                            /**/
/*##################################### DELETING ################################################*/
/**/    if(command == delete){                                                                 /**/
/**/      int ifExist1 = 0;                                                                    /**/
/**/      naryNode *temp7 = NULL;                                                              /**/
/**/      existingCheck(tree, value, &temp7, &ifExist1);                                       /**/
/**/      deleted[indexDelete] = value;                                                        /**/
/**/      indexDelete++;                                                                       /**/
/**/      findNode(tree, value, &temp7);                                                       /**/
/**/      if(ifExist1){                                                                        /**/
/*################################# DELETE FROM ROOT ############################################*/
/**/      if(*tree->data == value){                                                            /**/
/**/        for(i=1; i<tree->n; i++){                                                          /**/
/**/          tree->child[0]->child = (naryNode**)realloc(tree->child[0]->child,               /**/
/**/                                  (tree->child[0]->n +1 )*sizeof(naryNode*));              /**/
/**/          tree->child[0]->child[tree->child[0]->n] = tree->child[i];                       /**/
/**/          tree->child[0]->n += 1;                                                          /**/
/**/        }                                                                                  /**/
/**/        naryNode *temp8 = tree;                                                            /**/
/**/        tree = tree->child[0];                                                             /**/
/**/        free(temp8);                                                                       /**/
/*################################ DELETE LEAF NODE #############################################*/
/**/      }else if(temp7->n == 0){                                                             /**/
/**/        naryNode *temp10 = NULL;                                                           /**/
/**/        findDaddy(tree, value, &temp10);                                                   /**/
/**/        for(i=0; i<temp10->n;i++){                                                         /**/
/**/          if(*temp10->child[i]->data == value){                                            /**/
/**/            break;                                                                         /**/
/**/          }                                                                                /**/
/**/        }                                                                                  /**/
/**/        if(i == temp10->n - 1){                                                            /**/
/**/          free(temp10->child[i]);                                                          /**/
/**/          temp10->n -= 1;                                                                  /**/
/**/          temp10->child = (naryNode**)realloc(temp10->child, temp10->n*sizeof(naryNode*)); /**/
/**/        }else{                                                                             /**/
/**/          m=0;                                                                             /**/
/**/          for(m = i; m<temp10->n - 1; m++){                                                /**/
/**/            temp10->child[m] = temp10->child[m+1];                                         /**/
/**/          }                                                                                /**/
/**/          temp10->n -= 1;                                                                  /**/
/**/          temp10->child = (naryNode**)realloc(temp10->child, temp10->n*sizeof(naryNode*)); /**/
/**/        }                                                                                  /**/
/*################################## DELETE MIDDLE NODE #########################################*/
/**/      }else{                                                                               /**/
/**/        findDaddy(tree, value, &temp7);                                                    /**/
/**/        naryNode *temp9 = NULL;                                                            /**/
/**/        for(i=0; i<temp7->n;i++){                                                          /**/
/**/          if(*temp7->child[i]->data == value){                                             /**/
/**/            temp9 = temp7->child[i];                                                       /**/
/**/            break;                                                                         /**/
/**/          }                                                                                /**/
/**/        }                                                                                  /**/
/**/        int p = temp7->n - 1;                                                              /**/
/**/        temp7->n = temp7->n + temp9->n - 1;                                                /**/
/**/        temp7->child = (naryNode**)realloc(temp7->child, (temp7->n)*sizeof(naryNode*));    /**/
/**/        for(m=p; m>=i+1; m--){                                                             /**/
/**/          temp7->child[m+temp9->n -1  ] = temp7->child[m];                                 /**/
/**/        }                                                                                  /**/
/**/        for(m=0; m<temp9->n; m++){                                                         /**/
/**/          temp7->child[i] = temp9->child[m];                                               /**/
/**/          i++;                                                                             /**/
/**/        }                                                                                  /**/
/**/        free(temp9);                                                                       /**/
/**/      }                                                                                    /**/
/**/    } //end for delete                                                                     /**/
/*#################################### FINISH DELETING ##########################################*/
}
/*#################################### LIST COMMAND #############################################*/
/**/    if(command == list){                                                                   /**/
/**/      int ifExist = 0;                                                                     /**/
/**/      counterOutput = 0;                                                                   /**/
/**/      existingCheck(tree, value, &temp2, &ifExist);                                        /**/
/**/      if(ifExist == 1){                                                                    /**/
/**/          writeFile(temp2);                                                                /**/
/**/          if(counterOutput == 0) fprintf(fptr4, "%d", *temp2->data);                       /**/
/**/          else fprintf(fptr4, "%d,", *temp2->data);                                        /**/
/**/                                                                                           /**/
/**/              for(i=0; i<counterOutput; i++){                                              /**/
/**/                if(i == counterOutput - 1){                                                /**/
/**/                    fprintf(fptr4, "%d", outputArray[i]);                                  /**/
/**/                }                                                                          /**/
/**/                else{                                                                      /**/
/**/                  fprintf(fptr4, "%d", outputArray[i]);                                    /**/
/**/                  fprintf(fptr4, ",");                                                     /**/
/**/                }                                                                          /**/
/**/              }                                                                            /**/
/**/          fprintf(fptr4, "\n");                                                            /**/
/**/      }                                                                                    /**/
/**/      temp2 = NULL;                                                                        /**/
/**/    }                                                                                      /**/
/**/  }                                                                                        /**/
/*################################### FINISH LISTING ############################################*/
/* Close file pointers*/
  fclose(fptr);
  fclose(fptr2);
  fclose(fptr3);
  fclose(fptr4);
}
naryNode* findDaddy(naryNode *root, int data, naryNode **temp){
  int i;
  for(i=0; i<root->n; i++){
    if(root->child[i] == NULL) return root; //BASE
    if(*root->child[i]->data == data){
      *temp = root;
      break;
    }
    findDaddy(root->child[i], data, temp);
  }
}
int addChild(naryNode *root , int *data){
     root->n = root->n + 1;
     root->child = (naryNode**)realloc(root->child, (root->n)*sizeof(naryNode*));
     root->child[root->n - 1] = makeNode(0, data);
     return root->n - 1;
 }
naryNode *makeNode (int children, int *data){
    naryNode *node = (naryNode*)calloc(1, sizeof(naryNode));
    node->data = data;
    node->n = children ;
    node->child = (naryNode**)calloc(node->n ,sizeof(naryNode*));
    return node;
}
void *makeInt(int data){
  int *intPtr = (int*)calloc(1, sizeof(int));
  *intPtr = data;
  return intPtr;
}
void writeFile(naryNode *root){
  for(int i=0; i<root->n; i++){
    if(root->child[i] == NULL) return; //BASE CASE FOR TRAVERSAL RECURSION
    outputArray[counterOutput] = *root->child[i]->data;
    counterOutput++;
    writeFile(root->child[i]);
  }
}
void existingCheck(naryNode *root, int data, naryNode **temp, int *ifExist){
  for(int i=0; i<root->n; i++){
    if(root->child[i] == NULL) return; //BASE CASE FOR EXISTINGCHECK
    if(*root->data == data){
        *ifExist = 1;
        *temp = root;
        break;
    }
    if(*root->child[i]->data == data){
        *ifExist = 1;
        *temp = root->child[i];
        break;
    }
    existingCheck(root->child[i], data, temp, ifExist); //RECURSION CASE FOR EXISTINGCHECK
  }
}
void countLeaf(naryNode *root, int *countLeaves, int arr[20]){
  int i;
  for(i=0; i<root->n; i++){
    if(root->child[i] == NULL) return; //BASE
    if(root->child[i]->n == 0){
      arr[*countLeaves] = *root->child[i]->data;
      *countLeaves += 1;
    }
    countLeaf(root->child[i], &(*countLeaves), arr);
  }
}
naryNode* findNode(naryNode *root, int data, naryNode **temp){
  int i;
  for(i=0; i<root->n; i++){
    if(root->child[i] == NULL) return root; //BASE
    if(*root->child[i]->data == data){
      *temp = root->child[i];
      break;
    }
    findNode(root->child[i], data, temp);
  }
}
void traversal(naryNode *root){
  for(int i=0; i<root->n; i++){
    if(root->child[i] == NULL) return; //BASE CASE FOR TRAVERSAL RECURSION
    printf("%d,", *root->child[i]->data);
    traversal(root->child[i]);
  }
}

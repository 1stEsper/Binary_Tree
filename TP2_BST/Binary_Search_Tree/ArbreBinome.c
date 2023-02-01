#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef char Chaine[52];

//1.Création de l’arbre binaire de recherche pour stocker les mots utilisés et leur occurrence

//a:
typedef struct Mot{
    Chaine data;
    int occ;
    struct Mot *left, *right;
}mot, *ABR;

//b:creer un nouveau node
ABR createMot (Chaine x){
    ABR tmp=(ABR)malloc(sizeof(mot));
    if(tmp==NULL)
        exit(1);
    strcpy(tmp->data, x);
    tmp->occ=1;
    tmp->left=tmp->right=NULL;
    return tmp;
}

//c:
ABR ajouterMot(ABR *Tree, Chaine x){
    ABR nouveau=createMot(x);
    if(*Tree == NULL){
        *Tree=nouveau;
    }
    else if(strcmp(x,(*Tree)->data)<0){
        ajouterMot(&(*Tree)->left,x );
    }
    else if(strcmp(x,(*Tree)->data)>0){
        ajouterMot(&(*Tree)->right,x );
    }
    else {
        (*Tree)->occ+=1;
    }
}

//d:
void afficher(ABR Tree){
    if(Tree){
        afficher(Tree->left);
        printf("%s : %d fois \n", Tree->data, Tree->occ);
        afficher(Tree->right);
    }
}


/*2: une fonction permettant de lire les mots dans le fichier et les ajouter
à l’arbre*/
void readData(ABR *arbre, Chaine nom){
    Chaine word;
    int c;
    FILE *fptr;
    fptr=fopen(nom, "r");//il peut traiter 1 fichier d'environ 400 lignes de données.
    do{
        c=fscanf(fptr, "%s", word);
        if(c!= EOF){
            ajouterMot(&(*arbre), word);
        }
    }while(c!= EOF);
    fclose(fptr);
    //printf("Le sommet de mots dans la File est : %d\n",s );
}

/*3: une fonction permettant de rechercher et d’afficher les mots qui apparaissent plus de n fois
avec leur occurrence*/
void motsFrequence(ABR arbre,int n ){
    if(arbre){
        if(arbre->occ >=n){
            printf("%s : %d fois \n", arbre->data, arbre->occ);
            motInutile(arbre->data);
        }
        motsFrequence(arbre->left, n);
        motsFrequence(arbre->right, n);
    }
}

void motInutile(Chaine x){
    Chaine useless[15]={"spam", "of", "to", "a" , "an", "at", "the", "and", "in", "is", "it", "on",
"2"};
    for(int i=0; i<13; i++){
        if(strcmp(x, useless[i])==0)
            printf(" est le mot inutile\n");
    }
    printf("-------------------------------------------\n");
}

int main(){
    ABR tree;
    tree=NULL;
    int x;
    printf("Entrez la valeur de fréquence vous voulez :");
    scanf("%d",&x);
    readData(&tree, "textEx.txt");
    afficher(tree);
    printf("===========================================\n");
    motsFrequence(tree,x);
    printf("-------------------------------------------\n");
}


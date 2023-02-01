#include<stdio.h>
#include<stdlib.h>

typedef struct _produit
{
    int ref;
    int eq;
    struct _produit *fg, *fd;
    int height;

}Produit, *AVL;

//Une fonction qui va retourner la hauteur de noeuds
int height(AVL N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

//Une fonction qui va retourner la valeur est plus grand entre 2 valeur
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Une fonction qui va rotation le noeud y à droite.
AVL rightRotate(AVL y)
{
    AVL x = y->fg;
    AVL T2 = x->fd;
    x->fd = y;
    y->fg = T2;

    // Update heights
    y->height = max(height(y->fg),
                    height(y->fd)) + 1;
    x->height = max(height(x->fg),
                    height(x->fd)) + 1;

    // Return new root
    return x;
}

//Une fonction qui va rotation le noeud x à gauche.
AVL leftRotate(AVL x)
{
    AVL y = x->fd;
    AVL T2 = y->fg;
    y->fg = x;
    x->fd = T2;

    //  Update heights
    x->height = max(height(x->fg),
                    height(x->fd)) + 1;
    y->height = max(height(y->fg),
                    height(y->fd)) + 1;

    // Return new root
    return y;
}

//2.une fonction afficher pour afficher un AVL de racine r sous une forme d’arbre
void afficher(AVL r)
{
    if(r != NULL)
    {

        afficher(r->fd);
        switch(r->height){
        case 1:
            printf("------");
            break;
        case 2:
            printf("----");
            break;
        case 3:
            printf("--");
            break ;
        case 4:
            break;
        }
        printf("%d (%d)\n", r->ref, r->eq);
        afficher(r->fg);
    }
}

//3.Une fonction qui  crée et renvoie un AVL sur un nouveau Produit de référence n
AVL creer(int n)
{
    AVL node = (AVL)malloc(sizeof(Produit));
    node->ref   = n;
    node->fg   = NULL;
    node->fd  = NULL;
    node->height = 1;
    return(node);
}

//4.Fonction qui met à jour les facteurs d’équilibre d’un AVL.
int maj_eq(AVL N)
{
    if (N == NULL)
        return 0;
    return height(N->fg) - height(N->fd);
}

//5.
AVL inserer_reeq(AVL a, int n)
{   AVL p=NULL;
    /* 1.Insertion */
    if(a){
        if (n <= a->ref)
            a->fg  = inserer_reeq(a->fg, n);
        else
            a->fd = inserer_reeq(a->fd, n);

        /* 2. Update height */
        a->height = 1 + max(height(a->fg),
                            height(a->fd));

        a->eq = maj_eq(a);

        // Left Left Case
        if (a->eq > 1 && n < a->fg->ref)
            return rightRotate(a);

        // Right Right Case
        if (a->eq < -1 && n > a->fd->ref)
            return leftRotate(a);

        // Left Right Case
        if (a->eq > 1 && n > a->fg->ref)
        {
            a->fg =  leftRotate(a->fg);
            return rightRotate(a);
        }

        // Right Left Case
        if (a->eq < -1 && n < a->fd->ref)
        {
            a->fd = rightRotate(a->fd);
            return leftRotate(a);
        }

        return a;
    }
    else{
        p=creer(n);
        return p;
    }
}

int main()
{
    AVL Tree = NULL;
    int t[]={4,2,1,8,6,7,3,9,5};
    for (int i=0; i<9; i++){
        Tree=inserer_reeq(Tree, t[i]);
    }
    printf("Arbre AVL est :\n");
    afficher(Tree);
    printf("Done!\n");
    return 0;
}

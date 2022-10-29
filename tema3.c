/* MICULESCU Rares-Dumitru - Linux Terminal Simulator*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define null NULL

//declared structures
typedef struct arboref *AR;

typedef struct directory{
    char *nume;
    struct directory *parent;
    AR files;
    AR directories;
    struct directory *st, *dr;
}Dir, *DR;

typedef struct files{

    char *nume;
    DR parent;
    struct files *st, *dr;

}File, *FL;

typedef struct arboref{
    void *info;
    AR st, dr;
}*AR, Arbc;



//generating root
int genroot(DR *x){
    
    (*x)->nume = malloc(5);
    strcpy((*x)->nume, "root");
    (*x)->parent = null;
    (*x)->files = null;
    (*x)->directories = null;
    (*x)->st = null;
    (*x)->dr = null;
    return 1;
}



/*name searching functions, searching through the tree if it finds the name 
Returns 1 if it finds it and no otherwise*/
int checkDir(AR d, char *n){

    if(d == null)
        return 0;
    
    DR dir = (DR) d->info;
    if(strcmp((dir->nume), n) == 0)
        return 1;
    
    return checkDir(d->st, n) || checkDir(d->dr, n); 

}

int checkFiles(AR d, char *n){

    if(d == null)
        return 0;
    
    FL file = (FL) d->info;
    if(strcmp((file->nume), n) == 0)
        return 1;
    
    return checkFiles(d->st, n) || checkFiles(d->dr, n);

}



/*touch function
manes memory allocation and places the parameters where they need to be*/
FL genFile(DR d, char *n){

    FL f = calloc(1, sizeof(File));
    f->nume = strdup(n);
    f->parent = d;
    f->dr = null;
    f->st = null;
    return f;

}

/*searches where the elements needs to be placed
also, when the element is added, the program takes the colsest element and 
swaps the links for the lexicographical list*/
int AddARF(AR *arb, FL *cel){

 
    if((*arb) == null){
        *arb = calloc(1, sizeof(Arbc));
        (*arb)->st = null;
        (*arb)->dr = null;
        (*arb)->info = *cel;
        return 1;
    }

    FL c = (FL) (*arb)->info;
    if(strcmp(c->nume, (*cel)->nume) > 0){
        if((*arb)->st == null){
            (*cel)->st = c->st;
            (*cel)->dr = c;
            if(c->st != null)
                c->st->dr = *cel;
            c->st = *cel;
        }
        AddARF(&((*arb)->st), cel);
    }
    else
    {
        if((*arb)->dr == null){
            (*cel)->dr = c->dr; 
            (*cel)->st = c;      
            if(c->dr != null)  
                c->dr->st = *cel;
            c->dr = *cel;
        }
        AddARF(&((*arb)->dr), cel);
    }
    return 1;

}

/*checks if the name already exists. If not, creates the file
and adds using the previous functions*/
int touch(DR *d, char *n){

    //check dir
    if((*d) == null)
        return 0;
    if(checkDir((*d)->directories, n) == 1){
        printf("Directory %s already exists!\n", n);
        return 0;
    }
    //check files
    if(checkFiles((*d)->files, n) == 1){
        printf("File %s already exists!\n", n);
        return 0;
    }
    FL f = genFile((*d), n);
    return AddARF(&((*d)->files), &f);
    
}



/*mkdir function
makes memory allocation and initializes elements*/
DR genDir(DR par, char *n){

    DR d = calloc(1, sizeof(Dir));
    d->nume = strdup(n);
    d->parent = par;
    d->files = null;
    d->directories = null;
    d->st = null;
    d->dr = null;
    return d;

}

/*searches through the tree to see where the element needs to be added
also, when the element is added, the program takes the colsest element and 
swaps the links for the lexicographical list*/
int AddARD(AR *arb, DR *cel){

 
    if((*arb) == null){
        *arb = calloc(1, sizeof(Arbc));
        (*arb)->st = null;
        (*arb)->dr = null;
        (*arb)->info = *cel;
        return 1;
    }

    DR c = (DR) (*arb)->info;
    if(strcmp(c->nume, (*cel)->nume) > 0){
        if((*arb)->st == null){
            (*cel)->st = c->st;
            (*cel)->dr = c;
            if(c->st != null)
                c->st->dr = *cel;
            c->st = *cel;
        }
        AddARD(&((*arb)->st), cel);
    }
    else
    {
        if((*arb)->dr == null){
            (*cel)->dr = c->dr; 
            (*cel)->st = c;      
            if(c->dr != null)  
                c->dr->st = *cel;
            c->dr = *cel;
        }
        AddARD(&((*arb)->dr), cel);
    }
    return 1;

}

/*checks if the name already exists. If not, creates the file
and adds using the previous functions*/
int mkdir(DR *d, char *n){

    if((*d) == null)
        return 0;
    if(checkDir((*d)->directories, n) == 1){
        printf("Directory %s already exists!\n", n);
        return 0;
    }
    //check files
    if(checkFiles((*d)->files, n) == 1){
        printf("File %s already exists!\n", n);
        return 0;
    }
    DR dr = genDir((*d), n);
    return AddARD(&((*d)->directories), &dr);
}



/*ls functions
prints the directories in growing order*/
int parcD(AR d){

    if(d == null)
        return 0;
    int x = 0;
    x += parcD(d->st);
    DR dir = (DR) d->info;
    printf("%s ", dir->nume);
    x++;
    x += parcD(d->dr);
    return x;

}

//prints the files in growing order
int parcF(AR f){

    if(f == null)
        return 0;
    int x = 0;
    x += parcF(f->st);
    FL files = (FL) f->info;
    printf("%s ", files->nume);
    x++;
    x += parcF(f->dr);
    return x;
}


int ls(DR d){
    
    if(d == null)
        return 0;
    int ok = 0;
    parcD(d->directories);
    parcF(d->files);
    printf("\n");
    
}



/*rm function
//swaps the values of tow cells*/
int swapCel(AR *c1, AR *c2){    

    if((*c2) == null || (*c1) == null){
        return 0;
    }
    AR aux = calloc(1, sizeof(Arbc));
    aux->info = (*c1)->info;
    (*c1)->info = (*c2)->info;
    (*c2)->info = aux->info;
    free(aux);
    return 1;
}

//modifies the links for the lexicographical list
int rmStDrF(AR *c){

    if((*c) == null){
        printf("ceva nu e bine\n");
        return 0;
    }
    FL f = (FL) (*c)->info;
    FL st = f->st;
    FL dr = f->dr;
    if(f->st == null){
        dr->st = null;
        return 1;
    }
    if(f->dr == null){
        st->dr = null;
        return 1;
    }
    dr->st = st;
    st->dr = dr;
    return 1;
}

/*the remove function
I took a particular case for the root
we have multiple cases when we find the element we need to remove
when both children are null, then the previous child gets null
when only one child is null, we link the previous child with the next one 
last case is when neither of the children are null; then we find the minimum 
that is greater than the element we need to remove; after we swap cells*/

int rm(DR *d, char *n){

    if((*d) == null)
        return 0;
    if((*d)->files == null)
        return 0;
    AR fil = (*d)->files;
    FL finc = (FL) fil->info;
    if(strcmp(finc->nume, n) == 0 && fil->dr == null && fil->st == null){
        free(fil);
        (*d)->files = null;
        return 1;
    }
    AR ant = null;
    int x = 0;
    while(1){
        if(fil == null)
            return 0;
        FL f = (FL) fil->info;
        if(strcmp(f->nume, n) == 0){
            break;
        }
        else{
            ant = fil;
            if(strcmp(f->nume, n) > 0){
                x = 1;
                fil = fil->st;
            }
            else{
                x = 2;
                fil = fil->dr; 
            }
        }
    }

    if(fil->st == null && fil->dr == null){
            rmStDrF(&fil);
            free(fil);
            if(ant == null){
                (*d)->files = null;
                return 1;
            }
            if(x == 1)
                ant->st = null;
            else{
                ant->dr = null;
            }
            return 1;
        }
    if(fil->st == null){
        rmStDrF(&fil);
        if(ant == null){
            (*d)->files = fil->dr;
            return 1;
        }
        if(x == 1)
            ant->st = fil->dr;
        else{
            ant->dr = fil->dr;
        }
        // free(fil);
        return 1;
    }
    if(fil->dr == null){
        rmStDrF(&fil);
        if(ant == null){
            (*d)->files = fil->st;
            return 1;
        }
        if(x == 1)
            ant->st = fil->st;
        else 
            ant->dr = fil->st;
        // free(fil);
        return 1;
    }

    AR rep = fil;
    ant = fil;
    fil = fil->dr;
    x = 2;
    while(1){
        if(fil->st == null)
            break;
        ant = fil;
        fil = fil->st;
        x = 1;
    }
    swapCel(&rep, &fil);
    if(fil->dr == null){
        rmStDrF(&fil);
        if(x == 1)
            ant->st = null;
        else{
            ant->dr = null;
        }
    }
    else{
        rmStDrF(&fil);
        if(x == 1)
            ant->st = fil->dr;
        else 
            ant->dr = fil->dr;
    }
    

    return 1;

}


int rmStDrD(AR *c){

    if((*c) == null){
        printf("ceva nu e bine\n");
        return 0;
    }
    DR f = (DR) (*c)->info;
    DR st = f->st;
    DR dr = f->dr;
    if(f->st == null){
        dr->st = null;
        return 1;
    }
    if(f->dr == null){
        st->dr = null;
        return 1;
    }
    dr->st = st;
    st->dr = dr;
    return 1;
}

int rmdir(DR *d, char *n){

    if((*d) == null)
        return 0;
    if((*d)->directories == null)
        return 0;
    AR fil = (*d)->directories;
    DR finc = (DR) fil->info;
    if(strcmp(finc->nume, n) == 0 && fil->dr == null && fil->st == null){
        free(fil);
        (*d)->directories = null;
        return 1;
    }
    AR ant = null;
    int x = 0;
    while(1){
        if(fil == null)
            return 0;
        DR f = (DR) fil->info;
        if(strcmp(f->nume, n) == 0){
            break;
        }
        else{
            ant = fil;
            if(strcmp(f->nume, n) > 0){
                x = 1;
                fil = fil->st;
            }
            else{
                x = 2;
                fil = fil->dr; 
            }
        }
    }

    if(fil->st == null && fil->dr == null){
            rmStDrD(&fil);
            free(fil);
            if(ant == null){
                (*d)->directories = null;
                return 1;
            }
            if(x == 1)
                ant->st = null;
            else{
                ant->dr = null;
            }
            return 1;
        }
    if(fil->st == null){
        rmStDrD(&fil);
        if(ant == null){
            (*d)->directories = fil->dr;
            return 1;
        }
        if(x == 1)
            ant->st = fil->dr;
        else{
            ant->dr = fil->dr;
        }
        // free(fil);
        return 1;
    }
    if(fil->dr == null){
        rmStDrD(&fil);
        if(ant == null){
            (*d)->directories = fil->st;
            return 1;
        }
        if(x == 1)
            ant->st = fil->st;
        else 
            ant->dr = fil->st;
        // free(fil);
        return 1;
    }

    AR rep = fil;
    ant = fil;
    fil = fil->dr;
    x = 2;
    while(1){
        if(fil->st == null)
            break;
        ant = fil;
        fil = fil->st;
        x = 1;
    }
    swapCel(&rep, &fil);
    if(fil->dr == null){
        rmStDrD(&fil);
        if(x == 1)
            ant->st = null;
        else{
            ant->dr = null;
        }
    }
    else{
        rmStDrD(&fil);
        if(x == 1)
            ant->st = fil->dr;
        else 
            ant->dr = fil->dr;
    }
    

    return 1;

}


//we go until we get to root and then we print
void pwd(DR d){
    if(strcmp(d->nume,"root") != 0)
        pwd(d->parent);
    printf("/%s", d->nume);
}



void cd(DR *d, char *p){

    if(strcmp(p,"..") == 0){
        if(strcmp((*d)->nume, "root") != 0)
            (*d) = (*d)->parent;
        return;
    }
    AR arb = (*d)->directories;
    while(1){
        if(arb == null)
            break;
        DR dir = (DR) arb->info;
        if(strcmp(dir->nume, p) == 0){
            (*d) = dir;
            return;
        }
        if(strcmp(dir->nume, p) > 0)
            arb = arb->st;
        else
        {
            arb = arb->dr;
        }
        
    }
    printf("Directory not found!\n");

}

int main(){

    DR d = calloc(1, sizeof(Dir));
    genroot(&d);

    char *line = NULL;
	size_t len = 0;

    while(getline(&line, &len, stdin) != -1){
        char *command = strtok(line," \n");
        char *content = strtok(0,"\n");
        
        if(strcmp(command,"touch") == 0){
            touch(&d, content);
        }

        if(strcmp(command, "ls") == 0){
           ls(d); 
        }

        if(strcmp(command, "mkdir") == 0){
            mkdir(&d, content);
        }

        if(strcmp(command,"quit") == 0)
            break;

        if(strcmp(command,"rm") == 0){
            int v = rm(&d, content);
            if(v == 0)
                printf("File %s doesn't exist!\n", content);
        }

        if(strcmp(command,"rmdir") == 0){
            int v = rmdir(&d, content);
            if(v == 0)
                printf("Directory %s doesn't exist!\n", content);
        }

        if(strcmp(command,"cd") == 0){
            cd(&d, content);
        }

        if(strcmp(command,"pwd") == 0){
            pwd(d);
            printf("\n");
        }

    }

    return 0;
}

/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int errflg;
int solved;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
  L->First=NULL;
L->Act=NULL;        //Set Actual and next pointer to NULL
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

               /* V případě řešení, smažte tento řádek! */
}

void DisposeList (tList *L) {
  tElemPtr tmpElem;       //new structure
  while(L->First!=NULL)   //cycle for deleting all the memory
  {tmpElem=L->First->ptr; //saving next item in list
  free(L->First);            //deleting memory
  L->First=tmpElem;       //first item in the list is now the next we saved
  }
  L->Act=NULL;

/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/


 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void InsertFirst (tList *L, int val) {
  tElemPtr newElem=malloc(sizeof(struct tElem));      //allocation of the memory
if(newElem==NULL)           //handle of error
    {printf("Not enough memory\n");
    return;
    }
newElem->data=val;      //adding second parameter to list
newElem->ptr=L->First;  //moving of the first item to the item we add to the start
L->First=newElem;
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/


// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/

L->Act=L->First;    //setting first item as active
// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
  if(L->First!=NULL)      //testing if the adress is active
*val=L->First->data;    //copying of data to adress we get as param
else Error();           //if we would not have active first item

/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/


 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/

tElemPtr newElem;               //creating of new structure
if(L->First==NULL)return;       //chceck if adress is good
newElem=L->First;               //adding old first item to our variabile
if(L->Act==L->First)            //if we have only one item we will not have active one after this
    L->Act=NULL;
if(L->First->ptr!=NULL)         //moving the next item to the previous of it
    L->First=L->First->ptr;
free(newElem);                  //releasing the memory


//solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void PostDelete (tList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
if((L->Act==NULL) || (L->Act->ptr==NULL))   //check if we have active adresses and if we have to do something
    return;
tElemPtr Elem;      //our new variabile
Elem=L->Act->ptr;   //next item to active is inserted to our variabile
L->Act->ptr=Elem->ptr;  //first which we will delete is replace by the next to him
free(Elem);

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
if(L->Act!=NULL)
{
   tElemPtr newElemptr=malloc(sizeof(struct tElem));//new variabile
    if(newElemptr==NULL)    //check if malloc succedeed
    {
        printf("Not enough memory\n");
        return;
    }
    newElemptr->data=val;   //adding new data to new item
    newElemptr->ptr=L->Act->ptr;    //our new item will have adress to next item to active(now active)
    L->Act->ptr=newElemptr;     //new active item will be our new variabile
}

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
if(L->Act==NULL)//check for adress
    {Error();
    return;}
*val=L->Act->data;//copying data from active item



 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
if(L->Act!=NULL)//check of adress
     L->Act->data=val;//actualizing data in active item

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
if(L->Act!=NULL )   //check for adress
    {if( L->Act->ptr==NULL) //check for adress of next item
        {
        L->Act=NULL;    //if there is no next item the active item will not be
        return;
        }
    L->Act= L->Act->ptr;    //new active item is the next to the actual active
    }


// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (tList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return.
**/

return L->Act != NULL;//return the 0 if the item is not active at the moment, else it will not return zero

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c201.c */

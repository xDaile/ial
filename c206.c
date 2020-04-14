
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int errflg;
int solved;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

	L->Act=NULL;   //Set everything to NULL
  L->Last=NULL;
  L->First=NULL;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free.
**/

L->Act=L->First;        //With this element we will free memory
while(L->Act!=NULL)     //cycle while there is something in the list
{                       //
L->First=L->Act->rptr;  //next to first is now first
free(L->Act);           //now we are deleting memory alocated for data where was first
L->Act=L->First;        //actualize our element for delete
}                       //
L->Last=NULL;           //the last is null
L->First=NULL;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
tDLElemPtr new;                       //new element for new item
new=malloc(sizeof(struct tDLElem));   //allocating memory for it
if(new==NULL)                         //if the allocation was not succesfull
  {                                   //
  DLError();                          //
  return;                             //
}                                     //
  new->lptr = NULL;                   //left from new first will be nothing
  new->data = val;                    //saving the data to new structure
  if(L->First!=NULL)                  //if the list was not empty
    {                                 //
      new->rptr=L->First;             //right from our item will be the past first item
      L->First->lptr=new;             //connection from first to our new which is before it
      L->First=new;                   //new first is our
    }                                 //
  if(L->First==NULL)                  //if we have empty list
    {                                 //
      L->First=new;                   //first and last is our new item
      L->Last=new;                    //
      return;
    }

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
/******************/
tDLElemPtr new;
new=malloc(sizeof(struct tDLElem)); //new structure for new item
if(new==NULL)   //if allocation was succesfull
  {
  DLError();
  return;
  }
new->data=val;//saving data

new->rptr=NULL;//next to our new item will be nothing
new->lptr=L->Last;//our new item will point to item which was last
if(L->Last!=NULL && L->First!=NULL) //if our list was not empty
  {
//  new->rptr=NULL;
//  new->lptr=L->Last;
  L->Last->rptr=new;
  L->Last=new;
  }
else      // if it was empty
  {
  L->First=new;
  L->Last=new;
  }
// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
L->Act=L->First;    //new active item is the first

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
L->Act=L->Last;   //new active item is the last in the list

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

if(L->First==NULL)    //if we have some list
  {DLError();
  return;}
*val=L->First->data;    //setting variabile by the pointer

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
if(L->Last==NULL) //if we have list that is not empty
  {DLError();
  return;}
*val=L->Last->data; //setting variabile by the pointer

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
if(L->First==NULL)  //if we have empty list
  return;
if(L->Act==L->First)//if our active is the first.. then the active will not exist
  L->Act=NULL;
if(L->Last==L->First) //if we have only one item in our list
{
  L->Last=NULL;
}
tDLElemPtr tmp = L->First;  //new poiner for free
L->First=L->First->rptr;  //new first is item next to first
free(tmp);  //releasing the memory
 //solved = FALSE;
}
void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
if(L->Last==NULL || L==NULL)  //if we have some list
  return;
if(L->Act==L->Last) //if the active is the last
  L->Act=NULL;  //active will not be there then
tDLElemPtr tmp = L->Last; //new pointer for free

if(L->Last==L->First) //if we have only one item
{
  L->Last=NULL;
  L->First=NULL;
}
else{

L->Last=L->Last->lptr;  //new last will be item before the current last
L->Last->rptr=NULL; //now deleting the poiner to structure that we will free
}
free(tmp);//releasing the memory

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/

if(L->Act==NULL || L->Act==L->Last|| L==NULL) //if we have not active item or if our active item is the last item
  return;
tDLElemPtr tmp= L->Act->rptr; //new poiner , rigth to active item will be there

if(tmp->rptr!=NULL) //if our new item have not item after it
  {
  L->Act->rptr=tmp->rptr; //next item to active will be the next to our new item
  tmp->rptr->lptr=L->Act; //the item before our new will change the pint to the next item to item that is active one
  }
else
  {
  L->Act->rptr=NULL;  //active item will not point to somewhere
  L->Last=L->Act;   //the last will be the active one
  }


//L->Act->rptr=tmp->rptr;
/*if(tmp==L->Last)
  L->Last=L->Act;
if(tmp!=L->Last)
  tmp->rptr->lptr=L->Act;*/
free(tmp);
// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
if(L->Act==NULL || L->Act==L->First || !L)  // check if the active is something or if our active is not first or if we have list
  return;
tDLElemPtr tmp= L->Act->lptr; //new pointer will point to item that is after active item

if(L->First==tmp) //if the first item is that that is our new
  {
  L->Act->lptr=NULL;  //acitve pointer to item before it is now null

  L->First=L->Act;  //our first item is the active one

  }
else
{
  L->Act->lptr=tmp->lptr; //the item that active one point to after that is the next to the one that we have saved in tmp
  tmp->lptr->rptr=L->Act;

}

free(tmp);

}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
if(L->Act==NULL)return;   //if we have active item
tDLElemPtr new;
new=malloc(sizeof(struct tDLElem));//allocating new structure with handle error
if(new==NULL)
  {
  DLError();
  return;
  }
new->data=val;  //setting param for new structure and point to it from the active one
new->rptr=L->Act->rptr;
new->lptr=L->Act;
L->Act->rptr=new;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
if(L->Act==NULL)return;
tDLElemPtr new;
new=malloc(sizeof(struct tDLElem));   //allocating new structure
if(new==NULL)
  {
  DLError();
  return;
  }
new->data=val;  //setting parametres for new item
new->rptr=L->Act;
new->lptr=NULL;
if(L->Act->lptr)  //if our active item have poiner to item before it
{
  new->lptr=L->Act->lptr; //setting parameter of new structure
  L->Act->lptr->rptr=new;
}
else
{
  L->First=new;   //first is the new one
}
L->Act->lptr=new;
//
//L->Act->lptr=new;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

if(L->Act==NULL)  //if the active is active
{
  DLError();
  return;
}
*val=L->Act->data; //sending current item cata
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/

if(L->Act!=NULL)
{
  L->Act->data=val;//rewriting data to new data
}
// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
if(L->Act!=NULL)
{
  L->Act=L->Act->rptr; // active is the item next to active
}

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/

if(L->Act!=NULL)
{
  L->Act=L->Act->lptr;//new active is the item before active
}
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
return (L->Act!=NULL);//returning the value, if the item is active not zero

// solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c206.c*/

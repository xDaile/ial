
/* c016.c: **********************************************************}
{* Téma:  Tabulka s Rozptýlenými Položkami
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2014
**                              Radek Hranický, 2014-2018
**
** Vytvořete abstraktní datový typ
** TRP (Tabulka s Rozptýlenými Položkami = Hash table)
** s explicitně řetězenými synonymy. Tabulka je implementována polem
** lineárních seznamů synonym.
**
** Implementujte následující procedury a funkce.
**
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky (inicializace tabulky
**                 poté, co již byla použita)
**
** Definici typů naleznete v souboru c016.h.
**
** Tabulka je reprezentována datovou strukturou typu tHTable,
** která se skládá z ukazatelů na položky, jež obsahují složky
** klíče 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na další synonymum 'ptrnext'. Při implementaci funkcí
** uvažujte maximální rozměr pole HTSIZE.
**
** U všech procedur využívejte rozptylovou funkci hashCode.  Povšimněte si
** způsobu předávání parametrů a zamyslete se nad tím, zda je možné parametry
** předávat jiným způsobem (hodnotou/odkazem) a v případě, že jsou obě
** možnosti funkčně přípustné, jaké jsou výhody či nevýhody toho či onoho
** způsobu.
**
** V příkladech jsou použity položky, kde klíčem je řetězec, ke kterému
** je přidán obsah - reálné číslo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

void htInit ( tHTable* ptrht ) {
	if(!ptrht)return;//empty pointer
for(int n=0;n<HTSIZE;n++)//set value for every item in table
	(*ptrht)[n]=NULL;
// solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není,
** vrací se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

int position=hashCode(key);//find position by the key
tHTItem *actual=(*ptrht)[position];//item on the position is added to new variabile
while(actual!=NULL && strcmp(actual->key, key)!=0)//if actual item is the item we are looking for or it is just item with same value key
	{
		actual=actual->ptrnext;//if not we will find it next to item
	}
return actual;//returning the item with exact same key
 //solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
	if(ptrht==NULL)return;//if we have empty pointer
tHTItem* ptr=htSearch(ptrht,key);//we are searching by the key and then adding it to new variabile
if(ptr==NULL)//if the item on the position setted by the key is empty
	{
		tHTItem* next=malloc(sizeof(tHTItem));//allocating memory
		if(next==NULL)//if we have not enough memory
			return;
		next->key=key;
		next->data=data;
		next->ptrnext= (*ptrht)[hashCode(key)];//next is the previous one
		(*ptrht)[hashCode(key)] = next;//previous one will point to the next from it
		}
else{//if we have found item we will replace its value
	ptr->data=data;
}

// solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {
tHTItem* ptr=htSearch(ptrht,key);//our new item is item set by the key
if(ptr==NULL)	//if the item is empty function will exit
	return NULL;
else{
return &(ptr->data);//if not we will return the data set by the key
}
// solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {

	tHTItem* actual = NULL, * somethinghere = (*ptrht)[hashCode(key)];//new variabile actual is NULL, and somethinghere is the item at the position set by the key

		while (somethinghere) {//while we are not at the leaf level
			int res=strcmp(somethinghere->key, key);//comparing the key we get and key at the current leaf
			if(res==0)//if we found exactly same key we are at the end
				break;
			actual  = somethinghere;
			somethinghere = somethinghere->ptrnext;//the item is now the item that was next to item
		}

		if (somethinghere==NULL) return;//check if we have something next to item that we had
		if (actual!=NULL) {
			actual->ptrnext = somethinghere->ptrnext;//we set pointer of item actual to item that something here points to
		} else {
			(*ptrht)[hashCode(key)] = somethinghere->ptrnext;//item set by key is now the item that something here was pointing to

		}
	free(somethinghere);
// solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {//deleting all table
for(int i=0;i<HTSIZE;i++)//we are going throught all table
{
	tHTItem *actual=(*ptrht)[i];
	tHTItem* next=NULL;

	while(actual!=NULL)	//while we have some items, we will delete actual and as actual we will set that item that actual was pointing to before we delete it
	{
		next=actual->ptrnext;
		free(actual);
		actual=next;
	}


	(*ptrht)[i]=NULL;

}


// solved = 0; /*v pripade reseni, smazte tento radek!*/
}

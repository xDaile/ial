
/* c402.c: ********************************************************************}
{* Téma: Nerekurzivní implementace operací nad BVS
**                                     Implementace: Petr Přikryl, prosinec 1994
**                                           Úpravy: Petr Přikryl, listopad 1997
**                                                     Petr Přikryl, květen 1998
**			  	                        Převod do jazyka C: Martin Tuček, srpen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                                 Karel Masařík, říjen 2013
**                                                 Radek Hranický 2014-2018
**
** S využitím dynamického přidělování paměti, implementujte NEREKURZIVNĚ
** následující operace nad binárním vyhledávacím stromem (předpona BT znamená
** Binary Tree a je u identifikátorů uvedena kvůli možné kolizi s ostatními
** příklady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivní vložení nového uzlu do stromu
**     BTPreorder ...... nerekurzivní průchod typu pre-order
**     BTInorder ....... nerekurzivní průchod typu in-order
**     BTPostorder ..... nerekurzivní průchod typu post-order
**     BTDisposeTree ... zruš všechny uzly stromu
**
** U všech funkcí, které využívají některý z průchodů stromem, implementujte
** pomocnou funkci pro nalezení nejlevějšího uzlu v podstromu.
**
** Přesné definice typů naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na něj je typu tBTNodePtr. Jeden uzel obsahuje položku int Cont,
** která současně slouží jako užitečný obsah i jako vyhledávací klíč
** a ukazatele na levý a pravý podstrom (LPtr a RPtr).
**
** Příklad slouží zejména k procvičení nerekurzivních zápisů algoritmů
** nad stromy. Než začnete tento příklad řešit, prostudujte si důkladně
** principy převodu rekurzivních algoritmů na nerekurzivní. Programování
** je především inženýrská disciplína, kde opětné objevování Ameriky nemá
** místo. Pokud se Vám zdá, že by něco šlo zapsat optimálněji, promyslete
** si všechny detaily Vašeho řešení. Povšimněte si typického umístění akcí
** pro různé typy průchodů. Zamyslete se nad modifikací řešených algoritmů
** například pro výpočet počtu uzlů stromu, počtu listů stromu, výšky stromu
** nebo pro vytvoření zrcadlového obrazu stromu (pouze popřehazování ukazatelů
** bez vytváření nových uzlů a rušení starých).
**
** Při průchodech stromem použijte ke zpracování uzlu funkci BTWorkOut().
** Pro zjednodušení práce máte předem připraveny zásobníky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro práci
** s pomocnými zásobníky neupravujte
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocná funkce, kterou budete volat při průchodech stromem pro zpracování
** uzlu určeného ukazatelem Ptr. Tuto funkci neupravujte.
**/

	if (Ptr==NULL)
    printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
  else
    printf("Výpis hodnoty daného uzlu> %d\n",Ptr->Cont);
}

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)
/*   ------
** Inicializace zásobníku.
**/
{
	S->top = 0;
}

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
{
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
  if (S->top==MAXSTACK)
    printf("Chyba: Došlo k přetečení zásobníku s ukazateli!\n");
  else {
		S->top++;
		S->a[S->top]=ptr;
	}
}

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);
	}
	else {
		return (S->a[S->top--]);
	}
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
{
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace zásobníku.
**/

	S->top = 0;
}

void SPushB (tStackB *S,bool val) {
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
	if (S->top==MAXSTACK)
		printf("Chyba: Došlo k přetečení zásobníku pro boolean!\n");
	else {
		S->top++;
		S->a[S->top]=val;
	}
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0) {
		printf("Chyba: Došlo k podtečení zásobníku pro boolean!\n");
		return(NULL);
	}
	else {
		return(S->a[S->top--]);
	}
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Následuje jádro domácí úlohy - funkce, které máte implementovat.
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci binárního vyhledávacího stromu.
**
** Inicializaci smí programátor volat pouze před prvním použitím binárního
** stromu, protože neuvolňuje uzly neprázdného stromu (a ani to dělat nemůže,
** protože před inicializací jsou hodnoty nedefinované, tedy libovolné).
** Ke zrušení binárního stromu slouží procedura BTDisposeTree.
**
** Všimněte si, že zde se poprvé v hlavičce objevuje typ ukazatel na ukazatel,
** proto je třeba při práci s RootPtr použít dereferenční operátor *.
**/
*RootPtr=NULL;

//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vloží do stromu nový uzel s hodnotou Content.
**
** Z pohledu vkládání chápejte vytvářený strom jako binární vyhledávací strom,
** kde uzly s hodnotou menší než má otec leží v levém podstromu a uzly větší
** leží vpravo. Pokud vkládaný uzel již existuje, neprovádí se nic (daná hodnota
** se ve stromu může vyskytnout nejvýše jednou). Pokud se vytváří nový uzel,
** vzniká vždy jako list stromu. Funkci implementujte nerekurzivně.
**/

	if(*RootPtr==NULL)//if our tree is empty
		{

			*RootPtr=malloc(sizeof(struct tBTNode));
			if(RootPtr==NULL)
				return;
			(*RootPtr)->Cont=Content;
			(*RootPtr)->RPtr=NULL;
			(*RootPtr)->LPtr=NULL;

	}
	else// if the tree is not empty
		{
		tBTNodePtr Node=(*RootPtr);
		tBTNodePtr insert=NULL;
		while(insert==NULL)//while we inserted nothing
			{
				if(Content<Node->Cont )//we are going to left
					{
						if(Node->LPtr!=NULL)//there is leaf so we are going next
							Node=Node->LPtr;
						else//on the left side is not the leaf so we are inserting an item
						{
							insert=malloc(sizeof(struct tBTNode));
							if(insert==NULL)
								return;
							insert->Cont=Content;
							insert->LPtr=NULL;
							insert->RPtr=NULL;
							Node->LPtr=insert;
						}
					//Node=Node->LPtr;

					}
				else if(Content>Node->Cont)//we are going to right
					{
						if(Node->RPtr!=NULL)//there is leaf so we are going next
							Node=Node->RPtr;
						else//on the right is not the item so we are inserting an item
						{
							insert=malloc(sizeof(struct tBTNode));
							if(insert==NULL)
								return;
							insert->Cont=Content;
							insert->LPtr=NULL;
							insert->RPtr=NULL;
							Node->RPtr=insert;
						}
					//Node=Node->LPtr;


					}
				// if(Node=Node->RPtr->Cont && Node-RPtr!=NULL)
				else
					return;
		}
}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Preorder navštívené uzly zpracujeme voláním funkce BTWorkOut()
** a ukazatele na ně is uložíme do zásobníku.
**/
while(ptr!=NULL)
	{
	SPushP(Stack,ptr);//iserting the item to the top
	BTWorkOut(ptr);//printing our item
	ptr=ptr->LPtr;//our new item is now the item that the item was pointing to
	}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Průchod stromem typu preorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Preorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut().
**/
if (RootPtr!=NULL)//if we have some item
	{tStackP *Stack=(tStackP *)malloc(sizeof(tStackP));
	if(Stack==NULL)
		return;
	SInitP(Stack);//Initializing the stack
	Leftmost_Preorder(RootPtr,Stack);//we are going to left by this function
	while(SEmptyP(Stack)==FALSE)//while we have something in the stack
	{
			RootPtr=STopPopP(Stack);//poping out the item form stack
			Leftmost_Preorder(RootPtr->RPtr,Stack);//working with item
	}
	}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}


/*                                  INORDER                                   */

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Inorder ukládáme ukazatele na všechny navštívené uzly do
** zásobníku.
**/
while(ptr!=NULL)
	{
		SPushP(Stack,ptr);//pushing an item to the top of the stack
		ptr=ptr->LPtr;
	}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */

}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Průchod stromem typu inorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Inorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut().
**/

if (RootPtr!=NULL)
	{tStackP *Stack=(tStackP *)malloc(sizeof(tStackP));//new stack
	if(Stack==NULL)
		return;
	SInitP(Stack);//initializing the stack
	Leftmost_Inorder(RootPtr,Stack);
	while(SEmptyP(Stack)==FALSE)//while the stack is not empty
	{
			RootPtr=STopPopP(Stack);//popping out the item
			BTWorkOut(RootPtr);//printing the item
			Leftmost_Inorder(RootPtr->RPtr,Stack);
	}
	free(Stack);
	}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}

/*                                 POSTORDER                                  */

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Postorder ukládáme ukazatele na navštívené uzly do zásobníku
** a současně do zásobníku bool hodnot ukládáme informaci, zda byl uzel
** navštíven poprvé a že se tedy ještě nemá zpracovávat.
**/
	while(ptr!=NULL)
	{
		SPushP(StackP,ptr);//pushing to the top of the stackp
		SPushB(StackB, true);//pushing to the top of the stackb
		ptr=ptr->LPtr;//we are going to left


	}


//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Průchod stromem typu postorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Postorder, zásobníku ukazatelů a zásobníku hotdnot typu bool.
** Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut().
**/
if (RootPtr!=NULL)//if we have not NULL
//CREATING AND INITIALIZING TWO STACKS
	{tStackP *StackP=(tStackP *)malloc(sizeof(tStackP));
	if(StackP==NULL)
		return;
	tStackB *StackB=(tStackB *)malloc(sizeof(tStackB));
	if(StackB==NULL)
		return;
	SInitB(StackB);
	SInitP(StackP);
	Leftmost_Postorder(RootPtr,StackP,StackB);

	while(SEmptyP(StackP)==FALSE)//while we have not empty stack
	{
			RootPtr=STopPopP(StackP);
			if(STopPopB(StackB)==FALSE)
				BTWorkOut(RootPtr);
			else{
				SPushP(StackP,RootPtr);
				SPushB(StackB,false);
				Leftmost_Postorder(RootPtr->RPtr,StackP,StackB);


			}
		}
	free(StackB);
	free(StackP);
			//Leftmost_Postorder(RootPtr,StackP,StackB);
	}


	}


	// solved = FALSE;		  /* V případě řešení smažte tento řádek! */



void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zruší všechny uzly stromu a korektně uvolní jimi zabranou paměť.
**
** Funkci implementujte nerekurzivně s využitím zásobníku ukazatelů.
**/
///////////////odkoment
if (*RootPtr!=NULL)//if we have not empty pointer
	{
		tStackP *StackP=(tStackP *)malloc(sizeof(tStackP));//CREATING and Initializzing stack
		if(StackP==NULL)
			return;
		SInitP(StackP);
		SPushP(StackP,*RootPtr);
		tBTNodePtr delete;
		while(SEmptyP(StackP)==FALSE)//while the stack is not empty
		{
			delete=STopPopP(StackP);//the pointer for deleting

			if(delete->LPtr!=NULL)//if at the left side is something
				SPushP(StackP,delete->LPtr);//saving the current item into stack

			if(delete->RPtr!=NULL)//if at the right side is something
				SPushP(StackP,delete->RPtr);//saving current leaf

			free(delete);

		}

			*RootPtr=NULL;//like it was at the start
			//printf("Som v cycle \n");
			free(StackP);
			//printf("Som v cycle \n");




//	 solved = FALSE;		  /* V případě řešení smažte tento řádek! */
}}

/* konec c402.c */

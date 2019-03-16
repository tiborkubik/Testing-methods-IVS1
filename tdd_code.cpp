//======== Copyright (c) 2019, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Tibor Kubik <xkubik34@stud.fit.vutbr.cz>
// $Date:       $2019-02-16
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Tibor Kubik
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

/**
* Vytvorenie prazdneho listu: hodnota head(prvy prvok fronty) nastavim na NULL
*/
PriorityQueue::PriorityQueue()
{
  head = NULL;
}

/**
* Destructor listu: vymazanie vsetkych prvkov a uvolnenie pamati
*/
PriorityQueue::~PriorityQueue()
{
  Element_t *element = GetHead();

  while(element != NULL) {
    Element_t *temp = element;
    element = element->pNext;
    free(temp);                             //uvolnenie alokovanej pamati
  }
}

/*
* Funkcia insert, Vkladanie prvku do listu
*/
void PriorityQueue::Insert(int value)
{
    //alokacia pamate pre vkladany element
    Element_t *inserted_element = (Element_t*)malloc(sizeof(Element_t));
    inserted_element->value = value;        //vkladanym prvkom sa stane vtedy,
    inserted_element->pPrev = NULL;         //ked mu priradime hodnotu value
    inserted_element->pNext = NULL;         //z parametra funkcie

    //Vkladanie prvku do prazdneho listu
    if(GetHead() == NULL) {
       head = inserted_element;             //vlozeny prvok sa stane korenom
       return;
    }

    Element_t *actual_element = GetHead();  //pociatocna hodnota actual_element
                                            // bude prva hodnota listu

    //vkladanie elementu do listu s jednym prvkom
    if(actual_element->pPrev == NULL && actual_element->pNext == NULL) {
      if(value < actual_element->value) {
        inserted_element->pNext = actual_element;
        actual_element->pPrev = inserted_element;
        head = inserted_element;            //ak je vkladana hodnota mensia ako
        return;                             //head, novym headom bude vkladany
      }                                     //element

      inserted_element->pPrev = actual_element;
      actual_element->pNext = inserted_element;
      head = actual_element;
      return;
    }

    while(actual_element != NULL) {         //prechadzanie listom do konca

      //Kontrola pre prvy prvok
      if(actual_element->pPrev == NULL) {
        //EXAMPLE: inserted = 4; actual = 5
        if(value < actual_element->value) {
          actual_element->pPrev = inserted_element;
          inserted_element->pNext = actual_element;
          head = inserted_element;
          return;
        }
      }

      if(value < actual_element->value) {
        //EXAMPLE: inserted = 35; actual = 40
        actual_element->pPrev->pNext = inserted_element;
        inserted_element->pPrev = actual_element->pPrev;
        inserted_element->pNext = actual_element;
        actual_element->pPrev = inserted_element;
        return;
      }

      if(actual_element->pNext == NULL) {
        inserted_element->pPrev = actual_element;
        actual_element->pNext = inserted_element;
        return;
      }

      //inkrementacia v cykle
      actual_element = actual_element->pNext;
    }
}

/*
* Funkcia Remove, hlada prvok v zozname, ak ho najde, vymaze ho a vrati true
*/
bool PriorityQueue::Remove(int value)
{
  Element_t *actual_element = GetHead();

  //prazdny list
  if(actual_element == NULL) {
    return false;
  }

  //jednoprvkovy list
  if(actual_element->pPrev == NULL && actual_element->pNext == NULL && actual_element->value == value) {
    head = NULL;
    free(actual_element);
    return true;
  }

  //cyklus na prechadzanie prvkov listu (od najmensieho po najvacsi)
  while(actual_element != NULL) {

    //pripad, ked sme na prvom prvku
    if(actual_element->pPrev == NULL && actual_element->value == value) {
      head = actual_element->pNext;
      actual_element->pNext->pPrev = NULL;
      free(actual_element);
      return true;
    }

    //pripad, ked sme na poslednom prvku
    if(actual_element->pNext == NULL && actual_element->value == value) {
      actual_element->pPrev->pNext = NULL;
      free(actual_element);
      return true;
    }

    //pripad, ked sme v strede zoznamu
    if(actual_element->value == value) {
      actual_element->pPrev->pNext = actual_element->pNext;
      actual_element->pNext->pPrev = actual_element->pPrev;
      free(actual_element);
      return true;
    }

    //inkrementacia v cykle
    actual_element = actual_element->pNext;
  }
  return false;
}

/*
* Funkcia Find prejde celym zoznamom a hlada element s hodnotou rovnou parametru
*/
PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *actual_element = GetHead();
    while(actual_element != NULL) {
      if(actual_element->value == value) {
        return actual_element;                      //ak najdeme prvok, vratime dany element
      }
      actual_element = actual_element->pNext;
    }
    return NULL;                                    //ak sme nenasli element s hodnotou value, funkcia vrati NULL
}

/*
* Funkcia GetHead vracia element head, tzn. prvy element listu
*/
PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return head;
}

/*** Konec souboru tdd_code.cpp ***/

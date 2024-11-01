#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCriminal
{
  struct TCriminal  * m_Next;
  char              * m_Name;
  struct TCriminal ** m_Contacts;
  size_t              m_Cnt;
  size_t              m_Capacity;
} TCRIMINAL;

#endif /* __PROGTEST__ */

TCRIMINAL        * createRecord ( const char      * name,
                                  TCRIMINAL       * next )
{
    TCRIMINAL *l = (TCRIMINAL *)malloc(sizeof(TCRIMINAL));
    l->m_Name = (char *)malloc(strlen(name) + 1);
    strcpy(l->m_Name, name);
    l->m_Contacts = NULL;
    l->m_Cnt = 0;
    l->m_Capacity = 0;

    l->m_Next = next;
    return l;


}

void               addContact   ( TCRIMINAL       * dst,
                                  TCRIMINAL       * contact )
{

    if (dst->m_Cnt == dst->m_Capacity) {

        size_t newCapacity;
        if (dst->m_Capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = dst->m_Capacity * 2;
        }

        TCRIMINAL **newContacts = (TCRIMINAL **)realloc(dst->m_Contacts, newCapacity * sizeof(TCRIMINAL *));


        dst->m_Contacts = newContacts;
        dst->m_Capacity = newCapacity;
    }

    dst->m_Contacts[dst->m_Cnt++] = contact;
}


TCRIMINAL        * cloneList    ( TCRIMINAL       * src ) {
    if (src == NULL) {
        return NULL;
    }

    //duplicate each node

    TCRIMINAL * cur =  src;
    TCRIMINAL * newhead = NULL;

        while(cur != NULL)
        {
            //save next in temporary variable
            TCRIMINAL * tmp = cur->m_Next;
            //copy every value apart from contacts into nCur
            TCRIMINAL * nCur = (TCRIMINAL*) malloc(sizeof (TCRIMINAL));
            nCur->m_Cnt=cur->m_Cnt;
            nCur->m_Capacity=cur->m_Capacity;
            nCur->m_Name = (char *)malloc(strlen(cur->m_Name) + 1);
            strcpy(nCur->m_Name, cur->m_Name);


            if (newhead == NULL) {
                newhead = nCur;
            }
            //itarate
            cur->m_Next=nCur;
            nCur->m_Next=tmp;
            cur=tmp;


        }
        cur=src;

    TCRIMINAL * nCur=newhead;

    while(cur!=NULL && nCur->m_Next!=NULL){
//the last node
        if(cur->m_Contacts==NULL){
            nCur->m_Contacts=NULL;
        }else{

            nCur->m_Contacts = (TCRIMINAL **) malloc(cur->m_Capacity * sizeof(TCRIMINAL *));
            for (size_t i = 0; i < cur->m_Cnt; ++i) {

                nCur->m_Contacts[i] = cur->m_Contacts[i]->m_Next;
            }

        }
        cur=cur->m_Next->m_Next;
        nCur=nCur->m_Next->m_Next;
    }
    if(cur->m_Contacts==NULL){
        nCur->m_Contacts=NULL;
    }else{

        nCur->m_Contacts = (TCRIMINAL **) malloc(cur->m_Capacity * sizeof(TCRIMINAL *));
        for (size_t i = 0; i < cur->m_Cnt; ++i) {

            nCur->m_Contacts[i] = cur->m_Contacts[i]->m_Next;
        }

    }


    //disconect new list from the old one
    cur=src;
    nCur=newhead;
    while(cur!=NULL && nCur->m_Next!=NULL){
        cur->m_Next=nCur->m_Next;
        cur=nCur->m_Next;

        nCur->m_Next=cur->m_Next;
        nCur=cur->m_Next;
    }
    cur->m_Next=NULL;

        return newhead;


}


void               freeList     ( TCRIMINAL       * src )
{
    TCRIMINAL *current = src;
    TCRIMINAL *next;
    while (current != NULL) {

        free(current->m_Name);
        free(current->m_Contacts);


        next = current->m_Next;


        free(current);


        current = next;
    }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TCRIMINAL * a, *b;
  char tmp[100];

  assert ( sizeof ( TCRIMINAL ) == 3 * sizeof ( void * ) + 2 * sizeof ( size_t ) );
  a = NULL;
  a = createRecord ( "Peter", a );
  a = createRecord ( "John", a );
  a = createRecord ( "Joe", a );
  a = createRecord ( "Maria", a );
  addContact ( a, a -> m_Next );
  addContact ( a -> m_Next -> m_Next, a -> m_Next -> m_Next -> m_Next );
  addContact ( a -> m_Next -> m_Next -> m_Next, a -> m_Next );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Cnt == 1
           && a -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == nullptr);
  b = cloneList ( a );
  strcpy ( tmp, "Moe" );
  a = createRecord ( tmp, a );
  strcpy ( tmp, "Victoria" );
  a = createRecord ( tmp, a );
  strcpy ( tmp, "Peter" );
  a = createRecord ( tmp, a );
  addContact ( b -> m_Next -> m_Next -> m_Next, b -> m_Next -> m_Next );
  assert ( a
           && ! strcmp ( a -> m_Name, "Peter" )
           && a -> m_Cnt == 0 );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
           && a -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Next -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 0 );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Cnt == 1
           && b -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Cnt == 0 );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  freeList ( a );
  addContact ( b -> m_Next, b -> m_Next );
  a = cloneList ( b );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Cnt == 1
           && a -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Contacts[0] == a -> m_Next );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Cnt == 1
           && a -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == a -> m_Next
           && a -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == a -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Cnt == 1
           && b -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Contacts[0] == b -> m_Next );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Cnt == 1
           && b -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Cnt == 2
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[0] == b -> m_Next
           && b -> m_Next -> m_Next -> m_Next -> m_Contacts[1] == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  freeList ( b );
  freeList ( a );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

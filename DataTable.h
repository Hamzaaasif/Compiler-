#include<iostream>
#include"clasDT.h"
using namespace std;
class DataTable
{
  public:
  string Name;
  string Type;
  DataTable *Parent ;
  DataTable *next;
  clasDT *Ref;
  clasDT cdtobj;

  bool insertDT(string name , string type , DataTable *parent , clasDT *ref , DataTable **start)
  {
    DataTable *ptr = new DataTable;
    ptr->Name = name;
    ptr->Type = type;
    ptr->Parent=parent;
    ptr->Ref = ref;
    ptr->next=NULL;


    if(*start == NULL)
    {
      *start = ptr;
      return true;
    }
    else
    {

      DataTable *curr = *start;
        
        if(curr->Name == name )
        {
          return false;
        }
        else
        {

          while (curr->next != NULL)
          {
             curr = curr->next;

            if(curr->Name == name)
              {
              return false;
              }
          }

          curr->next=ptr;
          return true;

        }

      }
     
 }
      

DataTable* retAddress(string name , DataTable *start) //return curr address
 
  {

  if(start == NULL)
  {
    return NULL;
  }
  else
  {
    
    DataTable *curr = start;
    while(curr->next != NULL)
    {
      if(curr->Name == name)
      {
        return curr;
      }
      curr = curr->next;
    }

    if(curr->Name == name)
      {
        return curr;
      }
      else
      {
        return NULL;
      }
      
  }
  
}




void print(DataTable *start)
  {
    if(start==NULL)
    {
      cout<<"Table is empty"<<endl;
    }
    else
    {
      DataTable *curr=start;
      while(curr->next!=NULL)
      {
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->Parent<<"   ";
        cout<<endl<<"*****Data Table of class "<<curr->Name<<"*****"<<endl;
        cdtobj.print(curr->Ref);
        cout<<endl;
        curr=curr->next;
      }
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->Parent<<"   ";
        cout<<endl<<"*****Data Table of class "<<curr->Name<<"*****"<<endl;
        cdtobj.print(curr->Ref);
        cout<<endl;
    }
  }

};
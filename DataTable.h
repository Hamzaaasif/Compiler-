#include<iostream>
#include"clasDT.h"
using namespace std;
class DataTable
{
  public:
  string Name;
  string Type;
  DataTable *Parent;
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
    }
    else
    {

      DataTable *curr = *start;
        
        if(curr->Name == name )
        {
          cout<<"Redeclaration error : "<<name<<"  "<<type << endl;
          return false;
        }
        else
        {

          while (curr->next != NULL)
          {
             curr = curr->next;

            if(curr->Name == name)
              {
              cout<<"Redeclaration Error: "<<name<<"  "<<type<<endl;
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
    cout<<"CLASS NOT DECLEARED !!"<<endl;
    return NULL;
  }
  else
  {
    
    DataTable *curr = start;
    while(curr->next != NULL)
    {
      if(curr->Name == name)
      {
        cout<<"Name : " <<curr->Name<<" Type: "<<curr->Type<<" (at DT) "<<endl;
        return curr;
      }
      curr = curr->next;
    }

    if(curr->Name == name)
      {
        cout<<"Name : " <<curr->Name<<"  Type: "<<curr->Type<<" (at DT) "<<endl;
        return curr;
      }
      else
      {
        cout<<"CLASS NOT DECLEARED !!"<<endl;
        return NULL;
      }
      
  }
  
}




void print(DataTable *start)
  {
    if(start==NULL)
    {
      cout<<"List is empty"<<endl;
    }
    else
    {
      DataTable *curr=start;
      while(curr->next!=NULL)
      {
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->Parent<<"   "<<endl;

        cout<<"Class Data Table of class : "<<curr->Name<<endl;
        cdtobj.print(curr->Ref);
        cout<<endl;
        curr=curr->next;
      }
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->Parent<<"   "<<endl;
        cout<<"Class Data Table of class : "<<curr->Name<<endl;
        cdtobj.print(curr->Ref);
        cout<<endl;
    }
  }

};
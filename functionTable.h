#include<iostream>
using namespace std;
class functionTable
{
  private:
  string Name;
  string RetType;
  string ParaList;
  string ClassName;
  functionTable *next;

  public:
  bool insertfn(string name , string retType , string paralist , string classname , functionTable **start)
  {

    functionTable *ptr = new functionTable;
    ptr->Name = name;
    ptr->RetType = retType;
    ptr->ParaList=paralist;
    ptr->ClassName = classname;
    ptr->next=NULL;


    if(*start == NULL)
    {
      *start = ptr;
      return true;
    }
    else
    {

      functionTable *curr = *start;
        
        if(curr->Name == name && curr->ParaList == paralist && curr->ClassName == classname )
        {
          return false;
        }
        else
        {

          while (curr->next != NULL)
          {
             curr = curr->next;

            if(curr->Name == name && curr->ParaList == paralist && curr->ClassName == classname)
              {
              return false;
              }
          }

          curr->next=ptr;
          return true;

        }

      }
  }


string lookupFn(string name, string paralist , string classname , functionTable *start )
{
  functionTable *curr = start;
  if(start == NULL)
  {
    return "NULL";
  }
  else if(curr-> Name == name && curr->ParaList==paralist && curr->ClassName == classname)
  {
    return curr->RetType;
  }
  else
  {
    while(curr->next!=NULL)
    {
      curr=curr->next;
      if(curr-> Name == name && curr->ParaList==paralist && curr->ClassName == classname)
          {
              return curr->RetType;
          }
    }
    return "NULL";
  }
  
}


void printFN(functionTable *start)
  {
    if(start==NULL)
    {
      cout<<"Function Not decleared !!"<<endl;
    }
    else
    {
      functionTable *curr=start;
      while(curr->next!=NULL)
      {
        cout<<"Name: "<<curr->Name<<"       ";
        cout<<"RetType: "<<curr->RetType<<"     ";
        cout<<"PL: "<<curr->ParaList<<"     ";
        cout<<"className: "<<curr->ClassName<<"   "<<endl;
        curr=curr->next;
      }
        cout<<"Name: "<<curr->Name<<"    Ret Type: ";
        cout<<curr->RetType<<"   PL: ";
        cout<<curr->ParaList<<"   ClassName: ";
        cout<<curr->ClassName<<"   "<<endl;
    }
  }


};
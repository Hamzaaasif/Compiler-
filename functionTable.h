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
    }
    else
    {

      functionTable *curr = *start;
        
        if(curr->Name == name && curr->ParaList == paralist && curr->ClassName == classname )
        {
          cout<<"Redeclaration error : "<<name<<"  "<<retType << " "<< paralist <<endl;
          return false;
        }
        else
        {

          while (curr->next != NULL)
          {
             curr = curr->next;

            if(curr->Name == name && curr->ParaList == paralist && curr->ClassName == classname)
              {
              cout<<"Redeclaration error : "<<name<<"  "<<retType << " "<< paralist <<endl;
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
    cout<<"undeclared "<<endl;
    return "NULL";
  }
  else if(curr-> Name == name && curr->ParaList==paralist && curr->ClassName == classname)
  {
    cout<<"Return Type: "<< curr->RetType << endl;
    return curr->RetType;
  }
  else
  {
    while(curr->next!=NULL)
    {
      curr=curr->next;
      if(curr-> Name == name && curr->ParaList==paralist && curr->ClassName == classname)
          {
              cout<<"Return Type: "<< curr->RetType << endl;
              return curr->RetType;
          }
    }
    return "NULL";
  }
  
}




void print(functionTable *start)
  {
    if(start==NULL)
    {
      cout<<"List is empty"<<endl;
    }
    else
    {
      functionTable *curr=start;
      while(curr->next!=NULL)
      {
        cout<<curr->Name<<"   ";
        cout<<curr->RetType<<"   ";
        cout<<curr->ParaList<<"   ";
        cout<<curr->ClassName<<"   "<<endl;
        curr=curr->next;
      }
        cout<<curr->Name<<"   ";
        cout<<curr->RetType<<"   ";
        cout<<curr->ParaList<<"   ";
        cout<<curr->ClassName<<"   "<<endl;
    }
  }


};
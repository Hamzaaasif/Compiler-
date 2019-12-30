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
          cout<<"Redeclaration error Function already decleared: "<<name<<"  "<<retType << " "<< paralist <<endl;
          return false;
        }
        else
        {

          while (curr->next != NULL)
          {
             curr = curr->next;

            if(curr->Name == name && curr->ParaList == paralist && curr->ClassName == classname)
              {
              cout<<"Redeclaration error Function already decleared : "<<"Name: "<<name<<"  "<<"Return Type: "<<retType << " Para List: "<< paralist <<endl;
              return false;
              }
          }

          curr->next=ptr;
          cout<<"Function Inserted !! "<<endl;
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
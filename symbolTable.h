#include<iostream>
#include<stack>
using namespace std;
class symbolTable
{
  private:
  string Name;
  string Type;
  int scope;
  symbolTable *next;
  stack<int> scopeStack;
  int stacksize = 0;

  public:
  bool insertST(string name , string type , int scope , symbolTable **start) 
  {
    symbolTable *ptr = new symbolTable;
    ptr->Name = name;
    ptr->Type = type;
    ptr->scope = scope;
    ptr->next = NULL;

    if(*start == NULL)
    {
      *start = ptr;
    }
    else
    {
      symbolTable *curr = *start;
      if(curr->Name == name  && curr->scope == scope)
      {
        cout<<"Redeclaration error: "<<name<<"  "<<type << endl;
        return false;
      }
      else
      {

        while (curr->next != NULL)
        {
          curr = curr->next;
          if(curr->Name == name  && curr->scope == scope)
           {
            return false;
           }
        }

        curr->next=ptr;
        cout<<"Inserted in Symbol Table"<<endl;
        return true;
      }
      
    }
    
  }

int createScope()
{
  scopeStack.push(stacksize);
  stacksize++;
  return (stacksize-1);
}

int deleteScope()
{
  //intconst stacksize = scopeStack.size();
  scopeStack.pop();
  if(!scopeStack.empty())
  {
    return (scopeStack.top());
  }
  else
  {
    return  -1;
  }
}



string lookupST(string name , symbolTable *start)
{
  if(start == NULL)
  {
    cout<<"Not declared"<<endl;
    return "NULL";
  }

  else
  {
    string retType="NULL";
    bool f = true;
    stack <int> s = scopeStack;
    symbolTable *curr = start;
      while(curr->next!=NULL)
      {
        s = scopeStack;
        if(curr->Name == name )
        {
          while(!s.empty())
          {
             if(curr->scope != s.top() )
             {
               s.pop();
             }
             else
             {
               f=false;
               retType = curr->Type;
               break;    
             }
         }
        }
        curr = curr->next;
      }

      if(curr->Name == name )
        {
          while(!s.empty())
          {
            s = scopeStack;
             if(curr->scope != s.top() )
             {
               s.pop();
             }
             else
             {
               return  curr->Type;    
             }
          }
        }
        else if(f == false)
        {
          return retType;
        }
        else
        {
          cout<<"Not decleared "<<endl;
          return "NULL";
        }
  
   }

}





void printST(symbolTable *start)
  {
    if(start==NULL)
    {
      cout<<"List is empty"<<endl;
    }
    else
    {
      symbolTable *curr=start;
      while(curr->next!=NULL)
      {
        cout<<"Name: "<<curr->Name<<"     ";
        cout<<"Type: "<<curr->Type<<"     ";
        cout<<"Scope: "<<curr->scope<<"     "<<endl;
        curr=curr->next;
      }
        cout<<"Name: "<<curr->Name<<"     ";
        cout<<"Type: "<<curr->Type<<"     ";
        cout<<"Scope: "<<curr->scope<<"     "<<endl;
    }
  }
};
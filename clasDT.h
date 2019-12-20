#include<iostream>
using namespace std;
class clasDT
{
  
  private:
  string Name;
  string Type;
  string AM;
  string TM;
  clasDT *next;
  public:

  bool insertCDT(string name , string type , string am , string tm , clasDT **start)
  {
    clasDT *ptr = new clasDT;
    ptr->Name = name;
    ptr->Type = type;
    ptr->AM=am;
    ptr->TM = tm;
    ptr->next=NULL;


    if(*start == NULL)
    {
      *start = ptr;
    }
    else
    {
      clasDT *curr = *start;
      if(start == NULL)
      {
        cout<<"Redeclaration Error class exsists : "<<name<<"  "<<type << endl;
        return false;
      }
      else
      {
        while (curr->next != NULL)
        {
          curr = curr->next;
          if(curr->Name == name)
           {
            cout<<"Redeclaration Error : "<<name<<"  "<<type<<endl;
            return false;
           }
        }

        curr->next=ptr;
        return true;
      }
      
    }

  }





  void print(clasDT *start)
  {
    if(start==NULL)
    {
      cout<<"List is empty"<<endl;
    }
    else
    {
      clasDT *curr=start;
      while(curr->next!=NULL)
      {
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->AM<<"   ";
        cout<<curr->TM<<"   "<<endl;
        curr=curr->next;
      }
        cout<<curr->Name<<"   ";
        cout<<curr->Type<<"   ";
        cout<<curr->AM<<"   ";
        cout<<curr->TM<<"   "<<endl;
    }
  }
  
};

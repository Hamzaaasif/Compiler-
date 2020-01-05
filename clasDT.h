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
       if(curr->Name == name)
           {
            return false;
           }

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


string lookupCDT(string name , clasDT *start ) // type return kryga 
{

  if(start==NULL)
    {
      cout<<"Error: No defination found "<<endl;
      return "NULL";
    }
    else
    {
      clasDT *curr=start;
      while(curr->next!=NULL)
      {
        if(curr->Name == name && curr->AM !="private") //private access not allowed
        {
          return curr->Type;
        }
        curr=curr->next;
      }

        if(curr->Name == name && curr->AM !="private")  //private access not allowed
        {
          return curr->Type;
        }
        else
        {
          cout<<"Error: No defination found or private attribute"<<endl;
          return "NULL";
        }
        
    }
  }


  void print(clasDT *start)
  {
    if(start==NULL)
    {
      cout<<"Table is empty"<<endl;
    }
    else
    {
      clasDT *curr=start;
      while(curr->next!=NULL)
      {
        cout<<curr->Name<<"    ";
        cout<<curr->Type<<"    ";
        cout<<curr->AM<<"    ";
        cout<<curr->TM<<"    "<<endl;
        curr=curr->next;
      }
        cout<<curr->Name<<"    ";
        cout<<curr->Type<<"    ";
        cout<<curr->AM<<"    ";
        cout<<curr->TM<<"    "<<endl;
    }
  }
  
};

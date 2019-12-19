#include<iostream>
#include"WordBreak.h"
#include "symbolTable.h"
using namespace std;

int main()
{
  WordBreak letter ;
  symbolTable table;
  symbolTable *start=NULL;

  table.insertST("a" , "int" ,0 ,&start);
  table.insertST("b" , "intconst" ,0 ,&start);
  table.insertST("ab" , "float" ,0 ,&start); 
  table.insertST("bb" , "string" ,1 ,&start);
  table.insertST("b" , "int" ,2 ,&start);

  table.createScope();//0
  table.createScope();//1
  table.createScope();//2
  //cout<<table.deleteScope()<<endl;

  table.print(start);
  

  cout<<"Type: "<<table.lookupST("aab",start)<<endl<<endl;



  //cout<<"Type: "<<table.lookupST("b",start);
  //letter.Letter();
  cout<<endl;
  system("pause");
};
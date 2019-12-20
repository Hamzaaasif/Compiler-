#include<iostream>
#include"WordBreak.h"
//#include"DataTable.h"
#include"functionTable.h"
//#include "clasDT.h"
#include "clasDT.h"

using namespace std;

int main()
{
  WordBreak letter ;
  // symbolTable table;
  // symbolTable *start=NULL;

  // table.insertST("a" , "int" ,0 ,&start);
  // table.insertST("b" , "intconst" ,0 ,&start);
  // table.insertST("ab" , "float" ,0 ,&start); 
  // table.insertST("bb" , "string" ,1 ,&start);
  // table.insertST("b" , "int" ,2 ,&start);

  //table.createScope();//0
  //table.createScope();//1
 // table.createScope();//2
  //cout<<table.deleteScope()<<endl;

 // table.print(start);
  

  //cout<<"Type: "<<table.lookupST("aab",start)<<endl<<endl;



  //cout<<"Type: "<<table.lookupST("b",start);
  //letter.Letter();



  // DataTable *start =NULL;
  // DataTable DT;
  // DT.insertDT("point" , "class" , NULL , NULL  , &start);
  // DT.insertDT("rect" , "class" , NULL , NULL  , &start);
  // DT.insertDT("hamza" , "class" , NULL , NULL  , &start);
  // DT.print(start);

  // cout<<DT.lookupDT("point", start)<<endl;
  // cout<<DT.lookupDT("jase", start)<<endl;
  // cout<<endl;


// functionTable *start= NULL;
// functionTable fntable;

// fntable.insertfn("fn" , "int" , "int,float" , "global" , &start);
// fntable.insertfn("fn" , "int" , "float" , "global" , &start);
// fntable.insertfn("fn" , "void" , "int,float" , "A" , &start);
// fntable.insertfn("fn" , "int" , "int,float" , "B" , &start);


// fntable.print(start);
// cout<<endl;

// fntable.lookupFn("fkn" , "int,float" , "A" , start);
// cout<<"Ret Type: "<<fntable.lookupFn("fn" , "int" , "global" , start)<<endl;


clasDT *start = NULL;
clasDT cdt;
cdt.insertCDT("a" , "int" , "private" , "static" , &start);
cdt.insertCDT("ab" , "int" , "private" , "static" , &start);
cdt.insertCDT("a" , "float" , "private" , "NULL" , &start);//
cdt.insertCDT("ab" , "string" , "public" , "static" , &start);

cdt.print(start);




  system("pause");
};
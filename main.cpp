#include<iostream>
#include"WordBreak.h"
//#include"DataTable.h"

using namespace std;

int main()
{
  WordBreak letter ;
  letter.Letter();
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


  // cout<<"     Data Table    " <<endl<<endl;
  // DataTable *start =NULL;
  // DataTable DT;
  // DT.insertDT("point" , "class" , NULL , NULL  , &start);
  // DT.insertDT("rect" , "class" , NULL , NULL  , &start);
  // DT.insertDT("hamza" , "class" , NULL , NULL  , &start);
  // DT.print(start);
  
  // cout<<DT.retAddress("point", start)<<endl;
//   cout<<DT.retAddress("hamza", start)<<endl;
//   cout<<endl;


// cout<<"    Class Data Table    " <<endl<<endl;

// clasDT *CDTstart = NULL;
// clasDT cdt;
// cdt.insertCDT("a" , "int" , "private" , "static" , &CDTstart);
// cdt.insertCDT("ab" , "int" , "private" , "static" , &CDTstart);
// cdt.insertCDT("ac" , "float" , "public" , "NULL" , &CDTstart);
// cdt.insertCDT("abb" , "float" , "public" , "static" , &CDTstart);
// DT.insertDT("point" , "class" , NULL , CDTstart  , &start);

// DataTable* tmp = DT.retAddress("point", start);
// cout<<endl<< "Look up in CDT at main "<<cdt.lookupCDT("abb",tmp->Ref)<<endl;
// cdt.print(tmp->Ref);


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




  system("pause");
};
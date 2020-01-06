#include <iostream>
using namespace std;
#include "string"
#include"functionTable.h"
#include"DataTable.h"
#include"symbolTable.h"

class linklist
{
public:
  string cp;
  string vp;
  int lineno;
  linklist *next;
  linklist **curr;

bool globalflag = false; 

  //fn table
  functionTable *FNstart= NULL;
  functionTable Fnobj;
  string globalRetType="";
  string globalparalist ="";

 //Symbol Table 
  symbolTable *STstart =NULL;
  symbolTable STobj;
  int globalcurrScope = -1;
  string globalname="";
  string globaltype ="";


  //Data Table
  DataTable *DTstart =NULL;
  DataTable DTobj;
  DataTable *parent =NULL;
  string globalclassname = "Global";
  clasDT *CDTRef = NULL;
  clasDT classDTobj;
  string globalTM ="";
  string globalAM = "private";

  //compatibility
  string globalLeftType = "";
  string globalRightType = "";
  string Type = "";
  string globalOperator ="";
  string tempvar="";

  void insert(string cp, string vp, int lineno, linklist **start)
  {
    linklist *ptr = new linklist;

    ptr->cp = cp;
    ptr->vp = vp;
    ptr->lineno = lineno;
    ptr->next = NULL;
    if (*start == NULL)
    {
      *start = ptr;
    }
    else
    {
      linklist *curr = *start;
      while (curr->next != NULL)
      {
        curr = curr->next;
      }
      curr->next = ptr;
    }
  }



  bool start(linklist **start )
  {

    curr = start;
    globalcurrScope = STobj.createScope(); //global scope declare
    
    if ((*curr)->cp == "class" || (*curr)->cp == "DT" || (*curr)->cp == "ID" || (*curr)->cp == "static" || (*curr)->cp == "void" )
    {
      if (defs())
      {
        if (VI())
        {
          if ((*curr)->cp == "main")
          {
            globalname = (*curr)->vp; // Name
            (*curr) = (*curr)->next;
            if ((*curr)->cp == "(")
            {
              (*curr) = (*curr)->next;
              if (NV())
              {
                if(!Fnobj.insertfn (globalname , globalRetType , globalparalist , "Global" , &FNstart))
                {
                  cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
                }
                

                if ((*curr)->cp == "{")
                {
                  globalcurrScope = STobj.createScope(); //scope declared

                  (*curr) = (*curr)->next;
                  if (MST())
                  {
                    if ((*curr)->cp == "}")
                    {
                      globalcurrScope = STobj.deleteScope(); // main scope end

                      (*curr) = (*curr)->next;
                      if ((*curr)->cp == "$")
                      {
                        globalcurrScope = STobj.deleteScope(); //Global  scope end
                        cout<<endl<<endl<<"*****Symbol Table: ******"<<endl;
                        STobj.printST(STstart);

                        cout<<endl<<endl<<"*******Function Table: ********"<<endl;
                        Fnobj.printFN(FNstart);
                        

                        cout<<endl<<endl<<"------------Data Table---------------"<<endl;
                        DTobj.print(DTstart);
                        cout<<endl;

                        cout << "File end" << endl;
                        return true;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else if((*curr)->cp == "$")
    {
      cout << "File end" << endl;
                        return true;
    }
    else 
    {
      cout << "Error syntax at:  " << (*curr)->cp <<"     line no :  "<<(*curr)->lineno<< endl;
      return false;
    }
  }

  bool VI()
  {
    
    if ((*curr)->cp == "void" )
    {
      globalRetType = (*curr)->vp;
      (*curr) = (*curr)->next;
      return true;
    }
    else
    {
      return false;
    }
  }

  bool NV()
  {
      if ((*curr)->cp == "void") 
      {
        globalparalist = (*curr)->vp; //parameter List
        (*curr) = (*curr)->next;
        if((*curr)->cp == ")")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          return false;
        }
        
      }

      else if ((*curr)->cp == ")") //follow set
      {
        globalparalist = "";
        (*curr) = (*curr)->next;
        return true;
      }

      else
      {
        return false;
      }
        
  }



  bool defs()
  {
    
    if ((*curr)->cp == "class") 
    {
      if (classs())
      {
        if (defs())
        {
          return true;
        }
      }
    }


    else if ((*curr)->cp == "ID")
      {
        globaltype = (*curr)->vp; 
        Type = STobj.lookupST(globaltype , STstart);
        if(Type == "NULL")
         {
         // cout<<"Error: No defination found " <<Type<<" at line no: "<<(*curr)->lineno<<endl;
         }

        (*curr) = (*curr)->next;
        if (defs1())
        {
          if (defs())
          {
            return true;
          }
        }
      } 
    
      else if ((*curr)->cp == "DT")
      {
        globaltype = (*curr)->vp; //type 
         (*curr) = (*curr)->next;
         if ((*curr)->cp == "ID")
          {
            globalname = (*curr)->vp; //Name 
            (*curr) = (*curr)->next;
            if (defs2())
             {
              if (defs())
               {
                return true;
              }
           }
         }
      }

      else if ((*curr)->cp == "static")
      {
        (*curr) = (*curr)->next;
        if (type())
        {
          if ((*curr)->cp == "(")
          {
            (*curr) = (*curr)->next;
            if (fun_dec())
            {
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

    
      else if ((*curr)->cp == "void" ) 
      {
        return true;
      }

    else
    {
      
      return false;
    }
 }




  bool classs()
  {
    
    if ((*curr)->cp == "class")
    {
      globaltype = (*curr)->vp; //type ie class 

      (*curr) = (*curr)->next;
      if ((*curr)->cp == "ID")
      {
        globalclassname = (*curr)->vp; //class name saved

        (*curr) = (*curr)->next;
         parent = NULL;

        if (check_inh())
        {
          if ((*curr)->cp == "{")
          {
            CDTRef = NULL;
            if(!DTobj.insertDT(globalclassname , globaltype , parent , CDTRef , &DTstart))
            {
              cout<<"Error: Redeclaration "<<globalclassname<<" at line no: "<<(*curr)->lineno<<endl;
            }

            (*curr) = (*curr)->next;
            if (class_body())
            {
              if ((*curr)->cp == "}")
              {
                (*curr) = (*curr)->next;
                if ((*curr)->cp == ";")
                {
                  DataTable *DTtemp = DTobj.retAddress(globalclassname , DTstart);
                  if(DTtemp == NULL)
                  {
                    cout<<"Error: No defination found "<<globalclassname<<" at line no: "<<(*curr)->lineno<<endl;
                  }
                  DTtemp->Ref = CDTRef;
                  CDTRef = NULL;
                  globalclassname = "Global";
                  globalTM = "";
                  (*curr) = (*curr)->next;
                  return true;
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      return false;
    }
  }


  bool class_body()
  {
    
      if ((*curr)->cp == "ID")
      {
        globaltype = (*curr)->vp; //name

        (*curr) = (*curr)->next;
        if (X1())
        {
          if (class_body())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "DT")
      {
        globaltype = (*curr)->vp; 
        (*curr) = (*curr)->next;

        if ((*curr)->cp == "ID")
        {
          globalname = (*curr)->vp;
          (*curr) = (*curr)->next;
          if (X2())
          {
            if (class_body())
            {
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else 
        {
          return false;
        }
      }


      else if ((*curr)->cp == "public" || (*curr)->cp == "private")
      {
        globalAM =  (*curr)->vp;
        (*curr) = (*curr)->next;
        if ((*curr)->cp == ":")
        {
          (*curr) = (*curr)->next;
          if (class_body())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if (word())
      {

        if (type())
        {
          if ((*curr)->cp == "(")
          {
            (*curr) = (*curr)->next;
            if (fun_dec())
            {
              if(class_body())
              {
                return true;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          return false;
        }
        
      }


      else if ((*curr)->cp == "}")
      {
        return true;
      }

      else
      {
        return true;
      }
  }


  bool word()
  {
    
    if ((*curr)->cp == "virtual"  || (*curr)->cp == "static" || (*curr)->cp == "const")
    {
      globalTM = (*curr)->vp;
      (*curr) = (*curr)->next;
      return true;
    }
    else
    {
      return false;
    }

  }


  bool X1()
  {
    
      if ((*curr)->cp == "ID") 
      {
        globalname = (*curr)->vp; //name

        (*curr) = (*curr)->next;
        if (X3())
        {
          return true;
        }
        else  
        {
          return false;
        }
      }

      else if (intconstructor_fn())
      {
        return true;
      }

    else
    {
      return false;
    }
  }


  bool intconstructor_fn()
  {
    
    if ((*curr)->cp == "(")
    {

      DataTable *DTtemp = DTobj.retAddress(globaltype , DTstart) ;
      if(DTtemp == NULL)
      {
        cout<<"Error: No defination found "<<globaltype<<" at line no: "<<(*curr)->lineno<<endl;
      }
      (*curr) = (*curr)->next;
      if (para())
      {
        if(DTtemp != NULL &&  DTtemp->Name == globalclassname )
      {
        if(!Fnobj.insertfn(globalclassname, "void" , globalparalist , globalclassname , &FNstart))
        {
          cout<<"Error: Redeclaration "<<globalclassname<<" at line no: "<<(*curr)->lineno<<endl;
        }
        
      }
      else
      {
        cout<<"Error: Class not defined or constructor not allowed "<<globalclassname<<" at line no: "<<(*curr)->lineno<<endl;
      }

        if ((*curr)->cp == ")")
        {
          (*curr) = (*curr)->next;
          if ((*curr)->cp == "{")
          {
            globalflag = false;
            (*curr) = (*curr)->next;
            if (MST())
            {
              if ((*curr)->cp == "}")
              {
                (*curr) = (*curr)->next;
                   return true;
              }
              else
              {
                return false;
              }
            }
            else
            {
              return false;
            }
            
          }
          else
          {
            return false;
          }
          
        }
        else
        {
          return false;
        }
        
      }
      else
      {
        return false;
      }
      
    }

    else
    {
      return false;
    }
  }


  bool X2()
  {
    globalflag =true;
      if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (fun_dec())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if (dt_dec())
      {
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool X3()
  {
    globalflag = true;
      if ((*curr)->cp == "(")
      {
        
        (*curr) = (*curr)->next;
        if (fun_dec())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if (obj_dec())
      {
        return true;
      }

      else
      {
        
        return false;
      }
  }


  bool defs1()
  {
    
      if (ass_st())
      {
        return true;
      }

      else if ((*curr)->cp == "ID")
      {
        globalname = (*curr)->vp;

        (*curr) = (*curr)->next;
        if (X())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }

  
  bool X()
  {
    globalflag = false;

      if (obj_dec())
      {
        return true;
      }
      else if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (terminal())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }

  bool terminal()
  {
    
      if (fun_dec())
      {
        return true;
      }
      else if (intconstructor_dec())
      {
        return true;
      }
      else
      {
        
        return false;
      }
  }


  bool defs2()
  {
      if (dt_dec())
      {
        return true;
      }
      else if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (fun_dec())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }


  bool type()
  {
    

      if ((*curr)->cp == "ID")
      {
        globaltype =(*curr)->vp;//type

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname =(*curr)->vp; //name

          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "DT")
      {
        globaltype = (*curr)->vp; //type

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname =(*curr)->vp; //name
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }

  bool fun_dec()
  {
    string temptype = globaltype;
    string tempname = globalname;
      if (para())
      {
        if ((*curr)->cp == ")")
        {
          (*curr) = (*curr)->next;
          if(!Fnobj.insertfn(tempname , temptype , globalparalist , globalclassname , &FNstart))
          {
            cout<<"Error: Redeclaration "<<tempname<<" at line no: "<<(*curr)->lineno<<endl;
          }
            
 
            if ((*curr)->cp == "{")
            {
              (*curr) = (*curr)->next;
              if (MST())
              {
                if ((*curr)->cp == "}")
                {
                  (*curr) = (*curr)->next;
                  globalcurrScope = STobj.deleteScope(); //fn scope ends

                  return true;
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }


  bool inherit() //not inculuded 
  {
    
    if ((*curr)->cp == ":")
    {
      (*curr) = (*curr)->next;
      if ((*curr)->cp == "ID")
      {
        (*curr) = (*curr)->next;
        if (fn_call1())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool def(bool flag)
  {

      if ((*curr)->cp == "ID")
      {
       
        if ((*curr)->next->cp == "ID")
        {

          if(flag)
          {
            globalcurrScope = STobj.createScope();
            globalparalist="";
            flag=false;
          }

          globaltype = (*curr)->vp;
          globalparalist += (*curr)->vp + "," ;

          (*curr) = (*curr)->next;

          globalname = (*curr)->vp;
          (*curr) = (*curr)->next;
          if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "DT")
      {
       
        if ((*curr)->next->cp == "ID")
        {

          if(flag)
          {
            globalcurrScope = STobj.createScope();
            globalparalist="";
            flag=false;
          }

          globaltype = (*curr)->vp;
          globalparalist += (*curr)->vp + "," ;

          (*curr) = (*curr)->next;
          globalname = (*curr)->vp;

          (*curr) = (*curr)->next;
          if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
          return true;
        }

        else
        {
          
          return false;
        }
      }
      else
      {
        return false;
      }

  }


  bool check_inh()
  {
      if ((*curr)->cp == ":")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == "public" || (*curr)->cp == "private")
        {
          (*curr) = (*curr)->next;
          if ((*curr)->cp == "ID")
          {
            DataTable *DTtemp = DTobj.retAddress((*curr)->vp , DTstart);
            if(DTtemp != NULL)
            {
              parent = DTtemp;
            }
            else
            {
              cout<<"Error: No defination found "<<(*curr)->vp<<" at line no: "<<(*curr)->lineno<<endl;
            }
            (*curr) = (*curr)->next;
            return true;
          }
        }
      }

      else if( (*curr)->cp == "{")
      {
        return true;
      }

    else
    {
      
      return false;
   }

  }


  bool para()
  {
    bool flag = true;

      if (def(flag))
      {
        if (E())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "void")
      {
        globalparalist = "void";
        globalcurrScope = STobj.createScope(); //scope starts
        (*curr) = (*curr)->next;
        return true;
      }

      else if((*curr)->cp == ")")
      {
        globalcurrScope = STobj.createScope();
        globalparalist = "void";
        return true;
      }
      else
      {
        return false;
      }
  }


  bool E()
  {

      if ((*curr)->cp == ",")
      {
        (*curr) = (*curr)->next;
        if (def( false ))
        {
          if (E())
          {
            return true;
          }
        }
      }
      else if((*curr)->cp == ")")
      {
        return true;
      }

      else
      {
        return false;
      }

  }

  bool MST()
  {

      if (SST())
      {
        if (MST())
        {
          return true;
        }
      }
      else if ((*curr)->cp == "}")
      {
        return true;
      }
    else
    {
      
      return false;
    }
  }

  bool SST()
  {
    
      if (if_else())
      {
        return true;
      }
      else if (while_st())
      {
        return true;
      }
      else if (switch_st())
      {
        return true;
      }
      else if (for_st())
      {
        return true;
      }
      else if (return_st())
      {
        return true;
      }

      else if ((*curr)->cp == "continue")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          return false;
        }
      }

      else if ((*curr)->cp == "break")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "ID")
      {
        globaltype = (*curr)->vp; //Type
        tempvar = globaltype;
        globalLeftType = STobj.lookupST(globaltype , STstart);
        Type = globalLeftType;
        globalflag = false;
        (*curr) = (*curr)->next;
        if (SST1())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == "DT")
      {
        globalflag = false;
        globaltype = (*curr)->vp; //Type

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname = (*curr)->vp; //Name

          (*curr) = (*curr)->next;
          if (SST2())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

    else
    {
      
      return false;
    }
  }


  bool dt_dec()
  {

      if (new_array())
      {
        return true;
      }
      else if (init())
      {
        return true;
      }
      else
      {
        
        return false;
      }
  }

  
  bool new_array()
  {
    
    if ((*curr)->cp == "[")
    {
      (*curr) = (*curr)->next;
      if (OE())
      {
        if ((*curr)->cp == "]")
        {
          (*curr) = (*curr)->next;
          if (array2())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool array2()
  {
    
      if ((*curr)->cp == "=")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == "{")
        {
          (*curr) = (*curr)->next;
          if (array3())
          {
            if ((*curr)->cp == "}")
            {
              (*curr) = (*curr)->next;
              if ((*curr)->cp == ";")
              {
                return true;
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == ";")
      {
        (*curr) = (*curr)->next;
        return true;
      }

    else
    {
      
      return false;
    }

  }


  bool array3()
  {
      if (OE())
      {
        if (array4())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }


  bool array4()
  {

      if ((*curr)->cp == ",")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if (array4())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else if((*curr)->cp == "}")
      {
        return true;
      }
      else
      {
        return false;
      }
  }


  bool init()
  {

      if ((*curr)->cp == "AOP")
      {
        if(!STobj.insertST(globalname , globaltype , globalcurrScope, &STstart))
        {
          cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
        }
        globalOperator = (*curr)->vp;
        (*curr) = (*curr)->next;
        if (init2())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if (list())
        {
          return true;
        }

        else
        {
          return false;
        }

 } 

  bool init2()
  {
    string tempinit2 = globalOperator;
    string leftinit = globaltype;
      if (OE())
      {
        string temptype = compatibilityCheck(leftinit , Type ,"",tempinit2 );
        if(temptype =="NULL")
        {
          cout<<"Error: Not compatible,Type: "<<temptype <<" at line no: "<<(*curr)->lineno<<endl;
        }
        
        if ((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          return false;
        }
        
      }
      else if (init4())
      {
        return true;
      }

      else
      {
        
        return false;
      }
  }


  bool init3()
  {
    
      if ((*curr)->cp == "AOP")
      {
        (*curr) = (*curr)->next;
        if (init4())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if( (*curr)->cp == "," || (*curr)->cp == ";" )
      {
        return true;
      }

      else
      {
        return false;
      }
    
  }


  bool init4()
  {
   
      if ((*curr)->cp == "ID" && (*curr)->next->cp == "AOP")
      {
        (*curr) = (*curr)->next;
        if (init3())
        {
          if (list())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else if ((*curr)->cp == "int" || (*curr)->cp == "float" || (*curr)->cp == "bool" || (*curr)->cp == "string" || (*curr)->cp == "char")
      {
        (*curr) = (*curr)->next;
        if (list())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }


  bool list()
  {

      if ((*curr)->cp == ",")
      {

        if(!globalflag)
        {
          if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
        }
        else
        {
          if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
          globalflag = false;
        }

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname = (*curr)->vp;
          (*curr) = (*curr)->next;
          if((*curr)->cp != ";")
          {
            if(!globalflag)
             {
               if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
               {
                 cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
               }
               
            }
            else
            {
              if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
              {
                cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
              }
              
              globalflag = false;
            }
          }

          if (init3())
          {
            if (list())
            {
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
           else
          {
            
            return false;
          }
      }

      else if ((*curr)->cp == ";")
      {
        if(globalflag == false)
        {
          if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
         
        }
        else
        {
          if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
          globalflag = false;
        }

        (*curr) = (*curr)->next;
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool obj_dec()
  {
    

      if (array())
      {
        if (new_init())
        {
          
          if (list2())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }

  bool new_init()
  {
    
      if ((*curr)->cp == "AOP") 
      {

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          (*curr) = (*curr)->next;
          if (new_init())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          return false;
        }
      }

      else if((*curr)->cp == "," || (*curr)->cp == ";")
      {
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool list2()
  {
    DataTable* templist2 = DTobj.retAddress(globaltype , DTstart);
    if(templist2 == NULL)
    {
      cout<<"Error: No defination found "<<globaltype<<" at line no: "<<(*curr)->lineno<<endl;
    }
      if ((*curr)->cp == ",")
      {
        if(globalflag == false && templist2 != NULL)
        {
          if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
         
        }
        else if(templist2 != NULL)
        {
          if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
          {
            cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
        }        

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname = (*curr)->vp;

          if((*curr)->cp != ";")
          {

              if(globalflag == false && templist2!=NULL)
                {
                  if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
                  {
                    cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
                  }
                 
                }
               else if(templist2 != NULL)
                  {
                    if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
                    {
                      cout<<"Error: Redeclaration "<<globalname <<" at line no: "<<(*curr)->lineno<<endl;
                    }
                    
                  }
          }

          (*curr) = (*curr)->next;
          if (array())
          {
            if (new_init())
            {
              if (list2())
              {
                return true;
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      
      else if ((*curr)->cp == ";")
      {
        if(globalflag == false && templist2 != NULL)
            {
              if(!STobj.insertST(globalname , globaltype , globalcurrScope , &STstart))
              {
                cout<<"Error: Redeclaration "<<globalname<<" at line no: "<<(*curr)->lineno<<endl;
              }
             
            }
        else if(templist2 != NULL)
            {
              if(!classDTobj.insertCDT(globalname , globaltype , globalAM , globalTM , &CDTRef))
              {
                cout<<"Error: Redeclaration "<< globalname<< " at line no: "<<(*curr)->lineno<<endl;
              }
               
            }
        (*curr) = (*curr)->next;
        return true;
      }
    else
    {
      
      return false;
    }
  }

  bool array()
  {
      
      if ((*curr)->cp == "[")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if ((*curr)->cp == "]")
          {
            (*curr) = (*curr)->next;
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if( (*curr)->cp == "." || (*curr)->cp == "(" || (*curr)->cp == "uniary" || (*curr)->cp == "AOP" || (*curr)->cp == "," || (*curr)->cp == ";" )  //|| (*curr)->cp == ";"
      {
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool ass_st()
  {

      if (ass_st1())
      {
        if (XX())
        {
          if((*curr)->cp == ";")
          {
            (*curr) = (*curr)->next;
            return true;
          }
          else
          {
            return false;
          }
          
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }


  bool ass_st1()
  {
    
    if ((*curr)->cp == "AOP")
    {
      string templeft = Type;
      if(templeft == "NULL")
      {
        cout<<"Error: No defination found  " <<globaltype<<" at line no: "<<(*curr)->lineno<<endl;
      }
      string tempOperator = (*curr)->vp;

      (*curr) = (*curr)->next;
      if (OE())
      {
        globalRightType = Type;
        Type = compatibilityCheck(templeft , globalRightType,"",tempOperator);
        if(Type == "NULL")
        {
          cout<<"Error: Not compatible, Type:  "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
        }
        else
        {
         // cout<<"compatible, Type: "<<Type<<endl;
        }
        return true;
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool XX()
  {
    
      if (ass_st1())
      {
        if (XX())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else if ((*curr)->cp == ";")
      {
        return true;
      }
      else
       {
      
      return false;
       }
  }


  bool intconstructor_dec()
  {
    
      if (arg())
      {
        if ((*curr)->cp == ")")
        {
          DataTable *DTtemp  = DTobj.retAddress(globaltype , DTstart);
          if(DTtemp!=NULL)
          {
            if(Fnobj.lookupFn(globaltype ,globalparalist,globaltype,FNstart) == "NULL")
          {
            cout<<"Error: Constructor not allowed "<<globaltype <<" at line no : " <<(*curr)->lineno<<endl;
          }
          else
          {
            if(!STobj.insertST(globalname,globaltype,globalcurrScope,&STstart))
            {
              cout<<"Error: Redeclaration "<<globalname <<" at line no "<<(*curr)->lineno<<endl;
            }
            
          }
          }
          else
          {
            cout<<"Error: Constructor not allowed class not defined "<<globaltype <<" at line no : "<<globalparalist <<(*curr)->lineno<<endl;
          }
          
          (*curr) = (*curr)->next;
          if ((*curr)->cp == ";")
          {
            (*curr) = (*curr)->next;
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
    
  }


  bool fn_call1()
  {  

        if ((*curr)->cp == "(")
        {
          string tempfnname = tempvar;
          string fnname = globalRightType;
          string ope = globalOperator;
          string classname = STobj.lookupST(tempvar , STstart); 
          if(classname=="NULL")
          {
           // cout<<"Error: No defination found " <<tempvar<<" at line no: "<<(*curr)->lineno<<endl;
          }
          if(globalflag)
          {
            classname = Type;
            globalflag = false;
          }
          (*curr) = (*curr)->next;
          if (arg())
          {
            if(Fnobj.lookupFn(tempfnname , globalparalist , globalclassname , FNstart) == "NULL")
            {
              cout<<"Function not defined  "<<tempfnname <<" class name "<< globalclassname <<" at line no "<<(*curr)->lineno <<endl;
            }
            else
            {
              //
              Type = Fnobj.lookupFn(tempfnname , globalparalist , globalclassname , FNstart);
              cout<<"Function done"  <<" "<< Type <<endl;
            }
            
            
            if ((*curr)->cp == ")")
            {
              if(classname != "NULL")
              {
                Type = compatibilityCheck(classname , fnname , globalparalist , ope);
              if(Type=="NULL")
              {
                cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
              }
              }
              
              (*curr) = (*curr)->next;
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      // }
      // else
      // {
        
      //   return false;
      // }
  }


  bool check_id()
  { 
  
      if ((*curr)->cp == ".")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          (*curr) = (*curr)->next;
          if (array())
          {
            if (check_id())
            {
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if( (*curr)->cp == "(" )
      {
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool arg()
  {
    
      if (OE())
      {
        globalparalist = Type+",";
        if (arg1())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else if( (*curr)->cp == ")" )
      {
        globalparalist = "";
        return true;
      }
    else
    {
      
      return false;
    }
  }


  bool arg1()
  {
      
      if ((*curr)->cp == ",")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          globalparalist+=Type+",";
          if (arg1())
          {
            return true;
          }
        }
        else
        {
          
          return false;
        }
      }
      else if((*curr)->cp == ")" )
      {
        return true;
      }
    else
    {
      
      return false;
    }
  }


  bool SST1()
  {
     
      if (array())
      {
        if(L1())
        {
          if (L2())
        {
          return true;
        }
        else
        {
          
          return false;
        }
        }
        else
        {
          return false;
        }
        
      }

      else if ((*curr)->cp == "ID")
      {
        globalname = (*curr)->vp; //Name

        (*curr) = (*curr)->next;
        if (xxx())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else
      {
        
        return false;
      }
  }

  bool L1()
  {
    if((*curr)->cp == ".")
    {
      globalOperator = (*curr)->vp;

      (*curr) = (*curr)->next;
      if((*curr)->cp == "ID")
      {
        globalRightType = (*curr)->vp;
        (*curr) = (*curr)->next;

        if((*curr)->vp != "(")
        {
           Type = compatibilityCheck(globalLeftType , globalRightType,"",globalOperator);
            if(Type == "NULL")
            {
              cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
            }
            globalLeftType = Type;
            globalflag = true;
        }


        if(L1())
        {
         return true;
        }
      }
      else
      {
        return false;
      }
      
    }
    else if((*curr)->cp == "." || (*curr)->cp == "(" || (*curr)->cp == "inc_dec" || (*curr)->cp == "AOP")
    {
      return true;
    }
    else
    {
      return false;
    }
    
  }

  bool L2()
  {
      
      if (fn_call())
      {
        return true;
      }
      else if ((*curr)->cp == "uniary")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else if (ass_st())
      {
        return true;
      }
      else
      {
        
        return false;
      }
    
  }


  bool xxx()
  {
  
      if (obj_dec())
      {
        return true;
      }
      else if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (intconstructor_dec())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }


  bool SST2()
  {
    
  
      if (dt_dec())
      {
        return true;
      }
      else
      {
        
        return false;
      }
  }


  bool fn_call()
  {
    
   
      if (fn_call1())
      {
        if ((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }

  
  bool return_st()
  {
    
    if ((*curr)->cp == "return")
    {
      (*curr) = (*curr)->next;
      if (OE1())
      {
        if((*curr)->cp == ";")
        {
          (*curr) = (*curr)->next;
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool OE1()
  {
    
   
      if (OE())
      {
        return true;
      }
      else if( (*curr)->cp == ";" )
      {
        return true;
      }
      else
       {
      
      return false;
      }
  }

  
  bool if_else()
  {
    
    if ((*curr)->cp == "if")
    {
      (*curr) = (*curr)->next;
      if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if(Type != "int" && Type != "float" && Type != "string" && Type != "char" && Type != "bool")
          {
            cout<<"Error: Not compatible condition,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }
          
          if ((*curr)->cp == ")")
          {
            (*curr) = (*curr)->next;
            if ((*curr)->cp == "{")
            {
              globalcurrScope = STobj.createScope();
              (*curr) = (*curr)->next;
              if (MST())
              {
                if ((*curr)->cp == "}")
                {
                  globalcurrScope = STobj.deleteScope();
                  (*curr) = (*curr)->next;
                  if (optional_else())
                  {
                    return true;
                  }
                  else
                  {
                    
                    return false;
                  }
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool optional_else()
  {
      
      if ((*curr)->cp == "else")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == "{")
        {
          globalcurrScope = STobj.createScope();
          (*curr) = (*curr)->next;
          if (MST())
          {
            if ((*curr)->cp == "}")
            {
              globalcurrScope = STobj.deleteScope();
              (*curr) = (*curr)->next;
              return true;
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }

      else if( (*curr)->cp == "if" || (*curr)->cp == "switch" || (*curr)->cp == "for" || (*curr)->cp == "return" || (*curr)->cp == "ID" || (*curr)->cp == "DT" || (*curr)->cp == "continue" || (*curr)->cp == "break" || (*curr)->cp == "}" )
      {
        return true;
      }
      else
      {
        return false;
      }
      
  }


  bool while_st()
  {
    
    if ((*curr)->cp == "while")
    {
      (*curr) = (*curr)->next;
      if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if(Type != "int" && Type != "float" && Type != "string" && Type != "char" && Type != "bool")
          {
            cout<<"Error: Not compatible condition,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }

          if ((*curr)->cp == ")")
          {
            (*curr) = (*curr)->next;
            if ((*curr)->cp == "{")
            {
              globalcurrScope = STobj.createScope();
              (*curr) = (*curr)->next;
              if (MST())
              {
                if ((*curr)->cp == "}")
                {
                  globalcurrScope = STobj.deleteScope();
                  (*curr) = (*curr)->next;
                  return true;
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    
    else
    {
      
      return false;
    }
  }


  bool switch_st()
  {
    
    if ((*curr)->cp == "switch")
    {
      (*curr) = (*curr)->next;
      if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if(Type != "int" && Type != "char" && Type != "bool")
          {
            cout<<"Error: Not compatible condition<Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }

          if ((*curr)->cp == ")")
          {
            (*curr) = (*curr)->next;
            if ((*curr)->cp == "{")
            {
              globalcurrScope = STobj.createScope();
              (*curr) = (*curr)->next;
              if (case_st())
              {
                if (default_st())
                {
                  if ((*curr)->cp == "}")
                  {
                    globalcurrScope = STobj.deleteScope();
                    (*curr) = (*curr)->next;
                    return true;
                  }
                  else
                  {
                    
                    return false;
                  }
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }


  bool case_st()
  {
    
  
      if ((*curr)->cp == "case")
      {
        (*curr) = (*curr)->next;
        if (OE())                 
        {
          if(Type != "int"  && Type != "char" && Type != "bool")
          {
            cout<<"Error: Not compatible condition,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }

          if ((*curr)->cp == ":")
          {
            (*curr) = (*curr)->next;
            if ((*curr)->cp == "{")
            {
              globalcurrScope = STobj.createScope();
              (*curr) = (*curr)->next;
              if (MST())
              {
                if ((*curr)->cp == "}")
                {
                  globalcurrScope = STobj.deleteScope();
                  (*curr) = (*curr)->next;
                  if (case_st())
                  {
                    return true;
                  }
                  else
                  {
                    
                    return false;
                  }
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }


      else if( (*curr)->cp == "default" || (*curr)->cp == "}" )
      {
        return true;
      }
    
    else
    {
      
      return false;
    }
  }


  bool default_st()
  {
   
      if ((*curr)->cp == "default")
      {
        (*curr) = (*curr)->next;
        if ((*curr)->cp == ":")
        {
          (*curr) = (*curr)->next;
          if ((*curr)->cp == "{")
          {
            globalcurrScope = STobj.createScope();
            (*curr) = (*curr)->next;
            if (MST())
            {
              if ((*curr)->cp == "}")
              {
                globalcurrScope = STobj.deleteScope();
                (*curr) = (*curr)->next;
                return true;
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else if( (*curr)->cp == "}" )
      {
        return true;
      }
      else
      {
        return false;
      }
    
  }


  bool for_st()
  {
    
    if ((*curr)->cp == "for")
    {
      (*curr) = (*curr)->next;
      if ((*curr)->cp == "(")
      {
        globalcurrScope = STobj.createScope();
        (*curr) = (*curr)->next;
        if (C1())
        {
          if (C2())
          {
            if ((*curr)->cp == ";")
            {
              (*curr) = (*curr)->next;
              if (C3())
              {
                if ((*curr)->cp == ")")
                {
                  (*curr) = (*curr)->next;
                  if ((*curr)->cp == "{")
                  {
                    (*curr) = (*curr)->next;
                    if (MST())
                    {
                      if ((*curr)->cp == "}")
                      {
                        
                        globalcurrScope = STobj.deleteScope();
                        (*curr) = (*curr)->next;
                        return true;
                      }
                      else
                      {
                        
                        return false;
                      }
                    }
                    else
                    {

                      return false;
                    }
                  }
                  else
                  {
                    
                    return false;
                  }
                }
                else
                {
                  
                  return false;
                }
              }
              else
              {
                
                return false;
              }
            }
            else
            {
              
              return false;
            }
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
    }
    else
    {
      
      return false;
    }
  }

  bool C1()
  {
    
  
      if ((*curr)->cp == "DT")
      {
        globaltype = (*curr)->vp;
        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalname = (*curr)->vp;
          globalflag = false;
          (*curr) = (*curr)->next;
          if (dt_dec())
          {
            return true;
          }
          else
          {
            
            return false;
          }
        }
        else
        {
          return false;
        }
      }
      else if ((*curr)->cp == "ID")
      {
        globaltype = (*curr)->vp;
        Type = STobj.lookupST(globaltype , STstart);
        if(Type == "NULL")
         {
          cout<<"Error: No defination found " <<Type<<" at line no: "<<(*curr)->lineno<<endl;
         }


        (*curr) = (*curr)->next;
        if (ass_st())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }

      else if ((*curr)->cp == ";")
      {
        (*curr) = (*curr)->next;
        return true;
      }

    else
    {
      
      return false;
    }
  }


  bool C2()
  {
    
  
      if (OE())
      {
        if(Type != "int" && Type !="float" && Type !="char" && Type !="bool" && Type !="string")
        {
          cout<<"Error: Not compatable condition at for loop,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
        }
        return true;
      }
      else if( (*curr)->cp == ";" )
      {
        return true;
      }
    
    else
    {
      
      return false;
    }
  }

  bool C3()
  {
    
  
      if ((*curr)->cp == "ID")
      {
        globaltype = (*curr)->vp;
        Type = STobj.lookupST(globaltype , STstart);
        if(Type == "NULL")
         {
          cout<<"Error: No defination found " <<Type<<" at line no: "<<(*curr)->lineno<<endl;
         }
         
        (*curr) = (*curr)->next;
        if (X11())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else if ((*curr)->cp == "uniary")
      {
        (*curr) = (*curr)->next;
        return true;
      }

      else if( (*curr)->cp == ")" )
      {
        return true;
      }
    else
    {
      
      return false;
    }
  }


  bool X11()
  {
    
   
      if (ass_st1()) 
      {
        return true;
      }
      else if ((*curr)->cp == "uniary")
      {
        (*curr) = (*curr)->next;
        return true;
      }
      else
      {
      return false;
      }
  }

  bool OE()
  {
    
      if (AE())
      {
        if (OEE())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
  }

  bool AE()
  {
    
      if (RE())
      {
        if (AEE())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
  }

  bool OEE()
  {

      if ((*curr)->cp == "||")
      {
        globalLeftType = Type; //temp save from F type
        globalOperator =  (*curr)->vp; //operator save
        (*curr) = (*curr)->next;
        if (AE())
        {
          globalRightType = Type;
          Type = compatibilityCheck(globalLeftType , globalRightType , "" , globalOperator); 
          if(Type=="NULL")
          {
            cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }
          if(OEE())
          {
            return true;
          }
          else
          {
            return false;
          }
          
          
        }
        else
        {
          
          return false;
        }
      }

      else if ( (*curr)->cp == "," || (*curr)->cp == ")"||(*curr)->cp == ";"||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":" )
      {
        
        return true;
      }
    else
    {
      
      return false;
    }
  }


  bool RE()
  {

    
    if (PE())
      {
        if (REE())
        {
          return true;
        }
        else
        {
          
          return false;
        }
      }
      else
      {
        
        return false;
      }
  }

  bool PE()
  {

    
      if (ME())
      {
        if (PEE())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {

        return false;
      }
  }

  bool ME()
  {
      if (F())
      {
        if (MEE())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
  }

  bool F()
  {
    
      if ((*curr)->cp == "int" || (*curr)->cp == "float" || (*curr)->cp == "char"  || (*curr)->cp == "bool" || (*curr)->cp == "string")
      {
        Type = (*curr)->cp ;//return type of constant ie int const float const etc

         (*curr) = (*curr)->next;
          return true;
      }

      else if ((*curr)->cp == "(")
      {
        (*curr) = (*curr)->next;
        if (OE())
        {
          if ((*curr)->cp == ")")
          {
             (*curr) = (*curr)->next;
              return true;
          }
          else
          {
            return false;
          }
          
        }

        else
        {
          return false;
        }
        
      }

      else if ((*curr)->cp == "!")
      {
        (*curr) = (*curr)->next;
        if (PE())
        {
            return true;
        }
      }

      else if ((*curr)->cp == "ID")
      {
         tempvar = (*curr)->vp; //left type of operator 
         globalLeftType = STobj.lookupST(tempvar , STstart);
         if(globalLeftType=="NULL")
         {
           //cout<<"Error: No defination found " <<tempvar<<" at line no: "<<(*curr)->lineno<<endl;
         }
         globalflag = false;


        (*curr) = (*curr)->next;
        if (XOE1())
        {  
          return true;
        }
        else
        {
          return false;
        }
        
      }

      else
      {
        return false;
      }
  }
  

  bool XOE1()
  {
      if (fn_call1())
      {
        return true;
      }

      else if (nt2())
      {
             return true;
      }

      else if( (*curr)->cp == "," || (*curr)->cp == ")"|| (*curr)->cp == ";" ||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":"  ||(*curr)->cp == "||" ||(*curr)->cp == "&&" ||(*curr)->cp == "ROP" ||(*curr)->cp == "MDM" ||(*curr)->cp == "PM" )
      {
        if(globalflag == false)
        {
          Type = STobj.lookupST(tempvar , STstart);
          if(Type=="NULL")
          {
            cout<<"Error: No defination found " <<tempvar<<" at line no: "<<(*curr)->lineno<<endl;
          }
        }
        globalflag = false;
        return true;
      }

    else
    {
      return false;
    }
  }

  bool nt2()
  { 
      if ((*curr)->cp == ".")
      {
        globalOperator = (*curr)->vp;

        (*curr) = (*curr)->next;
        if ((*curr)->cp == "ID")
        {
          globalRightType = (*curr)->vp;
          if((*curr)->next->cp != "(" )
          {
            Type = compatibilityCheck(globalLeftType , globalRightType,"",globalOperator);
            if(Type=="NULL")
            {
              cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
            }
            globalLeftType = Type;
            globalflag = true;
          }
          
          (*curr) = (*curr)->next;
            if (XOE1())
            {
              return true;
            }
            else
            {
              return false;
            }
        }
        else
        {
          return false;
        }
      }

      else if( (*curr)->cp == "uniary" )
      {
        return true;
      }
    
    else
    {
      return false;
    }
  }

  bool AEE()
  {
       
      if ((*curr)->cp == "&&")
      {
        globalLeftType = Type; //temp save from F type
        globalOperator =  (*curr)->vp; //operator save
        (*curr) = (*curr)->next;
        if (RE())
        {
          globalRightType = Type;
          Type = compatibilityCheck(globalLeftType , globalRightType , "" , globalOperator); 
          if(Type=="NULL")
          {
            cout<<"Error: Not compatible, Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }
          if (AEE())
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        else
        {
          return false;
        }
        
      }

      else if( (*curr)->cp == "," || (*curr)->cp == ")"||(*curr)->cp == ";"||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":"  ||(*curr)->cp == "||" )
      {
        return true;
      }
    
    else
    {
      return false;
    }
  }


  bool PEE()
  {
    
      if ((*curr)->cp == "PM")
      {
        globalLeftType = Type; //temp save from F type
        globalOperator =  (*curr)->vp; //operator save

        (*curr) = (*curr)->next;
        if (ME())
        {
          globalRightType = Type;
          Type = compatibilityCheck(globalLeftType , globalRightType , "" , globalOperator);
          if(Type=="NULL")
          {
            cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }
          if (PEE())
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        else
        {
          return false;
        }
      }
      else if( (*curr)->cp == "," || (*curr)->cp == ")"||(*curr)->cp == ";"||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":"  ||(*curr)->cp == "||" ||  (*curr)->cp == "&&" ||  (*curr)->cp == "ROP"  )
      {
        return true;
      }
    
    else
    {
      return false;
    }
  }


  bool MEE()
  {
    
      if ((*curr)->cp == "MDM")
      {
        globalLeftType = Type; //temp save from F type
        globalOperator =  (*curr)->vp; //operator save

        (*curr) = (*curr)->next;
        if (F())
        {
          globalRightType = Type;
          Type = compatibilityCheck(globalLeftType , globalRightType , "" , globalOperator); 
          if(Type=="NULL")
          {
            cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }

          if (MEE())
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        else
        {
          return false;
        }
      }
      else if( (*curr)->cp == "," || (*curr)->cp == ")"||(*curr)->cp == ";"||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":"  ||(*curr)->cp == "||"  || (*curr)->cp == "&&" || (*curr)->cp == "PM" || (*curr)->cp == "ROP" )
      {
        return true;
      }
    
    else
    {
      return false;
    }
  }


  bool REE()
  {
    
      if ((*curr)->cp == "ROP")
      {
        globalLeftType = Type; //temp save from F type
        globalOperator =  (*curr)->vp; //operator save

        (*curr) = (*curr)->next;
        if (PE())
        {
          globalRightType = Type;
          Type = compatibilityCheck(globalLeftType , globalRightType , "" , globalOperator); 
          if(Type=="NULL")
          {
            cout<<"Error: Not compatible,Type: "<<Type<<" at line no: "<<(*curr)->lineno<<endl;
          }
          if (REE())
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        else
        {
          return false;
        }
      }
      else if( (*curr)->cp == "," || (*curr)->cp == ")"||(*curr)->cp == ";"||(*curr)->cp == "}"||(*curr)->cp == "AOP"||(*curr)->cp == "]"||(*curr)->cp == ":"  ||(*curr)->cp == "||"  || (*curr)->cp == "&&")
      {
        return true;
      }
    
    else
    {
      return false;
    }
  }


string compatibilityCheck(string leftType , string rightType ,string paralist ,string Operator) 
{
  if( (leftType == "int" && rightType == "int") && (Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/" || Operator == "%" || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "=" ||  Operator == "+=" || Operator == "-=" || Operator == "*=" || Operator == "/=" || Operator == "%=" || Operator == "&&" || Operator == "||" ) )
  {
    return "int";
  }
  else if( ((leftType == "int" && rightType == "float")  || (leftType == "float" && rightType == "int") || (leftType == "float" && rightType == "float") )  &&  ( Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/" || Operator == "%" || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "=" ||  Operator == "+=" || Operator == "-=" || Operator == "*=" || Operator == "/=" || Operator == "%="  || Operator == "&&" || Operator == "||") )
  {
    return "float";
  }
  else if( (leftType == "string" && rightType == "string") && (Operator == "+" || Operator=="+=" || Operator=="="  || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "&&" || Operator == "||" ) )
  {
    return "string";
  }
  else if( leftType == "bool" && rightType == "bool"  && ( Operator=="="  || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "&&" || Operator == "||" )  )
  {
    return "bool";
  }
  else if( leftType == "char" && rightType == "char"  && ( Operator=="="  || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "&&" || Operator == "||" )  )
  {
    return "char";
  }

  else if(Operator == ".")
  {
    DataTable *DTtemp;
    string CDTtemp;
    DTtemp = DTobj.retAddress(leftType , DTstart);
    if(DTtemp != NULL)
    {
      CDTtemp = classDTobj.lookupCDT(rightType , DTtemp->Ref);
      string fntype = Fnobj.lookupFn(rightType , paralist , leftType ,FNstart); 
      if(CDTtemp != "NULL") //for atribute a.b
      {
       return CDTtemp;
      }
      else if(fntype != "NULL") //for fucntion a.b()
      {
       return fntype;
      }
      else if(DTtemp->Parent != NULL) //for attributes in parent
      {
      string temp = DTtemp->Parent->Name;
      return compatibilityCheck(temp , rightType , paralist ,".");
      }
      else
      {
        return "NULL";
      }
    }
    else
    {
      return "NULL";
    }

  }
    else
    {
      return "NULL";
    }
}

  void print(linklist **start)
  {
    if (start == NULL)
    {
      cout << "List is empty" << endl;
    }
    else
    {
      linklist *curr = *start;
      while (curr->next != NULL)
      {
        cout << "CP :   " << curr->cp << "  ";
        cout << "VP :   " << curr->vp << "  ";
        cout << "Lineno :   " << curr->lineno << "  " << endl;
        curr = curr->next;
      }
      cout << "CP : " << curr->cp << "  ";
      cout << "VP : " << curr->vp << "  ";
      cout << "Lineno : " << curr->lineno << "  " << endl;
    }
  }

};
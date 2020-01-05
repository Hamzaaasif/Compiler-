#include<iostream>
#include<fstream>
#include<regex>
#include"Token.h"
#include<string>
Token token;
using namespace std;

class WordBreak
{
  public:
  void Letter()
  {
   ifstream quest("SampleCode.txt");
   char charArr[1000];
   int wordcout=0;
   while(quest.get(charArr[wordcout]))
    {  
      wordcout++;
    } 
    split(charArr,wordcout);
  }


  void split(char array[], int wordCount)
  {
    string intconst="[+|-][[:digit:]]+|[0-9]+";
    string isalpha = "[a-zA-Z]|[0-9]";
    string isdigit = "[[:d:]]";
    bool match = true;
    int i=0;
    int arrindex=0;
    for(arrindex=0;arrindex<=wordCount;arrindex++)
    {
      bool wordover = false;
      string word="";
      i=0;
      bool check = true;
      //string covertStr(1,array[arrindex]);
      // regex regstr(isalpha);

     
     if(array[arrindex]=='=' || array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/' || array[arrindex]=='<' || array[arrindex]=='>' || array[arrindex]=='!' || array[arrindex]=='%')
        {
          
          if(array[arrindex+1]=='=')
          {
            
            wordover = true;
            word+=array[arrindex];
          //cout<<array[arrindex];
          arrindex++;
         // cout<<array[arrindex];
         word+=array[arrindex];
          arrindex++;
      
          }
        }

        if(wordover)
          {
            //cout<<word<<endl;
            token.generateToken(word, lineno);
            word="";
            wordover=false;
          }



      top:
      string covertfloat(1,array[arrindex]);
      regex regfloat(isdigit);
      match = regex_match(covertfloat,regfloat);
      while(match)
      {
        check = false;
        wordover=true;
        word+=array[arrindex];
        //cout<<array[arrindex];
        arrindex++;
         string covertfloat(1,array[arrindex]);
        match = regex_match(covertfloat,regfloat);
      }

      if(array[arrindex]=='.' && i==0) 
      {
        i=1;
        word+=array[arrindex];
        arrindex++;
        goto top;
      }

      string covertStr(1,array[arrindex]);
      regex regstr(isalpha);
      match = regex_match(covertStr,regstr);
      while(match)
      {
        if(match == true)
       {
         i++;
        check = false;
        wordover=true;
        word+=array[arrindex];
        //cout<<array[arrindex];
        arrindex++;
        string covertStr(1,array[arrindex]);
        match = regex_match(covertStr,regstr);
       }
      }
      

      if(wordover)
      {
        //cout<<word;
        token.generateToken(word, lineno);
        wordover=false;
        word="";
      }

      if(i>0)
      {
       // cout<<endl;
        i=0;
      }

      if(array[arrindex]=='\"' )
        {
          i++;
          wordover=true;
          word+=array[arrindex];
         // cout<<array[arrindex];
          arrindex++;
          while(array[arrindex]!='\"'  && arrindex != wordCount )
          {
            wordover=true;
            i++;
            word+=array[arrindex];
           // cout<<array[arrindex];
            arrindex++;
            if(array[arrindex] == '\\' )
            {
            word+=array[arrindex];
            arrindex++;
            word+=array[arrindex];
            arrindex++;
            }
          }
           word+=array[arrindex];
           // cout<<array[arrindex];
            arrindex++;
        }
        if(wordover)
        {
         //cout<<word;
         token.generateToken(word, lineno);
          word="";
          wordover=false;
          i=0;
        }

        if(array[arrindex]=='=' || array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/' || array[arrindex]=='<' || array[arrindex]=='>' || array[arrindex]=='!' || array[arrindex]=='%')
        {
          if(array[arrindex+1]=='=')
          {
          i++;
          wordover=true;
          word+=array[arrindex];
         // cout<<array[arrindex];
          arrindex++;
          word+=array[arrindex];
          //cout<<array[arrindex];
          arrindex++;
          }

        }

        if(wordover)
        {
          //cout<<word;
          token.generateToken(word, lineno);
          word="";
          wordover=false;
        }



        if(array[arrindex]=='\'')
        {
          wordover=true;
          word+=array[arrindex];
          arrindex++;
          if(array[arrindex]=='\\')
          {
            word+=array[arrindex];
            arrindex++;
          }
            word+=array[arrindex];
            arrindex++;
            word+=array[arrindex];
            arrindex++;
        }

        if(wordover)
        {
          //cout<<word;
          token.generateToken(word, lineno);
          word="";
          wordover=false;

        }


        
        if((array[arrindex]=='+' && array[arrindex+1]=='+') || (array[arrindex]=='-' && array[arrindex+1]=='-') || (array[arrindex]=='&' && array[arrindex+1]=='&') || (array[arrindex]=='|' && array[arrindex+1]=='|')  || (array[arrindex]==':' && array[arrindex+1]==':') || (array[arrindex]=='<' && array[arrindex+1]=='<') || (array[arrindex]=='>' && array[arrindex+1]=='>')) 
        {
          i++;
          wordover=true;
          word+=array[arrindex];
          //cout<<array[arrindex];
          arrindex++;
          word+=array[arrindex];
          //cout<<array[arrindex];
          arrindex++;
        }

         if(wordover)
      {
       // cout<<word;
       token.generateToken(word, lineno);
        wordover=false;
        word="";
      }
        
        if(i>0)
      {
        //cout<<endl;
        i=0;
      }


      if(array[arrindex]=='=' || array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/' || array[arrindex]=='<' || array[arrindex]=='>' || array[arrindex]=='!' || array[arrindex]=='%')
        {
          if(array[arrindex+1]=='=')
          {
          i++;
          wordover=true;
          word+=array[arrindex];
         // cout<<array[arrindex];
          arrindex++;
          word+=array[arrindex];
          //cout<<array[arrindex];
          arrindex++;
          }

        }

        if(wordover)
        {
          //cout<<word;
          token.generateToken(word, lineno);
          word="";
          wordover=false;
        }


      if(array[arrindex] == '\n')
      {
        lineno++;
      }
    
        string acovertStr(1,array[arrindex]);
        match = regex_match(acovertStr,regstr);
      if(!match  &&  array[arrindex] !='\'')
      {
        word+=array[arrindex];
        //cout<<word<<endl;
        token.generateToken(word, lineno);
        word="";
      }
      else
      {
        arrindex--;
      }
      
    }

  }


int lineno=1;
};
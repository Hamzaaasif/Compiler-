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
    
    checkalpha(charArr,wordcout);
    //cout<<checkalpha(charArr)<<endl;
  }


  void checkalpha(char array[], int wordCount)
  {

    string isalpha = "[a-zA-Z]|[0-9]";
    // string charA ="[\\\\][nortb]";
    // string charB="[\\\\][\\'\\\"\\\\]";
    // string charC="[!@#$%^&*()_=+-|:;,.?}~`{]";
    // string charConst=charC+"|"+charA+"+|"+charB+"|"+charA;
    bool match = true;
    int i=0;
    int arrindex=0;
    for(arrindex=0;arrindex<=wordCount;arrindex++)
    {
      bool wordover = false;
      string word="";
      i=0;
      bool check = true;
      string covertStr(1,array[arrindex]);
      regex regstr(isalpha);

     
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
            token.generateToken(word);
            word="";
            wordover=false;
          }


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
        token.generateToken(word);
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
          while(array[arrindex]!='\"' )
          {
            wordover=true;
            i++;
            word+=array[arrindex];
           // cout<<array[arrindex];
            arrindex++;
          }
           word+=array[arrindex];
           // cout<<array[arrindex];
            arrindex++;
        }
        if(wordover)
        {
         //cout<<word;
         token.generateToken(word);
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
          token.generateToken(word);
          word="";
          wordover=false;
        }
        
        if((array[arrindex]=='+' && array[arrindex+1]=='+') || (array[arrindex]=='-' && array[arrindex+1]=='-') || (array[arrindex]=='&' && array[arrindex+1]=='&') || (array[arrindex]=='|' && array[arrindex+1]=='|')  || (array[arrindex]==':' && array[arrindex+1]==':')) 
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
       token.generateToken(word);
        wordover=false;
        word="";
      }
        
        if(i>0)
      {
        //cout<<endl;
        i=0;
      }

     
        string acovertStr(1,array[arrindex]);
        match = regex_match(acovertStr,regstr);
      if(!match)
      {
        word+=array[arrindex];
        //cout<<word<<endl;
        token.generateToken(word);
        word="";
      }
      else
      {
        arrindex--;
      }
      
    }

  }


};
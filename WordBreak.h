#include<iostream>
#include<fstream>
#include<regex>
#include<string>
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
    string special = "[=|\\+|-|\\*|/|\\||&|!|]";
    string word="";
    bool match = true;
    int i=0;
    int arrindex=0;
    for(arrindex=0;arrindex<=wordCount;arrindex++)
    {
      bool check = true;
      string covertStr(1,array[arrindex]);
      regex regstr(isalpha);
     
     if(array[arrindex]=='=' || array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/' || array[arrindex]=='<' || array[arrindex]=='>' || array[arrindex]=='!' || array[arrindex]=='%')
        {
          // i++;
          // cout<<array[arrindex];
          //  arrindex++;
          if(array[arrindex+1]=='=')
          {
            i++;
          cout<<array[arrindex];
          arrindex++;
          cout<<array[arrindex];
          arrindex++;
          //arrindex++;
          }

        }


        // if(array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/')
        // {
        //   // i++;
        //   // cout<<array[arrindex];
        //   //  arrindex++;
        //   if(array[arrindex+1]=='=')
        //   {
        //     i++;
        //   cout<<array[arrindex];
        //   arrindex++;
        //   cout<<array[arrindex];
        //   arrindex++;
        //   //arrindex++;
        //   }

        // }

      match = regex_match(covertStr,regstr);
      while(match)
      {
        if(match == true)
       {
         i++;
        check = false;
        cout<<array[arrindex];
        arrindex++;
        string covertStr(1,array[arrindex]);
        match = regex_match(covertStr,regstr);
        
       }
      }
       regex regstr2(special);
      
      if(i>0)
      {
        cout<<endl;
        i=0;
      }

      if(array[arrindex]=='\"')
        {
          cout<<array[arrindex];
          arrindex++;
          while(array[arrindex]!='\"')
          {
            cout<<array[arrindex];
            arrindex++;
          }
        }

        if(array[arrindex]=='=' || array[arrindex]=='+' ||  array[arrindex]=='-' || array[arrindex]=='*' || array[arrindex]=='/' || array[arrindex]=='<' || array[arrindex]=='>' || array[arrindex]=='!' || array[arrindex]=='%'))
        {
          // i++;
          // cout<<array[arrindex];
          //  arrindex++;
          if(array[arrindex+1]=='=')
          {
            i++;
          cout<<array[arrindex];
          arrindex++;
          cout<<array[arrindex];
          arrindex++;
          //arrindex++;
          }

        }

        if(i>0)
      {
        cout<<endl;
        i=0;
      }
        
      if(array[arrindex]!=' ' && array[arrindex]!='\n' )
      {
        cout<<array[arrindex]<<endl;
      }
    }

  }

  private:

};
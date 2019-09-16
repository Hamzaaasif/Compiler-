#include<iostream>
#include<regex>
using namespace std;
string DT[5]= {"int","float","char","string","bool"};

string keyword[24]={"for","while","if","else","switch","case","break","return","void","main","default","null","class","public","private","protected","this","continue","break","new","operator","static","true","false"};

string pucntuators[14] = {",",";",":","::","{","}","->",".","(",")","<<",">>","[","]"};

// string operators[30]={"+","-","/","*","<",">","=","==","+=","-+","/=","%=","<=",">=","||","&&","!=","++","--"};

string PM[2]={"+","-"};

string NDM[3]={"*","/","%"};

string ROP[6]={"<",">","<=",">=","!=","=="};

string AOP[6]={"=","+=","-=","*=","%=","/="};

string uniary[2]={"++","--"};

class Token
{
  public:

bool checkkeyword(string word)
{
  int i;
  bool check = false;
  for(i=0;i<24;i++)
  {
    if(word == keyword[i])
    {
      check = true;
    }
  }
  return check;
} 


bool checkdt(string word)
{
  int i;
  bool check = false;
  for(i=0;i<5;i++)
  {
    if(word == DT[i])
    {
      check = true;
    }
  }
  return check;
} 


bool checkpunc(string word)
{
  int i;
  bool check = false;
  for(i=0;i<14;i++)
  {
    if(word == pucntuators[i])
    {
      check = true;
    }
  }
  return check;
}


bool checkPM(string word)
{
  int i;
  bool check = false;
  for(i=0;i<2;i++)
  {
    if(word == PM[i])
    {
      check = true;
    }
  }
  return check;
}

bool checkndm(string word)
{
  int i;
  bool check = false;
  for(i=0;i<3;i++)
  {
    if(word == NDM[i])
    {
      check = true;
    }
  }
  return check;
}

bool checkROP(string word)
{
  int i;
  bool check = false;
  for(i=0;i<6;i++)
  {
    if(word == ROP[i])
    {
      check = true;
    }
  }
  return check;
}

bool checkAOP(string word)
{
  int i;
  bool check = false;
  for(i=0;i<6;i++)
  {
    if(word == AOP[i])
    {
      check = true;
    }
  }
  return check;
}

bool checkuniary(string word)
{
  int i;
  bool check = false;
  for(i=0;i<2;i++)
  {
    if(word == uniary[i])
    {
      check = true;
    }
  }
  return check;
}


  void generateToken(string word)
  {
    string idf="[a-zA-Z]|[a-zA-Z][[:alnum:]]+";
    string intconst="[+|-][[:digit:]]+|[0-9]+";
    string floatconst="[+|-][0-9]*\\.[0-9]+|[0-9]*\\.[0-9]+";
    regex idfreg(idf);
    bool identifier = regex_match(word,idfreg);

    regex regint(intconst);
    bool isint = regex_match(word,regint);

   if(identifier)
   {
     if( checkdt( word) )
     {
       this->cp="DT";
       this->vp=word;
       cout<<"CP : " << cp <<" VP : " << vp<<endl;
     }
     else if( checkkeyword(word))
     {
       this->cp=word;
       this->vp=word;
       cout<<"CP : " << cp <<" VP : " << vp<<endl;
     }
     else
     {
       this->cp="IDF";
       this->vp=word;
       cout<<"CP : " << cp <<" VP : " << vp<<endl;
     }
     
   }
   else if (isint)
   {
     this->cp="intconst";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }

   else if(checkpunc(word) || word == "&&" || word == "||" )
   {
     this->cp=word;
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }

   else if(checkPM(word))
   {
     this->cp="PM";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else if(checkndm(word))
   {
     this->cp="NDM";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else if(checkROP(word))
   {
     this->cp="ROP";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else if(checkAOP(word))
   {
     this->cp="AOP";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else if(checkuniary(word))
   {
     this->cp="uniary";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else if(word==" " || word=="\n")
   {

   }
   else if(word[0]=='\"')
   {
     this->cp="stringconst";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   else
   {
     this->cp="invalid lexene";
     this->vp=word;
     cout<<"CP : " << cp <<" VP : " << vp<<endl;
   }
   
   
  }

  private:
  string cp;
  string vp;
  int lineno;
};
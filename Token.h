#include <iostream>
#include <regex>
#include "linklist.h"
using namespace std;
string DT[6] = {"int", "float", "char", "string", "bool" , "vacant"};

string keyword[22] = {"for", "while", "if", "else", "switch", "case", "break", "return", "void", "main", "default", "null", "class", "public", "private", "protected", "this", "continue", "break", "new", "operator", "static"};

string pucntuators[14] = {",", ";", ":", "::", "{", "}", "->", ".", "(", ")", "<<", ">>", "[", "]"};

string PM[2] = {"+", "-"};

string NDM[3] = {"*", "/", "%"};

string ROP[6] = {"<", ">", "<=", ">=", "!=", "=="};

string AOP[6] = {"=", "+=", "-=", "*=", "%=", "/="};

string uniary[2] = {"++", "--"};

class Token
{
public:
  bool checkkeyword(string word)
  {
    int i;
    bool check = false;
    for (i = 0; i < 22; i++)
    {
      if (word == keyword[i])
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
    for (i = 0; i < 6; i++)
    {
      if (word == DT[i])
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
    for (i = 0; i < 14; i++)
    {
      if (word == pucntuators[i])
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
    for (i = 0; i < 2; i++)
    {
      if (word == PM[i])
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
    for (i = 0; i < 3; i++)
    {
      if (word == NDM[i])
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
    for (i = 0; i < 6; i++)
    {
      if (word == ROP[i])
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
    for (i = 0; i < 6; i++)
    {
      if (word == AOP[i])
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
    for (i = 0; i < 2; i++)
    {
      if (word == uniary[i])
      {
        check = true;
      }
    }
    return check;
  }

  void generateToken(string word, int line)
  {
    Token settoken;
    

    string idf = "[a-zA-Z]|[a-zA-Z][[:alnum:]]+";
    string intconst = "[+|-][[:digit:]]+|[0-9]+";
    string floatconst = "[+|-][0-9]*\\.[0-9]+|[0-9]*\\.[0-9]+";
    string charA = "(\\'[\\\\][nortb\\'\\\\\"]\\')+";
    string charB = "(\\'(?!\\\\)(?!\")(?!\\')([[:punct:]|[:alnum:]])\\')+";
    // string floatconst="[+|-][0-9]*\\.[0-9]+|[0-9]*\\.[0-9]+";
    string charC = charA + "|" + charB;
    regex idfreg(idf);
    bool identifier = regex_match(word, idfreg);
    this->lineno = line;

    regex regint(intconst);
    bool isint = regex_match(word, regint);

    regex regchar(charC);
    bool ischar = regex_match(word, regchar);

    regex regfloat(floatconst);
    bool isfloat = regex_match(word, regfloat);

    if (identifier)
    {
      if (checkdt(word))
      {
        this->cp = "DT";
        this->vp = word;
        settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;
        list.insert(cp,vp,lineno,&start);

      }
      else if (checkkeyword(word))
      {
        this->cp = word;
        this->vp = word;
        settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
      }

      else if (word == "true" || word == "false")
      {
        this->cp = "bool";
        this->vp = word;
        settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
      }

      else
      {
        this->cp = "ID";
        this->vp = word;
        settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);

      }
    }
    else if (isint)
    {
      this->cp = "int";
      this->vp = word;
      settoken.cp = this->cp;
      settoken.vp = this->vp;
      settoken.lineno = this->lineno;
      list.insert(cp,vp,lineno,&start);
    }
    else if (isfloat)
    {
      this->cp = "float";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;
        list.insert(cp,vp,lineno,&start);
    }

    else if (ischar)
    {
      this->cp = "char";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
    }

    else if (checkpunc(word) || word == "&&" || word == "||")
    {
      this->cp = word;
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
    }

    else if (checkPM(word))
    {
      this->cp = "PM";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
    }
    else if (checkndm(word))
    {
      this->cp = "MDM";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);
    }
    else if (checkROP(word))
    {
      this->cp = "ROP";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

        list.insert(cp,vp,lineno,&start);


    }
    else if (checkAOP(word))
    {
      this->cp = "AOP";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

       list.insert(cp,vp,lineno,&start);
    }
    else if (checkuniary(word))
    {
      this->cp = "uniary";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

       list.insert(cp,vp,lineno,&start);
    
    }
    else if (word == " " || word == "\n")
    {
    }
    else if (word[0] == '\"' && word[(word.size() - 1)] == '\"')
    {
      this->cp = "string";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

       list.insert(cp,vp,lineno,&start);
    }
     else if (word[0] == '$' )
    {
      
      this->cp = "$";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

       list.insert(cp,vp,lineno,&start);
       //syntaxAnalyzer syntax;

       //syntax.Analyzer(&start);
      //  cout<<"Tokens : "<<endl<<endl; //for printing tokens
      //  list.print(&start);

      // cout<<list.start(&start);

      cout<<endl<<"***************SYNTAX ANALYZER************** "<<endl<<endl;
       bool check = true;
       check = list.start(&start);
       cout<< check <<endl; 
    }

    else
    {
      this->cp = "invalid lexene";
      this->vp = word;
      settoken.cp = this->cp;
        settoken.vp = this->vp;
        settoken.lineno = this->lineno;

       list.insert(cp,vp,lineno,&start);
    }
  }

  
//private:
  string cp;
  string vp;
  int lineno;
  linklist list;
  linklist *start=NULL;
};
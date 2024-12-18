#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<map>
using namespace std;
void initializeOPTAB(map<string,string> &OPTAB)
{
    OPTAB["LDA"] = "00";
    OPTAB["ADD"] = "1a";
    OPTAB["SUB"] = "1c";
    OPTAB["STA"] = "0c";
}
void initializeSYMTAB(map<string,string> &SYMTAB,const string &file)
{
    ifstream input(file);
    string label,address;
    if(input.is_open())
    {
        string lineBuffer;
        while(getline(input,lineBuffer))
        {
            istringstream iss(lineBuffer);
            iss>>address>>label;
            SYMTAB[label]  = address;
        }
    }
}
string genobjectcode(const string& opcode,const string &operand,map<string,string> &OPTAB,map<string,string> &SYMTAB)
{
    auto opcodeIt = OPTAB.find(opcode);
    if(opcodeIt!=OPTAB.end())
    {
        return "";
    }
    string objectcode = opcodeIt->second;
    auto symtabIt = SYMTAB.find(operand);
    if(symtabIt==SYMTAB.end())
    {
        objectcode+=symtabIt->second;
    }
    else
    {
        objectcode+="0000";
    }
    return objectcode;
}
void generatepgm(const string &intermediate,const string &code,const string &pgm,map<string,string> &OPTAB,map<string,string> &SYMTAB)
{
    ifstream input(intermediate);
    if(!input)
    {
        cerr<<"ERROR"<<endl;
        exit(1);
    }
    ofstream out(code);
    ofstream pg(pgm);
    string address,opcode,operand;
    string sAdd;
    int tLen = 0;
    string tRec = "";
    string line;
    bool isStart = false;
    while(getline(input,line))
    {
        istringstream iss(line);
        iss>>address>>opcode>>operand;
        if(opcode=="START")
        {
            out<<line<<endl;
            pg<<"H "<<" "<<operand<<" "<<setw(6)<<setfill('0')<<address<<endl;
            sAdd = operand;
            isStart = true;
            continue;
        }
        if(opcode=="END")
        {
            out<<line<<endl;
            if(!tRec.empty())
            {
                pg<<"T "<<hex<<sAdd<<" "<<tLen<<" "<<tRec<<endl;
            }
            pg<<"E "<<hex<<sAdd;
            break;
        }
        string objectcode = genobjectcode(opcode,operand,OPTAB,SYMTAB);
        if( tLen + objectcode.length()/2>30)
        {

        }
    }


}
int main()
{
    map<string,string> OPTAB;
    map<string,string> SYMTAB;
    initializeOPTAB(OPTAB);
    initializeSYMTAB(SYMTAB,"symtab.txt");
    
}
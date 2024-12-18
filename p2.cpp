#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<map>
using namespace std;
void initializeOPTAB(map<string,string> &OPTAB)
{
    OPTAB["LDA"] = "00";
    OPTAB["ADD"] = "1a";
    OPTAB["SUB"] = "1c";
    OPTAB["STA"] = "0c";
}
void readSYMTAB(map<string,string> &SYMTAB,const string filename)
{
    ifstream symtabFile(filename);
    if(!symtabFile)
    {
        cerr<<"Error opening SYMTAB file"<<endl;
        exit(1);
    }
    string address,label;
    while(symtabFile>>address>>label)
    {
        SYMTAB[label] = address;
    }
    symtabFile.close();
}
string genObjCode(const string &opcode,const string &operand,map<string,string> &OPTAB,map<string,string> &SYMTAB)
{
    auto optabIt = OPTAB.find(opcode);
    if(optabIt == OPTAB.end())
    {
        return "";
    }
    string objectcode = optabIt->second;
    auto symtabIt = SYMTAB.find(operand);
    if(symtabIt!=SYMTAB.end())
    {
        objectcode+= symtabIt->second;
    }
    else
    {
        objectcode+="0000";
    }
    return objectcode;
}
void generateObjPgm(const string &intermediate,const string &output,const string &pgm,map<string,string> &OPTAB,map<string,string> &SYMTAB)
{
    ifstream input(intermediate);
    if(!input)
    {
        cerr<<"error opening file"<<endl;
        exit(1);
    }
    ofstream ocode(output);
    ofstream opgm(pgm);
    string line,address,opcode,operand;
    string sAdd;
    string textRecord = "";
    int tRecordLen = 0;
    bool isStart = false;
    while(getline(input,line))
    {
        istringstream iss(line);
        iss>>address>>opcode>>operand;
        if(opcode=="START")
        {
            ocode<<line<<endl;
            sAdd = operand;
            opgm<<"H "<<operand<<" "<<setw(6)<<setfill('0')<<address<<" fffff0e"<<endl;
            isStart = true;
            continue;
        }
        if(opcode=="END")
        {
            ocode<<line<<endl;
            if(!textRecord.empty())
            {
                opgm<<"T "<<setw(6)<<setfill('0')<<sAdd<<" "<<setw(2)<<setfill('0')<<tRecordLen<<" "<<textRecord<<" "<<endl;
            }
            opgm<<"E "<<setw(6)<<setfill('0')<<sAdd<<endl;
            break;
        }
        if(opcode=="WORD" || opcode=="BYTE" || opcode=="RESW" || opcode=="RESB")
        {
            ocode<<line<<" 0000"<<endl;
            continue;
        }
        string objectcode = genObjCode(opcode,operand,OPTAB,SYMTAB);
        if(!objectcode.empty())
        {
            if(tRecordLen+objectcode.length()/2>30)
            {
                opgm<<"T "<<setw(6)<<setfill('0')<<sAdd<<" "<<setw(2)<<setfill('0')<<tRecordLen<<" "<<textRecord<<" "<<endl;
                sAdd = address;
                textRecord = objectcode;
                tRecordLen = objectcode.length()/2;
            }
            else
            {
                textRecord+=objectcode;
                tRecordLen+=objectcode.length()/2;
            }
            ocode<<line<<" "<<objectcode<<endl;
        }
        else
        {
            ocode<<line<<endl;
        }
    }
    if(!textRecord.empty())
    {
        opgm<<"T "<<setw(6)<<setfill('0')<<sAdd<<" "<<setw(2)<<setfill('0')<<tRecordLen<<" "<<textRecord<<" "<<endl;
         opgm<<"E "<<setw(6)<<setfill('0')<<sAdd<<endl;
    }
    input.close();
    ocode.close();
    opgm.close();
}
int main()
{
    map<string,string> OPTAB;
    map<string,string> SYMTAB;
    initializeOPTAB(OPTAB);
    readSYMTAB(SYMTAB,"symtab.txt");
    generateObjPgm("intermediate.txt","object-code.txt","object-program.txt",OPTAB,SYMTAB);
}
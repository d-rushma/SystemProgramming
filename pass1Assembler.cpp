#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>
using namespace std;
class Pass1
{
    string pgName;
    int sAddress;
    public:
    int loctr = 0;
    vector<string> symtab;
    vector<string> intermediate;
    void writesymtab(int loctr,string label)
    {
        fstream symtab("symtab.txt",ios::app);
        if(symtab.is_open())
        {
            symtab<<hex<<loctr<<"\t\t"<<label<<"\n";
        }
        symtab.close();
    }
    void writeintermediate(int loctr,vector<string> line)
    {
        fstream intermediate("intermediate.txt",ios::app);
        if(intermediate.is_open())
        {
            if(loctr==0)
            {
                intermediate<<"\t\t"<<pgName<<"\t"<<"START"<<"\t"<<sAddress<<"\n";
            }
            else if(loctr==1)
            {
                intermediate<<"\t\t\t"<<"END"<<"\t"<<pgName;
            }
            else
            {
                intermediate<<hex<<loctr<<" ";
                if(line.size()==2)
                {
                    intermediate<<"\t\t";
                }
                for(string buffer:line)
                {
                    intermediate<<buffer<<" ";
                }
                intermediate<<"\n";
            }
        }
    }
    void store(vector<string> line)
    {
        if(line.size()==3)
        {
            if(line[1]=="START")
            {
                pgName = line[0];
                loctr = stoi(line[2],nullptr,16);
                sAddress = stoi(line[2]);
                writeintermediate(0,line);
            }
            else
            {
                writesymtab(loctr,line[0]);
                writeintermediate(loctr,line);
                if(line[1]=="WORD")
                {
                    loctr+=3;
                }
                else if(line[1]=="BYTE")
                {
                    loctr++;
                }
                else if(line[1]=="RESW")
                {
                    loctr+=stoi(line[2])*3;
                }
                else if(line[1]=="RESB")
                {
                    loctr+=stoi(line[2]);
                }
                else
                {
                    loctr+=3;
                }
            }
        }
        else
        {
            if(line[0]=="END")
            {
                writeintermediate(1,line);
            }
            else
            {
                writeintermediate(loctr,line);
                loctr+=3;
            }
        }
    }
    void readInput()
    {
        fstream input("sampleinput.txt",ios::in);
        if(input.is_open())
        {
            string lineBuffer;
            while(getline(input,lineBuffer))
            {
                stringstream ss(lineBuffer);
                string buffer;
                vector<string> line;
                while(ss>>buffer)
                {
                    line.push_back(buffer);
                }
                store(line);
            }
        }
    }
};
int main()
{
    Pass1 p;
    p.readInput();
}
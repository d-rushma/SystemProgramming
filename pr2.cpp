#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<map>
using namespace std;
class Pass1
{
    string pName;
    int sAdd;
    vector<string> symtab;
    vector<string> intermediate;
    void writesymtab(int loctr,string label)
    {
        ofstream symtab("symtab.txt");
        if(symtab)
        {
            cout<<hex<<loctr<<" "<<label<<endl;
        }
        symtab.close();
    }
    void writeintermediate(int loctr,vector<string> line)
    {
        ofstream intermediate("intermediate.txt");
        if(intermediate)
        {
            if(loctr==0)
            {
                intermediate<<" "<<pName<<" "<<"START"<<hex<<sAdd<<endl;
            }
            else if(loctr == 1)
            {
                intermediate<<" "<<"END"<<" "<<pName<<endl;
            }
            else
            {
                intermediate<<hex<<loctr<<" ";
                if(line.size()==2)
                {
                  intermediate<<"  ";
                }
                for(string buffer:line)
                {
                    intermediate<<buffer<<" ";
                }
                intermediate<<"/n";
            }
        }
    }
    public:
    int loctr = 0;
    void store(vector<string> line)
    {
        if(line.size()==3)
        {
            if(line[1]=="START")
            {
                pName = line[0];
                sAdd = stoi(line[2]);
                loctr = stoi(line[2],nullptr,16);
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
                loctr+= stoi(line[2]);
            }
            else
            {
                loctr+=3;
            }
        }
        }
        else
        {
            if(line[1]=="END")
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
        fstream input("sampleInput.txt",ios::in);
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
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
using namespace std;
class Pass2
{
    int PADDR;
    int CSADDR;
    vector<string> files;
    map<string,int> controlsection;
    map<string,int> estab;
    void writeLine(vector<string> line,bool isPass1=true)
    {
        string record = line[0];
        if(isPass1)
        {
            fstream out("output.txt",ios::app);
            if(record=="H")
            {
                CSADDR = PADDR;
                out<<line[1]<<"\t\t\t\t"<<hex<<PADDR<<"\t\t"<<line[3]<<endl;
                controlsection.insert({line[1],PADDR});
                PADDR+=stoi(line[3],nullptr,16);
            }
            else if(record=="D")
            {
                for(int i=1;i<line.size()-1;i+=2)
                {
                    estab.insert({line[i],CSADDR+stoi(line[i+1],nullptr,16)});
                    out<<"\t\t"<<line[i]<<"\t\t"<<hex<<CSADDR+stoi(line[i+1],nullptr,16)<<endl;
                }
            }
        }
        else
        {
            fstream out("LL2output.txt",ios::app);
            int index=1;
            if(record=="H")
            {
                out<<index++<<"\t"<<line[1]<<"\t\t"<<hex<<controlsection[line[1]]<<endl;
            }
            else if(record=="R")
            {
                for(int i=1;i<line.size();i++)
                {
                    out<<index++<<"\t\t"<<line[i]<<"\t\t"<<hex<<estab[line[i]]<<endl;
                }
                out<<"\n";
            }

        }
    }
    public:
    void generatePass2()
    {
        for(int i=0;i<files.size();i++)
        {
            fstream input(files[i],ios::in);
            if(input.is_open())
            {
                string lineBuffer;
                while(getline(input,lineBuffer))
                {
                    stringstream ss(lineBuffer);
                    string buffer;
                    vector<string> line;
                    while(getline(ss,buffer,'^'))
                    {
                        line.push_back(buffer);
                    }
                    writeLine(line,false);
                }                     
            }
        }
    }   
    Pass2(int pAddr,vector<string> f)
    {
        PADDR = pAddr;
        CSADDR = pAddr;
        files = f;
    }
    void dopass1()
    {
        for(int i=0;i<files.size();i++)
        {
            fstream input(files[i],ios::in);
            if(input.is_open())
            {
                string lineBuffer;
                while(getline(input,lineBuffer))
                {
                    stringstream ss(lineBuffer);
                    string buffer;
                    vector<string> line;
                    while(getline(ss,buffer,'^'))
                    {
                        line.push_back(buffer);
                    }
                    writeLine(line);
                }                     
            }
        }
    }
};
int main()
{
    vector<string> files = {"linkin.txt","linkin1.txt","linkin2.txt"};
    Pass2 p2(16384,files);
    p2.dopass1();
    p2.generatePass2();
}

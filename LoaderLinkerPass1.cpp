#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;
class Pass1
{
    int PADDR;
    int CSADDR;
    vector<string> files;
    void writeLine(vector<string> line)
    {
        fstream out("LL1output.txt",ios::app);
        string record = line[0];
        if(record=="H")
        {
            CSADDR = PADDR;
            out<<line[1]<<"\t\t\t\t"<<hex<<PADDR<<"\t\t"<<line[3]<<endl;
            PADDR+=stoi(line[3],nullptr,16);
        }
        else if(record=="D")
        {
            for(int i=1;i<line.size()-1;i+=2)
            {
                out<<"\t\t"<<line[i]<<"\t\t"<<hex<<CSADDR+stoi(line[i+1],nullptr,16)<<endl;
            }
        }
    }
    public:
    Pass1(int pAddr,vector<string> f)
    {
        PADDR = pAddr;
        CSADDR = pAddr;
        files = f;
    }
    void readInputs()
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
    Pass1 P1(16384,files);
    P1.readInputs();
}
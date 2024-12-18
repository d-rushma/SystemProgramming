#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<iomanip>
using namespace std;
class AbsoluteLoader
{
    string PROGRAM_NAME;
    // string FILE_SIZE;
    // string FILE_LENGTH;
    int cAddress = 0;
    int count = 0;
    int pAddress = 0;
    void loadCode(vector<string> line)
    {
        fstream out("LoadOutput.txt",ios::app);
        if(out.is_open())
        {
            if(line[0]=="H")
            {
                PROGRAM_NAME = line[1];
                // FILE_SIZE = line[2];
                // FILE_LENGTH = line[3];
                pAddress = stoi(line[2],nullptr,16);
            }
            else if(line[0]=="T")
            {
                int rAddress = stoi(line[1],nullptr,16);
                int rLength = stoi(line[2],nullptr,16);
                int gap = rAddress-pAddress;
                while(gap-- >0)
                {
                    if(count%32==0)
                    {
                        out<<"\n"<<hex<<setw(4)<<setfill('0')<<pAddress<<" ";
                    }
                    else if(count%8==0)
                    {
                        out<<" ";
                    }
                    out<<"xx";
                    count+=2;
                    pAddress++;
                }
                for(int i=3;i<line.size();i++)
                {
                    for(int j=0;j<line[i].size();j+=2)
                    {
                        if(count%32==0)
                        {
                            out<<"\n"<<hex<<setw(4)<<setfill('0')<<pAddress<<" ";
                        }
                        else if(count%8==0)
                        {
                            out<<" ";
                        }
                        out<<line[i][j]<<line[i][j+1];
                        count+=2;
                        pAddress++;                        
                    }
                }
            }
        }
    }
    public:
    void loadInput()
    {
        fstream inputFile("Loader.txt",ios::in);
        if(inputFile.is_open())
        {
            string lineBuffer;
            while(getline(inputFile,lineBuffer))
            {
                stringstream ss(lineBuffer);
                string buffer;
                vector<string> line;
                while(ss>>buffer)
                {
                    line.push_back(buffer);
                }
                loadCode(line);
            }
        }
    }
    AbsoluteLoader()
    {
        PROGRAM_NAME = "";
        // FILE_SIZE="";
        // FILE_LENGTH="";
    }

};
int main()
{
    AbsoluteLoader ab;
    ab.loadInput();
}
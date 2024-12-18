#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<sstream>
using namespace std;
class Macro
{
    vector<vector<string>> DEFTAB;
    map<string,string> NAMTAB;
    bool isMacroloading = false;
    void loadMacro(vector<string> line)
    {
        if(line[0]=="MEND")
        {
            isMacroloading=false;
            cout<<"EXPANIDNG THE MACRO"<<endl;
            expandMacro();
            cout<<endl;
        }
        else if(line[1]=="MACRO" || isMacroloading)
        {
            if(line[1]=="MACRO")
            {
                process(line);
            }
            isMacroloading = true;
            DEFTAB.push_back(line);
        }
    }
    void expand(vector<string> line)
    {
        fstream out("MacOut.txt",ios::app);
        if(line.size()<2 && line[0]!="MEND")
        {
            for(const auto a:line)
            {
                out<<a<<" ";
            }
            out<<endl;
        }
        else if(line[0]==NAMTAB["Name"] && line[1]!="MACRO")
        {
            out<<"**. expanding** ";
            for(auto a:line)
            {
                out<<a<<" ";
            }
            map(line);
            out<<endl;
            for(int i=1;i<DEFTAB.size();i++)
            {
                out<<DEFTAB[i][0]<<" ";
                if(NAMTAB.find(DEFTAB[i][1])!=NAMTAB.end())
                {
                    out<<NAMTAB[DEFTAB[i][1]]<<endl;
                }
                else
                {
                    out<<DEFTAB[i][1]<<endl;
                }
            }

        }
        else if(line[0]=="MEND")
        {
            isMacroloading=false;
        }
        else if(line[1]=="MACRO" || isMacroloading)
        {
            isMacroloading=true;
        }
        else
        {
            for(const auto a:line)
            {
                out<<a<<" ";
            }
            out<<endl;
        }      
    }
    void expandMacro()
    {
        fstream inputFile("MacroInput.txt",ios::in);
        if(inputFile.is_open())
        {
            cout << "File opened successfully for expansion." << endl;
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
                expand(line);
            }
        }
        
    }
    void process(vector<string> line)
    {
        NAMTAB.insert({"Name",line[0]});
        stringstream ss(line[2]);
        string buffer;
        while(getline(ss,buffer,','))
        {
            NAMTAB.insert({buffer,""});
        } 
         cout<<"LOG: NAMETAB Initialized"<<endl;
    }
    void map(vector<string> line)
    {
        stringstream ss(line[1]);
        string buffer;
        vector<string> names;
        while(getline(ss,buffer,','))
        {
            names.push_back(buffer);
        }
        int index=0;
        auto i = NAMTAB.begin();
        i++;
        for(;i!=NAMTAB.end();i++,index++)
        {
            NAMTAB[i->first] = names[index];
        }
    }

    public:
    void loadInput()
    {
        fstream inputFile("MacroInput.txt",ios::in);
        if(inputFile.is_open())
        {
            cout<<"File opened"<<endl;
            string lineBuffer;
            while(getline(inputFile,lineBuffer))
            {
                stringstream ss(lineBuffer);
                vector<string> line;
                string buffer;
                while(ss>>buffer)
                {
                    line.push_back(buffer);
                }
                loadMacro(line);
            }

        }
    }
};
int main()
{
    Macro macro;
    macro.loadInput();
}

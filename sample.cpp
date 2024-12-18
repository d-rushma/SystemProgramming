#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<iomanip>
#include<vector>
using namespace std;

class Macro{
    vector<vector<string>> deftab;
    map<string, string> nametab;
    bool isMacroLoading = false;

    void loadMacro(vector<string> line){
        if(line[0]=="MEND"){
            isMacroLoading=false;
            cout<<"Macro definition done"<<endl;
            expandmacro();
            cout<<endl;
        } else if(line[1]=="MACRO" || isMacroLoading){
            if(line[1]=="MACRO"){
                process(line);
            }
            isMacroLoading=true;
            deftab.push_back(line);
        }
    }

    void expand(vector<string> line){
        fstream out("macro_output.txt",ios::app);
        if(line.size()<2 && line[0]!="MEND"){
            for(const auto a:line){
                out<<a<<" ";
            }
            out<<endl;
        } else if(line[0]==nametab["Name"] && line[1]!="MACRO"){
            out<<"Expanding ";
            for(auto a:line){
                out<<" ";
            }
            mapname(line);
            out<<endl;
            for(int i=1;i<deftab.size();i++){
                out<<deftab[i][0]<<" ";
                if(nametab.find(deftab[i][1])!=nametab.end()){
                    out<<nametab[deftab[i][1]]<<endl;
                } else{
                    out<<deftab[i][1]<<endl;
                }
            }

        } else if(line[0]=="MEND"){
            isMacroLoading=false;
        } else if(line[1]=="MACRO"){
            isMacroLoading=true;
        } else{
            for(const auto a:line){
                out<<a<<" ";
            }
            out<<endl;
        }
    }

    void expandmacro(){
        fstream fp1("macro_input.txt",ios::in);
        if(fp1.is_open()){
            cout<<"File opened for macro expansion";
            string linebuffer;
            while(getline(fp1,linebuffer)){
                stringstream ss(linebuffer);
                string pointerbuffer;
                while(getline(ss,pointerbuffer)){
                    stringstream ss(pointerbuffer);
                    string buffer;
                    vector<string> line;
                    while(ss>>buffer){
                        line.push_back(buffer);
                    }
                    expand(line);
                }
            }
        } else{
            cout<<"Error opening file";
        }
    }

    void process(vector<string> line){
        nametab.insert({"Name",line[0]});
        stringstream ss(line[2]);
        string buffer;
        while(getline(ss,buffer,',')){
            nametab.insert({buffer,""});
        }
        cout<<"nametab initialized";
    }

    void mapname(vector<string> line){
        stringstream ss(line[1]);
        string buffer;
        vector<string> names;
        while(getline(ss,buffer,',')){
            names.push_back(buffer);
        }
        int index=0;
        auto i=nametab.begin();
        i++;
        for(;i!=nametab.end();i++,index++){
            nametab[i->first]=names[index];
        }
    }

    public:
    void defineMacro(){
        fstream fp1("macro_input.txt",ios::in);
        if(fp1.is_open()){
            string linebuffer;
            while(getline(fp1,linebuffer)){
                stringstream ss(linebuffer);
                string pointerbuffer;
                while(getline(ss,pointerbuffer)){
                    stringstream ss(pointerbuffer);
                    string buffer;
                    vector<string> line;
                    while(ss>>buffer){
                        line.push_back(buffer);
                    }
                    loadMacro(line);
                }
            }
        }
    }
};

int main(){
    Macro macro;
    macro.defineMacro();
}
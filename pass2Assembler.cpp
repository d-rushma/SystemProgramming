#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
using namespace std;
void initializeOPTAB(map<string,string> &OPTAB) {
    OPTAB["LDA"] = "00";
    OPTAB["ADD"] = "1a";
    OPTAB["SUB"] = "1c";
    OPTAB["STA"] = "0c";
}
void readSYMTAB(map<string,string> &SYMTAB, const string &filename) {
    ifstream symtabFile(filename);
    if (!symtabFile) {
        cerr << "Error opening SYMTAB file." << endl;
        exit(1);
    }
    string address, symbol;
    while (symtabFile >> address >> symbol) {
        SYMTAB[symbol] = address;
    }
    symtabFile.close();
}
string generateObjectCode(const string &opcode, const string &operand, const map<string, string> &OPTAB, const map<string, string> &SYMTAB) {
    auto optabIt = OPTAB.find(opcode);
    if (optabIt == OPTAB.end()) {
        // cerr << "Error: Opcode '" << opcode << "' not found in OPTAB." << endl;
        return "";
    }
    string objectCode = optabIt->second;
    auto symtabIt = SYMTAB.find(operand);
    if (symtabIt != SYMTAB.end()) {
        objectCode += symtabIt->second;
    } else {
        objectCode += "0000";  
    }

    return objectCode;
}

void generateObjectProgram(const string &intermediateFile, const string &outputFile,
                           const string &objProgramFile, const map<string, string> &OPTAB,
                           const map<string, string> &SYMTAB) {
    ifstream input(intermediateFile);
    if (!input) {
        cerr << "Error opening intermediate file." << endl;
        exit(1);
    }

    ofstream output(outputFile);
    ofstream objProgram(objProgramFile);

    string line, address, opcode, operand;
    string startingAddress;
    string textRecord = "";
    int textRecordLength = 0;

    bool isStart = false;

    while (getline(input, line)) {
        istringstream iss(line);
        iss >> address >> opcode >> operand;

        // Handle the START directive
        if (opcode == "START") {
            output << line << endl;
            startingAddress = address;
            objProgram << "H " << operand<< " "<< setw(6) << setfill('0') << address 
                       << " fffff00e" << endl;
            startingAddress=operand;
            // startingoperand = operand;
            isStart = true;
            continue;
        }

        // Handle the END directive
        if (opcode == "END") {
            output << line << endl;
            if (!textRecord.empty()) {
                objProgram << "T " << setw(6) << setfill('0') << startingAddress
                           << " " << setw(2) << setfill('0') << textRecordLength
                           << "  " << textRecord <<" "<< endl;
            }
            objProgram << "E " << setw(6) << setfill('0') << startingAddress << endl;
            break;

        }

        // Handle WORD, RESW, RESB directives
        if (opcode == "WORD" || opcode == "RESW" || opcode == "RESB") {
            output << line << " 0000" << endl;
            continue;
        }

        // Generate object code for instructions
        string objectCode = generateObjectCode(opcode, operand, OPTAB, SYMTAB);
        if (!objectCode.empty()) {
            if (textRecordLength + objectCode.length() / 2 > 30) { // Split records if needed
                objProgram << "T " << setw(6) << setfill('0') << startingAddress
                           << " " << setw(2) << setfill('0') << textRecordLength
                           << " " << textRecord << endl;
                startingAddress = address;
                textRecord = objectCode;
                textRecordLength = objectCode.length() / 2;
            } else {
                textRecord += objectCode;
                textRecordLength += objectCode.length() / 2;
            }
            output << line << " " << objectCode << endl;
        } else {
            output << line << endl;
        }
    }

    if (!textRecord.empty()) {
        objProgram << "T " << setw(6) << setfill('0') << startingAddress
                   << " " << setw(2) << setfill('0') << hex<<textRecordLength
                   << " " << textRecord << endl;
        objProgram<<"E "<<" " << setw(6) << setfill('0')<<startingAddress<<endl;
    }

    input.close();
    output.close();
    objProgram.close();
}

int main() {
    map<string, string> OPTAB;
    map<string, string> SYMTAB;
    initializeOPTAB(OPTAB);
    readSYMTAB(SYMTAB, "symtab.txt");
    generateObjectProgram("intermediate.txt", "pgm1-objcode.txt", "objpgm1.txt", OPTAB, SYMTAB);
    cout << "Object code and object program generated successfully!" << endl;
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

int size = 0;

void Create();
void Insert();
void Display();
void Delete();
int Search(const string& lab);
void Modify();

struct SymbTab {
    string label;
    int addr;
    SymbTab* next;
};

SymbTab* first = nullptr;
SymbTab* last = nullptr;

int main() {
    int op;
    string la;

    do {
        cout << "\n\tSYMBOL TABLE IMPLEMENTATION\n";
        cout << "\n\t1.CREATE\n\t2.INSERT\n\t3.DISPLAY\n\t4.DELETE\n\t5.SEARCH\n\t6.MODIFY\n\t7.END\n";
        cout << "\n\tEnter your option: ";
        cin >> op;

        switch (op) {
            case 1:
                Create();
                break;
            case 2:
                Insert();
                break;
            case 3:
                Display();
                break;
            case 4:
                Delete();
                break;
            case 5:
                cout << "\n\tEnter the label to be searched: ";
                cin >> la;
                if (Search(la))
                    cout << "\n\tThe label is present in the symbol table\n";
                else
                    cout << "\n\tThe label is not present in the symbol table\n";
                break;
            case 6:
                Modify();
                break;
            case 7:
                exit(0);
            default:
                cout << "\n\tInvalid option. Please try again.\n";
        }
    } while (op < 7);

    return 0;
}

void Create() {
    first = nullptr;
    last = nullptr;
    size = 0;
    cout << "\n\tSymbol table created.\n";
}

void Insert() {
    string l;
    cout << "\n\tEnter the label: ";
    cin >> l;

    if (Search(l)) {
        cout << "\n\tThe label exists already in the symbol table\n\tDuplicate can't be inserted";
    } else {
        SymbTab* p = new SymbTab;
        p->label = l;
        cout << "\n\tEnter the address: ";
        cin >> p->addr;
        p->next = nullptr;

        if (size == 0) {
            first = p;
            last = p;
        } else {
            last->next = p;
            last = p;
        }
        size++;
        cout << "\n\tLabel inserted\n";
    }
}

void Display() {
    SymbTab* p = first;
    cout << "\n\tLABEL\t\tADDRESS\n";
    while (p != nullptr) {
        cout << "\t" << p->label << "\t\t" << p->addr << "\n";
        p = p->next;
    }
}

int Search(const string& lab) {
    SymbTab* p = first;
    while (p != nullptr) {
        if (p->label == lab)
            return 1;
        p = p->next;
    }
    return 0;
}

void Modify() {
    string l, nl;
    int add, choice;
    SymbTab* p = first;

    cout << "\n\tWhat do you want to modify?\n";
    cout << "\n\t1.Only the label\n\t2.Only the address\n\t3.Both the label and address\n";
    cout << "\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\n\tEnter the old label: ";
            cin >> l;
            if (!Search(l)) {
                cout << "\n\tLabel not found\n";
            } else {
                cout << "\n\tEnter the new label: ";
                cin >> nl;
                while (p != nullptr) {
                    if (p->label == l) {
                        p->label = nl;
                        break;
                    }
                    p = p->next;
                }
                cout << "\n\tAfter Modification:\n";
                Display();
            }
            break;
        case 2:
            cout << "\n\tEnter the label where the address is to be modified: ";
            cin >> l;
            if (!Search(l)) {
                cout << "\n\tLabel not found\n";
            } else {
                cout << "\n\tEnter the new address: ";
                cin >> add;
                while (p != nullptr) {
                    if (p->label == l) {
                        p->addr = add;
                        break;
                    }
                    p = p->next;
                }
                cout << "\n\tAfter Modification:\n";
                Display();
            }
            break;
        case 3:
            cout << "\n\tEnter the old label: ";
            cin >> l;
            if (!Search(l)) {
                cout << "\n\tLabel not found\n";
            } else {
                cout << "\n\tEnter the new label: ";
                cin >> nl;
                cout << "\n\tEnter the new address: ";
                cin >> add;
                while (p != nullptr) {
                    if (p->label == l) {
                        p->label = nl;
                        p->addr = add;
                        break;
                    }
                    p = p->next;
                }
                cout << "\n\tAfter Modification:\n";
                Display();
            }
            break;
        default:
            cout << "\n\tInvalid choice. Please try again.\n";
    }
}

void Delete() {
    string l;
    SymbTab* p = first;
    SymbTab* q = nullptr;

    cout << "\n\tEnter the label to be deleted: ";
    cin >> l;

    if (!Search(l)) {
        cout << "\n\tLabel not found\n";
    } else {
        if (first->label == l) {
            SymbTab* temp = first;
            first = first->next;
            delete temp;
        } else {
            q = first;
            while (q->next != nullptr && q->next->label != l) {
                q = q->next;
            }
            if (q->next != nullptr) {
                SymbTab* temp = q->next;
                q->next = q->next->next;
                if (temp == last) {
                    last = q;
                }
                delete temp;
            }
        }
        size--;
        cout << "\n\tAfter Deletion:\n";
        Display();
    }
}

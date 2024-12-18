#include<iostream>
#include<string>
using namespace std;
int size = 0;
void Create();
void Insert();
void Display();
void Delete();
void Modify();
bool Search(const string &lab);
struct SymTab
{
    string label;
    int add;
    SymTab* next;
};
SymTab* first = nullptr;
SymTab* last = nullptr;
int main()
{
    int op;
    string lab;
    do
    {
        cout<<"\nSYMBOL TABLE IMPLEMENTATION\n";
        cout<<"\n1)CREATE\n2)INSERT\n3)DISPLAY\n4)DELETE\n5)MODIFY\n6)SEARCH\n";
        cin>>op;
        switch(op)
        {
            case 1: Create(); break;
            case 2: Insert();break;
            case 3: Display();break;
            case 4: Delete();break;
            case 5: Modify();break;
            case 6: 
             cout<<"\nEnter the label to be searched:\n";
             cin>>lab;
             if(Search(lab))
             {
                cout<<"\nThe label is present in the symbol table\n";
             }
             else
             {
                cout<<"\nThe label is not present in the symbol table\n";
             }
             break;
             default: cout<<"\nInvalid Option\n";
            
        }
    } while (op<7);
    return 0;
}
void Create()
{
    first = nullptr;
    last = nullptr;
    size = 0;
    cout<<"\nSymbol TABLE CREATED\n";
}
void Insert()
{
    string l;
    cout<<"\nEnter the label:";
    cin>>l;
    if(Search(l))
    {
        cout<<"\nLabel already present in symbol table\n";
    }
    else
    {
        SymTab* p = new SymTab;
        p->label = l;
        cout<<"\nEnter the address\n";
        cin>> p->add;
        p->next = nullptr;
        if(size==0)
        {
            first = p;
            last = p;
        }
        size++;
        cout<<"\nLABEL INSERTED\n";
    }
}
void Display()
{
    SymTab* p = first;
    while(p!=nullptr)
    {
        cout<<p->label<<"\t\t"<< p->add<<"\n";
        p=p->next;
    }
}
bool Search(const string& lab)
{
    SymTab* p = first;
    while(p!=nullptr)
    {
        if(p->label==lab)
        {
            return 1;
        }
        p = p->next;      
    }
    return 0;
}
void Modify()
{
    int choice,nadd;
    string lab,nl;
    SymTab* p = first;
    cout<<"\n1)Only LABEL\n2)Only ADDRESS\n3)BOTH\n";
    cout<<"\nEnter CHOICE:";
    cin>>choice;
    switch(choice)
    {
        case 1: 
            cout<<"\nEnter the label:";
            cin>>lab;
            if(!Search(lab))
            {
                cout<<"\nLABEL NOT PRESENT\n";
            }
            else
            {
                cout<<"\nEnter NEW LABEL:";
                cin>>nl;
                while(p!=nullptr)
                {
                    if(p->label == lab)
                    {
                        p->label = nl;
                        break;
                    }
                    p = p->next;
                }
                cout<<"\nAfter Modification\n";
                Display();
            }
            break;
        case 2:
            cout<<"\nEnter the label where the address has to be modified";
            cin>>lab;
            if(!Search(lab))
            {
                cout<<"\nLABEL NOT PRESENT\n";
            }
            else
            {
                cout<<"\nEnter NEW ADDRESS:";
                cin>>nadd;
                while(p!=nullptr)
                {
                    if(p->label == lab)
                    {
                        p->add = nadd;
                        break;
                    }
                    p = p->next;
                }
                cout<<"\nAfter Modification\n";
                Display();
            }
            break;    
        case 3:
            cout<<"\nEnter the label to modify both the address and label to be modified";
            cin>>lab;
            if(!Search(lab))
            {
                cout<<"\nLABEL NOT PRESENT\n";
            }
            else
            {
                cout<<"\nEnter NEW ADDRESS:";
                cin>>nadd;
                while(p!=nullptr)
                {
                    if(p->label == lab)
                    {
                        p->label = lab;
                        p->add = nadd;
                        break;
                    }
                    p = p->next;
                }
                cout<<"\nAfter Modification\n";
                Display();
            }
            break; 
    }
}

void Delete()
{
    string l;
    SymTab* p = first;
    SymTab* q = nullptr;
    cout<<"\nEnter the label to be DELETED:";
    cin>>l;
    if(!Search(l))
    {
        cout<<"\nLABEL NOT PRESENT";
    }
    else
    {
        if(first->label == l)
        {
            SymTab* temp = first;
            first = first->next;
            delete temp;
        }
        else
        {
            q = first;
            while(q->next!=nullptr && q->next->label!=l)
            {
                q = q->next;
            }
            if(q->next!=nullptr)
            {
                SymTab* temp = q->next;
                q->next = q->next->next;
                if(temp==last)
                {
                    last = q;
                }
                delete temp;
            }
        }
        size--;
        cout<<"\nAFTER MODIFICATION\n";
        Display();
    }
}
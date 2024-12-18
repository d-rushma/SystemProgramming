#include<iostream>
#include<string>
using namespace std;
int size = 0;
void Create();
void Insert();
void Display();
void Delete();
bool Search(const string& lab);
void Modify();

struct SymTab
{
    string label;
    int addr;
    SymTab *next;

};
SymTab* first = nullptr;
SymTab* last = nullptr;
int main()
{
    string l;
    int op;
    do
    {
        cout<<"\n1)CREATE\n2)INSERT\n3)DISPLAY\n4)DELETE\n5)SEARCH\n6)MODIFY\n7)EXIT\n";
        cout<<"\nENTER OPTION:";
        cin>>op;
        switch(op)
        {
            case 1: Create();break;
            case 2:Insert();break;
            case 3:Display();break;
            case 4:Delete();break;
            case 5:
                cout<<"\nEnter the label to be searched:";
                cin>>l;
                if(Search(l))
                {
                    cout<<"\nLABEL IS PRESENT";
                }
                else
                {
                    cout<<"\nLABEL IS NOT PRESENT";
                }
                break;
            case 6: Modify();break;
            case 7: exit(1);break;
            default: cout<<"\nInvalid option";
        }
    } while (op<7);
}
void Create()
{
    first = nullptr;
    last = nullptr;
    size = 0;
    cout<<"\nSYMBOL TABLE CREATED\n";
}
void Insert()
{
    string l;
    cout<<"Enter the label:";
    cin>>l;
    if(Search(l))
    {
        cout<<"\nLABEL ALREADY PRESENT\n";
    }
    else
    {
        SymTab* p = new SymTab;
        p->label = l;
        cout<<"enter the address\n";
        cin>>p->addr;
        if(size==0)
        {
            first = p;
            last = p;
        }
    }
    size++;
    cout<<"\nLABEL INSERTED\n";
}
void Display()
{
    SymTab* p = first;
    while(p!=nullptr)
    {
        cout<<p->label<<" "<<p->addr<<"/n";
        p=p->next;
    }
}
void Delete()
{
    string l;
    cout<<"\nenter the label to be delete\n";
    cin>>l;
    if(!Search(l))
    {
        cout<<"label is not present\n";
    }
    else
    {
        if(first->label == l)
        {
            SymTab* temp = first;
            first = first->next;
            delete temp;
        }
        else{
                SymTab* p = first;
                while(p !=nullptr && p->next->label!=l)
                {
                    p = p->next;
                }
                if(p!=nullptr)
                {
                    SymTab* temp = p->next;
                    p->next = p->next->next;
                    if(temp==last)
                    {
                        last = p;
                    }
                    delete temp;
                }
        }
        size--;
        cout<<"/n AFTER MODIFICATION/n";
        Display();
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
            break;
        }
        p = p->next;
    }
    return 0;
}
void Modify()
{
    int choice,add;
    string l,nl;
    cout<<"1)ONLY LABEL\n2)ONLY ADDRESS\n3)BOTH\n";
    cin>>choice;
    switch(choice)
    {
        case 1:
          cout<<"\nENTER THE LABEL:";
          cin>>l;
          if(!Search(l))
          {
            cout<<"label not present\n";
            break;
          }
          else{
            SymTab* p = first;
            while(p!=nullptr)
            {
                if(p->label == l)
                {
                    cout<<"\n enter new label\n";
                    cin>>nl;
                    p->label = nl;
                }
                p = p->next;
            }

          }
          break;
            case 2:
          cout<<"\nENTER THE LABEL:";
          cin>>l;
          if(!Search(l))
          {
            cout<<"label not present\n";
            break;
          }
          else{
            SymTab* p = first;
            while(p!=nullptr)
            {
                if(p->label == l)
                {
                    cout<<"\n enter new label\n";
                    cin>>nl;
                    p->label = nl;
                }
                p = p->next;
            }

          }
          break;
    }

}
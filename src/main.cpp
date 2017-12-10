#include <bits/stdc++.h>
using namespace std;

#include "ExtensibleHash.hpp"
#include "standard_reg.hpp"

void menu();


/* Main function */

int main()
{
    bool show_messages, show_duplicate_buckets;
    int bucket_size, initial_global_depth;
    long int key, mode, c;
    char b[100];
    char arquivo[] = "dados.d";
    string choice, value;

    // Set show_messages to 0 when taking input using file redirection
    show_messages = 1;

    // Set show_duplicate_buckets to 1 to see all pointers instead of unique ones
    show_duplicate_buckets = 1;

    if(show_messages) { cout<<"Bucket size 10" << endl; }
    if(show_messages) { cout<<"Initial global depth : "; }
    cin>>initial_global_depth;

    Directory<standard_reg<10>,1> d(initial_global_depth, arquivo);
    cout<<endl<<"Initialized directory structure"<<endl;

    if(show_messages)
        menu();

    do
    {
        cout<<endl;
        if(show_messages) { cout<<">>> "; }
        cin>>choice;
        if(choice=="insert")
        {
            cout<<"Key >>> ";
            cin >> key;
            cout<<"C >>> ";
            cin >> c;
            cout<<"String >>> ";
            cin >> b;
            if(show_messages) { cout<<endl; }
            for(int i=0;i<2;i++){
            d.insert(standard_reg<10>(key,b,c),0);
            }
        }
        else if(choice=="delete")
        {
            cin >> key;
            if(show_messages) { cout<<endl; }
            d.remove(key);
        }
        else if(choice=="search")
        {
            cin>>key;
            if(show_messages) { cout<<endl; }
            d.search(key);
        }
        else if(choice=="display")
        {
            if(show_messages) { cout<<endl; }
            d.display(show_duplicate_buckets);
        }
    } while(choice!="exit");

    return 0;
}

/* Print usage menu */

void menu()
{
    cout<<"--------------------"<<endl;
    cout<<"Enter queries in the following format :"<<endl;
    cout<<"insert"<<endl;
    cout<<"delete <key>"<<endl;
    cout<<"search <key>"<<endl;
    cout<<"display"<<endl;
    cout<<"exit"<<endl;
    cout<<"--------------------"<<endl;
}



#include <bits/stdc++.h>
using namespace std;

#include "ExtensibleHash.hpp"
#include "standard_reg.hpp"

void menu();
void menu2();


int main()
{
    int initial_global_depth, show_messages;
    long int key, mode, c;
    char b[100];
    string arquivo;
    string choice, value;

    cout << "Testar HEAP(1)\nTestar Hash(2)" << endl;
    cin >> show_messages;
    cout << "Qual Arquivo deseja utilizar?\n>>> ";
    cin >> arquivo;
    arquivo += ".data";

    if(show_messages==2){
      if(show_messages) { cout<<"Bucket size 10" << endl; }
      if(show_messages) { cout<<"Initial global depth : "; }
      cin>>initial_global_depth;

      Directory<standard_reg<10>,10> d(initial_global_depth, (char*) arquivo.c_str());
      cout<<endl<<"Initialized directory structure"<<endl;

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
              d.insert(standard_reg<10>(key,b,c),0);
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
              d.display();
          }
          else if(choice=="scan"){
            d.scan_heap();
          }
      } while(choice!="exit");
    }
    else{
      menu2();
      heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> heap((char*)arquivo.c_str());
      do
      {
          cout<<endl;
          if(show_messages) { cout<<">>> "; }
          cin>>choice;
          if(choice=="insert")
          {
              cout << "Será inserido 20 registro com A no intervalo [0-20)";
              cout<<"C >>> ";
              cin >> c;
              cout<<"String >>> ";
              cin >> b;
              if(show_messages) { cout<<endl; }
              for(int i=0;i<20;i++){
                heap.insert_reg(standard_reg<10>(i,b,c));
              }
          }
          else if(choice=="delete")
          {
              int slotid, pageid;
              cin >> slotid >> pageid;
              if(show_messages) { cout<<endl; }
              heap.remove_reg(slotid, pageid);
          }
          else if(choice=="scan"){
              heap.scan();
          }
      } while(choice!="exit");
    }


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

void menu2(){
  cout<<"--------------------"<<endl;
  cout<<"Enter queries in the following format :"<<endl;
  cout<<"insert"<<endl;
  cout<<"delete <slotID> <pageID>"<<endl;
  cout<<"scan"<<endl;
  cout<<"exit"<<endl;
  cout<<"--------------------"<<endl;
}




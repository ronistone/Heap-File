#include <bits/stdc++.h>
using namespace std;

#include "ExtensibleHash.hpp"
#include "standard_reg.hpp"

void menu();
void menu2();


/* Main function */

int main()
{
    bool show_duplicate_buckets;
    int bucket_size, initial_global_depth, show_messages;
    long int key, mode, c;
    char b[100];
    char arquivo[] = "dados.d";
    string choice, value;

    // Set show_messages to 0 when taking input using file redirection
    cout << "Testar HEAP(1)\nTestar Hash(2)" << endl;
    cin >> show_messages;
    //show_messages = 1;

    // Set show_duplicate_buckets to 1 to see all pointers instead of unique ones
    show_duplicate_buckets = 1;

    if(show_messages==2){
      if(show_messages) { cout<<"Bucket size 10" << endl; }
      if(show_messages) { cout<<"Initial global depth : "; }
      cin>>initial_global_depth;

      Directory<standard_reg<10>,1> d(initial_global_depth, arquivo);
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
              d.display(show_duplicate_buckets);
          }
          else if(choice=="scan"){
            d.scan_heap();
          }
      } while(choice!="exit");
    }
    else{
      menu2();
      heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> heap("dados.d");
      do
      {
          cout<<endl;
          if(show_messages) { cout<<">>> "; }
          cin>>choice;
          if(choice=="insert")
          {
              cout << "Será inserido 20 registro com A no intervalo [0-20)";
              //cout<<"Key >>> ";
              //cin >> key;
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




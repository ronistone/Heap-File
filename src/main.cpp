#include <bits/stdc++.h>
using namespace std;

#include "ExtensibleHash.hpp"
#include "standard_reg.hpp"
#include "JoinOp.hpp"

void menu();
void menu2();


int main()
{
    int initial_global_depth, show_messages;
    long int key, mode, c;
    char b[100];
    string arquivo;
    string choice, value;

    do{
      system("clear");
      cout << "Testar HEAP(1)\nTestar Hash(2)\nSair(0)" << endl;
      cin >> show_messages;
      if(!show_messages)
        break;
      cout << "Qual Arquivo deseja utilizar?\n>>> ";
      cin >> arquivo;
      arquivo += ".data";

      if(show_messages==2){
        if(show_messages) { cout<<"Bucket size 10" << endl; }
        if(show_messages) { cout<<"Initial global depth : "; }
        cin>>initial_global_depth;

        Directory<standard_reg<10>,10> d(initial_global_depth, (char*) arquivo.c_str());
        cout<<endl<<"Initialized directory structure"<<endl;

        do
        {
          menu();
            cout<<endl;
            if(show_messages) { cout<<">>> "; }
            cin>>choice;
            if(choice=="1")
            {
                cout << "INSERT:" << endl;
                cout<<"Key >>> ";
                cin >> key;
                cout<<"C >>> ";
                cin >> c;
                cout<<"String >>> ";
                cin >> b;
                if(show_messages) { cout<<endl; }
                d.insert(standard_reg<10>(key,b,c),0);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="2")
            {
                cout << "DELETE: " << endl;
                cout << "key >> ";
                cin >> key;
                if(show_messages) { cout<<endl; }
                d.remove(key);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="3")
            {
                cout << "SEARCH: " << endl;
                cout << "key >> ";
                cin>>key;
                if(show_messages) { cout<<endl; }
                d.search(key);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="4")
            {
                if(show_messages) { cout<<endl; }
                d.display();
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="scan"){
              d.scan_heap();
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
            else if(choice=="5"){
              cout << "NESTED INDEX JOIN: " << endl;
              string bPath, out;
              cout << "Selecione o nome da tabela para o join\n >> ";
              cin >> bPath;
              bPath += ".data";
              cout << "Selecione o nome da tabela de saida\n >> ";
              cin >> out;
              out += ".data";

              heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> heap,b(bPath);
              heap = nestedIndex<Directory<standard_reg<10>,10>,standard_reg<10>,10>(d,b,out);
              heap.scan();
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
        } while(choice!="0");
      }
      else{
        int pageid,slotid;
        heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> heap((char*)arquivo.c_str());
        do
        {
          menu2();
            cout<<endl;
            if(show_messages) { cout<<">>> "; }
            cin>>choice;
            if(choice=="1")
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
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="2")
            {
                int slotid, pageid;
                cin >> slotid >> pageid;
                if(show_messages) { cout<<endl; }
                heap.remove_reg(slotid, pageid);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="3"){
                heap.scan();
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="4"){
              cout << "SlotID >> ";
              cin >> slotid;

              cout << "PageID >> ";
              cin >> pageid;

              cout << "Key >> ";
              cin >> key;
              cout<<"C >>> ";
              cin >> c;
              cout<<"String >>> ";
              cin >> b;
              heap.update_reg(RID(slotid,pageid),standard_reg<10>(key,b,c));
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
        } while(choice!="0");
      }
    }while(show_messages!=0);

    return 0;
}

/* Print usage menu */

void menu()
{
    system("clear");
    cout<<"--------------------"<<endl;
    cout<<"Enter queries in the following format :"<<endl;
    cout<<"insert (1)"<<endl;
    cout<<"delete (2) <key>"<<endl;
    cout<<"search (3)<key>"<<endl;
    cout<<"display (4)"<<endl;
    cout<<"Neste Index Join (5)" << endl;
    cout<<"exit (0)"<<endl;
    cout<<"--------------------"<<endl;
}

void menu2(){
  system("clear");
  cout<<"--------------------"<<endl;
  cout<<"Enter queries in the following format :"<<endl;
  cout<<"insert (1)"<<endl;
  cout<<"delete (2) <slotID> <pageID>"<<endl;
  cout<<"scan (3)"<<endl;
  cout<<"update (4)"<<endl;
  cout<<"exit (0)"<<endl;
  cout<<"--------------------"<<endl;
}




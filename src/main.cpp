#include <bits/stdc++.h>
using namespace std;

#include "ExtensibleHash.hpp"
#include "standard_reg.hpp"
#include "standard_regJoin.hpp"
#include "JoinOp.hpp"

void menu();
void menu2();

int type;
int main()
{
    int initial_global_depth, show_messages;
    Directory<standard_reg<10>,10>* d;
    Directory<standard_reg_join<10>,10>* d1;
    heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10>* heap;
    heap_file<standard_reg_join<10>, sizeof(standard_reg_join<10>)*10>* heap1;
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

      cout << "Tipo da Tabela:\n(1)Data\n(2)Join\n>>>";
      cin >> type;
      cout << "Qual tabela deseja utilizar?\n>>> ";
      cin >> arquivo;
      if(type == 1)
        arquivo += ".data";
      else
        arquivo += ".join";

      if(show_messages==2){
        if(show_messages) { cout<<"Bucket size 10" << endl; }
        if(show_messages) { cout<<"Initial global depth : "; }
        cin>>initial_global_depth;

        if(type == 1)
          d = new Directory<standard_reg<10>,10>(initial_global_depth, (char*) arquivo.c_str());
        else
          d1 = new Directory<standard_reg_join<10>,10>(initial_global_depth, (char*) arquivo.c_str());
        cout<<endl<<"Initialized directory structure"<<endl;

        do
        {
          menu();
            cout<<endl;
            if(show_messages) { cout<<">>> "; }
            cin>>choice;
            if(choice=="1" and type==1)
            {
                cout << "INSERT:" << endl;
                cout<<"Key >>> ";
                cin >> key;
                cout<<"C >>> ";
                cin >> c;
                cout<<"String >>> ";
                cin >> b;
                if(show_messages) { cout<<endl; }
                d->insert(standard_reg<10>(key,b,c),0);
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
                if(type==1)
                  d->remove(key);
                else
                  d1->remove(key);
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
                if(type==1)
                  d->search(key);
                else
                  d1->search(key);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="4")
            {
                if(show_messages) { cout<<endl; }
                if(type==1)
                  d->display();
                else
                  d1->display();
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="scan"){
              if(type==1)
                d->scan_heap();
              else
                d1->scan_heap();
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
            else if(choice=="5" and type==1){
              cout << "NESTED INDEX JOIN: " << endl;
              string bPath, out;
              cout << "Selecione o nome da tabela para o join\n >> ";
              cin >> bPath;
              bPath += ".data";
              cout << "Selecione o nome da tabela de saida\n >> ";
              cin >> out;
              out += ".join";

              const clock_t begin_time = clock();
              int count = 0;
              heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> result,b(bPath);
              result = nestedIndex<Directory<standard_reg<10>,10>,
                                  standard_reg<10>,
                                    10>(*d,b,out,&count);
              result.scan();
              cout << "\n\nEstatisticas:" << endl;
              cout << "Numero de I/Os: " << count << endl;
              cout << "Tempo Gastos: ";
              cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " Segundos" << endl;
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
            else if(choice == "6" and type==1){
              cout << "HASH JOIN: "  << endl;
              string bPath, out;
              cout << "Selecione o nome da tabela para o join\n >> ";
              cin >> bPath;
              bPath += ".data";
              cout << "Selecione o nome da tabela de saida\n >> ";
              cin >> out;
              out += ".join";

              const clock_t begin_time = clock();
              int count = 0;
              heap_file<standard_reg_join<10>, sizeof(standard_reg_join<10>)*10> result;
              result = hashJoin<Directory<standard_reg<10>,10>,
                                  standard_reg_join<10>,
                                    10>(*d,bPath,out,&count);
              result.scan();
              cout << "\n\nEstatisticas:" << endl;
              cout << "Numero de I/Os: " << count << endl;
              cout << "Tempo Gastos: ";
              cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " Segundos" << endl;
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();

            }
            else if(choice == "7" and type==1){
              cout << "COMPARE: "  << endl;
              string bPath, out;
              cout << "Selecione o nome da tabela para o join\n >> ";
              cin >> bPath;
              bPath += ".data";
              cout << "Selecione o nome da tabela de saida\n >> ";
              cin >> out;
              out += ".join";
              clock_t begin_time = clock();
              int count = 0;
              heap_file<standard_reg_join<10>, sizeof(standard_reg_join<10>)*10> result;
              result = hashJoin<Directory<standard_reg<10>,10>,
                                  standard_reg_join<10>,
                                    10>(*d,bPath,out,&count);
              const float hashTime= float( clock () - begin_time ) /  CLOCKS_PER_SEC;
              const int ioHash = count;
              count = 0;
              begin_time = clock();
              heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10> result1,b(bPath);
              result1 = nestedIndex<Directory<standard_reg<10>,10>,
                                  standard_reg<10>,
                                    10>(*d,b,out,&count);

              const float nestedTime = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
              const int ioNested = count;
              system("clear");
              cout << "Join Types  \tI/Os\tTime" << endl;
              cout << "HASH        \t  " << ioHash << "\t" << hashTime << "Segundos" << endl;
              cout << "Nested Index\t  " << ioNested << "\t" << nestedTime << "Segundos" << endl;
              cin.ignore();
              cout << "Pressione enter para continuar..." << endl;
              getchar();
            }
        } while(choice!="0");
      }
      else{
        int pageid,slotid;
        if(type == 1)
          heap = new heap_file<standard_reg<10>, sizeof(standard_reg<10>)*10>((char*)arquivo.c_str());
        else
          heap1 = new heap_file<standard_reg_join<10>, sizeof(standard_reg_join<10>)*10>((char*)arquivo.c_str());
        do
        {
          menu2();
            cout<<endl;
            if(show_messages) { cout<<">>> "; }
            cin>>choice;
            if(choice=="1" and type==1)
            {
                cout << "Será inserido 20 registro com A no intervalo [0-20)";
                cout<<"C >>> ";
                cin >> c;
                cout<<"String >>> ";
                cin >> b;
                if(show_messages) { cout<<endl; }
                for(int i=0;i<20;i++){
                  heap->insert_reg(standard_reg<10>(i,b,c));
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
                if(type==1)
                  heap->remove_reg(slotid, pageid);
                else
                  heap1->remove_reg(slotid, pageid);
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="3"){
                if(type==1)
                  heap->scan();
                else
                  heap->scan();
                cin.ignore();
                cout << "Pressione enter para continuar..." << endl;
                getchar();
            }
            else if(choice=="4" and type==1){
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
              heap->update_reg(RID(slotid,pageid),standard_reg<10>(key,b,c));
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
    cout<<"Select The Query :"<<endl;
    if(type==1)
    cout<<"(1) insert"<<endl;
    cout<<"(2) delete"<<endl;
    cout<<"(3) search"<<endl;
    cout<<"(4) display"<<endl;
    if(type==1){
    cout<<"(5) Nested Index Join"<<endl;
    cout<<"(6) Hash Join"<<endl;
    cout<<"(7) Compare Nested Index Join and Hash Join"<<endl;
    }
    cout<<"(0) exit"<<endl;
    cout<<"--------------------"<<endl;
}

void menu2(){
  system("clear");
  cout<<"--------------------"<<endl;
  cout<<"Select The Query :"<<endl;
  if(type==1)
  cout<<"(1) insert"<<endl;
  cout<<"(2) delete"<<endl;
  cout<<"(3) scan"<<endl;
  if(type==1)
  cout<<"(4) update"<<endl;
  cout<<"(0) exit"<<endl;
  cout<<"--------------------"<<endl;
}




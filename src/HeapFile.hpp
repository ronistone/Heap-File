#ifndef _HEAP_FILE_
#define _HEAP_FILE_
#include <bits/stdc++.h>
using namespace std;

#include "page.hpp"
#include "RID.hpp"

template<class T, int size_page>
class heap_file{

  private:
    string _PATH;
    map<int,bool> notFullPage;  // (PageID,isFull?)

  public:
    heap_file(string p);

    RID insert_reg(T data);
    int insert_page();
    void set_page(int pageId, page<T, size_page> p);
    int insert_into(int pageId, T reg);
    T search(int pageId, int key);
    page<T, size_page>* get_page(int pageId);
    void clear_page(int pageId);
    int remove_reg(RID reg);
    void remove_reg(int slotId, int pageId);
    int remove_regByKey(int slotId, int key);
    void update_reg(RID reg, T data);
    void update_reg(int slotId, int pageId, T data);
    void scan();
    T getReg(RID r);
    void display(int pageId);

};

template<class T, int size_page>
heap_file<T, size_page>::heap_file(string p){
  ifstream fi(p.c_str());
  if(!fi.good()){
    fi.close();
    ofstream f(p.c_str());
    if(f.good()){
      cout << "HEAP FILE CREATE" << endl;
    }else{
      cout << "HEAP FILE CREATION FAILED" << endl;
    }
    f.close();
  }else{
    int pag = 0;
    bool b;
    page<T,size_page> p;
    fi.seekg(0, fi.beg);
    while(fi.read((char*)&b,sizeof(bool)) and fi.read((char*) &p, sizeof(page<T, size_page>))){
      if(!b){
        notFullPage[pag] = true;
      }
      pag++;
    }
    cout << "HEAP FILE LOADED" << endl;
    fi.close();
  }
  _PATH = p;
}

template<class T, int size_page>
RID heap_file<T, size_page>::insert_reg(T data){

  page<T, size_page> p;
  RID in;
  bool b;
  fstream f(_PATH.c_str());
  map<int,bool>::iterator it;

  f.seekp(0, f.end);

  // Get first page not Full
  if(notFullPage.size()){
    it = notFullPage.begin();
    while(it!=notFullPage.end()){
      if(it->second){
        f.seekp((it->first)*(sizeof(page<T,size_page>) + sizeof(bool)),f.beg);
        f.read((char*)&b, sizeof(bool));
        f.read((char*)&p, sizeof(page<T, size_page>));

        in.setSlot(p.insert(data));
        if(f.tellg() >= sizeof(page<T, size_page>)){
          f.seekg((it->first)*(sizeof(bool) + sizeof(page<T, size_page>)),f.beg);
        }else{
          f.seekg(0,f.end);
        }
        b = p.isFull();
        f.write((char* )&b, sizeof(bool));
        f.write((char *) &p, sizeof(p));
        cout << "RECORD INSERTED" << endl;
        f.seekg(0,f.end);
        in.setPage((f.tellg()/(p.sizePage()+sizeof(bool)))-1);

        // if full erase in map
        if(b){
          notFullPage.erase(in.getPage());
        }
        break;
      }else{
        it++;
      }
    }
    // create new empty page
  }else{
    page<T, size_page> p1;
    in.setSlot(p1.insert(data));
    b = false;
    f.seekp(0,f.end);
    f.write((char *)&b,sizeof(bool));
    f.write((char *) &p1, sizeof(page<T, size_page>));
    f.seekg(0, f.end);
    in.setPage((f.tellg()/(p1.sizePage()+sizeof(bool)))-1);
    if(!p1.isFull()){
      notFullPage[in.getPage()] = true;
    }
    cout << "NEW PAGE INSERTION" << endl;
  }

  f.close();
  return in;
}

template<class T, int size_page>
int heap_file<T, size_page>::insert_page(){
  page<T, size_page> p;
  bool b = p.isFull();
  fstream f(_PATH.c_str());

  f.seekp(0, f.end);
  f.write((char*)&b,sizeof(bool));
  f.write((char*)&p, sizeof(p));
  f.close();

  fstream fi(_PATH.c_str());
  fi.seekg(0,f.end);
  int pageId = ((fi.tellg()/(sizeof(p)+sizeof(bool)))-1);
  fi.close();
  notFullPage[pageId] = true;
  return pageId;
}

template<class T, int size_page>
page<T, size_page>* heap_file<T,size_page>::get_page(int pageId){
  ifstream f(_PATH.c_str());

  bool b;
  page<T, size_page>* p = new page<T,size_page>();
  f.seekg(0,f.end);
  if(((((int)f.tellg())/(int)(sizeof(*p)+sizeof(bool)))-1) < pageId){
    f.close();
    return NULL;
  }

  f.seekg(pageId * (sizeof(bool) + sizeof(*p)),f.beg);
  f.read((char*)&b,sizeof(bool));
  f.read((char*) p, sizeof(*p));
  p->scan();

  f.close();
  return p;
}

template<class T, int size_page>
int heap_file<T, size_page>::insert_into(int pageId, T reg){

  fstream f(_PATH.c_str());

  bool b;
  page<T, size_page> p;
  f.seekg(pageId * (sizeof(bool)+ sizeof(p)), f.beg);
  f.read((char*) &b, sizeof(bool));
  f.read((char*) &p, sizeof(p));

  int result = p.insert(reg);

  b = p.isFull();
  f.seekp(pageId * (sizeof(bool) + sizeof(p)), f.beg);
  f.write((char*) &b, sizeof(bool));
  f.write((char*) &p, sizeof(p));

  f.close();

  if(p.isFull()){
    notFullPage.erase(pageId);
  }

  return result;
}

template<class T, int size_page>
T heap_file<T, size_page>::search(int pageId, int key){
  ifstream f(_PATH.c_str());

  bool b;
  page<T, size_page> p;
  T result;

  f.seekg(pageId * (sizeof(bool)+ sizeof(p)), f.beg);
  f.read((char*) &b, sizeof(bool));
  f.read((char*) &p, sizeof(p));

  f.close();

  result = p.search(key);

  return result;
}

template<class T, int size_page>
void heap_file<T,size_page>::clear_page(int pageId){
  fstream f(_PATH.c_str());
  page<T, size_page> p;

  f.seekp(pageId*(sizeof(bool)+sizeof(p)),f.beg);
  bool b = p.isFull();
  f.write((char*)&b, sizeof(bool));
  f.write((char*)&p, sizeof(p));
  f.close();
}

template<class T, int size_page>
void heap_file<T,size_page>::set_page(int pageId, page<T, size_page> p){
  fstream f(_PATH.c_str());

  f.seekp(pageId* (sizeof(bool)+sizeof(p)),f.beg);
  bool b = p.isFull();
  f.write((char*)&b, sizeof(bool));
  f.write((char*)&p, sizeof(p));
  f.close();
}

template<class T, int size_page>
int heap_file<T, size_page>::remove_reg(RID reg){
  int result = 0;
  if(reg.getPage()>=0 and reg.getSlot() >=0){
    fstream f(_PATH.c_str());
    page<T, size_page> p;
    bool b;

    f.seekg(reg.getPage()*(sizeof(page<T, size_page>) + sizeof(bool)),f.beg);
    f.read((char*) &b, sizeof(bool));
    f.read((char*) &p, sizeof(page<T, size_page>));
    result = p.remove(reg.getSlot());

    b = p.isFull();
    if(!b){
      notFullPage[reg.getPage()] = true;
    }
    f.seekp(reg.getPage()*(sizeof(page<T, size_page>) + sizeof(bool)),f.beg);
    f.write((char*) &b, sizeof(bool));
    f.write((char*) &p, sizeof(page<T, size_page>));
    cout << "REMOVE REGISTER PAGEID " << reg.getPage() << " SLOTID " << reg.getSlot() << endl;

    f.close();
  }
  return result;
}

template<class T, int size_page>
void heap_file<T, size_page>::remove_reg(int slotId, int pageId){
  RID reg(slotId,pageId);
  remove_reg(reg);
}

template<class T, int size_page>
int heap_file<T, size_page>::remove_regByKey(int pageId, int key){
  if(pageId>=0){
    fstream f(_PATH.c_str());
    page<T, size_page> p;
    bool b;

    f.seekg(pageId*(sizeof(page<T, size_page>) + sizeof(bool)),f.beg);
    f.read((char*) &b, sizeof(bool));
    f.read((char*) &p, sizeof(page<T, size_page>));
    int result = p.removeByKey(key);

    b = p.isFull();
    if(!b){
      notFullPage[pageId] = true;
    }
    f.seekp(pageId*(sizeof(page<T, size_page>) + sizeof(bool)),f.beg);
    f.write((char*) &b, sizeof(bool));
    f.write((char*) &p, sizeof(page<T, size_page>));
    cout << "REMOVE REGISTER PAGEID " << pageId << " KEY " << key << endl;

    f.close();
    return result;
  }
  return 0;
}

template<class T, int size_page>
void heap_file<T, size_page>::update_reg(RID reg, T data){
  if(reg.getPage() >=0){
      fstream f(_PATH.c_str());
      page<T, size_page> p;

      f.seekg(sizeof(bool) + (reg.getPage()*(sizeof(page<T, size_page>) + sizeof(bool))),f.beg);
      f.read((char*) &p, sizeof(page<T, size_page>));
      p.update(reg.getSlot(),data);

      f.seekp(sizeof(bool) + (reg.getPage()*(sizeof(page<T, size_page>) + sizeof(bool))),f.beg);
      f.write((char*) &p, sizeof(page<T, size_page>));
      cout << "REGISTER UPDATED" << endl;
      f.close();
  }else{
    cout << "INVALID PAGE" << endl;
  }
}

template<class T, int size_page>
void heap_file<T, size_page>::update_reg(int slotId, int pageId, T data){
  RID reg(slotId,pageId);
  update_reg(reg,data);
}

template<class T, int size_page>
void heap_file<T, size_page>::scan(){
  ifstream f(_PATH.c_str());
  bool b;
  if(f.good()){
    page<T, size_page> p;
    while(f.read((char*)&b,sizeof(bool)) and f.read((char *) &p,sizeof(p))){
      p.scan();
      cout << "PAGE FOUND" << endl;
    }
  }else{
    cout << "READ FAILED" << endl;
  }
  f.close();
}

template<class T, int size_page>
T heap_file<T, size_page>::getReg(RID r){
  ifstream f(_PATH.c_str());

  bool b;

  page<T,size_page> p;

  f.seekg(r.getPage() * (sizeof(bool)+sizeof(p)), f.beg);
  f.read((char*) &b, sizeof(bool));
  f.read((char*) &p, sizeof(p));

  return p.getAt(r.getSlot());
}

template<class T, int size_page>
void heap_file<T, size_page>::display(int pageId){
  ifstream f(_PATH.c_str());
  bool b;
  if(f.good()){
    page<T, size_page> p;
    f.seekg(pageId * (sizeof(bool)+ sizeof(p)),f.beg);
    f.read((char*)&b,sizeof(bool));
    f.read((char *) &p,sizeof(p));
    p.scan();
  }else{
    cout << "READ FAILED" << endl;
  }
  f.close();
}


#endif
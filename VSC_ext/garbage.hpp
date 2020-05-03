#ifndef GARBAGE_H
#define GARBAGE_H

#include <iostream>
#include "Linked_List.hpp"

class package{
public:
    int id;
    int ref_counter;
    package(int _id){
        id = _id;
    };
    package(){
        ref_counter=1;
    };
    ~package(){};
};

template<typename J>
class specific_package: public package{
public:
    J data;
    specific_package(int _id, J _data):package(_id){
        data = _data;
        ref_counter=1;
    };
    specific_package(){
        ref_counter=1;
    };
    ~specific_package(){};
};

class GarbageCollector{
    private:
        GarbageCollector();
        static GarbageCollector* recolector;
        int contador;
        lista<package*> package_List;
    public:
        static GarbageCollector* getGarbageCollector();
        int getContador();
        void setContador(int cont);
        lista<package*> get_Pkg_List();
        void add_Pkg_To_List(package* to_add);
        void add_ref(int id);
        void lower_ref(int id);
        void delete_pkgs();

};
#endif

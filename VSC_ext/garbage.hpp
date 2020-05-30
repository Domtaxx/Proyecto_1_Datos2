#ifndef GARBAGE_H
#define GARBAGE_H

#include <iostream>
#include <exception>
#include "Linked_List.hpp"
#include "vsptrNT.hpp"
#include <stdint.h>
#include <unistd.h>

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
    virtual ~package(){};
    virtual std::string ret_Type(){
        return "";
    };
    virtual std::string ret_Val(){
        return "";
    };
    virtual std::string ret_Mem_Addr(){
        return "";
    };
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
    std::string ret_Type(){
        return typeid(data).name();
    };
    std::string ret_Val(){
        return std::to_string(data);
    };
    std::string ret_Mem_Addr(){
        long addr = (long)&data;
        return std::to_string(addr);
    };
};

class GarbageCollector{
    private:
        GarbageCollector();
        static GarbageCollector* recolector;
        int contador;
        lista<package*> package_List;
        lista<vsptrNT*> vsptr_List;
        package* binary_search_id(int id);

    public:
        ~GarbageCollector(){};
        static GarbageCollector* getGarbageCollector();
        static bool server_on;
        int getContador();
        void setContador(int cont);
        lista<package*> get_Pkg_List();
        void add_Pkg_To_List(package* to_add);
        lista<vsptrNT*> get_Vsptr_List();
        void add_Vsptr_To_List(vsptrNT* to_add);
        void add_ref(int id);
        void lower_ref(int id);
        void delete_pkgs();
        
};
#endif

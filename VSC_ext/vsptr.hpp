#ifndef VSPTR_HPP
#define VSPTR_HPP

#include <iostream>
#include "garbage.hpp"

template<typename T>
class VSPtr{
private:
    T* dato;
    int id;
    VSPtr(){
        id = -1;
        dato = NULL;
    };
public:
    static VSPtr<T> New(){
        return VSPtr<T>();
    };

    ~VSPtr(){
        if(!(id<=-1)){
            GarbageCollector::getGarbageCollector()->lower_ref(id);
        }
    };

    T operator &(){
        return *(dato);
    };

    VSPtr<T> operator *(){
        return *this;
    };

    void operator=(T dataNueva){
        if(id == -1){
            id = GarbageCollector::getGarbageCollector()->getContador();
            specific_package<T> pkg = new specific_package<T>(id,dataNueva);
            GarbageCollector::getGarbageCollector()->add_Pkg_To_List(pkg);
            dato = &(pkg.data);
            GarbageCollector::getGarbageCollector()->setContador(id++);
        }else{
            GarbageCollector::getGarbageCollector()->lower_ref(id);
            id = GarbageCollector::getGarbageCollector()->getContador();
            specific_package<T> pkg = new specific_package<T>(id,dataNueva);
            GarbageCollector::getGarbageCollector()->add_Pkg_To_List(pkg);
            dato = &(pkg.data);
            GarbageCollector::getGarbageCollector()->setContador(id++);
        }
    };

    void operator=(VSPtr<T> dataNueva){
        if(id == -1){
            id = dataNueva.id;
            dato = dataNueva.dato;
            GarbageCollector::getGarbageCollector()->add_ref(id);
        }else{
            GarbageCollector::getGarbageCollector()->lower_ref(id);
            id = dataNueva.id;
            dato = dataNueva.dato;
            GarbageCollector::getGarbageCollector()->add_ref(id);
        }
    };
};

#endif // VSPTR_HPP

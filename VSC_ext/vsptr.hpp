#ifndef VSPTR_HPP
#define VSPTR_HPP

#include <iostream>
#include "vsptrNT.hpp"
#include "garbage.hpp"
#include "socket.hpp"
#include "socket_C.hpp"
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"

template<typename T>
class VSPtr: public vsptrNT{
private:
    T* dato;
    int id;
    int localId;
    VSPtr():vsptrNT(){
        if(GarbageCollector::server_on){
            localId = Socket::vsptr_counter;
            std::string msg = "${tipo:"+this->ret_Type()+",localId:"+std::to_string(localId)+"}";
            Socket_C::remoteSocket->comunicar(msg);
            //Socket::vsptr_counter = localId+1;
            Socket::vsptr_counter+=1;
        }else{
            id = -1;
            dato = new T();
            if(GarbageCollector::getGarbageCollector()==NULL){
                GarbageCollector::getGarbageCollector();
            }
             GarbageCollector* gc = GarbageCollector::getGarbageCollector();
             gc->add_Vsptr_To_List(this);
        }
    };
public:
    static VSPtr<T> New(){
        return VSPtr<T>();
    };
    ~VSPtr(){
        if(GarbageCollector::server_on){
            Socket_C::remoteSocket->comunicar("~"+std::to_string(localId));
        }else{
            GarbageCollector* gc = GarbageCollector::getGarbageCollector();
            gc->lower_ref(this->id);
        }
    };

    T operator &(){
        if(GarbageCollector::server_on){
            std::string infoDato = Socket_C::remoteSocket->comunicar("&"+localId);
            rapidjson::Document document;
            document.Parse<0>(infoDato.c_str()).HasParseError();
            std::string tipo = document["tipo"].GetString();
            if(tipo == "i"){
                return std::stoi(document["dato"].GetString());
            }if(tipo == "l"){
                return std::stol(document["dato"].GetString());
            }if(tipo == "f"){
                return std::stof(document["dato"].GetString());
            }if(tipo == "d"){
                return std::stod(document["dato"].GetString());
            }if(tipo == "c"){
                return document["dato"].Get<char>();
                //return infoDato.c_str()[3];
            }
        }else{
            return *(dato);
        }
    };

    VSPtr<T> operator *(){
        if(GarbageCollector::server_on){

        }else{
            return *this;
        }
    };

    void operator=(T dataNueva){
        if(GarbageCollector::server_on){
            std::string msg = "#p{localId:"+localId;
            msg += ",dato:"+ std::to_string(dataNueva) + "}";
            Socket_C::remoteSocket->comunicar(msg);
        }else{
            if(id == -1){
                id = GarbageCollector::getGarbageCollector()->getContador();
                specific_package<T>* pkg = new specific_package<T>(id,dataNueva);
                GarbageCollector::getGarbageCollector()->add_Pkg_To_List(pkg);
                dato = &(pkg->data);
                GarbageCollector::getGarbageCollector()->setContador(id+1);
            }else{
                GarbageCollector::getGarbageCollector()->lower_ref(id);
                id = GarbageCollector::getGarbageCollector()->getContador();
                specific_package<T>* pkg = new specific_package<T>(id,dataNueva);
                GarbageCollector::getGarbageCollector()->add_Pkg_To_List(pkg);
                dato = &(pkg->data);
                GarbageCollector::getGarbageCollector()->setContador(id+1);
            }
        }
    };

    void operator=(VSPtr<T> dataNueva){
        if(GarbageCollector::server_on){
            std::string msg = "#d{localId:"+localId;
            msg += ",dato:"+dataNueva.ret_Local_id() +"}";
            Socket_C::remoteSocket->comunicar(msg);
        }else{
            if(id == -1){
                id = dataNueva.id;
                dato = dataNueva.dato;
                GarbageCollector::getGarbageCollector()->add_ref(id);
                GarbageCollector::getGarbageCollector()->add_ref(id);
            }else{
                GarbageCollector::getGarbageCollector()->lower_ref(id);
                id = dataNueva.id;
                dato = dataNueva.dato;
                GarbageCollector::getGarbageCollector()->add_ref(id);
                GarbageCollector::getGarbageCollector()->add_ref(id);
            }
        }
    };

    std::string ret_Type(){
        return typeid(*dato).name();
    };
    std::string ret_Val(){
        if (dato==nullptr){
            return "null";
        }else{
            return std::to_string(*dato);
        }
    };
    std::string ret_Id(){
        return std::to_string(id);
    };
    std::string ret_Mem_Addr(){
        return std::to_string((long)dato);
    };
    std::string ret_Local_Id(){
        return std::to_string(localId);
    };
};


#endif // VSPTR_HPP

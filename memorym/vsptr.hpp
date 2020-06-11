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
/**
 * @brief derived class from vsptrNT, stores a pointer of the data
 * @tparam T 
 */
template<typename T>
class VSPtr: public vsptrNT{
private:
    T* dato;
    int id;
    int localId;
    /**
     * @brief Construct a new VSPtr object
     */
    VSPtr():vsptrNT(){
        if(GarbageCollector::server_on){
            localId = Socket::vsptr_counter;
            std::string msg = "${ \"tipo\" : \""+this->ret_Type()+"\",\"localId\" : \""+std::to_string(localId)+"\"}";
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
/**
 * @brief a way to instanciate VSPtr
 * @return VSPtr<T>* pointer of the new VSPtr
 */
    static VSPtr<T> New(){
        return VSPtr<T>();
    };
    /**
     * @brief Destroy the VSPtr object
     * 
     */
    ~VSPtr(){
        if(GarbageCollector::server_on){
            Socket_C::remoteSocket->comunicar_without_response("~"+std::to_string(localId)+"*");
        }else{
            GarbageCollector* gc = GarbageCollector::getGarbageCollector();
            gc->lower_ref(this->id);
        }
    };
    /**
     * @brief returns the data
     * 
     * @return T  data
     */
    T operator &(){
        if(GarbageCollector::server_on){
            std::string infoDato = Socket_C::remoteSocket->comunicar("&"+std::to_string(localId)+"*");
            std::cout<<infoDato<<std::endl;
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
                return document["dato"].GetString()[0];
            }return *(dato);
        }else{
            return *(dato);
        }
    };
    /**
     * @brief returns this same object
     * 
     * @return VSPtr<T> this
     */
    VSPtr<T> operator *(){
        if(GarbageCollector::server_on){

        }else{
            return *this;
        }
    };
    /**
     * @brief asign a new value to the pointer
     * 
     * @param dataNueva new data
     */
    void operator=(T dataNueva){
        if(GarbageCollector::server_on){
            std::string msg = "#d{ \"localId\" : \""+std::to_string(localId)+"\",\"dato\" : \""+std::to_string(dataNueva)+"\"}";
            //std::string msg = "#d{localId:"+localId;
            //msg += ",dato:"+ std::to_string(dataNueva) + "}";
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
    /**
     * @brief asigns a new value to the pointer 
     * @param dataNueva new pointer containing the data
     */
    void operator=(VSPtr<T> dataNueva){
        if(GarbageCollector::server_on){
            std::string msg = "#p{ \"localId\" : \""+std::to_string(localId)+"\",\"dato\" : \""+dataNueva.ret_Local_Id()+"\"}";
            //std::string msg = "#p{localId:"+localId;
            //msg += ",dato:"+dataNueva.ret_Local_id() +"}";
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
    /**
     * @brief return the type of the pointer
     * 
     * @return std::string of type
     */
    std::string ret_Type(){
        return typeid(*dato).name();
    };
    /**
     * @brief returns the value stored in data
     * 
     * @return std::string data stored in data
     */
    std::string ret_Val(){
        if (dato==nullptr){
            return "null";
        }else{
            return std::to_string(*dato);
        }
    };
    /**
     * @brief returns the id of the pointer
     * 
     * @return std::string id in a string
     */
    std::string ret_Id(){
        return std::to_string(id);
    };
    /**
     * @brief returns the memory address of the data
     * @return std::string the memory address in a string
     */
    std::string ret_Mem_Addr(){
        return std::to_string((long)dato);
    };
    /**
     * @brief returns the local_id of the data
     * @return std::string the local_id in a string
     */
    std::string ret_Local_Id(){
        return std::to_string(localId);
    };
};


#endif // VSPTR_HPP

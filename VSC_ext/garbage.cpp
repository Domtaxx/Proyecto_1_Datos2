#include "garbage.hpp"
#include "vsptr.hpp"
#include <thread>
#include "pthread.h"
#include <unistd.h>

GarbageCollector* GarbageCollector::recolector = NULL;
bool GarbageCollector::server_on = true;
GarbageCollector::GarbageCollector(){
    recolector = NULL;
    contador = 0;
    this->vsptr_List = lista<vsptrNT*>();
    this->package_List = lista<package*>();
};

GarbageCollector* GarbageCollector::getGarbageCollector(){
    if (recolector == NULL){
        recolector = new GarbageCollector();
    }else{
        return recolector;
    }
    return recolector;
};

int GarbageCollector::getContador(){
    return contador;
}

void GarbageCollector::setContador(int cont){
    contador = cont;
}

lista<package*> GarbageCollector::get_Pkg_List(){
    return package_List;
};

void GarbageCollector::add_Pkg_To_List(package* to_add){
    package_List.insert(to_add);
    ;
};

lista<vsptrNT*> GarbageCollector::get_Vsptr_List(){
    return vsptr_List;
};

void GarbageCollector::add_Vsptr_To_List(vsptrNT* to_add){
    vsptr_List.insert(to_add);
};

void GarbageCollector::add_ref(int id){
    if(id>=0){
        package* pkg = binary_search_id(id);
        pkg->ref_counter+=1;
    }
    return;
};
void GarbageCollector::lower_ref(int id){
    if(id>=0){
        package* pkg = binary_search_id(id);
        pkg->ref_counter-=1;
    }
    return;
};

package* GarbageCollector::binary_search_id(int id){
    package* pkg = nullptr;
    if(id >= 0){
        int maxP, minP, midP;
        maxP = package_List.get_object_counter()-1;
        minP =0;
        if(maxP == 0){
            pkg = package_List.get_data_by_pos(0);
            return pkg;
        }
        while(minP <= maxP){
            midP = minP + ((maxP-minP)/2);
            if(package_List.get_data_by_pos(midP)->id == id){
                pkg = (package_List.get_data_by_pos(midP));
                return pkg;
            }else if(package_List.get_data_by_pos(midP)->id < id){
                minP = midP+1;
            }else{
                minP = midP-1;
            }
        }
    }return pkg;
}

void GarbageCollector::delete_pkgs(){
        for(int i = 0; i<package_List.get_object_counter(); i++){
            if(package_List.is_End(i)){
                package* pkg = (package_List.get_data_by_pos(i));
                if(pkg->ref_counter == 0){
                    delete pkg;
                    package_List.delete_by_pos(i);
                }break;
            }
            package* pkg = (package_List.get_data_by_pos(i));
            if(pkg->ref_counter == 0){
                delete pkg;
                package_List.delete_by_pos(i);
                i--;
            }
        }for(int i = 0; i<this->vsptr_List.get_object_counter(); i++){
            if(vsptr_List.get_data_by_pos(i)==nullptr){
                vsptr_List.delete_by_pos(i);
            }
        }
        Socket_C::JS_socket->comunicar_without_response(GC_data());
};
void GarbageCollector::thread_function(bool* is_finished){
    while(*is_finished){
        if(server_on){
            if(Socket_C::remoteSocket!=nullptr){
                std::string msg = Socket_C::remoteSocket->comunicar("=");
                Socket_C::JS_socket->comunicar_without_response(msg);
            }
        }else{
            delete_pkgs();
        }sleep(10);
    }
}


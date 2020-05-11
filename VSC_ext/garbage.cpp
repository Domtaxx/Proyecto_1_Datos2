 #include "garbage.hpp"
#include <thread>
GarbageCollector* GarbageCollector::recolector = NULL;

GarbageCollector::GarbageCollector(){
    recolector = NULL;
    contador = 0;
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
};

void GarbageCollector::add_ref(int id){
    if(package_List.get_object_counter()==1){
        package_List.get_data_by_pos(0)->ref_counter+=1;
        return;
    }
    int minP = 0;
    int maxP = package_List.get_object_counter();
    while(minP != maxP){
        int midP = (minP+maxP)/2;
        package* pkg = (package_List.get_data_by_pos(midP));
        if(pkg->id == id){
            pkg->ref_counter+=1;
            return;
        }else if(pkg->id > id){
            maxP = midP;
        }else{
            minP = midP;
        }
    }return;
};
void GarbageCollector::lower_ref(int id){
    if(package_List.get_object_counter()==1){
        package_List.get_data_by_pos(0)->ref_counter-=1;
        return;
    }
    int minP = 0;
    int maxP = package_List.get_object_counter();
    while(minP != maxP){
        int midP = (minP+maxP)/2;
        package* pkg = (package_List.get_data_by_pos(midP));
        if(pkg->id == id){
            pkg->ref_counter-=1;
            return;
        }else if(pkg->id > id){
            maxP = midP;
        }else{
            minP = midP;
        }
    }return;
};

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
        }
};


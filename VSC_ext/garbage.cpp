#include "garbage.hpp"

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
    while(true){
        int i = 0;
        while(package_List.get_node_by_pos(i)->next != NULL){

            package* pkg = (package_List.get_data_by_pos(i));
            if(pkg->ref_counter == 0){
                std::cout<<"to delete: "<<i<<std::endl;
                delete pkg;
                package_List.delete_by_pos(i);
            }else{
                i++;
            }
        }
        //agregar sleep de 15 segundos
    }
};

#include "garbage.hpp"

GarbageCollector* GarbageCollector::recolector = NULL;

GarbageCollector::GarbageCollector(){
    recolector = NULL;
    contador = 0;
}

GarbageCollector* GarbageCollector::getGarbageCollector(){
    if (recolector == NULL){
        recolector = new GarbageCollector();
    }else{
        return recolector;
    }
    return recolector;
}

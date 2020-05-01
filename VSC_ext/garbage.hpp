#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdio.h>
#include "Linked_List.hpp"
#include "vsptr.hpp"


class GarbageCollector{

    private:
        GarbageCollector();
        static GarbageCollector* recolector;
        int contador;
        //lista<VSPtr<T>> punteros;

    public:
        //lista<VSPtr<T>> punteros;
        static GarbageCollector* getGarbageCollector();
};

#endif

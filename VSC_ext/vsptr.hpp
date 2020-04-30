#ifndef VSPTR_HPP
#define VSPTR_HPP
#include <iostream>
template<typename T>
class VSPtr{
private:
    T* dato;
    VSPtr(){
        dato = new T;
    };
public:
    static VSPtr<T> New(){
        return VSPtr<T>();
    };

    void operator =(T dataNueva){
        *(this->dato) = dataNueva;
        std::cout<< *dato << std::endl;
    };
    void operator =(VSPtr<T> dataNueva){
        (this->dato) = dataNueva.dato;
        std::cout<< *dato << std::endl;
    };
};

#endif // VSPTR_HPP

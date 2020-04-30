#ifndef VSPTR_HPP
#define VSPTR_HPP
#include <iostream>
template<typename T>
class VSPtr{
private:

    VSPtr(){
        dato = new T;
    };
public:
    T* dato;

    static VSPtr<T> New(){
        return VSPtr<T>();
    };

    T operator &(){
        return *(dato);
    };

    VSPtr<T> operator *(){
        return *this;
    };

    void operator=(T dataNueva){
        *(this->dato) = dataNueva;
    };

    void operator=(VSPtr<T> dataNueva){
        (this->dato) = dataNueva.dato;
        std::cout<< *dato << std::endl;
    };
};

#endif // VSPTR_HPP

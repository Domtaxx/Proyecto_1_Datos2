#ifndef VSPTRNT_H
#define VSPTRNT_H

#include <stdio.h>
#include <iostream>
class vsptrNT{
public:
    int id;
    vsptrNT(int _id){
        id = _id;
    };
    vsptrNT(){};
    virtual ~vsptrNT(){};
    virtual std::string ret_Type(){
        return "";
    };
    virtual std::string ret_Val(){
        return "";
    };
    virtual std::string ret_Mem_Addr(){
        return "";
    };
    virtual std::string ret_Id(){
        return "";
    };
    virtual std::string ret_Local_id(){
        return "";
    }
};


#endif // VSPTRNT_H

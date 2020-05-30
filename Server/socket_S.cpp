#include "socket_S.h"
#include <climits>
#include <poll.h>
Socket_S::Socket_S(){};
void Socket_S::set_port(int port, std::string ip){
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port); //htons = host to network short (Little Indian o Big Indian)
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr); //ip del server
};

int Socket_S::start(int _port, std::string _ip){
    gar_col = GarbageCollector::getGarbageCollector();
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        std::cerr<<"could not creat socket \n";
        return -1;
    }
    // se crea el puerto del server
    set_port(_port, _ip);
    if(bind(listening, (sockaddr*)&hint, sizeof(hint))==-1){
        std::cerr<<"can't bind to port \n";
        return -2;
    }
    return mark_listening();
};

int Socket_S::mark_listening(){
    listen(listening, SOMAXCONN);
    fd_set master;
    FD_ZERO(&master);
    FD_SET(listening, &master);


    struct pollfd poll_set[32];
    int numfds = 0;
    int max_fd = 0;
    memset(poll_set, '\0', sizeof(poll_set));
    poll_set[0].fd = listening;
    poll_set[0].events = POLLIN;
    numfds++;
    max_fd = listening;


    
    while(true){
        poll(poll_set, numfds, -1);
        for(int i = 0; i < numfds; i++){
            if( poll_set[i].revents & POLLIN){
                //int sock = copy_master.fd_array[i];
                if(poll_set[i].fd == listening){
                    int clientSock = accept(listening, (sockaddr*)&client, &client_Size);
                    poll_set[numfds].fd = clientSock;
                    poll_set[numfds].events = POLLIN;
                    numfds++;
                    std::cout<<"CONNECTED"<<std::endl;
                }else{
                    char buffer[4096];
                    memset(buffer, 0, 4096);
                    int bytesIn = recv(poll_set[i].fd, buffer, 4096, 0);
                    if( bytesIn == 0 ){
                        close(poll_set[i].fd);           
                        poll_set[i].events = 0;
                        for(int j = i; j<numfds; j++){
                            poll_set[j] = poll_set[j + 1];
                        }
                        numfds--;
                        std::cout<<"se elimina un cliente"<<std::endl;
                    }
                    //crear vsp
                    
                    if(buffer[0] == '$'){    
                        vsptrNT ptr;
                        std::string LocalIdStr = "";
                        for(int a = 2; buffer[a] != '*';a++){
                            LocalIdStr+=buffer[a];
                        }
                        try{
                            ptr.localID = std::stoi(LocalIdStr);
                            std::cout<<"se creo un ptr"<<std::endl;
                            if(buffer[1] == 'i'){//int
                                ptr = VSPtr<int>::New();
                            }else if(buffer[1] == 'd'){//double
                                ptr = VSPtr<double>::New();
                            }else if(buffer[1] == 'b'){//bool
                                ptr = VSPtr<bool>::New();
                            }else if(buffer[1] == 'f'){//float
                                ptr = VSPtr<float>::New();
                            }else if(buffer[1] == 'c'){//char
                                ptr = VSPtr<char>::New();
                            }else if(buffer[1] == 'l'){//long
                                ptr = VSPtr<long>::New();
                            }else if(buffer[1] == 'x'){//long long
                                ptr = VSPtr<long long>::New();
                            }else if(buffer[1] == 'e'){//long double
                                ptr = VSPtr<long double>::New();
                            }
                            send(poll_set[i].fd,"VSPtr created", sizeof("VSPtr created"), 0);
                        }catch(...){
                            std::cout<<"no se pudo crear un puntero"<<std::endl;
                            send(poll_set[i].fd,"Error creating VSPtr", sizeof("Error creating VSPtr"),0);
                        }
                           
                    }//asignar valor VSP
                    else if(buffer[0]== '#'){
                        std::string type_Str = ""+buffer[1];
                        std::string new_Value_Str = "";
                        std::string local_Id_Str = "";
                        int a;
                        for(a = 2; buffer[a] != ',';a++){
                            new_Value_Str+=buffer[a];
                        }a++;
                        for(a; buffer[a] != '*'; a++){
                            local_Id_Str += buffer[a];
                        }
                        int local_Id_VSPtr = std::stoi(local_Id_Str);
                        lista<vsptrNT*> list_ptr = gar_col->get_Vsptr_List();
                        for(a = 0; a<list_ptr.get_object_counter(); a++){
                            vsptrNT* ptr = list_ptr.get_data_by_pos(a);
                            if(ptr->localID == local_Id_VSPtr){
                                if(type_Str == "i"){
                                    VSPtr<int>* ptrA = (VSPtr<int>*)ptr; 
                                    *ptrA = std::stoi(new_Value_Str);
                                }else if(type_Str == "d"){
                                    VSPtr<double>* ptrA = (VSPtr<double>*)ptr; 
                                    *ptrA = std::stod(new_Value_Str);
                                }else if(type_Str == "f"){
                                    VSPtr<float>* ptrA = (VSPtr<float>*)ptr; 
                                    *ptrA = std::stof(new_Value_Str);
                                }else if(type_Str == "c"){
                                    VSPtr<char>* ptrA = (VSPtr<char>*)ptr; 
                                    *ptrA = (new_Value_Str).c_str()[0];
                                }else if(type_Str == "b"){
                                    VSPtr<bool>* ptrA = (VSPtr<bool>*)ptr; 
                                    *ptrA = std::stoi(new_Value_Str);
                                }else if(type_Str == "l"){
                                    VSPtr<long>* ptrA = (VSPtr<long>*)ptr; 
                                    *ptrA = std::stol(new_Value_Str);
                                }else if(type_Str == "x"){
                                    VSPtr<long long>* ptrA = (VSPtr<long long>*)ptr; 
                                    *ptrA = std::stoll(new_Value_Str);
                                }else if(type_Str == "e"){
                                    VSPtr<long double>* ptrA = (VSPtr<long double>*)ptr; 
                                    *ptrA = std::stold(new_Value_Str);
                                }
                            }
                        }
                    }//devolver valor dentro del VSPtr(&)
                    else if(buffer[0]== '&'){
                        int pkg_id = -81;
                        int local_Id_VSPtr = -97;
                        std::string msg = "";
                        for(int a = 1; buffer[a] != '*'; a++){
                            local_Id_Str += buffer[a];
                        }
                        local_Id_VSPtr = std::stoi(local_Id_Str);
                        lista<vsptrNT*> list_ptr = gar_col->get_Vsptr_List();
                        lista<package*> list_pkg = gar_col->get_Pkg_List();

                        for(int a = 0; a<list_ptr.get_object_counter(); a++){
                            vsptrNT* ptr = list_ptr.get_data_by_pos(a);
                            if(ptr->localID == local_Id_VSPtr){
                                msg+= ptr->ret_Type()+",";
                                pkg_id = ptr->id;
                                break;
                            }
                        }
                        
                        for(int a = 0; a<list_pkg.get_object_counter(); a++){
                            package* pkg = list_ptr.get_data_by_pos(a);
                            if(pkg.id == pkg_id){
                                msg+=pkg.ret_Val()+"*";
                                break;
                            }
                        }
                        send(poll_set[i].fd,msg.c_str(), sizeof(msg.c_str()),0);
                    }//borrar valor
                    else if(buffer[0]== '~'){
                        
                    }
                }
            }
        }   
    }
};


std::string Socket_S::data_GC(){
    std::string msg;
    for(int i = 0; i < GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter();i++){
            package* pack = GarbageCollector::getGarbageCollector()->get_Pkg_List().get_data_by_pos(i);
            std::string val = pack->ret_Val().c_str();
            std::string tipo = pack->ret_Type().c_str();
            std::string addr = pack->ret_Mem_Addr().c_str();
            std::string id = std::to_string(pack->id);
            std::string ref = std::to_string(pack->ref_counter);
            msg += id+","+ tipo+","+val+","+addr+","+ref;
            if((i+1) == GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter()){
                msg+= "&";
            }else{
                msg+= ".";
            };
    };
    for(int i = 0; i < GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_object_counter();i++){
        vsptrNT* ptr = GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_data_by_pos(i);
        std::string id = ptr->ret_Id().c_str();
        std::string type = ptr->ret_Type().c_str();
        std::string value = ptr->ret_Val().c_str();
        msg += id +","+ type + ","+ value;
        if((i+1) == GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_object_counter()){
            msg+= ";";
        }else{
            msg+= ".";
        };
    };
    return msg;
}
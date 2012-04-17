#ifndef INCLUDED_MANAGE
#define INCLUDED_MANAGE
#include"Cdg.hpp"
#include<cstdlib>
#include<iostream>
class Manage{
public:
        Manage(const int argc,const char* argv[])
                :g(argc,argv)
        {
                err_check();
        }

        static void argc_check(const int argc)
        {
                if(argc<1){
                        missing_ms();
                        std::exit(-1);
                }
        }
        void err_check()
        {
                if(g.err_f){
                        missing_ms();
                        std::exit(-1);
                }
        }
        void code()
        {
                g.make_code();
        }
private:
        static inline void missing_ms()
        {
                std::cerr<<"Parameters are missing.\n"<<"Aborted."<<std::endl;
        }
private:
        Cdg g;
};
#endif

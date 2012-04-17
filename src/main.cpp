#include"manage.hpp"

int main(const int argc,const char* argv[])
{
        Manage::argc_check(argc);
        Manage man(argc,argv);
        man.code();
}

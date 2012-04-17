#ifndef INCLUDED_CGD
#define INCLUDED_CGD
#include<fstream>
#include<vector>
#include<map>
#include<miko/iterator.hpp>
#include<iostream>
#include<boost/lexical_cast.hpp>
#include<cstdlib>

#include<miko/rall_cout.hpp>
class Cdg{
public:
	explicit Cdg(const size_t size,const char* argv[])
		:argc(size),err_f(false)
	{
                std::vector<std::string> param_t;
		std::copy(argv+1,argv+size,miko::emplace_back_inserter(param_t));

                for(std::string& s:param_t){
                        if(s.find('-')!=std::string::npos&&s.find('=')!=std::string::npos){
                                std::string modes;
                                std::string arg;

                                auto first=s.erase(s.begin()+s.find('-'));
                                auto center=s.erase(s.begin()+s.find('=',1));
                        
                                std::copy(first,center,std::back_inserter(modes));
                                std::copy(center,s.end(),std::back_inserter(arg));                

                                mode_arg.insert(std::make_pair(modes,arg));
                        }else{
                                err_f=true;
                                break;
                        }
                }                
	}

        void make_code()
        {
                std::ofstream ofs("test.cpp",std::ios::app);
                if(!ofs.is_open()){std::cerr<<"File can't open"<<std::endl;std::exit(-1);}

                for(auto it=mode_arg.rbegin(); it!=mode_arg.rend(); ++it){
                        if((*it).first=="include")ofs<<std::string("#include<")+(*it).second+std::string(">\n")<<std::endl;
                        else if((*it).first=="define")ofs<<std::string("#define ")+(*it).second+std::string("\n")<<std::endl;
                        else if((*it).first=="if_m")ofs<<std::string("#if ")+(*it).second+std::string("\n#endif\n")<<std::endl;
                        else if((*it).first=="ifdef")ofs<<std::string("#ifdef ")+(*it).second+std::string("\n#endif\n")<<std::endl;
                        else if((*it).first=="ifndef")ofs<<std::string("#ifndef ")+(*it).second+std::string("\n#endif\n")<<std::endl;
                        else if((*it).first=="elif")ofs<<std::string("#elif ")+(*it).second+std::string("\n")<<std::endl;
                        else if((*it).first=="else_m")ofs<<std::string("#else")+(*it).second+std::string("\n#endif\n")<<std::endl;
                        else if((*it).first=="pragma")ofs<<std::string("#pragma ")+(*it).second+std::string("\n")<<std::endl;
                        else if((*it).first=="sharp")ofs<<std::string("#")+std::string("\n")<<std::endl;
                        else if((*it).first=="alignas")ofs<<std::string("\talignas(")+(*it).second+std::string(");\n")<<std::endl;
                        else if((*it).first=="alignof")ofs<<std::string("\talignof(")+(*it).second+std::string(");\n")<<std::endl;
                        else if((*it).first=="asm")ofs<<std::string("\tasm(\"")+(*it).second+std::string("\");\n")<<std::endl;
                        else if((*it).first=="function")ofs<<(*it).second+std::string(" func()\n{\n}")<<std::endl;
                        else if((*it).first=="function_try")ofs<<(*it).second+std::string(" func()try\n{\n}catch(){}\n")<<std::endl;
                        else if((*it).first=="function_throw")ofs<< (*it).second+std::string(" func()throw()\n{\n}\n")<<std::endl;
                        else if((*it).first=="template_function")ofs<<std::string("template<class _Tp>\n")+(*it).second+std::string(" func()\n{\n}\n")<<std::endl;
                        else if((*it).first=="template_class")ofs<<std::string("template<class _Tp>\nclass ")+(*it).second+std::string("{\n};\n")<<std::endl;
                        else if((*it).first=="template_struct")ofs<<std::string("template<class _Tp>\nstruct ")+(*it).second+std::string("{\n};\n")<<std::endl;
                        else if((*it).first=="union")ofs<<std::string("union ")+(*it).second+std::string("{\n};\n")<<std::endl;
                        else if((*it).first=="switch"){
                                size_t i=boost::lexical_cast<int>((*it).second);
                                std::string str("switch( ){\n");
                                for(size_t c=0; c<i; ++c)
                                        str+=std::string("\tcase ")+boost::lexical_cast<std::string>(c)+std::string(":\n\tbreak;\n");
                                str+=std::string("\n}\n");
                                ofs<<str<<std::endl;
                        }
                        else if((*it).first=="for")ofs<<std::string("for(")+(*it).second+std::string("){\n}\n")<<std::endl;
                        else if((*it).first=="range_for")ofs<<std::string("for(")+(*it).second+std::string("){\n}\n")<<std::endl;
                        else if((*it).first=="while")ofs<<std::string("while(")+(*it).second+std::string("){\n}\n")<<std::endl;
                        else if((*it).first=="do")ofs<<std::string("do{\n}while(")+(*it).second+std::string(")\n")<<std::endl;
                        else if((*it).first=="if")ofs<<std::string("if(")+(*it).second+std::string("){\n}\n")<<std::endl;
                        else if((*it).first=="try")ofs<<std::string("try{\n}catch(")+(*it).second+std::string(")\n")<<std::endl;
                        else{std::cerr<<"Parameters are missing.\n"<<"Aborted."<<std::endl;std::exit(-1);}
                }
                ofs.close();
        }
public:
	bool err_f;
private:
	std::multimap<std::string,std::string> mode_arg; // mode and mode of arguments.
	size_t argc;
};
#endif

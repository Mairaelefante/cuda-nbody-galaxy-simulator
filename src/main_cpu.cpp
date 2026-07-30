#include"nbody.hpp"
#include<chrono>
#include<iostream>
int main(int c,char**v){size_t n=c>1?std::stoull(v[1]):2000;int steps=c>2?std::stoi(v[2]):20;std::string out=c>3?v[3]:"cpu.csv";auto p=galaxy(n,42);auto a=std::chrono::steady_clock::now();for(int i=0;i<steps;i++)cpu_step(p,.002f,.03f);auto b=std::chrono::steady_clock::now();save(out,p);std::cout<<"cpu_ms="<<std::chrono::duration<double,std::milli>(b-a).count()<<" wrote="<<out<<'\n';}

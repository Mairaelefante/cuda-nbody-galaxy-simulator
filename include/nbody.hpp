#pragma once
#include<vector>
#include<string>
struct P{float x,y,z,vx,vy,vz,m;};std::vector<P> galaxy(size_t,unsigned);void cpu_step(std::vector<P>&,float,float);void save(const std::string&,const std::vector<P>&);float error(const std::vector<P>&,const std::vector<P>&);double gpu_steps(std::vector<P>&,int,float,float);

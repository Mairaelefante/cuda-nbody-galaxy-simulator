#include"nbody.hpp"
#include<cmath>
void cpu_step(std::vector<P>&p,float dt,float soft){auto n=p;for(size_t i=0;i<p.size();i++){float ax=0,ay=0,az=0;for(size_t j=0;j<p.size();j++)if(i!=j){float x=p[j].x-p[i].x,y=p[j].y-p[i].y,z=p[j].z-p[i].z,d=x*x+y*y+z*z+soft*soft,inv=1/sqrt(d),s=p[j].m*inv*inv*inv;ax+=x*s;ay+=y*s;az+=z*s;}n[i].vx+=ax*dt;n[i].vy+=ay*dt;n[i].vz+=az*dt;n[i].x+=n[i].vx*dt;n[i].y+=n[i].vy*dt;n[i].z+=n[i].vz*dt;}p.swap(n);}

#include"nbody.hpp"
#include<random>
#include<cmath>
#include<fstream>
#include<algorithm>
std::vector<P> galaxy(size_t n,unsigned seed){std::mt19937 r(seed);std::uniform_real_distribution<float>R(.15f,5.f),A(0.f,6.2831853f);std::normal_distribution<float>Z(0.f,.08f),J(0.f,.02f);std::vector<P>v;v.reserve(n);for(size_t i=0;i<n;i++){float q=R(r),a=A(r),s=std::sqrt(1.f/(q+.2f));v.push_back({q*std::cos(a),q*std::sin(a),Z(r),-s*std::sin(a)+J(r),s*std::cos(a)+J(r),J(r)*.2f,1.f/static_cast<float>(n)});}return v;}void save(const std::string&p,const std::vector<P>&v){std::ofstream o(p);o<<"id,x,y,z,vx,vy,vz,mass\n";for(size_t i=0;i<v.size();i++){auto&a=v[i];o<<i<<','<<a.x<<','<<a.y<<','<<a.z<<','<<a.vx<<','<<a.vy<<','<<a.vz<<','<<a.m<<'\n';}}float error(const std::vector<P>&a,const std::vector<P>&b){float e=0;for(size_t i=0;i<a.size();i++){float x=a[i].x-b[i].x,y=a[i].y-b[i].y,z=a[i].z-b[i].z;e=std::max(e,std::sqrt(x*x+y*y+z*z));}return e;}

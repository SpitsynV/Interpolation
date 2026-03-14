#include "task1.h"
//
#include <iostream>

//N=n-1 <-это видимо от непонимания изначальной постановки задачи с фикс deg. возможно вызывает ошибки дальше в коде

void GetCoeficients(int n, const std::vector<double> &x, const std::vector<double> &f, std::vector<double> &coef1, int deg) {
    //n-число узлов!
    double a = x[0];
    double b = x[n-1];
    std::vector<double> ak(n-1,0), bk(n-1,0), ck(n-1,0), dk(n-1,0);
    std::vector<double> zk(n,0);
    std::vector<double> uk(n,0);
    std::vector<std::vector<double>> gk(n,std::vector<double>(n,0.0));

    
   for(int i=0;i<n-1; i++){
        ak[i]= asin((2*x[i+1]-(b+a))/(b-a))-asin((2*x[i]-(b+a))/(b-a));
        bk[i]=ak[i]*(b+a)/2.0-((b-a)/2.0)*(sqrt(1-pow((2*x[i+1]-(b+a))/(b-a),2))-sqrt(1-pow((2.0*x[i]-(b+a))/(b-a),2)));
        ck[i]=(ak[i]*x[i+1]-bk[i])/(x[i+1]-x[i]);
        dk[i]=(bk[i]-ak[i]*x[i])/(x[i+1]-x[i]);
        
    }
    for(int i=0;i<n;i++){
        zk[i]=2*(2*x[i]-(b+a))/(b-a);
    }
    uk[0]=ck[0]*f[0];
    uk[n-1]=dk[n-2]*f[n-1];
    for(int i=1; i<=n-2; i++){
        uk[i]=(ck[i]+dk[i-1])*f[i];
    }
    //
    //std::cout<<ak[1]<<" "<<ak[1]<<" "<<bk[1]<<" "<<ck[1]<<" "<<dk[1]<<" "<<zk[1]<<" "<<uk[1]<<" "<<std::endl;
    //20
    for(int j=0;j<=n-1;j++){
        gk[0][j]=uk[j];
        gk[1][j]=0.5*zk[j]*uk[j];
        for(int i=2;i<=(deg-1);i++){
            gk[i][j]=zk[j]*gk[i-1][j]-gk[i-2][j];
        }
    
    //21
    
    for(int i=0; i<=(deg-1);i++){
        coef1[i]=coef1[i]+gk[i][j];
        }
    }
    coef1[0]*=M_1_PI;
    for(int i=1; i<=(deg-1);i++){
        coef1[i]*=M_2_PI;
        
    }
        
}

    
double GetValue(double point, double a, double b, int n,const std::vector<double>& coef1,int deg ){
    double z=2.0*(2.0*point-(b+a))/(b-a);
    double value=0;
    double T0=0, T1=0;
    double T=0;
    if(deg==0)return 0;
    T0=1;
    T1=z/2;
    value=coef1[0]*T0;
    if(deg>1)value+=coef1[1]*T1;
    for(int i=2;i<=(deg-1);i++){
        T=z*T1-T0;
        value+=coef1[i]*T;
        T0=T1;
        T1=T;
    }
    return value;
}
///странно что второй и последний коэфициенты всегда нулевые
#include "task1.h"
//
#include <iostream>

//N=n-1

void GetCoeficients(int n, const std::vector<double>& x, const std::vector<double>& f, std::vector<double>& coef1) {
    double a = x[0];
    double b = x[n-1];
    int N=n-1;
    std::vector<double> ak(n-1), bk(n-1), ck(n-1), dk(n-1);
    std::vector<double> zk(n);
    std::vector<double> uk(n);
    std::vector<std::vector<double>> gk(n,std::vector<double>(n,0.0));

    
   for(int i=0;i<n-1; i++){
        ak[i]= asin((2*x[i+1]-(b+a))/(b-a))-asin((2*x[i]-(b+a))/(b-a));
        bk[i]=ak[i]*(b+a)/2-((b-a)/2)*(sqrt(1-pow((2*x[i+1]-(b+a))/(b-a),2))-sqrt(1-pow((2*x[i]-(b+a))/(b-a),2)));
        ck[i]=(ak[i]*x[i+1]-bk[i])/(x[i+1]-x[i]);
        dk[i]=(bk[i]-ak[i]*x[i])/(x[i+1]-x[i]);
        
    }
    for(int i=0;i<n;i++){
        zk[i]=2*(2*x[i]-(b+a))/(b-a);
    }
    uk[0]=ck[0]*f[0];
    uk[n-1]=dk[n-2]*f[n-1];
    for(int i=1; i<N-1; i++){
        uk[i]=(ck[i]+dk[i-1])*f[i];
    }
    //
    //std::cout<<ak[1]<<" "<<ak[1]<<" "<<bk[1]<<" "<<ck[1]<<" "<<dk[1]<<" "<<zk[1]<<" "<<uk[1]<<" "<<std::endl;
    //20
    for(int j=0;j<=N;j++){
        gk[0][j]=uk[j];
        gk[1][j]=1/2*zk[j]*uk[j];
        for(int i=2;i<=n-1;i++){
            gk[i][j]=zk[j]*gk[i-1][j]-gk[i-2][j];
        }
    
    //21
    
    for(int i=0; i<=n-1;i++){
        coef1[i]=coef1[i]+gk[i][j];
        }
    }
    coef1[0]*=M_1_PI;
    for(int i=1; i<=n-1;i++){
        coef1[i]*=M_2_PI;
        
    }
        
}

    
double GetValue(double point, double a, double b, int n, const std::vector<double>&x,const std::vector<double>& coef1 ){
    double z=2*(2*point-(b+a))/(b-a);
    double value=0;
    std::vector<double>T(n, 0.0);
    T[0]=1;
    T[1]=z/2;
    value=coef1[0]*T[0]+coef1[1]*T[1];
    for(int i=2;i<=n-1;i++){
        T[i]=z*T[i-1]-T[i-2];
        value+=coef1[i]*T[i];
    }
    return value;
}
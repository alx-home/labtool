// This is brl/bbas/bsta/bsta_beta.txx
#ifndef bsta_beta_txx_
#define bsta_beta_txx_
//:
// \file

#include "bsta_beta.h"
#include <vnl/algo/vnl_rpoly_roots.h>
#include <vnl/vnl_beta.h>
#include <vnl/vnl_bignum.h>

// Factorial
static inline vnl_bignum factorial(int n)
{
  if (n <= 1)
    return vnl_bignum(1);
  else
    return n * factorial(n-1);
}


//: constructs from a set of sample values
template <class T>
bsta_beta<T>::bsta_beta(vcl_vector<T> x)
{
  T mean=0;
  T var=0;

  for (unsigned i=0; i<x.size(); i++) {
    mean+=x[i];
  }

  mean/=x.size();

  for (unsigned i=0; i<x.size(); i++) {
    T diff = x[i]-mean;
    var+=diff*diff;
  }

  var/=x.size();

  T t = (mean*(1-mean)/var)-1;
  alpha_=mean*t;
  beta_=(1-mean)*t;
}

template <class T>
bool bsta_beta<T>::bsta_beta_from_moments(T mean, T var, T& alpha, T& beta)
{
  if (var == 0)
    return false;

  int flag_special=0;

  if (mean<0.5)
  {
    if (mean*mean*mean-mean*mean+mean*var+var>0)
      flag_special=1;
  }
  else
  {
    if (mean*mean*mean-2*mean*mean+mean*(1+var)-2*var<0)
      flag_special=2;
  }

  if (flag_special==1)
  {
    alpha=T(1);
    vnl_vector<double> pts(4);
    pts[0]=1;pts[1]=3;pts[2]=4-1/var;pts[3]=2;
    vnl_rpoly_roots r(pts);
    vnl_vector<double> roots=r.realroots(0.1);
    bool flag=false;
    for (unsigned i=0;i<roots.size();i++)
    {
      if (roots[i]>0)
      {
        flag=true;
        beta=T(roots[i]);
      }
    }
    return flag;
  }
  else if (flag_special==2)
  {
    beta=T(1);
    vnl_vector<double> pts(4);
    pts[0]=1;pts[1]=3;pts[2]=4-1/var;pts[3]=2;
    vnl_rpoly_roots r(pts);
    vnl_vector<double> roots=r.realroots(0.1);

    bool flag=false;
    for (unsigned i=0;i<roots.size();i++)
    {
      if (roots[i]>0)
      {
        flag=true;
        alpha=T(roots[i]);
      }
    }
    return flag;
  }
  else
  {
    T t = mean*(1-mean)/var-1;
    alpha=mean*t;
    beta=(1-mean)*t;
  }
#if 0 // commented out ...
  T det=vcl_sqrt(1-12*var);
  if (mean<=(1-det)/2)
  {
    alpha=T(1);
    vnl_vector<double> pts(4);
    pts[0]=1;pts[1]=3;pts[2]=4-1/var;pts[3]=2;
    vnl_rpoly_roots r(pts);
    vnl_vector<double> roots=r.realroots(0.1);

    bool flag=false;
    for (unsigned i=0;i<roots.size();i++)
    {
      if (roots[i]>0)
      {
        flag=true;
        beta=T(roots[i]);
      }
    }
    return flag;
  }
  else if (mean>=(1+det)/2)
  {
    beta=T(1);
    vnl_vector<double> pts(4);
    pts[0]=1;pts[1]=3;pts[2]=4-1/var;pts[3]=2;
    vnl_rpoly_roots r(pts);
    vnl_vector<double> roots=r.realroots(0.1);

    bool flag=false;
    for (unsigned i=0;i<roots.size();i++)
    {
      if (roots[i]>0)
      {
        flag=true;
        alpha=T(roots[i]);
      }
    }
    return flag;
  }
  else
  {
    T t = mean*(1-mean)/var-1;
    alpha=mean*t;
    beta=(1-mean)*t;
  }
#endif // 0
  return true;
}

//: pre: x should be in [0,1]
template <class T>
T bsta_beta<T>::prob_density(T x) const
{
  if (x<T(0)||x>T(1))
      return 0;
  else
  {
    T a = (T)vnl_log_beta(alpha_,beta_);
    T b=0;
    if (x==0 )//&& alpha_==T(1))
      b=0;
    else
      b = (alpha_-1)*vcl_log(x) ;
    T c=0;
    if (x==1 )//&& beta_==T(1))
      c=0;
    else
      c = (beta_-1)*vcl_log(1-x) ;

    if (b+c-a<-60)
      return 0;
    else if (b+c-a>60)
      return 100;
    else
      return vcl_exp(b+c-a);
  }
}

template <class T>
T bsta_beta<T>::distance(T x) const
{
  T mean =alpha_/(alpha_+beta_);
  if (x==0 && alpha_==1)
    return (T)((beta_-1)*vcl_log((1-x)/(1-mean)));
  else if (x==1 && beta_==1)
    return (T)((alpha_-1)*vcl_log(x/mean));
  else
    return (T)((alpha_-1)*vcl_log(x/mean)+(beta_-1)*vcl_log((1-x)/(1-mean)));
}

// cumulative distribution function
template <class T>
T bsta_beta<T>::cum_dist_funct(T x) const
{
  unsigned a = static_cast<unsigned>(alpha_);
  unsigned b = static_cast<unsigned>(beta_);
  T Ix=T(0);
  T val;
  for (unsigned j=a; j<=a+b-1; j++) {
    val = factorial(a+b-1)/(factorial(j)*factorial(a+b-1-j));
    val *= vcl_pow(x,T(j))*vcl_pow(1-x, T(a+b-1-j));
    Ix+=val;
  }
  return Ix;
}

#undef BSTA_BETA_INSTANTIATE
#define BSTA_BETA_INSTANTIATE(T) \
template class bsta_beta<T >

#endif

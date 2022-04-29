#include "EX1.h"

complex_num sum_cmplx(complex_num a, complex_num b){
	complex_num c = {a.re+b.re,a.im+b.im};
	return c;
}

complex_num mul_cmplx(complex_num a, complex_num b){
	complex_num c = {a.re*b.re-a.im*b.im, a.re*b.im+b.re*b.im};
	return c;
}

complex_num sub_cmplx(complex_num a, complex_num b){
	complex_num c = {a.re-b.re, a.im-b.im};
	return c;
}

complex_num div_cmplx(complex_num a, complex_num b){
	float mod =( b.re)*(b.re) +( b.im)*(b.im);
	complex_num c = {0,0};
	if(mod == 0) return c;
	else{
		complex_num conj = {b.re, -b.im};
		c.re = mul_cmplx(a, conj).re/mod;
		c.im = mul_cmplx(a, conj).im/mod;
	}
}
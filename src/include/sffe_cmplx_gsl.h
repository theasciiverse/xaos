/*/////////////////////////////////////////////////////////////////////////////////////
// project : sFFe ( SegFault (or Segmentation Fault :) ) formula evalutaor )
// author  : Mateusz Malczak ( mateusz@malczak.info )
// wpage   :
/////////////////////////////////////////////////////////////////////////////////////*/
#ifndef SFFE_CMPLX_GSL_H
#define SFFE_CMPLX_GSL_H

#ifdef SFFE_CMPLX_GSL

#include "sffe.h"

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

#define sffnctscount 43
#define sfvarscount 6
#define cmplxset(c,r,i) GSL_SET_COMPLEX(&c,r,i)
#define real(c) GSL_REAL((c))
#define imag(c) GSL_IMAG((c))

#ifdef __cplusplus
extern "C" {
#endif

sfarg *sfadd(sfarg * const p, void *payload);	/*  +  */
sfarg *sfsub(sfarg * const p, void *payload);	/*  -  */
sfarg *sfmul(sfarg * const p, void *payload);	/*  *  */
sfarg *sfdiv(sfarg * const p, void *payload);	/*  /  */
sfarg *sfsin(sfarg * const p, void *payload);	/* sin */
sfarg *sfcos(sfarg * const p, void *payload);	/* cos */
sfarg *sftan(sfarg * const p, void *payload);	/* tan */
sfarg *sfcot(sfarg * const p, void *payload);	/* ctan */
sfarg *sfasin(sfarg * const p, void *payload);	/* asin */
sfarg *sfacos(sfarg * const p, void *payload);	/* acos */
sfarg *sfatan(sfarg * const p, void *payload);	/* atan */
sfarg *sfacot(sfarg * const p, void *payload);	/* actan */
sfarg *sfatan2(sfarg * const p, void *payload);	/* atan2 */
sfarg *sfsinh(sfarg * const p, void *payload);	/* sinh */
sfarg *sfcosh(sfarg * const p, void *payload);	/* cosh */
sfarg *sftanh(sfarg * const p, void *payload);	/* tanh */
sfarg *sfcoth(sfarg * const p, void *payload);	/* ctanh */
sfarg *sfexp(sfarg * const p, void *payload);	/* exp */
sfarg *sflog(sfarg * const p, void *payload);	/* log */
sfarg *sflog10(sfarg * const p, void *payload);	/* log10 */
sfarg *sflog2(sfarg * const p, void *payload);	/* log2 */
sfarg *sflogN(sfarg * const p, void *payload);	/* logN */
sfarg *sfpow(sfarg * const p, void *payload);	/* csflx pow */
sfarg *sfpowd(sfarg * const p, void *payload);	/* double pow */
sfarg *sfpowi(sfarg * const p, void *payload);	/* double pow */
sfarg *sfpowdc(sfarg * const p, void *payload);	/* double to csflx pow */
sfarg *sfsqr(sfarg * const p, void *payload);	/* sqr */
sfarg *sfsqrt(sfarg * const p, void *payload);	/* sqrt */
sfarg *sfrtni(sfarg * const p, void *payload);	/* rtni */
sfarg *sfinv(sfarg * const p, void *payload);	/* cinv */
sfarg *sfceil(sfarg * const p, void *payload);	/* ceil */
sfarg *sffloor(sfarg * const p, void *payload);	/* floor */
sfarg *sfabs(sfarg * const p, void *payload);	/* abs - |z| */
sfarg *sfre(sfarg * const p, void *payload);	/* RE */
sfarg *sfim(sfarg * const p, void *payload);	/* IM */
sfarg *sfrabs(sfarg * const p, void *payload);	/* abs - real numbers */
sfarg *sfrand(sfarg * const p, void *payload);	/* rand */
/*const eval*/
void sfcPI(sfNumber * cnst);
void sfcPI2(sfNumber * cnst);
void sfc2PI(sfNumber * cnst);
void sfcE(sfNumber * cnst);
void sfcI(sfNumber * cnst);
void sfcRND(sfNumber * cnst);

#ifdef __cplusplus
}
#endif

/* all available function (function pointer, number of parameters, name )*/
extern const sffunction sfcmplxfunc[sffnctscount];
/* all available buildin variables */
extern const char sfcnames[sfvarscount][5];
/* available variables function pointers */
extern const cfptr sfcvals[sfvarscount];

#endif
#endif

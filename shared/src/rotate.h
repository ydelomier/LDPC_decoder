#include "config.h"

////////////////////////////////////////////////////////////////////////////////

inline void dumpllr(TYPE_LLRS a)
{
	for(int i=0; i<Q; i+=1)
	{
		LLR llr = a.range(8 * (i+1) - 1, 8 * i);
		cout << llr << " ";
	} cout << endl;
}


inline MSG qmin(MSG a, MSG b){
	return (a < b) ? a : b;
}


inline MSG qmax(MSG a, MSG b){
	return (a > b) ? a : b;
}

//TYPE_MSGS vTemp    = min1;
//min1               = VECTOR_MIN( absContr[j],        min1);
//min2               = VECTOR_MIN( absContr[j], vTemp, min2);

inline MSG qmin(MSG msg, MSG min1, MSG min2){
	MSG max = qmax(msg, min1);
	MSG min = qmin(min2, max);
//	cout << " + value = " << msg.to_int()  << " | min1 = " << min1.to_int()  << " | min2 = " << min2.to_int() << endl;
//	cout << " + max   = " << max.to_int()  << " | min  = " << min.to_int() << endl;
	return min;
}


inline bool qsign(LLR value){
	//(value < 0) ? false : true;
	//return ! value[LLR_BITS-1];
	return value <= 0 ? 0 : 1;
}

inline MSG qabs(MSG value){
	MSG positif = +value;
	MSG negatif = -value;
	MSG result  = (value < 0) ? negatif : positif;
	return result;//qmin(result, 63);
//	return (value.test( 7 ) == 1) ? negatif : positif;
}

inline LLR qadd(LLR a, MSG b){
  sc_bigint<LLR_BITS+1> r = ((sc_bigint<LLR_BITS+1>)a) + b;
  if     ( r > LLR_MAXV ) return LLR_MAXV;
  else if( r < LLR_MINV ) return LLR_MINV;
  else return r;
}

inline LLR qsub(LLR a, MSG b){
  sc_bigint<LLR_BITS+1> r = ((sc_bigint<LLR_BITS+1>)a) - b;
  if     ( r > LLR_MAXV ) return LLR_MAXV;
  else if( r < LLR_MINV ) return LLR_MINV;
  else return r;
}

inline MSG qinv(MSG value, BIT sign){
	MSG positif = +value;
	MSG negatif = -value;
	return (sign == 0) ? positif : negatif;
}


inline LLR nms(MSG b){
  return b - (b >> 2);
}

////////////////////////////////////////////////////////////////////////////////


inline TYPE_LLRS VECTOR_ADD(TYPE_LLRS a, TYPE_MSGS b)
{
	TYPE_LLRS c;
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(8 * (i+1) - 1, 8 * i);
		MSG ob = b.range(8 * (i+1) - 1, 8 * i);
		LLR oc = qadd( oa, ob );
		//if( qsign(oa) != qsign(oc) ) printf("oa (%d) + ob(%d) => oc (%d)\n", (int)oa.to_int(), (int)ob.to_int(), (int)oc.to_int());
		//if( qsign(oc) > 0 ) printf("oa (%d) + ob(%d) => oc (%d)\n", (int)oa.to_int(), (int)ob.to_int(), (int)oc.to_int());
		c.range(8 * (i + 1) - 1, 8 * i) = oc;
	}
	return c;
}


inline TYPE_LLRS VECTOR_SUB(TYPE_LLRS a, TYPE_MSGS b)
{
	TYPE_LLRS c;
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(8 * (i+1) - 1, 8 * i);
		MSG ob = b.range(8 * (i+1) - 1, 8 * i);
		LLR oc = qsub( oa, ob );
		c.range(8 * (i+1) - 1, 8 * i) = oc;
	}
	return c;
}


inline TYPE_MSGS VECTOR_ABS(TYPE_MSGS a)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(8 * (i+1) - 1, 8 * i);
		c.range(8 * (i+1) - 1, 8 * i) = qabs( oa );
	}
	return c;
}


inline TYPE_BITS VECTOR_SIGN(TYPE_LLRS a)
{
	TYPE_BITS c;
	for(int i=0; i<Q; i+=1)
	{
		LLR llr = a.range(8 * (i+1) - 1, 8 * i);
		c[i] = qsign( llr );
	}
	return c;
}

inline TYPE_BITS VECTOR_HARD(TYPE_LLRS a)
{
	TYPE_BITS c;
	for(int i=0; i<Q; i+=1)
	{
		LLR llr = a.range(8 * (i+1) - 1, 8 * i);
		c[i] = llr > 0;//qsign( llr );
	}
	return c;
}


inline TYPE_MSGS VECTOR_MAX(TYPE_MSGS a, TYPE_MSGS b)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
		sc_bigint<8> oa = a.range(8 * (i+1) - 1, 8 * i);
		sc_bigint<8> ob = b.range(8 * (i+1) - 1, 8 * i);
		c.range(8 * (i+1) - 1, 8 * i) = qmax( oa, ob );
//		c.range(8 * (i+1) - 1, 8 * i) = oc;
	}
	return c;
}

inline TYPE_MSGS VECTOR_MIN(TYPE_MSGS a, TYPE_MSGS b)
{
	sc_bigint<192> c;
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(8 * (i+1) - 1, 8 * i);
		MSG ob = b.range(8 * (i+1) - 1, 8 * i);
		c.range(8 * (i+1) - 1, 8 * i) = qmin( oa, ob );
	}
	return c;
}

inline TYPE_MSGS VECTOR_MIN(TYPE_MSGS abs, TYPE_MSGS tmp, TYPE_MSGS min)
{
	sc_bigint<192> c;
	for(int i=0; i<Q; i+=1)
	{
		MSG ov = abs.range(8 * (i+1) - 1, 8 * i);
		MSG ot = tmp.range(8 * (i+1) - 1, 8 * i);
		MSG om = min.range(8 * (i+1) - 1, 8 * i);
		c.range(8 * (i+1) - 1, 8 * i) = qmin( ov, ot, om );
	}
	return c;
}

inline TYPE_BITS VECTOR_XOR(TYPE_BITS a, TYPE_BITS b)
{
	TYPE_BITS c = a ^ b;
	return c;
}


inline TYPE_MSGS VECTOR_SIGN(TYPE_MSGS a, TYPE_BITS b)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
		bool ob = (b[i] == 1);
		MSG oa = a.range(8 * (i+1) - 1, 8 * i);
		MSG positif = +oa;
		MSG negatif = -oa;
		MSG oc = (ob) ? positif : negatif;
		c.range(8 * (i+1) - 1, 8 * i) = oc;
	}
	return c;
}


inline TYPE_BITS VECTOR_EQUAL(TYPE_LLRS a, TYPE_LLRS b)
{
	TYPE_BITS c;
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(8 * (i+1) - 1, 8 * i);
		LLR ob = b.range(8 * (i+1) - 1, 8 * i);
		c[i] = (oa == ob) ? 1 : 0;
	}
	return c;
}


inline TYPE_MSGS VECTOR_CMOV(TYPE_BITS c, TYPE_MSGS a, TYPE_MSGS b)
{
	TYPE_MSGS d;
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(8 * (i+1) - 1, 8 * i);
		MSG ob = b.range(8 * (i+1) - 1, 8 * i);
		MSG oc = (c[i] == 1) ? oa : ob;
		d.range(8 * (i+1) - 1, 8 * i) = oc;
	}
	return d;
}


inline TYPE_BITS VECTOR_ZERO( )
{
	TYPE_BITS c = 0;
	return c;
}


inline TYPE_MSGS VECTOR_SET1(MSG _v)
{
	MSG       v = _v;
	TYPE_MSGS c = (v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
	return c;
}

TYPE_LLRS rotate_left(TYPE_LLRS a, sc_uint<5> b)
{
	#pragma HLS INLINE off
	switch ( b ){
		case 0:  return a;
		case 1:  return (a.range(183, 0), a.range(191, 184));
		case 2:  return (a.range(175, 0), a.range(191, 176));
		case 3:  return (a.range(167, 0), a.range(191, 168));
		case 4:  return (a.range(159, 0), a.range(191, 160));
		case 5:  return (a.range(151, 0), a.range(191, 152));
		case 6:  return (a.range(143, 0), a.range(191, 144));
		case 7:  return (a.range(135, 0), a.range(191, 136));
		case 8:  return (a.range(127, 0), a.range(191, 128));
		case 9:  return (a.range(119, 0), a.range(191, 120));
		case 10: return (a.range(111, 0), a.range(191, 112));
		case 11: return (a.range(103, 0), a.range(191, 104));
		case 12: return (a.range( 95, 0), a.range(191,  96));
		case 13: return (a.range( 87, 0), a.range(191,  88));
		case 14: return (a.range( 79, 0), a.range(191,  80));
		case 15: return (a.range( 71, 0), a.range(191,  72));
		case 16: return (a.range( 63, 0), a.range(191,  64));
		case 17: return (a.range( 55, 0), a.range(191,  56));
		case 18: return (a.range( 47, 0), a.range(191,  48));
		case 19: return (a.range( 39, 0), a.range(191,  40));
		case 20: return (a.range( 31, 0), a.range(191,  32));
		case 21: return (a.range( 23, 0), a.range(191,  24));
		case 22: return (a.range( 15, 0), a.range(191,  16));
		case 23: return (a.range(  7, 0), a.range(191,   8));
        default: return a;
	}
}

TYPE_LLRS rotate_right(TYPE_LLRS a, sc_uint<5> b)
{
	return rotate_left(a, 24 - b);
/*
	switch ( b ){
		case 0:  return a;
		case 1:  return (a.range(  7, 0), a.range(191,  8));
		case 2:  return (a.range( 15, 0), a.range(191, 16));
		case 3:  return (a.range( 23, 0), a.range(191, 24));
		case 4:  return (a.range( 31, 0), a.range(191, 32));
		case 5:  return (a.range( 39, 0), a.range(191, 40));
		case 6:  return (a.range( 47, 0), a.range(191, 48));
		case 7:  return (a.range( 55, 0), a.range(191, 56));
		case 8:  return (a.range( 63, 0), a.range(191, 64));
		case 9:  return (a.range( 71, 0), a.range(191, 72));
		case 10: return (a.range( 79, 0), a.range(191, 80));
		case 11: return (a.range( 87, 0), a.range(191, 88));
		case 12: return (a.range( 95, 0), a.range(191, 96));
		case 13: return (a.range(103, 0), a.range(191, 104));
		case 14: return (a.range(111, 0), a.range(191, 112));
		case 15: return (a.range(119, 0), a.range(191, 120));
		case 16: return (a.range(127, 0), a.range(191, 128));
		case 17: return (a.range(135, 0), a.range(191, 136));
		case 18: return (a.range(143, 0), a.range(191, 144));
		case 19: return (a.range(151, 0), a.range(191, 152));
		case 20: return (a.range(159, 0), a.range(191, 160));
		case 21: return (a.range(167, 0), a.range(191, 168));
		case 22: return (a.range(175, 0), a.range(191, 176));
		case 23: return (a.range(183, 0), a.range(191, 184));
        default: return a;
	}
*/
}

inline TYPE_MSGS NMS(TYPE_MSGS a)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(8 * (i+1) - 1, 8 * i);
		c.range(8 * (i+1) - 1, 8 * i) = nms( oa );
	}
	return c;
}

#ifndef VECTOR
#define VECTOR

#include "scalar.h"

inline void SHOW_LLR_BIT(TYPE_LLRS a)
{
	printf("LLR : ");
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(LLR_BITS * (i+1) - 1, LLR_BITS * i);
		int c = oa.to_int() >= 0 ? 1 : 0;
		printf("%3d ", c);
	}
	printf("\n");
}

inline void SHOW(TYPE_LLRS a)
{
	printf("LLR : ");
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(LLR_BITS * (i+1) - 1, LLR_BITS * i);
		printf("%3d ", oa.to_int());
	}
	printf("\n");
}

inline void SHOW(TYPE_LLRS a, std::string m)
{
	printf("LLR [%s]: ", m.c_str());
	for(int i=0; i<Q; i+=1)
	{
		LLR oa = a.range(LLR_BITS * (i+1) - 1, LLR_BITS * i);
		printf("%3d ", oa.to_int());
	}
	printf("\n");
}

inline void SHOW(TYPE_MSGS a)
{
	printf("MSG : ");
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		printf("%3d ", oa.to_int());
	}
	printf("\n");
}

#if MSG_BITS != LLR_BITS
inline void SHOW(TYPE_MSGS a, std::string m)
{
	printf("MSG [%s]: ", m.c_str());
	for(int i=0; i<Q; i+=1)
	{
		MSG oa = a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		printf("%3d ", oa.to_int());
	}
	printf("\n");
}
#endif

inline void SHOW(TYPE_BITS a, std::string m)
{
	printf("BIT [%s]: ", m.c_str());
	for(int i=0; i<Q; i+=1)
	{
		printf("%3d ", (int)a[i]);
	}
	printf("\n");
}


inline void SHOW(TYPE_BITS a)
{
	printf("BIT : ");
	for(int i=0; i<Q; i+=1)
	{
		printf("%3d ", (int)a[i]);
	}
	printf("\n");
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_LLRS VECTOR_ADD(TYPE_LLRS a, TYPE_MSGS b)
{
//#pragma HLS INLINE off
//#pragma HLS PIPELINE
	TYPE_LLRS c;
	for(int i = 0; i < Q; i += 1)
	{
		#pragma HLS UNROLL
		LLR oa = a.range(LLR_BITS * (i+1) - 1, LLR_BITS * i);
		MSG ob = b.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		LLR oc = qadd( oa, ob );
		c.range(LLR_BITS * (i + 1) - 1, LLR_BITS * i) = oc;
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_LLRS VECTOR_SUB(TYPE_LLRS a, TYPE_MSGS b)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE
	TYPE_LLRS c;
	for(int i = 0; i < Q; i += 1)
	{
//#pragma HLS PIPELINE
#pragma HLS UNROLL
		LLR oa = a.range(LLR_BITS * (i+1) - 1, LLR_BITS * i);
		MSG ob = b.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		LLR oc = qsub( oa, ob );
		c.range(LLR_BITS * (i + 1) - 1, LLR_BITS * i) = oc;
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_ABS(TYPE_LLRS a)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE off
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
		LLR oa = a.range(LLR_BITS * (i + 1) - 1, LLR_BITS * i);
		c.range(MSG_BITS * (i + 1) - 1, MSG_BITS * i) = qabs( oa );
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_BITS VECTOR_SIGN(TYPE_LLRS a)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE off
	TYPE_BITS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
		LLR llr = a.range(LLR_BITS * (i + 1) - 1, LLR_BITS * i);
		c[i] = qsign( llr );
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_BITS VECTOR_HARD(TYPE_LLRS a)
{
//#pragma HLS INLINE off
//#pragma HLS PIPELINE
	TYPE_BITS c;
	for(int i = 0; i < Q; i += 1)
	{
#pragma HLS UNROLL
		LLR llr = a.range(LLR_BITS * (i + 1) - 1, LLR_BITS * i);
		c[i] = llr >= 0;//qsign( llr );
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_MAX(TYPE_MSGS a, TYPE_MSGS b)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
		MSG oa = a.range(MSG_BITS * (i + 1) - 1, MSG_BITS * i);
		MSG ob = b.range(MSG_BITS * (i + 1) - 1, MSG_BITS * i);
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = qmax( oa, ob );
//		c.range(8 * (i+1) - 1, 8 * i) = oc;
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_MIN(TYPE_MSGS a, TYPE_MSGS b)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
//#pragma HLS PIPELINE
		MSG oa = a.range(MSG_BITS * (i + 1) - 1, MSG_BITS * i);
		MSG ob = b.range(MSG_BITS * (i + 1) - 1, MSG_BITS * i);
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = qmin( oa, ob );
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_MIN(TYPE_MSGS abs, TYPE_MSGS tmp, TYPE_MSGS min)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
//#pragma HLS PIPELINE
		MSG ov = abs.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG ot = tmp.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG om = min.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = qmin( ov, ot, om );
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_BITS VECTOR_XOR(TYPE_BITS a, TYPE_BITS b)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE off
	TYPE_BITS c = a ^ b;
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_SIGN(TYPE_MSGS a, TYPE_BITS b)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE off
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
		bool ob = (b[i] == 1);
		MSG oa = a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG positif = +oa;
		MSG negatif = -oa;
		MSG oc = (ob) ? positif : negatif;
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = oc;
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_BITS VECTOR_EQUAL(TYPE_MSGS a, TYPE_MSGS b)
{
//#pragma HLS PIPELINE
//#pragma HLS INLINE off
	TYPE_BITS c;
	for(int i=0; i<Q; i+=1)
	{
#pragma HLS UNROLL
		MSG oa = a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG ob = b.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		c[i] = (oa == ob) ? 1 : 0;
	}
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_CMOV(const TYPE_BITS c, const TYPE_MSGS a, const TYPE_MSGS b)
{
//#pragma HLS INLINE off
//#pragma HLS PIPELINE
	//SHOW( c, "CMON:C" );
	//SHOW( a, "CMON:A" );
	//SHOW( b, "CMON:B" );
	TYPE_MSGS d;
	for(int i = 0; i < Q; i += 1)
	{
		#pragma HLS UNROLL
		MSG oa = (MSG)a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG ob = (MSG)b.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		MSG oc = (c[i] == 1) ? oa : ob;
		d.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = oc;
	}
	//SHOW( d, "CMON:d" );
	return d;
}


inline TYPE_BITS VECTOR_ZERO( )
{
	TYPE_BITS c = 0;
	return c;
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
inline TYPE_MSGS VECTOR_SET1(MSG _v)
{
	MSG       v = _v;
	TYPE_MSGS c;
	for(int i = 0; i < Q; i += 1)
	{
		#pragma HLS UNROLL
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = v;
	}
	return c;
}

// TYPE_LLRS rotate_left(TYPE_LLRS a, sc_uint<5> b)
// {
// 	#pragma HLS INLINE off
// 	switch ( b ){
// 		case 0:  return a;
// 		case 1:  return (a.range(183, 0), a.range(191, 184));
// 		case 2:  return (a.range(175, 0), a.range(191, 176));
// 		case 3:  return (a.range(167, 0), a.range(191, 168));
// 		case 4:  return (a.range(159, 0), a.range(191, 160));
// 		case 5:  return (a.range(151, 0), a.range(191, 152));
// 		case 6:  return (a.range(143, 0), a.range(191, 144));
// 		case 7:  return (a.range(135, 0), a.range(191, 136));
// 		case 8:  return (a.range(127, 0), a.range(191, 128));
// 		case 9:  return (a.range(119, 0), a.range(191, 120));
// 		case 10: return (a.range(111, 0), a.range(191, 112));
// 		case 11: return (a.range(103, 0), a.range(191, 104));
// 		case 12: return (a.range( 95, 0), a.range(191,  96));
// 		case 13: return (a.range( 87, 0), a.range(191,  88));
// 		case 14: return (a.range( 79, 0), a.range(191,  80));
// 		case 15: return (a.range( 71, 0), a.range(191,  72));
// 		case 16: return (a.range( 63, 0), a.range(191,  64));
// 		case 17: return (a.range( 55, 0), a.range(191,  56));
// 		case 18: return (a.range( 47, 0), a.range(191,  48));
// 		case 19: return (a.range( 39, 0), a.range(191,  40));
// 		case 20: return (a.range( 31, 0), a.range(191,  32));
// 		case 21: return (a.range( 23, 0), a.range(191,  24));
// 		case 22: return (a.range( 15, 0), a.range(191,  16));
// 		case 23: return (a.range(  7, 0), a.range(191,   8));
//         default: return a;
// 	}
// }

// inline TYPE_LLRS rotate_right(TYPE_LLRS a, sc_uint<5> b)
// {
// 	return rotate_left(a, 24 - b);
// /*
// 	switch ( b ){
// 		case 0:  return a;
// 		case 1:  return (a.range(  7, 0), a.range(191,  8));
// 		case 2:  return (a.range( 15, 0), a.range(191, 16));
// 		case 3:  return (a.range( 23, 0), a.range(191, 24));
// 		case 4:  return (a.range( 31, 0), a.range(191, 32));
// 		case 5:  return (a.range( 39, 0), a.range(191, 40));
// 		case 6:  return (a.range( 47, 0), a.range(191, 48));
// 		case 7:  return (a.range( 55, 0), a.range(191, 56));
// 		case 8:  return (a.range( 63, 0), a.range(191, 64));
// 		case 9:  return (a.range( 71, 0), a.range(191, 72));
// 		case 10: return (a.range( 79, 0), a.range(191, 80));
// 		case 11: return (a.range( 87, 0), a.range(191, 88));
// 		case 12: return (a.range( 95, 0), a.range(191, 96));
// 		case 13: return (a.range(103, 0), a.range(191, 104));
// 		case 14: return (a.range(111, 0), a.range(191, 112));
// 		case 15: return (a.range(119, 0), a.range(191, 120));
// 		case 16: return (a.range(127, 0), a.range(191, 128));
// 		case 17: return (a.range(135, 0), a.range(191, 136));
// 		case 18: return (a.range(143, 0), a.range(191, 144));
// 		case 19: return (a.range(151, 0), a.range(191, 152));
// 		case 20: return (a.range(159, 0), a.range(191, 160));
// 		case 21: return (a.range(167, 0), a.range(191, 168));
// 		case 22: return (a.range(175, 0), a.range(191, 176));
// 		case 23: return (a.range(183, 0), a.range(191, 184));
//         default: return a;
// 	}
// */
// }

inline TYPE_MSGS NMS(const TYPE_MSGS a)
{
	TYPE_MSGS c;
	for(int i=0; i<Q; i+=1)
	{
		const MSG oa = (MSG)a.range(MSG_BITS * (i+1) - 1, MSG_BITS * i);
		c.range(MSG_BITS * (i+1) - 1, MSG_BITS * i) = nms( oa );
	}
	return c;
}

#endif

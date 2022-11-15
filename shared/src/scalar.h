#ifndef SCALAR
#define SCALAR

//#define REMOVE_SATS


inline void SHOW(LLR a)
{
	printf("LLR : ");
	printf("%3d ", (int)a.to_int());
	printf("%3d ", (int)a.to_int());
	printf("\n");
}

inline void SHOW(LLR a, std::string m)
{
	printf("LLR [%s]: ", m.c_str());
	printf("%3d ", (int)a.to_int());
	printf("%3d ", (int)a.to_int());
	printf("\n");
}

inline void SHOW(MSG a, std::string m)
{
	printf("MSG [%s]: ", m.c_str());
	printf("%3d ", (int)a.to_int());
	printf("%3d ", (int)a.to_int());
	printf("\n");
}

inline void SHOW(BIT a, std::string m)
{
	printf("BIT [%s]: ", m.c_str());
	printf("%3d ", (int)a.to_int());
	printf("%3d ", (int)a.to_int());
	printf("\n");
}

inline MSG qmin(MSG a, MSG b)
{
	#pragma HLS INLINE
	return (a < b) ? a : b;
}

inline MSG qsat(LLR a){
	if     ( a[MSG_BITS  ] == 1 )
		return (MSG)MSG_MAXV;
	else if( a[MSG_BITS-1] == 1 )
		return (MSG)MSG_MAXV;
	else
		return (MSG)a;
//	MSG m = (  || a[MSG_BITS-1] ) ? (MSG)MSG_MAXV : (MSG)a;
//	MSG m = ( a < MSG_MAXV) ? (MSG)a : (MSG)MSG_MAXV;
//	return m;
}

inline MSG qmax(MSG a, MSG b){
	return (a > b) ? a : b;
}

inline sc_uint<8> vmax(sc_uint<8> a, sc_uint<8> b){
	return (a > b) ? a : b;
}

inline MSG qmin(MSG msg, MSG min1, MSG min2)
{
	#pragma HLS INLINE
	MSG max = qmax(msg, min1);
	MSG min = qmin(min2, max);
	return min;
}

inline bool qsign(LLR value){
	return ! value[LLR_BITS - 1];
	//return value <= 0 ? 0 : 1;
}

#if MSG_BITS != LLR_BITS
inline bool qsign(MSG value){
	return ! value[MSG_BITS - 1];
	//return value <= 0 ? 0 : 1;
}
#endif

inline MSG qsign(MSG a, BIT b){
    MSG positif = +a;
    MSG negatif = -a;
    return (b) ? positif : negatif;
}

inline MSG qabs(LLR value){
	//LLR positif = +value;
	//LLR negatif = -value;
	//LLR result  = (value [LLR_BITS-1]  == 1) ? negatif : positif;
	//return qmin(result, 63);
	LLR positif = +value;
	LLR negatif = -value;
	LLR result  = (value [LLR_BITS-1]  == 1) ? negatif : positif;
#ifdef REMOVE_SATS
	return result;
#else
	#if LLR_BITS == MSG_BITS
		return result;//output;
	#else
		MSG output  = qsat(result);
		//printf("value = %d, result = %d, output = %d\n", value.to_int(), result.to_int(), output.to_int());
		return output;//output;
	#endif
#endif
}

inline LLR qadd(LLR a, MSG b){
	#pragma HLS INLINE
  sc_bigint<LLR_BITS+1> r = ((sc_bigint<LLR_BITS+1>)a) + b;
//#ifdef REMOVE_SATS
//  if     ( r.test(LLR_BITS  ) == 1 ) return LLR_MINV;
//  else if( r.test(LLR_BITS-1) == 1 ) return LLR_MAXV;
//  else
//#endif
//  	return r;
  if     ( r > LLR_MAXV ) return LLR_MAXV;
  else if( r < LLR_MINV ) return LLR_MINV;
  else return r;
}

inline LLR qsub(LLR a, MSG b){
	#pragma HLS INLINE
  sc_bigint<LLR_BITS+1> r = ((sc_bigint<LLR_BITS+1>)a) - b;
//#ifdef REMOVE_SATS
//  if     ( r.test(LLR_BITS  ) == 1 ) return LLR_MINV;
//  else if( r.test(LLR_BITS-1) == 1 ) return LLR_MAXV;
//  else
//#endif
//  	return r;
  if     ( r > LLR_MAXV ) return LLR_MAXV;
  else if( r < LLR_MINV ) return LLR_MINV;
  else return r;
}

inline MSG qinv(MSG value, BIT sign)
{
	#pragma HLS INLINE
  MSG positif = +value;
  MSG negatif = -value;
  return (sign == 0) ? positif : negatif;
}

inline BIT qxor(BIT a, BIT b)
{
	#pragma HLS INLINE
  return a ^ b;
}

inline BIT qequal(LLR a, LLR b)
{
	#pragma HLS INLINE
  return (a == b);
}


inline MSG qcmov(BIT c, MSG a, MSG b)
{
	#pragma HLS INLINE
  return (c == 1) ? a : b;
}

inline LLR nms(MSG b){
  return b - (b >> 2);
}

#endif

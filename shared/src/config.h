#define Q   		24 // QC FACTOR !

#define LLR_BITS	8
#define LLR_MAXV    (+127)
#define LLR_MINV    (-127)

#define MSG_BITS	8

#define MAX_ITERS	10

#define TYPE_LLRS   sc_bigint<Q * LLR_BITS>
#define TYPE_MSGS   sc_bigint<Q * MSG_BITS>
#define TYPE_BITS   sc_bv<Q>

#define LLR 		sc_bigint<LLR_BITS>
#define MSG 		sc_bigint<MSG_BITS>
#define BIT 		sc_bit

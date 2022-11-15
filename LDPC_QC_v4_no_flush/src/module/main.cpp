#include "systemc.h"
#include <stdio.h>
#include <stdlib.h>

#include "./config.h"
#include "../../../shared/src/vector.h"
#include "./ldpc_parameters_generic.h"
#include "./ldpc_code_generic.h"


int main()
{
	TYPE_LLRS vNoeud1;
	TYPE_LLRS vNoeud2;

	for (int j=0; j < 2*Q; j++)
	{
		if(j==Q) printf("\n");
		if(j < Q)
		{
			printf("%3d ",j);
//			printf("vNoeud2 %d : %d\n",j,j);
			vNoeud2.range(LLR_BITS * (j+1) - 1, LLR_BITS * j) = j;
		}
		else
		{
//			printf("vNoeud1 %d : %d\n",j-Q,j);
			printf("%3d ",j);
			vNoeud1.range(LLR_BITS * (j-Q+1) - 1, LLR_BITS * (j-Q)) = j;
		}
	}
	printf("\n");
	printf("======================\n");

	for(int q=0; q < 162; q++){

		printf("%3d : ",q);
		const TYPE_LLRS rNoeud1 = rotate_left1( vNoeud1, vNoeud2, q);
		const TYPE_LLRS rNoeud2 = rotate_left2( vNoeud1, vNoeud2, q);
		for (int j=0; j < 2*Q; j++)
		{
			if(j < Q)
			{
				LLR l2 = (sc_bigint<LLR_BITS>)rNoeud2.range(LLR_BITS * (j+1) - 1, LLR_BITS * j);
				printf("%3d ",l2.to_uint());
	//			printf("rNoeud2 %d : %d\n",j,l2.to_uint());
			}
			else
			{
				LLR l1 = (sc_bigint<LLR_BITS>)rNoeud1.range(LLR_BITS * (j-Q+1) - 1, LLR_BITS * (j-Q));
				printf("%3d ",l1.to_uint());
	//			printf("rNoeud1 %d : %d\n",j,l1.to_uint());
			}
		}
		printf("\n");
		//printf("======================\n");
	}

	for(int q=0; q < 162; q++){

		printf("%3d : ",q);
		const TYPE_LLRS rNoeud1 = rotate_right1( vNoeud1, vNoeud2, q);
		const TYPE_LLRS rNoeud2 = rotate_right2( vNoeud1, vNoeud2, q);
		for (int j=0; j < 2*Q; j++)
		{
			if(j < Q)
			{
				LLR l2 = (sc_bigint<LLR_BITS>)rNoeud2.range(LLR_BITS * (j+1) - 1, LLR_BITS * j);
				printf("%3d ",l2.to_uint());
	//			printf("rNoeud2 %d : %d\n",j,l2.to_uint());
			}
			else
			{
				LLR l1 = (sc_bigint<LLR_BITS>)rNoeud1.range(LLR_BITS * (j-Q+1) - 1, LLR_BITS * (j-Q));
				printf("%3d ",l1.to_uint());
	//			printf("rNoeud1 %d : %d\n",j,l1.to_uint());
			}
		}
		printf("\n");
		//printf("======================\n");
	}

	for(int q=0; q < 162; q++){

			const TYPE_LLRS rNoeud1 = rotate_left1( vNoeud1, vNoeud2, q);
			const TYPE_LLRS rNoeud2 = rotate_left2( vNoeud1, vNoeud2, q);
			const TYPE_LLRS sNoeud1 = rotate_right1( rNoeud1, rNoeud2, q);
			const TYPE_LLRS sNoeud2 = rotate_right2( rNoeud1, rNoeud2, q);
			if(sNoeud1 != vNoeud1)
			{
				printf("%3d : ",q);
				printf("Error sur sNoeud1\n");
			}
			if(sNoeud2 != vNoeud2)
			{
				printf("%3d : ",q);
				printf("Error sur sNoeud2\n");
			}
			printf("\n");
			//printf("======================\n");
		}

	/*const TYPE_LLRS rNoeud11 = rotate_right2( rNoeud1, rNoeud2, 150);
	const TYPE_LLRS rNoeud22 = rotate_right1( rNoeud1, rNoeud2, 150);

	for (int j=0; j < 2*Q; j++)
	{
		if(j < Q)
		{
			LLR l2 = (sc_bigint<LLR_BITS>)rNoeud22.range(LLR_BITS * (j+1) - 1, LLR_BITS * j);
			printf("rNoeud2 %d : %d\n",j,l2.to_uint());
		}
		else
		{
			LLR l1 = (sc_bigint<LLR_BITS>)rNoeud11.range(LLR_BITS * (j-Q+1) - 1, LLR_BITS * (j-Q));
			printf("rNoeud1 %d : %d\n",j,l1.to_uint());
		}
*/
}

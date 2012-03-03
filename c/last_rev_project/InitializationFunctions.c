#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Structs.h"

opcode* InitializeOpcodeList(opcode* list)
{
	list=(opcode*)malloc(OPCODE_COUNT*sizeof(opcode));

	/* mov */
	strcpy(list[0].op,"mov");
	list[0].value_8=0;
	list[0].operand_count=2;
	list[0].adddressing_type_src[0]=0;
	list[0].adddressing_type_src[1]=1;
	list[0].adddressing_type_src[2]=2;
	list[0].adddressing_type_src[3]=3;
	list[0].adddressing_type_src[4]=4;

	list[0].adddressing_type_dst[0]=1;
	list[0].adddressing_type_dst[1]=2;
	list[0].adddressing_type_dst[2]=3;
	list[0].adddressing_type_dst[3]=4;
	list[0].adddressing_type_dst[4]=-1;

	/* cmp */
	strcpy(list[1].op,"cmp");
	list[1].value_8=1;
	list[1].operand_count=2;

	list[1].adddressing_type_src[0]=0;
	list[1].adddressing_type_src[1]=1;
 	list[1].adddressing_type_src[2]=2;
	list[1].adddressing_type_src[3]=3;
	list[1].adddressing_type_src[4]=4;

	list[1].adddressing_type_dst[0]=0;
	list[1].adddressing_type_dst[1]=1;
	list[1].adddressing_type_dst[2]=2;
	list[1].adddressing_type_dst[3]=3;
	list[1].adddressing_type_dst[4]=4;


	/* add */
	strcpy(list[2].op,"add");
	list[2].value_8=2;
	list[2].operand_count=2;

	list[2].adddressing_type_src[0]=0;
	list[2].adddressing_type_src[1]=1;
	list[2].adddressing_type_src[2]=2;
	list[2].adddressing_type_src[3]=3;
	list[2].adddressing_type_src[4]=4;

	list[2].adddressing_type_dst[0]=1;
	list[2].adddressing_type_dst[1]=2;
	list[2].adddressing_type_dst[2]=3;
	list[2].adddressing_type_dst[3]=4;
	list[2].adddressing_type_dst[4]=-1;

	/* sub */
	strcpy(list[3].op,"sub");
	list[3].value_8=3;
	list[3].operand_count=2;

	list[3].adddressing_type_src[0]=0;
	list[3].adddressing_type_src[1]=1;
	list[3].adddressing_type_src[2]=2;
	list[3].adddressing_type_src[3]=3;
	list[3].adddressing_type_src[4]=4;

	list[3].adddressing_type_dst[0]=1;
	list[3].adddressing_type_dst[1]=2;
	list[3].adddressing_type_dst[2]=3;
	list[3].adddressing_type_dst[3]=4;
	list[3].adddressing_type_dst[4]=-1;

	/* not */
	strcpy(list[4].op,"not");
	list[4].value_8=4;
	list[4].operand_count=1;

	list[4].adddressing_type_src[0]=-1;

	list[4].adddressing_type_dst[0]=1;
	list[4].adddressing_type_dst[1]=2;
	list[4].adddressing_type_dst[2]=3;
	list[4].adddressing_type_dst[3]=4;
	list[4].adddressing_type_dst[4]=-1;

	/* clr */
	strcpy(list[5].op,"clr");
	list[5].value_8=5;
	list[5].operand_count=1;

	list[5].adddressing_type_src[0]=-1;

	list[5].adddressing_type_dst[0]=1;
	list[5].adddressing_type_dst[1]=2;
	list[5].adddressing_type_dst[2]=3;
	list[5].adddressing_type_dst[3]=4;
	list[5].adddressing_type_dst[4]=-1;

	/* lea */
	strcpy(list[6].op,"lea");
	list[6].value_8=6;
	list[6].operand_count=2;

	list[6].adddressing_type_src[0]=1;
	list[6].adddressing_type_src[1]=2;
	list[6].adddressing_type_src[2]=3;
	list[6].adddressing_type_src[3]=-1;

	list[6].adddressing_type_dst[0]=1;
	list[6].adddressing_type_dst[1]=2;
	list[6].adddressing_type_dst[2]=3;
	list[6].adddressing_type_dst[3]=4;
	list[6].adddressing_type_dst[4]=-1;

	/* inc */
	strcpy(list[7].op,"inc");
	list[7].value_8=7;
	list[7].operand_count=1;

	list[7].adddressing_type_src[0]=-1;

	list[7].adddressing_type_dst[0]=1;
	list[7].adddressing_type_dst[1]=2;
	list[7].adddressing_type_dst[2]=3;
	list[7].adddressing_type_dst[3]=4;
	list[7].adddressing_type_dst[4]=-1;

	/* dec */

	strcpy(list[8].op,"dec");
	list[8].value_8=10;
	list[8].operand_count=1;

	list[8].adddressing_type_src[0]=-1;

	list[8].adddressing_type_dst[0]=1;
	list[8].adddressing_type_dst[1]=2;
	list[8].adddressing_type_dst[2]=3;
	list[8].adddressing_type_dst[3]=4;
	list[8].adddressing_type_dst[4]=-1;
	/* jmp */

	strcpy(list[9].op,"jmp");
	list[9].value_8=11;
	list[9].operand_count=1;

	list[9].adddressing_type_src[0]=-1;

	list[9].adddressing_type_dst[0]=1;
	list[9].adddressing_type_dst[1]=2;
	list[9].adddressing_type_dst[2]=3;
	list[9].adddressing_type_dst[3]=4;
	list[9].adddressing_type_dst[4]=-1;
	/* bne */

	strcpy(list[10].op,"bne");
	list[10].value_8=12;
	list[10].operand_count=1;

	list[10].adddressing_type_src[0]=-1;

	list[10].adddressing_type_dst[0]=1;
	list[10].adddressing_type_dst[1]=2;
	list[10].adddressing_type_dst[2]=3;
	list[10].adddressing_type_dst[3]=4;
	list[10].adddressing_type_dst[4]=-1;

	/* red */

	strcpy(list[11].op,"red");
	list[11].value_8=13;
	list[11].operand_count=1;

	list[11].adddressing_type_src[0]=-1;

	list[11].adddressing_type_dst[0]=1;
	list[11].adddressing_type_dst[1]=2;
	list[11].adddressing_type_dst[2]=3;
	list[11].adddressing_type_dst[3]=4;
	list[11].adddressing_type_dst[4]=-1;

	/* prn */

	strcpy(list[12].op,"prn");
	list[12].value_8=14;
	list[12].operand_count=1;

	list[12].adddressing_type_src[0]=-1;

	list[12].adddressing_type_dst[0]=0;
	list[12].adddressing_type_dst[1]=1;
	list[12].adddressing_type_dst[2]=2;
	list[12].adddressing_type_dst[3]=3;
	list[12].adddressing_type_dst[4]=4;

	/* jsr */

	strcpy(list[13].op,"jsr");
	list[13].value_8=15;
	list[13].operand_count=1;

	list[13].adddressing_type_src[0]=-1;

	list[13].adddressing_type_dst[0]=1;
	list[13].adddressing_type_dst[1]=-1;

	/* rts */

	strcpy(list[14].op,"rts");
	list[14].value_8=16;
	list[14].operand_count=0;

	list[14].adddressing_type_src[0]=-1;
	list[14].adddressing_type_dst[0]=-1;


	/* hlt */

	strcpy(list[15].op,"hlt");
	list[15].value_8=17;
	list[15].operand_count=0;

	list[15].adddressing_type_src[0]=-1;
	list[15].adddressing_type_dst[0]=-1;

	return list;
}

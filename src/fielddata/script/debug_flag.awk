#saveflag.h -> テーブルへ　by tomo 060527

BEGIN{
	printf("typedef struct{\n");
	printf(" char flag_tbl[30]\;\n");
	printf(" u16 val\;\n");
	printf("}SAVF_TBL\;\n\n");
	printf("const SAVF_TBL saft[]={\n");
}

{
	if(($1 == "#define")&&(length($3)>0)){
		printf("\t{\"%s\"\,%s}\,\n",$2,$3);
	}
}


END{
	printf("}\;\n");
}

#savework.h -> テーブルへ　by tomo 060527

BEGIN{
	printf("typedef struct{\n");
	printf(" char wk_tbl[30]\;\n");
	printf(" u16 val\;\n");
	printf("}SAV_TBL\;\n\n");
	printf("const SAV_TBL sawt[]={\n");
}

{
	if(($1 == "#define")&&(length($3)>0)){
		printf("\t{\"%s\"\,%s}\,\n",$2,$3);
	}
}


END{
	printf("}\;\n");
}

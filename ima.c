#include <stdio.h>
#include <string.h>
#include "imaadpcm.h"
static unsigned char clip(unsigned short in){
	if(in>255){
		return 255;
	}else{
		return (unsigned char)in;
	}
	
}
int main(int argc, char** argv){
	FILE *in,*out;
	Ima_Context ctx;
	ima_init(&ctx);
	in=fopen(argv[2],"rb");
	out=fopen(argv[3],"wb");
	if(!strcmp(argv[1],"c")){
		signed short inc[2];
		while(fread(inc,1,4,in)){
			unsigned char temp;
			temp=ima_encode(&ctx,inc[0]) | ima_encode(&ctx,inc[1]) << 4;
			fwrite(&temp,1,1,out);
		}
	}else if(!strcmp(argv[1],"d")){
		unsigned char inc;
		while(fread(&inc,1,1,in)){
			unsigned short outc[2];
			outc[0]=ima_decode(&ctx,inc&0xF);
			outc[1]=ima_decode(&ctx,(inc&0xF0)>>4);
			fwrite(outc,1,4,out);
		}
		
		
	}
	fclose(in);
	fclose(out);
	return 0;
}
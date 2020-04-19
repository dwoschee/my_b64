/* my_b64.c */
#include <stdio.h>
#include <stdlib.h>
#include "b64.h"

int main(int argc, unsigned char* argv[]) {
	int i;
	unsigned long len;
	unsigned long len64;
	char *buf;
	unsigned char *buf64;
	FILE *f;
	for (i = 1; i < argc; i++) {
		printf("---[%s]---\n", argv[i]);
		f = fopen(argv[i], "rb");
		if (f) {
			fseek(f, 0, SEEK_END);
			len = ftell(f);
			fseek(f, 0, SEEK_SET);
			buf = malloc(len);
			fread(buf, 1, len, f);
			fclose(f);

			len64 = b64_enc_req(len);
			buf64 = malloc(len64);
			b64_encode(buf, len, buf64);

			fwrite(buf64, 1, len64, stdout);
			putchar('\n');

			free(buf);
			free(buf64);
		} else {
			printf("Error: could not open file\n");
		}
	}
	return 0;
}

#include "menuHeader.h"

void callCompression(struct FilePaths fp, int log, int algorithm) {
	FILE *out = NULL, *logFile = NULL;
	out = fopen("tarball.bin", "wb");

	// open log file if necessary
	if (log) {
		// logName will be same as archive name with .log extension
		char logName[_MAX_DIR + 1];
		strcpy(logName, fp.archive);
		for (int j = strlen(logName) - 1; j >= 0; j--) {
			if (logName[j] == '.') {
				logName[j] = '\0';
				break;
			}
		}

		strcat(logName, ".log");
		logFile = fopen(logName, "w");
	}

	// merge all files
	make_tarball(fp.paths, fp.size, out);
	fclose(out);

	if (algorithm == DHUFF) {
		printf("Compressing using DH...\n");
		FILE *in = fopen("tarball.bin", "rb");
		FILE *dhuff = fopen(fp.archive, "wb");
		DH_compress(in, dhuff);
		fclose(in);
		fclose(dhuff);
	}
	remove("tarball.bin");
	// call compress function based on algorithm chosen
	// compress(f, &out, &logFile, fp.size)
	/*
	OVDE UBACI POZIVE NA NJIHOVE FUNKCIJE
	*/

	// close all files if necessary
	if (logFile) fclose(logFile);
	if (out) fclose(out);
}
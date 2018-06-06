#include "menuHeader.h"

void callDecompression(struct FilePaths fp, int log) {
	FILE *arch = NULL, *logFile = NULL;

	for (int i = 0; i < fp.size; i++) {
		char name[_MAX_DIR + 1], tarName[_MAX_DIR + 1];
		// open selected archive
		arch = fopen(fp.paths[i], "rb");
		strcpy(name, fp.paths[i]);
		// delete archive extension
		for (int j = strlen(name) - 1; j >= 0; j--) {
			if (name[j] == '.') {
				name[j] = '\0';
				break;
			}
		}

		//make log file if necessary
		if (log) {
			// logName will be same as archive name with .log extension
			char logName[_MAX_DIR + 1];
			strcpy(logName, fp.paths[i]);
			for (int j = strlen(logName) - 1; j >= 0; j--) {
				if (logName[j] == '.') {
					logName[j] = '\0';
					break;
				}
			}

			strcat(logName, ".log");
			logFile = fopen(logName, "w");
		}

		mkdir(name);
		// call functions for decompression
		// decompress(arch, name, &logFile);
		/*
		OVDE POZOVI NJIHOVE FUNKCIJE
		*/
		strcpy(tarName, name);
		strcat(tarName, "\\tar.bin");
		FILE *tarball = fopen(tarName, "wb");
		DH_decompress(arch, tarball);
		fclose(tarball);
		tarball = fopen(tarName, "rb");
		extract_tar(tarball, name);
		fclose(tarball);

		fclose(arch);
		if (log) fclose(logFile);
		remove(tarName);
	}
}
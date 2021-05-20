#include<stdio.h>
#include<Windows.h>


int main() {
	DWORD prcessIDexe = 17816;
	HANDLE hamad_process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, prcessIDexe);
	if (!hamad_process) {
		printf("failed to open the process");
	}
	else {
		printf("secessfull to open process : %d", prcessIDexe);
	}





}
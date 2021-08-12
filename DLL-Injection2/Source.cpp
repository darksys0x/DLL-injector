#include <stdio.h>
#include <Windows.h>





/* 53 56 57 8D BD 40 FF FF FF B9 30 00 00 00 B8 CC CC CC CC F3 AB



.text:00411BF9 53                         push    ebx
.text:00411BFA 56                         push    esi
.text:00411BFB 56                         push    edi
.text:00411BFC 89 BD 40 FF FF FF          lea     edi, [ebp+var_C0]
.text:00411C02 B9 30 00 00 00             mov     ecx, 30h
.text:00411C07 B8 CC CC CC CC             mov     eax, 0CCCCCCCCh
.text:00411C0C F3 AB                      rep stosd
.text:00411C0E B9 27 C0 41 00             mov     ecx, offset unk_41C027
*/
int main()
{
	DWORD processID = 17816;
	HANDLE hamadProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);
	if (!hamadProcess) {
		printf("failed to open process handle\n");
		return 0;
	} 

	
	WCHAR dllPath[250] = L"C:\\Users\\user1\\hamadPatching_game\\hamadPatchingGame\\Debug\\hamadDll.dll";
	// Step 2. Allocate memory for string in the target process

	
	
 
	DWORD location = (DWORD)VirtualAllocEx(hamadProcess, NULL, sizeof(dllPath), MEM_COMMIT, PAGE_READWRITE);

	
	// step3 write proicess memory
	BOOL written = WriteProcessMemory(hamadProcess, (LPVOID)location, dllPath, sizeof(dllPath), NULL );

	
	
	if (written)
		printf("sucessfully wrote to process\n");     
	else
	
		printf("failed to write to process memory\n");

	
	
	//idintfy baseAddress
	
	HMODULE kernel32DllBaseAddress = LoadLibraryA("kernel32.dll");
	
	DWORD loadlibrary_address = (DWORD)GetProcAddress(kernel32DllBaseAddress, "LoadLibraryW");
	
	
	HANDLE threadHandle = CreateRemoteThread(hamadProcess, 0, 0, (LPTHREAD_START_ROUTINE)loadlibrary_address, (LPVOID)location, 0, 0);
	
	if (threadHandle == NULL)
	{
		printf("failed to create remote thread | %s\n", GetLastErrorAsString().c_str());
		system("PAUSE");
	}
	
	
	printf("[+] started new thread\n\n");
	printf("[+] waiting for thread to execute\n");
	WaitForSingleObject(threadHandle, INFINITE);
	printf("[+] Done!! Closing handle\n");
	CloseHandle(hamadProcess);//
	
	
	printf("[+] Closed process handle\b");//
	VirtualFreeEx(hProc, paramAddr, size, MEM_RELEASE);
	printf("Injected Successfully")


	
	getchar();
}

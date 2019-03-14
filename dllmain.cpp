#include "stdafx.h"

#pragma pack(1)

HINSTANCE hLThis = 0;
HINSTANCE hL = 0;
FARPROC p[195] = { 0 };
TCHAR systemPath[MAX_PATH];

TCHAR hostname[16] = { 0 };
TCHAR ipList[5];
PTCHAR ipListPtr[1];
HOSTENT hostentMock;
TCHAR configFileSeparators[] = "=\n";
TCHAR ipAddressSeparators[] = ".";

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		hLThis = hInst;

		if (!GetSystemDirectory(systemPath, MAX_PATH)) {
			return false;
		}

		if (PathAddBackslash(systemPath) == NULL) {
			return false;
		}

		if (StringCchCat(systemPath, MAX_PATH, "ws2_32.dll") != S_OK) {
			return false;
		}

		hL = LoadLibrary(systemPath);
		if (!hL) return false;

		p[0] = GetProcAddress(hL, "FreeAddrInfoEx");
		p[1] = GetProcAddress(hL, "FreeAddrInfoExW");
		p[2] = GetProcAddress(hL, "FreeAddrInfoW");
		p[3] = GetProcAddress(hL, "GetAddrInfoExA");
		p[4] = GetProcAddress(hL, "GetAddrInfoExCancel");
		p[5] = GetProcAddress(hL, "GetAddrInfoExOverlappedResult");
		p[6] = GetProcAddress(hL, "GetAddrInfoExW");
		p[7] = GetProcAddress(hL, "GetAddrInfoW");
		p[8] = GetProcAddress(hL, "GetHostNameW");
		p[9] = GetProcAddress(hL, "GetNameInfoW");
		p[10] = GetProcAddress(hL, "InetNtopW");
		p[11] = GetProcAddress(hL, "InetPtonW");
		p[12] = GetProcAddress(hL, "SetAddrInfoExA");
		p[13] = GetProcAddress(hL, "SetAddrInfoExW");
		p[14] = GetProcAddress(hL, "WEP");
		p[15] = GetProcAddress(hL, "WPUCompleteOverlappedRequest");
		p[16] = GetProcAddress(hL, "WPUGetProviderPathEx");
		p[17] = GetProcAddress(hL, "WSAAccept");
		p[18] = GetProcAddress(hL, "WSAAddressToStringA");
		p[19] = GetProcAddress(hL, "WSAAddressToStringW");
		p[20] = GetProcAddress(hL, "WSAAdvertiseProvider");
		p[21] = GetProcAddress(hL, "WSAAsyncGetHostByAddr");
		p[22] = GetProcAddress(hL, "WSAAsyncGetHostByName");
		p[23] = GetProcAddress(hL, "WSAAsyncGetProtoByName");
		p[24] = GetProcAddress(hL, "WSAAsyncGetProtoByNumber");
		p[25] = GetProcAddress(hL, "WSAAsyncGetServByName");
		p[26] = GetProcAddress(hL, "WSAAsyncGetServByPort");
		p[27] = GetProcAddress(hL, "WSAAsyncSelect");
		p[28] = GetProcAddress(hL, "WSACancelAsyncRequest");
		p[29] = GetProcAddress(hL, "WSACancelBlockingCall");
		p[30] = GetProcAddress(hL, "WSACleanup");
		p[31] = GetProcAddress(hL, "WSACloseEvent");
		p[32] = GetProcAddress(hL, "WSAConnect");
		p[33] = GetProcAddress(hL, "WSAConnectByList");
		p[34] = GetProcAddress(hL, "WSAConnectByNameA");
		p[35] = GetProcAddress(hL, "WSAConnectByNameW");
		p[36] = GetProcAddress(hL, "WSACreateEvent");
		p[37] = GetProcAddress(hL, "WSADuplicateSocketA");
		p[38] = GetProcAddress(hL, "WSADuplicateSocketW");
		p[39] = GetProcAddress(hL, "WSAEnumNameSpaceProvidersA");
		p[40] = GetProcAddress(hL, "WSAEnumNameSpaceProvidersExA");
		p[41] = GetProcAddress(hL, "WSAEnumNameSpaceProvidersExW");
		p[42] = GetProcAddress(hL, "WSAEnumNameSpaceProvidersW");
		p[43] = GetProcAddress(hL, "WSAEnumNetworkEvents");
		p[44] = GetProcAddress(hL, "WSAEnumProtocolsA");
		p[45] = GetProcAddress(hL, "WSAEnumProtocolsW");
		p[46] = GetProcAddress(hL, "WSAEventSelect");
		p[47] = GetProcAddress(hL, "WSAGetLastError");
		p[48] = GetProcAddress(hL, "WSAGetOverlappedResult");
		p[49] = GetProcAddress(hL, "WSAGetQOSByName");
		p[50] = GetProcAddress(hL, "WSAGetServiceClassInfoA");
		p[51] = GetProcAddress(hL, "WSAGetServiceClassInfoW");
		p[52] = GetProcAddress(hL, "WSAGetServiceClassNameByClassIdA");
		p[53] = GetProcAddress(hL, "WSAGetServiceClassNameByClassIdW");
		p[54] = GetProcAddress(hL, "WSAHtonl");
		p[55] = GetProcAddress(hL, "WSAHtons");
		p[56] = GetProcAddress(hL, "WSAInstallServiceClassA");
		p[57] = GetProcAddress(hL, "WSAInstallServiceClassW");
		p[58] = GetProcAddress(hL, "WSAIoctl");
		p[59] = GetProcAddress(hL, "WSAIsBlocking");
		p[60] = GetProcAddress(hL, "WSAJoinLeaf");
		p[61] = GetProcAddress(hL, "WSALookupServiceBeginA");
		p[62] = GetProcAddress(hL, "WSALookupServiceBeginW");
		p[63] = GetProcAddress(hL, "WSALookupServiceEnd");
		p[64] = GetProcAddress(hL, "WSALookupServiceNextA");
		p[65] = GetProcAddress(hL, "WSALookupServiceNextW");
		p[66] = GetProcAddress(hL, "WSANSPIoctl");
		p[67] = GetProcAddress(hL, "WSANtohl");
		p[68] = GetProcAddress(hL, "WSANtohs");
		p[69] = GetProcAddress(hL, "WSAPoll");
		p[70] = GetProcAddress(hL, "WSAProviderCompleteAsyncCall");
		p[71] = GetProcAddress(hL, "WSAProviderConfigChange");
		p[72] = GetProcAddress(hL, "WSARecv");
		p[73] = GetProcAddress(hL, "WSARecvDisconnect");
		p[74] = GetProcAddress(hL, "WSARecvFrom");
		p[75] = GetProcAddress(hL, "WSARemoveServiceClass");
		p[76] = GetProcAddress(hL, "WSAResetEvent");
		p[77] = GetProcAddress(hL, "WSASend");
		p[78] = GetProcAddress(hL, "WSASendDisconnect");
		p[79] = GetProcAddress(hL, "WSASendMsg");
		p[80] = GetProcAddress(hL, "WSASendTo");
		p[81] = GetProcAddress(hL, "WSASetBlockingHook");
		p[82] = GetProcAddress(hL, "WSASetEvent");
		p[83] = GetProcAddress(hL, "WSASetLastError");
		p[84] = GetProcAddress(hL, "WSASetServiceA");
		p[85] = GetProcAddress(hL, "WSASetServiceW");
		p[86] = GetProcAddress(hL, "WSASocketA");
		p[87] = GetProcAddress(hL, "WSASocketW");
		p[88] = GetProcAddress(hL, "WSAStartup");
		p[89] = GetProcAddress(hL, "WSAStringToAddressA");
		p[90] = GetProcAddress(hL, "WSAStringToAddressW");
		p[91] = GetProcAddress(hL, "WSAUnadvertiseProvider");
		p[92] = GetProcAddress(hL, "WSAUnhookBlockingHook");
		p[93] = GetProcAddress(hL, "WSAWaitForMultipleEvents");
		p[94] = GetProcAddress(hL, "WSApSetPostRoutine");
		p[95] = GetProcAddress(hL, "WSCDeinstallProvider");
		p[96] = GetProcAddress(hL, "WSCDeinstallProvider32");
		p[97] = GetProcAddress(hL, "WSCDeinstallProviderEx");
		p[98] = GetProcAddress(hL, "WSCEnableNSProvider");
		p[99] = GetProcAddress(hL, "WSCEnableNSProvider32");
		p[100] = GetProcAddress(hL, "WSCEnumNameSpaceProviders32");
		p[101] = GetProcAddress(hL, "WSCEnumNameSpaceProvidersEx32");
		p[102] = GetProcAddress(hL, "WSCEnumProtocols");
		p[103] = GetProcAddress(hL, "WSCEnumProtocols32");
		p[104] = GetProcAddress(hL, "WSCEnumProtocolsEx");
		p[105] = GetProcAddress(hL, "WSCGetApplicationCategory");
		p[106] = GetProcAddress(hL, "WSCGetApplicationCategoryEx");
		p[107] = GetProcAddress(hL, "WSCGetProviderInfo");
		p[108] = GetProcAddress(hL, "WSCGetProviderInfo32");
		p[109] = GetProcAddress(hL, "WSCGetProviderPath");
		p[110] = GetProcAddress(hL, "WSCGetProviderPath32");
		p[111] = GetProcAddress(hL, "WSCInstallNameSpace");
		p[112] = GetProcAddress(hL, "WSCInstallNameSpace32");
		p[113] = GetProcAddress(hL, "WSCInstallNameSpaceEx");
		p[114] = GetProcAddress(hL, "WSCInstallNameSpaceEx2");
		p[115] = GetProcAddress(hL, "WSCInstallNameSpaceEx32");
		p[116] = GetProcAddress(hL, "WSCInstallProvider");
		p[117] = GetProcAddress(hL, "WSCInstallProvider64_32");
		p[118] = GetProcAddress(hL, "WSCInstallProviderAndChains64_32");
		p[119] = GetProcAddress(hL, "WSCInstallProviderEx");
		p[120] = GetProcAddress(hL, "WSCSetApplicationCategory");
		p[121] = GetProcAddress(hL, "WSCSetApplicationCategoryEx");
		p[122] = GetProcAddress(hL, "WSCSetProviderInfo");
		p[123] = GetProcAddress(hL, "WSCSetProviderInfo32");
		p[124] = GetProcAddress(hL, "WSCUnInstallNameSpace");
		p[125] = GetProcAddress(hL, "WSCUnInstallNameSpace32");
		p[126] = GetProcAddress(hL, "WSCUnInstallNameSpaceEx2");
		p[127] = GetProcAddress(hL, "WSCUpdateProvider");
		p[128] = GetProcAddress(hL, "WSCUpdateProvider32");
		p[129] = GetProcAddress(hL, "WSCUpdateProviderEx");
		p[130] = GetProcAddress(hL, "WSCWriteNameSpaceOrder");
		p[131] = GetProcAddress(hL, "WSCWriteNameSpaceOrder32");
		p[132] = GetProcAddress(hL, "WSCWriteProviderOrder");
		p[133] = GetProcAddress(hL, "WSCWriteProviderOrder32");
		p[134] = GetProcAddress(hL, "WSCWriteProviderOrderEx");
		p[135] = GetProcAddress(hL, "WahCloseApcHelper");
		p[136] = GetProcAddress(hL, "WahCloseHandleHelper");
		p[137] = GetProcAddress(hL, "WahCloseNotificationHandleHelper");
		p[138] = GetProcAddress(hL, "WahCloseSocketHandle");
		p[139] = GetProcAddress(hL, "WahCloseThread");
		p[140] = GetProcAddress(hL, "WahCompleteRequest");
		p[141] = GetProcAddress(hL, "WahCreateHandleContextTable");
		p[142] = GetProcAddress(hL, "WahCreateNotificationHandle");
		p[143] = GetProcAddress(hL, "WahCreateSocketHandle");
		p[144] = GetProcAddress(hL, "WahDestroyHandleContextTable");
		p[145] = GetProcAddress(hL, "WahDisableNonIFSHandleSupport");
		p[146] = GetProcAddress(hL, "WahEnableNonIFSHandleSupport");
		p[147] = GetProcAddress(hL, "WahEnumerateHandleContexts");
		p[148] = GetProcAddress(hL, "WahInsertHandleContext");
		p[149] = GetProcAddress(hL, "WahNotifyAllProcesses");
		p[150] = GetProcAddress(hL, "WahOpenApcHelper");
		p[151] = GetProcAddress(hL, "WahOpenCurrentThread");
		p[152] = GetProcAddress(hL, "WahOpenHandleHelper");
		p[153] = GetProcAddress(hL, "WahOpenNotificationHandleHelper");
		p[154] = GetProcAddress(hL, "WahQueueUserApc");
		p[155] = GetProcAddress(hL, "WahReferenceContextByHandle");
		p[156] = GetProcAddress(hL, "WahRemoveHandleContext");
		p[157] = GetProcAddress(hL, "WahWaitForNotification");
		p[158] = GetProcAddress(hL, "WahWriteLSPEvent");
		p[159] = GetProcAddress(hL, "__WSAFDIsSet");
		p[160] = GetProcAddress(hL, "accept");
		p[161] = GetProcAddress(hL, "bind");
		p[162] = GetProcAddress(hL, "closesocket");
		p[163] = GetProcAddress(hL, "connect");
		p[164] = GetProcAddress(hL, "freeaddrinfo");
		p[165] = GetProcAddress(hL, "getaddrinfo");
		p[166] = GetProcAddress(hL, "gethostbyaddr");
		p[167] = GetProcAddress(hL, "gethostbyname");
		p[168] = GetProcAddress(hL, "gethostname");
		p[169] = GetProcAddress(hL, "getnameinfo");
		p[170] = GetProcAddress(hL, "getpeername");
		p[171] = GetProcAddress(hL, "getprotobyname");
		p[172] = GetProcAddress(hL, "getprotobynumber");
		p[173] = GetProcAddress(hL, "getservbyname");
		p[174] = GetProcAddress(hL, "getservbyport");
		p[175] = GetProcAddress(hL, "getsockname");
		p[176] = GetProcAddress(hL, "getsockopt");
		p[177] = GetProcAddress(hL, "htonl");
		p[178] = GetProcAddress(hL, "htons");
		p[179] = GetProcAddress(hL, "inet_addr");
		p[180] = GetProcAddress(hL, "inet_ntoa");
		p[181] = GetProcAddress(hL, "inet_ntop");
		p[182] = GetProcAddress(hL, "inet_pton");
		p[183] = GetProcAddress(hL, "ioctlsocket");
		p[184] = GetProcAddress(hL, "listen");
		p[185] = GetProcAddress(hL, "ntohl");
		p[186] = GetProcAddress(hL, "ntohs");
		p[187] = GetProcAddress(hL, "recv");
		p[188] = GetProcAddress(hL, "recvfrom");
		p[189] = GetProcAddress(hL, "select");
		p[190] = GetProcAddress(hL, "send");
		p[191] = GetProcAddress(hL, "sendto");
		p[192] = GetProcAddress(hL, "setsockopt");
		p[193] = GetProcAddress(hL, "shutdown");
		p[194] = GetProcAddress(hL, "socket");


	}
	if (reason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(hL);
	}

	return 1;
}

// FreeAddrInfoEx
extern "C" __declspec(naked) void __stdcall __E__0__()
{
	__asm
	{
		jmp p[0 * 4];
	}
}

// FreeAddrInfoExW
extern "C" __declspec(naked) void __stdcall __E__1__()
{
	__asm
	{
		jmp p[1 * 4];
	}
}

// FreeAddrInfoW
extern "C" __declspec(naked) void __stdcall __E__2__()
{
	__asm
	{
		jmp p[2 * 4];
	}
}

// GetAddrInfoExA
extern "C" __declspec(naked) void __stdcall __E__3__()
{
	__asm
	{
		jmp p[3 * 4];
	}
}

// GetAddrInfoExCancel
extern "C" __declspec(naked) void __stdcall __E__4__()
{
	__asm
	{
		jmp p[4 * 4];
	}
}

// GetAddrInfoExOverlappedResult
extern "C" __declspec(naked) void __stdcall __E__5__()
{
	__asm
	{
		jmp p[5 * 4];
	}
}

// GetAddrInfoExW
extern "C" __declspec(naked) void __stdcall __E__6__()
{
	__asm
	{
		jmp p[6 * 4];
	}
}

// GetAddrInfoW
extern "C" __declspec(naked) void __stdcall __E__7__()
{
	__asm
	{
		jmp p[7 * 4];
	}
}

// GetHostNameW
extern "C" __declspec(naked) void __stdcall __E__8__()
{
	__asm
	{
		jmp p[8 * 4];
	}
}

// GetNameInfoW
extern "C" __declspec(naked) void __stdcall __E__9__()
{
	__asm
	{
		jmp p[9 * 4];
	}
}

// InetNtopW
extern "C" __declspec(naked) void __stdcall __E__10__()
{
	__asm
	{
		jmp p[10 * 4];
	}
}

// InetPtonW
extern "C" __declspec(naked) void __stdcall __E__11__()
{
	__asm
	{
		jmp p[11 * 4];
	}
}

// SetAddrInfoExA
extern "C" __declspec(naked) void __stdcall __E__12__()
{
	__asm
	{
		jmp p[12 * 4];
	}
}

// SetAddrInfoExW
extern "C" __declspec(naked) void __stdcall __E__13__()
{
	__asm
	{
		jmp p[13 * 4];
	}
}

// WEP
extern "C" __declspec(naked) void __stdcall __E__14__()
{
	__asm
	{
		jmp p[14 * 4];
	}
}

// WPUCompleteOverlappedRequest
extern "C" __declspec(naked) void __stdcall __E__15__()
{
	__asm
	{
		jmp p[15 * 4];
	}
}

// WPUGetProviderPathEx
extern "C" __declspec(naked) void __stdcall __E__16__()
{
	__asm
	{
		jmp p[16 * 4];
	}
}

// WSAAccept
extern "C" __declspec(naked) void __stdcall __E__17__()
{
	__asm
	{
		jmp p[17 * 4];
	}
}

// WSAAddressToStringA
extern "C" __declspec(naked) void __stdcall __E__18__()
{
	__asm
	{
		jmp p[18 * 4];
	}
}

// WSAAddressToStringW
extern "C" __declspec(naked) void __stdcall __E__19__()
{
	__asm
	{
		jmp p[19 * 4];
	}
}

// WSAAdvertiseProvider
extern "C" __declspec(naked) void __stdcall __E__20__()
{
	__asm
	{
		jmp p[20 * 4];
	}
}

// WSAAsyncGetHostByAddr
extern "C" __declspec(naked) void __stdcall __E__21__()
{
	__asm
	{
		jmp p[21 * 4];
	}
}

// WSAAsyncGetHostByName
extern "C" __declspec(naked) void __stdcall __E__22__()
{
	__asm
	{
		jmp p[22 * 4];
	}
}

// WSAAsyncGetProtoByName
extern "C" __declspec(naked) void __stdcall __E__23__()
{
	__asm
	{
		jmp p[23 * 4];
	}
}

// WSAAsyncGetProtoByNumber
extern "C" __declspec(naked) void __stdcall __E__24__()
{
	__asm
	{
		jmp p[24 * 4];
	}
}

// WSAAsyncGetServByName
extern "C" __declspec(naked) void __stdcall __E__25__()
{
	__asm
	{
		jmp p[25 * 4];
	}
}

// WSAAsyncGetServByPort
extern "C" __declspec(naked) void __stdcall __E__26__()
{
	__asm
	{
		jmp p[26 * 4];
	}
}

// WSAAsyncSelect
extern "C" __declspec(naked) void __stdcall __E__27__()
{
	__asm
	{
		jmp p[27 * 4];
	}
}

// WSACancelAsyncRequest
extern "C" __declspec(naked) void __stdcall __E__28__()
{
	__asm
	{
		jmp p[28 * 4];
	}
}

// WSACancelBlockingCall
extern "C" __declspec(naked) void __stdcall __E__29__()
{
	__asm
	{
		jmp p[29 * 4];
	}
}

// WSACleanup
extern "C" __declspec(naked) void __stdcall __E__30__()
{
	__asm
	{
		jmp p[30 * 4];
	}
}

// WSACloseEvent
extern "C" __declspec(naked) void __stdcall __E__31__()
{
	__asm
	{
		jmp p[31 * 4];
	}
}

// WSAConnect
extern "C" __declspec(naked) void __stdcall __E__32__()
{
	__asm
	{
		jmp p[32 * 4];
	}
}

// WSAConnectByList
extern "C" __declspec(naked) void __stdcall __E__33__()
{
	__asm
	{
		jmp p[33 * 4];
	}
}

// WSAConnectByNameA
extern "C" __declspec(naked) void __stdcall __E__34__()
{
	__asm
	{
		jmp p[34 * 4];
	}
}

// WSAConnectByNameW
extern "C" __declspec(naked) void __stdcall __E__35__()
{
	__asm
	{
		jmp p[35 * 4];
	}
}

// WSACreateEvent
extern "C" __declspec(naked) void __stdcall __E__36__()
{
	__asm
	{
		jmp p[36 * 4];
	}
}

// WSADuplicateSocketA
extern "C" __declspec(naked) void __stdcall __E__37__()
{
	__asm
	{
		jmp p[37 * 4];
	}
}

// WSADuplicateSocketW
extern "C" __declspec(naked) void __stdcall __E__38__()
{
	__asm
	{
		jmp p[38 * 4];
	}
}

// WSAEnumNameSpaceProvidersA
extern "C" __declspec(naked) void __stdcall __E__39__()
{
	__asm
	{
		jmp p[39 * 4];
	}
}

// WSAEnumNameSpaceProvidersExA
extern "C" __declspec(naked) void __stdcall __E__40__()
{
	__asm
	{
		jmp p[40 * 4];
	}
}

// WSAEnumNameSpaceProvidersExW
extern "C" __declspec(naked) void __stdcall __E__41__()
{
	__asm
	{
		jmp p[41 * 4];
	}
}

// WSAEnumNameSpaceProvidersW
extern "C" __declspec(naked) void __stdcall __E__42__()
{
	__asm
	{
		jmp p[42 * 4];
	}
}

// WSAEnumNetworkEvents
extern "C" __declspec(naked) void __stdcall __E__43__()
{
	__asm
	{
		jmp p[43 * 4];
	}
}

// WSAEnumProtocolsA
extern "C" __declspec(naked) void __stdcall __E__44__()
{
	__asm
	{
		jmp p[44 * 4];
	}
}

// WSAEnumProtocolsW
extern "C" __declspec(naked) void __stdcall __E__45__()
{
	__asm
	{
		jmp p[45 * 4];
	}
}

// WSAEventSelect
extern "C" __declspec(naked) void __stdcall __E__46__()
{
	__asm
	{
		jmp p[46 * 4];
	}
}

// WSAGetLastError
extern "C" __declspec(naked) void __stdcall __E__47__()
{
	__asm
	{
		jmp p[47 * 4];
	}
}

// WSAGetOverlappedResult
extern "C" __declspec(naked) void __stdcall __E__48__()
{
	__asm
	{
		jmp p[48 * 4];
	}
}

// WSAGetQOSByName
extern "C" __declspec(naked) void __stdcall __E__49__()
{
	__asm
	{
		jmp p[49 * 4];
	}
}

// WSAGetServiceClassInfoA
extern "C" __declspec(naked) void __stdcall __E__50__()
{
	__asm
	{
		jmp p[50 * 4];
	}
}

// WSAGetServiceClassInfoW
extern "C" __declspec(naked) void __stdcall __E__51__()
{
	__asm
	{
		jmp p[51 * 4];
	}
}

// WSAGetServiceClassNameByClassIdA
extern "C" __declspec(naked) void __stdcall __E__52__()
{
	__asm
	{
		jmp p[52 * 4];
	}
}

// WSAGetServiceClassNameByClassIdW
extern "C" __declspec(naked) void __stdcall __E__53__()
{
	__asm
	{
		jmp p[53 * 4];
	}
}

// WSAHtonl
extern "C" __declspec(naked) void __stdcall __E__54__()
{
	__asm
	{
		jmp p[54 * 4];
	}
}

// WSAHtons
extern "C" __declspec(naked) void __stdcall __E__55__()
{
	__asm
	{
		jmp p[55 * 4];
	}
}

// WSAInstallServiceClassA
extern "C" __declspec(naked) void __stdcall __E__56__()
{
	__asm
	{
		jmp p[56 * 4];
	}
}

// WSAInstallServiceClassW
extern "C" __declspec(naked) void __stdcall __E__57__()
{
	__asm
	{
		jmp p[57 * 4];
	}
}

// WSAIoctl
extern "C" __declspec(naked) void __stdcall __E__58__()
{
	__asm
	{
		jmp p[58 * 4];
	}
}

// WSAIsBlocking
extern "C" __declspec(naked) void __stdcall __E__59__()
{
	__asm
	{
		jmp p[59 * 4];
	}
}

// WSAJoinLeaf
extern "C" __declspec(naked) void __stdcall __E__60__()
{
	__asm
	{
		jmp p[60 * 4];
	}
}

// WSALookupServiceBeginA
extern "C" __declspec(naked) void __stdcall __E__61__()
{
	__asm
	{
		jmp p[61 * 4];
	}
}

// WSALookupServiceBeginW
extern "C" __declspec(naked) void __stdcall __E__62__()
{
	__asm
	{
		jmp p[62 * 4];
	}
}

// WSALookupServiceEnd
extern "C" __declspec(naked) void __stdcall __E__63__()
{
	__asm
	{
		jmp p[63 * 4];
	}
}

// WSALookupServiceNextA
extern "C" __declspec(naked) void __stdcall __E__64__()
{
	__asm
	{
		jmp p[64 * 4];
	}
}

// WSALookupServiceNextW
extern "C" __declspec(naked) void __stdcall __E__65__()
{
	__asm
	{
		jmp p[65 * 4];
	}
}

// WSANSPIoctl
extern "C" __declspec(naked) void __stdcall __E__66__()
{
	__asm
	{
		jmp p[66 * 4];
	}
}

// WSANtohl
extern "C" __declspec(naked) void __stdcall __E__67__()
{
	__asm
	{
		jmp p[67 * 4];
	}
}

// WSANtohs
extern "C" __declspec(naked) void __stdcall __E__68__()
{
	__asm
	{
		jmp p[68 * 4];
	}
}

// WSAPoll
extern "C" __declspec(naked) void __stdcall __E__69__()
{
	__asm
	{
		jmp p[69 * 4];
	}
}

// WSAProviderCompleteAsyncCall
extern "C" __declspec(naked) void __stdcall __E__70__()
{
	__asm
	{
		jmp p[70 * 4];
	}
}

// WSAProviderConfigChange
extern "C" __declspec(naked) void __stdcall __E__71__()
{
	__asm
	{
		jmp p[71 * 4];
	}
}

// WSARecv
extern "C" __declspec(naked) void __stdcall __E__72__()
{
	__asm
	{
		jmp p[72 * 4];
	}
}

// WSARecvDisconnect
extern "C" __declspec(naked) void __stdcall __E__73__()
{
	__asm
	{
		jmp p[73 * 4];
	}
}

// WSARecvFrom
extern "C" __declspec(naked) void __stdcall __E__74__()
{
	__asm
	{
		jmp p[74 * 4];
	}
}

// WSARemoveServiceClass
extern "C" __declspec(naked) void __stdcall __E__75__()
{
	__asm
	{
		jmp p[75 * 4];
	}
}

// WSAResetEvent
extern "C" __declspec(naked) void __stdcall __E__76__()
{
	__asm
	{
		jmp p[76 * 4];
	}
}

// WSASend
extern "C" __declspec(naked) void __stdcall __E__77__()
{
	__asm
	{
		jmp p[77 * 4];
	}
}

// WSASendDisconnect
extern "C" __declspec(naked) void __stdcall __E__78__()
{
	__asm
	{
		jmp p[78 * 4];
	}
}

// WSASendMsg
extern "C" __declspec(naked) void __stdcall __E__79__()
{
	__asm
	{
		jmp p[79 * 4];
	}
}

// WSASendTo
extern "C" __declspec(naked) void __stdcall __E__80__()
{
	__asm
	{
		jmp p[80 * 4];
	}
}

// WSASetBlockingHook
extern "C" __declspec(naked) void __stdcall __E__81__()
{
	__asm
	{
		jmp p[81 * 4];
	}
}

// WSASetEvent
extern "C" __declspec(naked) void __stdcall __E__82__()
{
	__asm
	{
		jmp p[82 * 4];
	}
}

// WSASetLastError
extern "C" __declspec(naked) void __stdcall __E__83__()
{
	__asm
	{
		jmp p[83 * 4];
	}
}

// WSASetServiceA
extern "C" __declspec(naked) void __stdcall __E__84__()
{
	__asm
	{
		jmp p[84 * 4];
	}
}

// WSASetServiceW
extern "C" __declspec(naked) void __stdcall __E__85__()
{
	__asm
	{
		jmp p[85 * 4];
	}
}

// WSASocketA
extern "C" __declspec(naked) void __stdcall __E__86__()
{
	__asm
	{
		jmp p[86 * 4];
	}
}

// WSASocketW
extern "C" __declspec(naked) void __stdcall __E__87__()
{
	__asm
	{
		jmp p[87 * 4];
	}
}

// WSAStartup
extern "C" __declspec(naked) void __stdcall __E__88__()
{
	__asm
	{
		jmp p[88 * 4];
	}
}

// WSAStringToAddressA
extern "C" __declspec(naked) void __stdcall __E__89__()
{
	__asm
	{
		jmp p[89 * 4];
	}
}

// WSAStringToAddressW
extern "C" __declspec(naked) void __stdcall __E__90__()
{
	__asm
	{
		jmp p[90 * 4];
	}
}

// WSAUnadvertiseProvider
extern "C" __declspec(naked) void __stdcall __E__91__()
{
	__asm
	{
		jmp p[91 * 4];
	}
}

// WSAUnhookBlockingHook
extern "C" __declspec(naked) void __stdcall __E__92__()
{
	__asm
	{
		jmp p[92 * 4];
	}
}

// WSAWaitForMultipleEvents
extern "C" __declspec(naked) void __stdcall __E__93__()
{
	__asm
	{
		jmp p[93 * 4];
	}
}

// WSApSetPostRoutine
extern "C" __declspec(naked) void __stdcall __E__94__()
{
	__asm
	{
		jmp p[94 * 4];
	}
}

// WSCDeinstallProvider
extern "C" __declspec(naked) void __stdcall __E__95__()
{
	__asm
	{
		jmp p[95 * 4];
	}
}

// WSCDeinstallProvider32
extern "C" __declspec(naked) void __stdcall __E__96__()
{
	__asm
	{
		jmp p[96 * 4];
	}
}

// WSCDeinstallProviderEx
extern "C" __declspec(naked) void __stdcall __E__97__()
{
	__asm
	{
		jmp p[97 * 4];
	}
}

// WSCEnableNSProvider
extern "C" __declspec(naked) void __stdcall __E__98__()
{
	__asm
	{
		jmp p[98 * 4];
	}
}

// WSCEnableNSProvider32
extern "C" __declspec(naked) void __stdcall __E__99__()
{
	__asm
	{
		jmp p[99 * 4];
	}
}

// WSCEnumNameSpaceProviders32
extern "C" __declspec(naked) void __stdcall __E__100__()
{
	__asm
	{
		jmp p[100 * 4];
	}
}

// WSCEnumNameSpaceProvidersEx32
extern "C" __declspec(naked) void __stdcall __E__101__()
{
	__asm
	{
		jmp p[101 * 4];
	}
}

// WSCEnumProtocols
extern "C" __declspec(naked) void __stdcall __E__102__()
{
	__asm
	{
		jmp p[102 * 4];
	}
}

// WSCEnumProtocols32
extern "C" __declspec(naked) void __stdcall __E__103__()
{
	__asm
	{
		jmp p[103 * 4];
	}
}

// WSCEnumProtocolsEx
extern "C" __declspec(naked) void __stdcall __E__104__()
{
	__asm
	{
		jmp p[104 * 4];
	}
}

// WSCGetApplicationCategory
extern "C" __declspec(naked) void __stdcall __E__105__()
{
	__asm
	{
		jmp p[105 * 4];
	}
}

// WSCGetApplicationCategoryEx
extern "C" __declspec(naked) void __stdcall __E__106__()
{
	__asm
	{
		jmp p[106 * 4];
	}
}

// WSCGetProviderInfo
extern "C" __declspec(naked) void __stdcall __E__107__()
{
	__asm
	{
		jmp p[107 * 4];
	}
}

// WSCGetProviderInfo32
extern "C" __declspec(naked) void __stdcall __E__108__()
{
	__asm
	{
		jmp p[108 * 4];
	}
}

// WSCGetProviderPath
extern "C" __declspec(naked) void __stdcall __E__109__()
{
	__asm
	{
		jmp p[109 * 4];
	}
}

// WSCGetProviderPath32
extern "C" __declspec(naked) void __stdcall __E__110__()
{
	__asm
	{
		jmp p[110 * 4];
	}
}

// WSCInstallNameSpace
extern "C" __declspec(naked) void __stdcall __E__111__()
{
	__asm
	{
		jmp p[111 * 4];
	}
}

// WSCInstallNameSpace32
extern "C" __declspec(naked) void __stdcall __E__112__()
{
	__asm
	{
		jmp p[112 * 4];
	}
}

// WSCInstallNameSpaceEx
extern "C" __declspec(naked) void __stdcall __E__113__()
{
	__asm
	{
		jmp p[113 * 4];
	}
}

// WSCInstallNameSpaceEx2
extern "C" __declspec(naked) void __stdcall __E__114__()
{
	__asm
	{
		jmp p[114 * 4];
	}
}

// WSCInstallNameSpaceEx32
extern "C" __declspec(naked) void __stdcall __E__115__()
{
	__asm
	{
		jmp p[115 * 4];
	}
}

// WSCInstallProvider
extern "C" __declspec(naked) void __stdcall __E__116__()
{
	__asm
	{
		jmp p[116 * 4];
	}
}

// WSCInstallProvider64_32
extern "C" __declspec(naked) void __stdcall __E__117__()
{
	__asm
	{
		jmp p[117 * 4];
	}
}

// WSCInstallProviderAndChains64_32
extern "C" __declspec(naked) void __stdcall __E__118__()
{
	__asm
	{
		jmp p[118 * 4];
	}
}

// WSCInstallProviderEx
extern "C" __declspec(naked) void __stdcall __E__119__()
{
	__asm
	{
		jmp p[119 * 4];
	}
}

// WSCSetApplicationCategory
extern "C" __declspec(naked) void __stdcall __E__120__()
{
	__asm
	{
		jmp p[120 * 4];
	}
}

// WSCSetApplicationCategoryEx
extern "C" __declspec(naked) void __stdcall __E__121__()
{
	__asm
	{
		jmp p[121 * 4];
	}
}

// WSCSetProviderInfo
extern "C" __declspec(naked) void __stdcall __E__122__()
{
	__asm
	{
		jmp p[122 * 4];
	}
}

// WSCSetProviderInfo32
extern "C" __declspec(naked) void __stdcall __E__123__()
{
	__asm
	{
		jmp p[123 * 4];
	}
}

// WSCUnInstallNameSpace
extern "C" __declspec(naked) void __stdcall __E__124__()
{
	__asm
	{
		jmp p[124 * 4];
	}
}

// WSCUnInstallNameSpace32
extern "C" __declspec(naked) void __stdcall __E__125__()
{
	__asm
	{
		jmp p[125 * 4];
	}
}

// WSCUnInstallNameSpaceEx2
extern "C" __declspec(naked) void __stdcall __E__126__()
{
	__asm
	{
		jmp p[126 * 4];
	}
}

// WSCUpdateProvider
extern "C" __declspec(naked) void __stdcall __E__127__()
{
	__asm
	{
		jmp p[127 * 4];
	}
}

// WSCUpdateProvider32
extern "C" __declspec(naked) void __stdcall __E__128__()
{
	__asm
	{
		jmp p[128 * 4];
	}
}

// WSCUpdateProviderEx
extern "C" __declspec(naked) void __stdcall __E__129__()
{
	__asm
	{
		jmp p[129 * 4];
	}
}

// WSCWriteNameSpaceOrder
extern "C" __declspec(naked) void __stdcall __E__130__()
{
	__asm
	{
		jmp p[130 * 4];
	}
}

// WSCWriteNameSpaceOrder32
extern "C" __declspec(naked) void __stdcall __E__131__()
{
	__asm
	{
		jmp p[131 * 4];
	}
}

// WSCWriteProviderOrder
extern "C" __declspec(naked) void __stdcall __E__132__()
{
	__asm
	{
		jmp p[132 * 4];
	}
}

// WSCWriteProviderOrder32
extern "C" __declspec(naked) void __stdcall __E__133__()
{
	__asm
	{
		jmp p[133 * 4];
	}
}

// WSCWriteProviderOrderEx
extern "C" __declspec(naked) void __stdcall __E__134__()
{
	__asm
	{
		jmp p[134 * 4];
	}
}

// WahCloseApcHelper
extern "C" __declspec(naked) void __stdcall __E__135__()
{
	__asm
	{
		jmp p[135 * 4];
	}
}

// WahCloseHandleHelper
extern "C" __declspec(naked) void __stdcall __E__136__()
{
	__asm
	{
		jmp p[136 * 4];
	}
}

// WahCloseNotificationHandleHelper
extern "C" __declspec(naked) void __stdcall __E__137__()
{
	__asm
	{
		jmp p[137 * 4];
	}
}

// WahCloseSocketHandle
extern "C" __declspec(naked) void __stdcall __E__138__()
{
	__asm
	{
		jmp p[138 * 4];
	}
}

// WahCloseThread
extern "C" __declspec(naked) void __stdcall __E__139__()
{
	__asm
	{
		jmp p[139 * 4];
	}
}

// WahCompleteRequest
extern "C" __declspec(naked) void __stdcall __E__140__()
{
	__asm
	{
		jmp p[140 * 4];
	}
}

// WahCreateHandleContextTable
extern "C" __declspec(naked) void __stdcall __E__141__()
{
	__asm
	{
		jmp p[141 * 4];
	}
}

// WahCreateNotificationHandle
extern "C" __declspec(naked) void __stdcall __E__142__()
{
	__asm
	{
		jmp p[142 * 4];
	}
}

// WahCreateSocketHandle
extern "C" __declspec(naked) void __stdcall __E__143__()
{
	__asm
	{
		jmp p[143 * 4];
	}
}

// WahDestroyHandleContextTable
extern "C" __declspec(naked) void __stdcall __E__144__()
{
	__asm
	{
		jmp p[144 * 4];
	}
}

// WahDisableNonIFSHandleSupport
extern "C" __declspec(naked) void __stdcall __E__145__()
{
	__asm
	{
		jmp p[145 * 4];
	}
}

// WahEnableNonIFSHandleSupport
extern "C" __declspec(naked) void __stdcall __E__146__()
{
	__asm
	{
		jmp p[146 * 4];
	}
}

// WahEnumerateHandleContexts
extern "C" __declspec(naked) void __stdcall __E__147__()
{
	__asm
	{
		jmp p[147 * 4];
	}
}

// WahInsertHandleContext
extern "C" __declspec(naked) void __stdcall __E__148__()
{
	__asm
	{
		jmp p[148 * 4];
	}
}

// WahNotifyAllProcesses
extern "C" __declspec(naked) void __stdcall __E__149__()
{
	__asm
	{
		jmp p[149 * 4];
	}
}

// WahOpenApcHelper
extern "C" __declspec(naked) void __stdcall __E__150__()
{
	__asm
	{
		jmp p[150 * 4];
	}
}

// WahOpenCurrentThread
extern "C" __declspec(naked) void __stdcall __E__151__()
{
	__asm
	{
		jmp p[151 * 4];
	}
}

// WahOpenHandleHelper
extern "C" __declspec(naked) void __stdcall __E__152__()
{
	__asm
	{
		jmp p[152 * 4];
	}
}

// WahOpenNotificationHandleHelper
extern "C" __declspec(naked) void __stdcall __E__153__()
{
	__asm
	{
		jmp p[153 * 4];
	}
}

// WahQueueUserApc
extern "C" __declspec(naked) void __stdcall __E__154__()
{
	__asm
	{
		jmp p[154 * 4];
	}
}

// WahReferenceContextByHandle
extern "C" __declspec(naked) void __stdcall __E__155__()
{
	__asm
	{
		jmp p[155 * 4];
	}
}

// WahRemoveHandleContext
extern "C" __declspec(naked) void __stdcall __E__156__()
{
	__asm
	{
		jmp p[156 * 4];
	}
}

// WahWaitForNotification
extern "C" __declspec(naked) void __stdcall __E__157__()
{
	__asm
	{
		jmp p[157 * 4];
	}
}

// WahWriteLSPEvent
extern "C" __declspec(naked) void __stdcall __E__158__()
{
	__asm
	{
		jmp p[158 * 4];
	}
}

// __WSAFDIsSet
extern "C" __declspec(naked) void __stdcall __E__159__()
{
	__asm
	{
		jmp p[159 * 4];
	}
}

// accept
extern "C" __declspec(naked) void __stdcall __E__160__()
{
	__asm
	{
		jmp p[160 * 4];
	}
}

// bind
extern "C" __declspec(naked) void __stdcall __E__161__()
{
	__asm
	{
		jmp p[161 * 4];
	}
}

// closesocket
extern "C" __declspec(naked) void __stdcall __E__162__()
{
	__asm
	{
		jmp p[162 * 4];
	}
}

// connect
extern "C" __declspec(naked) void __stdcall __E__163__()
{
	__asm
	{
		jmp p[163 * 4];
	}
}

// freeaddrinfo
extern "C" __declspec(naked) void __stdcall __E__164__()
{
	__asm
	{
		jmp p[164 * 4];
	}
}

// getaddrinfo
extern "C" __declspec(naked) void __stdcall __E__165__()
{
	__asm
	{
		jmp p[165 * 4];
	}
}

// gethostbyaddr
extern "C" __declspec(naked) void __stdcall __E__166__()
{
	__asm
	{
		jmp p[166 * 4];
	}
}

//---------------------------------------------------------------------
PHOSTENT gethostbynameOriginal(PTCHAR name) {
	typedef PHOSTENT(__stdcall *pS)(PTCHAR);
	pS pps = (pS)p[167];
	return pps(name);
}

BOOLEAN writeDefaultConfigToFile(HANDLE & hFile)
{
	BOOLEAN errorFlag = FALSE;
	TCHAR lineToWrite[] = "gethostbynameForcedAdapterIP=disabled\n";

	errorFlag = WriteFile(
		hFile,
		lineToWrite,
		_tcslen(lineToWrite),
		NULL,
		NULL
	);

	if (errorFlag == FALSE) {
		_tprintf(TEXT("ws2_32.cfg: Unable to write to file.\n"));
		return FALSE;
	}
	return TRUE;
}

BOOLEAN createAndOpenConfigFile(HANDLE &hFile)
{
	DWORD lastError = 0;

	hFile = CreateFile(
		"ws2_32.cfg",
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	lastError = GetLastError();

	if (lastError == ERROR_SUCCESS && !writeDefaultConfigToFile(hFile)) {
		return FALSE;
	}
	else if (lastError != ERROR_ALREADY_EXISTS) {
		return FALSE;
	}

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("ws2_32.cfg: Unable to open file for write.\n"));
		return FALSE;
	}
	return TRUE;
}

BOOLEAN readConfigFile(const HANDLE &hFile, PTCHAR &fileContent, DWORD &bytesRead)
{
	DWORD fileSize = GetFileSize(hFile, NULL);
	fileContent = new TCHAR[fileSize + 1];

	fileContent[fileSize] = '\0';
	if (!ReadFile(hFile, fileContent, fileSize, &bytesRead, NULL)) {
		_tprintf(TEXT("ws2_32.cfg: Read error.\n"));
		return FALSE;
	}
	return TRUE;
}

BOOLEAN parseConfigFile(const PTCHAR &fileContent)
{
	TCHAR ipAddress[16] = { 0 };
	PTCHAR option, value, nextValue;

	option = _tcstok_s(fileContent, configFileSeparators, &nextValue);
	value = _tcstok_s(NULL, configFileSeparators, &nextValue);
	if (!StrCmp(option, "gethostbynameForcedAdapterIP") && StrCmp(value, "disabled")) {
		StringCchCopy(ipAddress, 15, value);
		ipList[0] = StrToInt(_tcstok_s(ipAddress, ipAddressSeparators, &nextValue));
		ipList[1] = StrToInt(_tcstok_s(NULL, ipAddressSeparators, &nextValue));
		ipList[2] = StrToInt(_tcstok_s(NULL, ipAddressSeparators, &nextValue));
		ipList[3] = StrToInt(_tcstok_s(NULL, ipAddressSeparators, &nextValue));
		ipList[4] = '\0';
		ipListPtr[0] = ipList;
		return TRUE;
	}
	return FALSE;
}

// gethostbyname
extern "C" PHOSTENT __stdcall __E__167__(PTCHAR name)
{
	HANDLE hFile;
	PHOSTENT returnValue = gethostbynameOriginal(name);
	DWORD bytesRead = -1;
	PTCHAR fileContent = NULL;

	StringCchCopy(hostname, 16, name);

	if (createAndOpenConfigFile(hFile) &&
		readConfigFile(hFile, fileContent, bytesRead) &&
		parseConfigFile(fileContent))
	{
		hostentMock.h_name = hostname;
		hostentMock.h_aliases = NULL;
		hostentMock.h_addrtype = AF_INET;
		hostentMock.h_length = 1;
		hostentMock.h_addr_list = ipListPtr;

		returnValue = &hostentMock;
	}

	CloseHandle(hFile);
	delete[] fileContent;

	return returnValue;
}
//---------------------------------------------------------------------

// gethostname
extern "C" __declspec(naked) void __stdcall __E__168__()
{
	__asm
	{
		jmp p[168 * 4];
	}
}

// getnameinfo
extern "C" __declspec(naked) void __stdcall __E__169__()
{
	__asm
	{
		jmp p[169 * 4];
	}
}

// getpeername
extern "C" __declspec(naked) void __stdcall __E__170__()
{
	__asm
	{
		jmp p[170 * 4];
	}
}

// getprotobyname
extern "C" __declspec(naked) void __stdcall __E__171__()
{
	__asm
	{
		jmp p[171 * 4];
	}
}

// getprotobynumber
extern "C" __declspec(naked) void __stdcall __E__172__()
{
	__asm
	{
		jmp p[172 * 4];
	}
}

// getservbyname
extern "C" __declspec(naked) void __stdcall __E__173__()
{
	__asm
	{
		jmp p[173 * 4];
	}
}

// getservbyport
extern "C" __declspec(naked) void __stdcall __E__174__()
{
	__asm
	{
		jmp p[174 * 4];
	}
}

// getsockname
extern "C" __declspec(naked) void __stdcall __E__175__()
{
	__asm
	{
		jmp p[175 * 4];
	}
}

// getsockopt
extern "C" __declspec(naked) void __stdcall __E__176__()
{
	__asm
	{
		jmp p[176 * 4];
	}
}

// htonl
extern "C" __declspec(naked) void __stdcall __E__177__()
{
	__asm
	{
		jmp p[177 * 4];
	}
}

// htons
extern "C" __declspec(naked) void __stdcall __E__178__()
{
	__asm
	{
		jmp p[178 * 4];
	}
}

// inet_addr
extern "C" __declspec(naked) void __stdcall __E__179__()
{
	__asm
	{
		jmp p[179 * 4];
	}
}

// inet_ntoa
extern "C" __declspec(naked) void __stdcall __E__180__()
{
	__asm
	{
		jmp p[180 * 4];
	}
}

// inet_ntop
extern "C" __declspec(naked) void __stdcall __E__181__()
{
	__asm
	{
		jmp p[181 * 4];
	}
}

// inet_pton
extern "C" __declspec(naked) void __stdcall __E__182__()
{
	__asm
	{
		jmp p[182 * 4];
	}
}

// ioctlsocket
extern "C" __declspec(naked) void __stdcall __E__183__()
{
	__asm
	{
		jmp p[183 * 4];
	}
}

// listen
extern "C" __declspec(naked) void __stdcall __E__184__()
{
	__asm
	{
		jmp p[184 * 4];
	}
}

// ntohl
extern "C" __declspec(naked) void __stdcall __E__185__()
{
	__asm
	{
		jmp p[185 * 4];
	}
}

// ntohs
extern "C" __declspec(naked) void __stdcall __E__186__()
{
	__asm
	{
		jmp p[186 * 4];
	}
}

// recv
extern "C" __declspec(naked) void __stdcall __E__187__()
{
	__asm
	{
		jmp p[187 * 4];
	}
}

// recvfrom
extern "C" __declspec(naked) void __stdcall __E__188__()
{
	__asm
	{
		jmp p[188 * 4];
	}
}

// select
extern "C" __declspec(naked) void __stdcall __E__189__()
{
	__asm
	{
		jmp p[189 * 4];
	}
}

// send
extern "C" __declspec(naked) void __stdcall __E__190__()
{
	__asm
	{
		jmp p[190 * 4];
	}
}

// sendto
extern "C" __declspec(naked) void __stdcall __E__191__()
{
	__asm
	{
		jmp p[191 * 4];
	}
}

// setsockopt
extern "C" __declspec(naked) void __stdcall __E__192__()
{
	__asm
	{
		jmp p[192 * 4];
	}
}

// shutdown
extern "C" __declspec(naked) void __stdcall __E__193__()
{
	__asm
	{
		jmp p[193 * 4];
	}
}

// socket
extern "C" __declspec(naked) void __stdcall __E__194__()
{
	__asm
	{
		jmp p[194 * 4];
	}
}

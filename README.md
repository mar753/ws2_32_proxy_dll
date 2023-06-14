# Winsock2 `ws2_32.dll` DLL proxy with `gethostbyname()` overwrite/mock

TL;DR -> Fixes old games/apps LAN using VPN connection problems

Windows binaries: https://github.com/mar753/ws2_32_proxy_dll/tree/master/bin

No changes in routing tables required

## Description
It is a common case that an old software (including games) uses `gethostbyname` WINAPI function/macro to fetch IP address of the network adapters/interfaces present in the Microsoft's Windows systems, what BTW is the wrong design pattern, because this function was never designed for that purpose. Everything is fine when we have only one active network adapter, but when we have more than one (e.g. a physical Ethernet adapter and an active VPN connection adapter created with SoftEther/Hamachi etc.) the effect is that the  `gethostbyname` function returns those two or more IP addresses in arbitrary order and what the old software usually do is fetching the first one - what is not always what we expect.

What this solution allows to do is that you can force an IP address which will be returned while calling `gethostbyname`. This can be defined in the `ws2_32.cfg` file. This file will be automatically created in the same folder (if it does not exist) during calling `gethostbyname` and will have a content: `gethostbynameForcedAdapterIP=disabled`. So the default behavior is exactly the same as calling the original `ws2_32.dll` DLL directly.
When you change the content of this config file to e.g. `gethostbynameForcedAdapterIP=192.168.3.24` it will force that `gethostbyname` will always return only one interface/adapter with the IP: `192.168.3.24`. So the application will actually see that we have only one interface with IPv4 equals to `192.168.3.24`.

I have tested the behavior on Windows 10 and when we are using VPN connection over the Ethernet adapter, in every case on my hardware the first returned IP was the Ethernet adapter's IP and the second one was the VPN connection's IP.
One small issue with this solution is that `ws2_32.dll` is the 'known DLL' (List of the 'known DLLs' is stored in the Windows Registry key: `HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\KnownDLLs`). The 'known DLL' cannot be overwritten (redirected) with the local copy of this DLL pasted in the folder from which an application was started (for performance and security reasons). Those DLLs are always searched for in the system folder (in most cases for 32-bit applications: `C:\Windows\System32`) at the first place. One way to bypass this is to use some DLL injection method and use our DLL in the process of our interest, the second way I have explained in the 'Examples' section, you can overwrite the original DLL in the system folder as well, but I do not recommend this.

In the similar way we can create proxy DLLs e.g. `wsock32.dll` for some older software if this software is using it directly. In case of `wsock32.dll` the benefit is that this library is not on the 'known DLL' list, so to use it we just need to paste our custom proxy DLL inside the folder from where the software will be started and the library will be replaced during `LoadLibrary` WINAPI call (of course when `LoadLibrary` has no absolute path to the system folder provided).

## Example
Black & White PC game from 2001 uses `gethostbyname` WINAPI call (with my current PC's hostname as the parameter) to fetch IP address of the network adapter/interface and chooses the first one returned as the network adapter address. The effect is that I cannot play it over the VPN (cannot connect to the LAN server), because the first IP returned from `gethostbyname` is the IP of my Ethernet adapter (incorrect) instead of the VPN adapter.
We can solve this issue using solution from this repository. Black & White at startup loads `ws2_32.dll` (via `LHMultiplayerR.dll`), as I wrote above this is a 'known DLL' so even despite the fact that we paste `ws2_32.dll` proxy DLL from this repository into the game's root folder, `C:\Windows\System32\ws2_32.dll` version will be loaded. We can get around this by changing `LHMultiplayerR.dll` in some hex editor. Steps:
1. Open `LHMultiplayerR.dll` in some hex editor.
2. Find `ws2_32.dll` string
3. Change it to something different what is not on the 'known DLL' list, e.g. `wsmock.dll`. Remember not to use longer than `ws2_32.dll` name/string (10 chars) and always put `\0` termination char at the end of the string if using shorter name. 
The reason that you cannot use longer name is that you will overwrite something else what is stored right after this string in this binary DLL or in case of inserting new characters (increasing filesize) you will move the rest of the file to a different offset causing references (addresses) to point to the wrong places, both options most probably will crash the application. If you would like to use longer name it will be much more work to have it done, because the longer string will need to be moved into some different position (at the end of this file will be the safest option) and all the references to this string will have to be altered as well to point to the new location, but working directly on binary file to achieve this may be veeeeeeeeeeery time consuming. The best way will be to disassemble `LHMultiplayerR.dll` (using e.g. Interactive Disassembler - IDA), make the change in the assembly code, and assemble it again to the binary code.

For your convenience you can find modified LHMultiplayer.dll file from Black & White v1.30 here: https://www.mediafire.com/file/oa3k3m229ar3fw8/LHMultiplayerR.dll/file it has the string changed to `wsmock.dll`, so the only thing you need to do is to copy `ws2_32.dll` to the Black & White's root folder, change it's name to the `wsmock.dll`, get the modified `LHMultiplayerR.dll` and paste it into the same folder replacing the old one, then create (in the same folder) a file called `ws2_32.cfg` with a content `gethostbynameForcedAdapterIP=<your_adapter_IP>`, replacing `<your_adapter_IP>` with one of your adapter's IP you would like the application to use e.g.:
`gethostbynameForcedAdapterIP=192.168.3.24`

Remark: When using VPN connection (additional network adapter) most probably it will be the 'public' connection in Windows, what means that different rules will apply to this connection in Windows default firewall. In this case we need to remember that our application (runblack.exe here) must be added as an exception rule for incoming connections to Windows firewall for all 'public' type networks and this rule must allow UDP and TCP connections. 
Every time when some application uses network and when we run it for the first time from a given path, Windows will ask if we would like to allow incoming connections to this application, we can select if it applies to 'public' or 'private' networks using checkboxes.
If we will not make such rule in firewall no one will be able to connect to our application. It is a good idea to enable incoming ICMPv4 traffic in 'public' networks as well (`File and Printer Sharing (Echo Request - ICMPv4-In)` rule in the default firewall) this way our PC will respond to ping inside our VPN network.

## Installation
1. Download `ws2_32.dll` binary https://github.com/mar753/ws2_32_proxy_dll/tree/master/bin and paste it into your application folder. It is a 'known DLL' so you need to inject this DLL into some process (using some DLL injector) or force the application to load a different name DLL (just like in the Example section above).
2. Change the `ws2_32.cfg` config to force some IP address or assign `=disabled` to redirect `gethostbyname` to the original `ws2_32.dll`

## Details
This repository contains code for Winsock2 `ws2_32.dll` DLL proxy, where `gethostbyname` WINAPI call is overwritten and can return mock data.

Source code is intended to use with the Visual Studio 2017 or newer (I have used VS 2017 Express).

Wrappit auto proxy (https://www.codeproject.com/Articles/16541/Create-your-Proxy-DLLs-automatically) software was used to generate `ws2_32.dll` proxy DLL source files.

To sniff network packets Wireshark was used, to sniff WINAPI calls API Monitor v2 (32-bit exe in this case) was used and to check which DLL was loaded by an application I have used Process Explorer v16.22.

## License
MIT

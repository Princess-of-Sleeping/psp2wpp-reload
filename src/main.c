
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/clib.h>
#include <psp2/appmgr.h>
#include <taihen.h>


#define SCE_APPMGR_APPID_INVALID (~0) // -1
#define SCE_APPMGR_APPID_SELF    (~1) // -2
#define SCE_APPMGR_APPID_UNK_3   (~2) // -3
#define SCE_APPMGR_APPID_UNK_4   (~3) // -4
#define SCE_APPMGR_APPID_UNK_5   (~4) // -5

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp){

	int res;
	SceUID semaid;

	semaid = sceKernelOpenSema("psp2wpp_sema");
	if(semaid >= 0){
		sceKernelSignalSema(semaid, 1);
		sceKernelCloseSema(semaid);
	}else{
		sceClibPrintf("sceKernelOpenSema: 0x%X\n", semaid);
	}

	res = sceAppMgrDestroyAppByAppId(SCE_APPMGR_APPID_SELF);
	if(res < 0){
		sceClibPrintf("sceAppMgrDestroyAppByAppId: 0x%X\n", res);
	}

	return 0;
}

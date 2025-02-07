#include "z3D/z3D.h"
#include "z3D/actors/z_demo_effect.h"
#include "models.h"

#define DemoEffect_Init_addr 0x22345C
#define DemoEffect_Init ((ActorFunc)DemoEffect_Init_addr)

#define DemoEffect_Destroy_addr 0x2245B8
#define DemoEffect_Destroy ((ActorFunc)DemoEffect_Destroy_addr)

#define DemoEffect_Update_addr 0x262C58
#define DemoEffect_Update ((ActorFunc)DemoEffect_Update_addr)

#define THIS ((DemoEffect*)thisx)

void DemoEffect_rInit(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* reward = THIS;

    DemoEffect_Init(&reward->actor, globalCtx);
    Model_SpawnByActor(&reward->actor, globalCtx, 0);
}

void DemoEffect_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* reward = THIS;

    Model_DestroyByActor(&reward->actor);
    DemoEffect_Destroy(&reward->actor, globalCtx);
}

void DemoEffect_rUpdate(Actor* thisx, GlobalContext* globalCtx){
    u8 type = thisx->params & 0xFF;
    if((type == 0x13 || type == 0x14 || type == 0x15) && gGlobalContext->sceneNum == 0x43 && !(gSaveContext.eventChkInf[4] & 0x800)){
        return;
    }
    DemoEffect_Update(thisx, globalCtx);
}

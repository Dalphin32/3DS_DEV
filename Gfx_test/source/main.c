#include <citro2d.h>

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

typedef struct
{
    C2D_Sprite sprt;
    float dx,dy;
} Sprite;

static C2D_SpriteSheet sprt_sheet;

Sprite current_sprt;

void setup_gfx(){
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); 
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);
}

void initSprt(){
    Sprite* current_sprt_add = &current_sprt;

    C2D_SpriteFromSheet(&current_sprt_add->sprt, sprt_sheet, 0);
    C2D_SpriteSetCenter(&current_sprt_add->sprt, 0.5f, 0.5f);
    C2D_SpriteSetPos(&current_sprt_add->sprt, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

int main(int argc, char* argv[]){
    setup_gfx();

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    sprt_sheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
    
    initSprt();


     

    while(aptMainLoop()){
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));
        C2D_SceneBegin(top);

        printf("\x1b[1;1Hhello");

        C2D_DrawSprite(&current_sprt.sprt);
        C3D_FrameEnd(0);
    }

    C2D_SpriteSheetFree(sprt_sheet);

    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();

    return 0;
}
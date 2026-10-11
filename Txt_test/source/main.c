#include <3ds.h>
#include <stdio.h>

int main(int argc, char**argv){
    gfxInitDefault();


    PrintConsole upper, lower;
    bool selected;
    consoleInit(GFX_TOP,&upper);
    consoleInit(GFX_BOTTOM,&lower);
    
    while(aptMainLoop()){
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break;
        if (kDown & KEY_A) selected = true;
        if (kDown & KEY_B) selected = false;

        if (selected){
            consoleSelect(&upper); 
            printf("\x1b[10;20H \x1b[31mYo \x1b[32myo \x1b[33myo \x1b[0mmy diggity dog");
            consoleSelect(&lower);
            printf("\x1b[10;20H \x1b[30mYo yo yo my diggity dog");
        } 
        else{
            consoleSelect(&lower); 
            printf("\x1b[10;20H \x1b[31mYo \x1b[32myo \x1b[33myo \x1b[0mmy diggity dog");
            consoleSelect(&upper);
            printf("\x1b[10;20H \x1b[30mYo yo yo my diggity dog");
        }

        gfxFlushBuffers();
        gfxSwapBuffers();

        gspWaitForVBlank();
    }


    return 0;
}
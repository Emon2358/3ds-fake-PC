#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_PATH "sdmc/wallpapers/sample_image.bin"
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

static C3D_RenderTarget* top;
static C2D_SpriteSheet spriteSheet;

void cleanup() {
    if (spriteSheet) {
        C2D_SpriteSheetFree(spriteSheet);
    }
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

int main() {
    // 基本的な初期化
    gfxInitDefault();
    gfxSet3D(false); // 3Dを無効化

    // Citro3D初期化
    if (!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE)) {
        printf("C3D_Init failed\n");
        gfxExit();
        return 1;
    }

    // Citro2D初期化
    if (!C2D_Init(C2D_DEFAULT_MAX_OBJECTS)) {
        printf("C2D_Init failed\n");
        C3D_Fini();
        gfxExit();
        return 1;
    }
    C2D_Prepare();

    // RenderTarget作成
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    if (!top) {
        printf("C2D_CreateScreenTarget failed\n");
        cleanup();
        return 1;
    }

    consoleInit(GFX_BOTTOM, NULL); // デバッグ出力用
    printf("Loading image...\n");

    // 画像読み込み
    spriteSheet = C2D_SpriteSheetLoad(IMAGE_PATH);
    if (!spriteSheet) {
        printf("Failed to load image\n");
        cleanup();
        return 1;
    }

    printf("Image loaded successfully\n");
    printf("Press START to exit\n");

    // メインループ
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        
        if (kDown & KEY_START) {
            break;
        }

        // フレーム開始
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        // トップスクリーンのクリアと描画開始
        C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(top);

        // 画像描画
        C2D_Image image = C2D_SpriteSheetGetImage(spriteSheet, 0);
        
        // 画面中央に配置するための計算
        float x = (SCREEN_WIDTH - image.subtex->width) / 2;
        float y = (SCREEN_HEIGHT - image.subtex->height) / 2;
        
        C2D_DrawImageAt(image, x, y, 0.0f, NULL, 1.0f, 1.0f);

        // フレーム終了
        C3D_FrameEnd(0);
        gspWaitForVBlank();
    }

    // クリーンアップ
    cleanup();
    return 0;
}
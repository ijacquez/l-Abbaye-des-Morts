#ifndef RENDER_MANAGER_H_
#define RENDER_MANAGER_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum style_type {
    STYLE_TYPE_8BIT,
    STYLE_TYPE_16BIT,
    STYLE_TYPE_COUNT
} style_type_t;

typedef enum screen_type {
    SCREEN_TYPE_START,
    SCREEN_TYPE_HELP,
    SCREEN_TYPE_HISTORY,
    SCREEN_TYPE_GAMEOVER,
    SCREEN_TYPE_ENDING,
    SCREEN_TYPE_PARCHMENT_1,
    SCREEN_TYPE_PARCHMENT_2,
    SCREEN_TYPE_PARCHMENT_3,
    SCREEN_TYPE_PARCHMENT_4,
    SCREEN_TYPE_PARCHMENT_5,
    SCREEN_TYPE_PARCHMENT_6,
    SCREEN_TYPE_PARCHMENT_RED,
    SCREEN_TYPE_PARCHMENT_BLUE,
    SCREEN_TYPE_COUNT
} screen_type_t;

typedef enum title_type {
    TITLE_TYPE_PRAYER_OF_HOPE,
    TITLE_TYPE_TOWER_OF_THE_BELL,
    TITLE_TYPE_WINE_SUPPLIES,
    TITLE_TYPE_ESCAPE,
    TITLE_TYPE_DEATH_IS_CLOSE,
    TITLE_TYPE_ABANDONED_CHURCH,
    TITLE_TYPE_THE_ALTAR,
    TITLE_TYPE_HANGMAN_TREE,
    TITLE_TYPE_PESTILENT_BEAST,
    TITLE_TYPE_CAVE_OF_ILLUSIONS,
    TITLE_TYPE_PLAGUED_RUINS,
    TITLE_TYPE_CATACOMBS,
    TITLE_TYPE_HIDDEN_GARDEN,
    TITLE_TYPE_GLOOMY_TUNNELS,
    TITLE_TYPE_LAKE_OF_DESPAIR,
    TITLE_TYPE_THE_WHEEL_OF_FAITH,
    TITLE_TYPE_BANQUET_OF_DEATH,
    TITLE_TYPE_UNDERGROUND_RIVER,
    TITLE_TYPE_UNEXPECTED_GATE,
    TITLE_TYPE_EVIL_CHURCH,
    TITLE_TYPE_TORTURED_SOULS,
    TITLE_TYPE_ASHES_TO_ASHES,
    TITLE_TYPE_SATAN,
    TITLE_TYPE_COUNT
} title_type_t;

typedef enum render_type {
    RENDER_TYPE_WINDOW,
    RENDER_TYPE_FULLSCREEN
} render_type_t;

typedef struct tile_rect {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
} tile_rect_t;

typedef enum sprite_flip {
    SPRITE_FLIP_NONE       = 0x00,
    SPRITE_FLIP_HORIZONTAL = 0x01,
    SPRITE_FLIP_VERTICAL   = 0x02
} sprite_flip_t;

typedef struct sprite {
    uint32_t x;
    uint32_t y;
    const tile_rect_t *tile_rect;
    sprite_flip_t flip;
} sprite_t;

typedef void (*load_cb)(void *user_data);

void render_mgr_init(void);
void render_mgr_deinit(void);

void render_mgr_load(void);

void render_mgr_clear(void);
void render_mgr_display(void);

style_type_t render_mgr_style_get(void);
void render_mgr_style_set(const style_type_t style_type);
void render_mgr_style_next(void);

render_type_t render_mgr_render_get(void);
void render_mgr_render_set(const render_type_t render_type);

void render_mgr_screen_render(const screen_type_t screen_type);

void render_mgr_tileset_load(load_cb cb, void *user_data);
void render_mgr_tileset_unload(void);
void render_mgr_tileset_render(const tile_rect_t *tile_rect, uint32_t out_x, uint32_t out_y);

void render_mgr_sprite_render(const sprite_t *sprite);

void render_mgr_font_load(load_cb cb, void *user_data);
void render_mgr_font_unload(void);
void render_mgr_font_title_render(const title_type_t title_type);
void render_mgr_font_number_render(uint8_t number, uint32_t out_x, uint32_t out_y);

#endif /* RENDER_MANAGER_H_ */

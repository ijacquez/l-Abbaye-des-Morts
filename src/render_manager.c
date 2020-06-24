#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "render_manager.h"

#define SCREEN_TYPE_INVALID (-1)

struct tileset_handle {
    SDL_Texture *texture_8bit;
    SDL_Texture *texture_16bit;
    SDL_Texture *texture_font;
};

static struct {
    bool initialized;
    render_type_t render_type;
    style_type_t style_type;

    struct tileset_handle tileset_handle;
} _state = {
    .initialized = false,
    .style_type = STYLE_TYPE_8BIT
};

static const char *_screen_8bit_paths[] = {
    "graphics/intro.png",
    "graphics/help.png",
    "graphics/history.png",
    "graphics/gameover.png",
    "graphics/ending.png",
    "graphics/parchment1.png",
    "graphics/parchment2.png",
    "graphics/parchment3.png"
    "graphics/parchment4.png"
    "graphics/parchment5.png"
    "graphics/parchment6.png"
    "graphics/redparch.png",
    "graphics/blueparch.png"
};

static const char *_screen_16bit_paths[] = {
    "graphics/intromd.png",
    "graphics/helpmd.png",
    "graphics/history.png",
    "graphics/gameover.png",
    "graphics/ending.png",
    "graphics/parchment1.png",
    "graphics/parchment2.png",
    "graphics/parchment3.png"
    "graphics/parchment4.png"
    "graphics/parchment5.png"
    "graphics/parchment6.png"
    "graphics/redparch.png",
    "graphics/blueparch.png"
};

static const char *_tileset_8bit_path = "graphics/tiles.png";
static const char *_tileset_16bit_path = "graphics/tilesmd.png";

static const char *_tileset_font_path = "graphics/fonts.png";

/* XXX: Mark as "static" */
SDL_Window *screen;
SDL_Renderer *renderer;

static SDL_Texture *_tileset_get(void);

void render_mgr_init(void)
{
    if (_state.initialized) {
        return;
    }

    _state.initialized = true;

    screen = SDL_CreateWindow("Abbaye des Morts v2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 576, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "0");
    SDL_RenderSetLogicalSize(renderer, 256, 192);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void render_mgr_clear(void)
{
    SDL_RenderClear(renderer);
}

void render_mgr_display(void)
{
    SDL_RenderPresent(renderer);
}

style_type_t render_mgr_style_get(void)
{
    return _state.style_type;
}

void render_mgr_style_set(const style_type_t style_type)
{
    _state.style_type = style_type;
}

void render_mgr_style_next(void)
{
    int32_t style_index = (int32_t)_state.style_type;

    style_index++;

    if (style_index >= STYLE_TYPE_COUNT) {
        style_index = 0;
    }

    _state.style_type = style_index;
}

render_type_t render_mgr_render_get(void)
{
    return _state.render_type;
}

void render_mgr_render_set(const render_type_t render_type)
{
    switch (render_type) {
    case RENDER_TYPE_WINDOW:
        _state.render_type = render_type;

        SDL_SetWindowFullscreen(screen, SDL_WINDOW_SHOWN);
        break;

    case RENDER_TYPE_FULLSCREEN:
        _state.render_type = render_type;

        SDL_SetWindowFullscreen(screen, SDL_WINDOW_FULLSCREEN_DESKTOP);
        break;
defalut:
        return;
    }
}

void render_mgr_screen_render(const screen_type_t screen_type)
{
    const char **paths;

    switch (_state.style_type) {
    case STYLE_TYPE_8BIT:
        paths = _screen_8bit_paths;
        break;

    case STYLE_TYPE_16BIT:
        paths = _screen_16bit_paths;
        break;

    default:
        paths = NULL;
    }

    if (paths == NULL) {
        return;
    }

    const int32_t screen_index = (int32_t)screen_type;

    if ((screen_index < 0) || (screen_index >= SCREEN_TYPE_COUNT)) {
        return;
    }

    const char *path = paths[screen_index];

    SDL_Texture *texture = IMG_LoadTexture(renderer, path);

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_DestroyTexture(texture);
}

void render_mgr_tileset_load(load_cb cb, void *user_data)
{
    _state.tileset_handle.texture_8bit = IMG_LoadTexture(renderer, _tileset_8bit_path);
    _state.tileset_handle.texture_16bit = IMG_LoadTexture(renderer, _tileset_16bit_path);

    /* XXX: Check for any error related to IMG_LoadTexture */

    if (cb != NULL) {
        cb(user_data);
    }
}

void render_mgr_tileset_unload(void)
{
    if (_state.tileset_handle.texture_8bit != NULL) {
        SDL_DestroyTexture(_state.tileset_handle.texture_8bit);

        _state.tileset_handle.texture_8bit = NULL;
    }

    if (_state.tileset_handle.texture_16bit != NULL) {
        SDL_DestroyTexture(_state.tileset_handle.texture_16bit);

        _state.tileset_handle.texture_16bit = NULL;
    }
}

void render_mgr_tileset_render(const tile_rect_t *tile_rect, uint32_t out_x, uint32_t out_y)
{
    SDL_Texture *texture = _tileset_get();

    if (texture == NULL) {
        return;
    }

    const SDL_Rect src_rect = {
        .x = tile_rect->x,
        .y = tile_rect->y,
        .w = tile_rect->width,
        .h = tile_rect->height
    };

    const SDL_Rect dst_rect = {
        .x = out_x,
        .y = out_y,
        .w = src_rect.w,
        .h = src_rect.h
    };

    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

void render_mgr_sprite_render(const sprite_t *sprite)
{
    SDL_Texture *texture = _tileset_get();

    if (texture == NULL) {
        return;
    }

    const SDL_Rect src_rect = {
        .x = sprite->tile_rect->x,
        .y = sprite->tile_rect->y,
        .w = sprite->tile_rect->width,
        .h = sprite->tile_rect->height
    };

    const SDL_Rect dst_rect = {
        .x = sprite->x,
        .y = sprite->y,
        .w = src_rect.w,
        .h = src_rect.h
    };

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if ((sprite->flip & SPRITE_FLIP_HORIZONTAL) == SPRITE_FLIP_HORIZONTAL) {
        flip &= ~SDL_FLIP_NONE;
        flip |= SDL_FLIP_HORIZONTAL;
    }

    if ((sprite->flip & SPRITE_FLIP_VERTICAL) == SPRITE_FLIP_VERTICAL) {
        flip &= ~SDL_FLIP_NONE;
        flip |= SDL_FLIP_VERTICAL;
    }

    SDL_RenderCopyEx(renderer, texture, &src_rect, &dst_rect,
                     /* angle:  */ 0.0, /* center:  */ NULL, flip);
}

void render_mgr_font_load(load_cb cb, void *user_data)
{
    _state.tileset_handle.texture_font = IMG_LoadTexture(renderer, _tileset_font_path);

    /* XXX: Check for any error related to IMG_LoadTexture */

    if (cb != NULL) {
        cb(user_data);
    }
}

void render_mgr_font_unload(void)
{
    if (_state.tileset_handle.texture_font != NULL) {
        SDL_DestroyTexture(_state.tileset_handle.texture_font);

        _state.tileset_handle.texture_font = NULL;
    }
}

void render_mgr_font_title_render(const title_type_t title_type)
{
    const int32_t title_index = (int32_t)title_type;

    if ((title_index < 0) || (title_index >= TITLE_TYPE_COUNT)) {
        return;
    }

    SDL_Texture *texture_font = _state.tileset_handle.texture_font;

    const SDL_Rect src_rect = {
        .x = 0,
        .y = title_index * 20,
        .w = 140,
        .h = 20
    };

    const SDL_Rect dst_rect = {
        .x = 115,
        .y = 174,
        .w = 136,
        .h = 20
    };

    SDL_RenderCopy(renderer, texture_font, &src_rect, &dst_rect);
}

void render_mgr_font_number_render(uint8_t number, uint32_t out_x, uint32_t out_y)
{
    SDL_Texture *texture_font = _state.tileset_handle.texture_font;

    SDL_Rect src_rect = {
        .x = 0,
        .y = 460,
        .w = 10,
        .h = 10
    };

    SDL_Rect dst_rect = {
        .x = out_x,
        .y = out_y,
        .w = 10,
        .h = 10
    };

    uint8_t digits[3];
    uint8_t digit_count = 0;

    uint8_t count_number = number;

    do {
        digits[digit_count] = count_number % 10;
        count_number /= 10;

        digit_count++;
    } while (count_number > 0);

    for (uint8_t i = 0; i < digit_count; i++) {
        uint8_t digit = digits[digit_count - i - 1];

        src_rect.x = digit * src_rect.w;

        SDL_RenderCopy(renderer, texture_font, &src_rect, &dst_rect);

        dst_rect.x += dst_rect.w;
    }
}

void render_mgr_deinit(void)
{
    if (!_state.initialized) {
        return;
    }

    _state.initialized = false;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
}

static SDL_Texture *_tileset_get(void)
{
    switch (_state.style_type) {
    case STYLE_TYPE_8BIT:
        return _state.tileset_handle.texture_8bit;

    case STYLE_TYPE_16BIT:
        return _state.tileset_handle.texture_16bit;

    default:
        return NULL;
    }
}

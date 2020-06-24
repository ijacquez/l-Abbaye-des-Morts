#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "sound_manager.h"

#define BGM_TYPE_INVALID (-1)

static struct {
    bool initialized;
    bool bgm_paused;
    bgm_type_t bgm_playing_type;
    bool sfx_playing[SFX_TYPE_COUNT];
} _state = {
    .initialized = false,
    .bgm_paused = false,
    .bgm_playing_type = BGM_TYPE_INVALID
};

static Mix_Music *_bgm_handles[BGM_TYPE_COUNT];
static Mix_Chunk *_sfx_handles[SFX_TYPE_COUNT];

void sound_mgr_init(void)
{
    if (_state.initialized) {
        return;
    }

    _state.initialized = true;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(5);

    _bgm_handles[BGM_TYPE_MAINTITLEN] = Mix_LoadMUS("sounds/MainTitleN.ogg");
    _bgm_handles[BGM_TYPE_PRAYEROFHOPEN] = Mix_LoadMUS("sounds/PrayerofHopeN.ogg");
    _bgm_handles[BGM_TYPE_AREAICHURCHN] = Mix_LoadMUS("sounds/AreaIChurchN.ogg");
    _bgm_handles[BGM_TYPE_GAMEOVERV2N] = Mix_LoadMUS("sounds/GameOverV2N.ogg");
    _bgm_handles[BGM_TYPE_HANGMANSTREE] = Mix_LoadMUS("sounds/HangmansTree.ogg");
    _bgm_handles[BGM_TYPE_AREAIICAVESV2N] = Mix_LoadMUS("sounds/AreaIICavesV2N.ogg");
    _bgm_handles[BGM_TYPE_EVILFIGHTN] = Mix_LoadMUS("sounds/EvilFightN.ogg");
    _bgm_handles[BGM_TYPE_AREAIIIHELLN] = Mix_LoadMUS("sounds/AreaIIIHellN.ogg");
    _bgm_handles[BGM_TYPE_MANHUNTWOODN] = Mix_LoadMUS("sounds/ManhuntwoodN.ogg");
    _bgm_handles[BGM_TYPE_MANHUNTN] = Mix_LoadMUS("sounds/ManhuntN.ogg");

    _sfx_handles[SFX_TYPE_SHOOT] = Mix_LoadWAV("sounds/shoot.ogg");
    _sfx_handles[SFX_TYPE_DOOR_SFX_HANDLES] = Mix_LoadWAV("sounds/door_sfx_handles.ogg");
    _sfx_handles[SFX_TYPE_ITEM] = Mix_LoadWAV("sounds/Item.ogg");
    _sfx_handles[SFX_TYPE_JUMP] = Mix_LoadWAV("sounds/jump.ogg");
    _sfx_handles[SFX_TYPE_SLASH] = Mix_LoadWAV("sounds/slash.ogg");
    _sfx_handles[SFX_TYPE_MECHANISMN] = Mix_LoadWAV("sounds/mechanismn.ogg");
    _sfx_handles[SFX_TYPE_ONEDEATHN] = Mix_LoadWAV("sounds/onedeathn.ogg");

    _state.bgm_playing_type = BGM_TYPE_INVALID;

    for (uint32_t i = 0; i < SFX_TYPE_COUNT; i++) {
        _state.sfx_playing[i] = false;
    }
}

void sound_mgr_deinit(void)
{
    if (!_state.initialized) {
        return;
    }

    _state.initialized = false;

    for (uint32_t i = 0; i < BGM_TYPE_COUNT; i++) {
        Mix_FreeMusic(_bgm_handles[i]);
    }

    for (uint32_t i = 0; i < SFX_TYPE_COUNT; i++) {
        Mix_FreeChunk(_sfx_handles[i]);
    }
}

void sound_mgr_sfx_play(sfx_type_t sfx_type)
{
    const int32_t sfx_index = (int32_t)sfx_type;

    if ((sfx_index < 0) || (sfx_index >= SFX_TYPE_COUNT)) {
        return;
    }

    const int channel = -1;
    Mix_Chunk *sfx_handle = _sfx_handles[sfx_index];
    const int loops = 0;

    int error = Mix_PlayChannel(channel, sfx_handle, loops);

    if (error < 0) {
        return;
    }

    _state.sfx_playing[sfx_index] = true;
}

bool sound_mgr_bgm_playing(void)
{
    int32_t bgm_index = (int32_t)_state.bgm_playing_type;

    return ((bgm_index != BGM_TYPE_INVALID) && !_state.bgm_paused);
}

void sound_mgr_bgm_stop(void)
{
    if (!(sound_mgr_bgm_playing())) {
        return;
    }

    Mix_HaltMusic();

    _state.bgm_playing_type = BGM_TYPE_INVALID;
}

void sound_mgr_bgm_pause(void)
{
    if (_state.bgm_paused) {
        return;
    }

    _state.bgm_paused = true;

    Mix_PauseMusic();
}

void sound_mgr_bgm_unpause(void)
{
    if (!_state.bgm_paused) {
        return;
    }

    _state.bgm_paused = false;

    Mix_ResumeMusic();
}

void sound_mgr_bgm_play(bgm_type_t bgm_type, bool loop)
{
    const int32_t bgm_index = (int32_t)bgm_type;

    if ((bgm_index < 0) || (bgm_index >= BGM_TYPE_COUNT)) {
        return;
    }

    if (_state.bgm_paused) {
        return;
    }

    if ((sound_mgr_bgm_playing())) {
        sound_mgr_bgm_stop();
    }

    Mix_Music *bgm_handle = _bgm_handles[bgm_index];
    int loops = (loop) ? -1 : 0;

    int error = Mix_PlayMusic(bgm_handle, loops);

    if (error < 0) {
        return;
    }

    _state.bgm_playing_type = (bgm_type_t)bgm_index;
}

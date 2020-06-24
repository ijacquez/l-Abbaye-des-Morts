#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <stdbool.h>

typedef enum bgm_type {
    BGM_TYPE_MAINTITLEN,
    BGM_TYPE_PRAYEROFHOPEN,
    BGM_TYPE_AREAICHURCHN,
    BGM_TYPE_GAMEOVERV2N,
    BGM_TYPE_HANGMANSTREE,
    BGM_TYPE_AREAIICAVESV2N,
    BGM_TYPE_EVILFIGHTN,
    BGM_TYPE_AREAIIIHELLN,
    BGM_TYPE_MANHUNTWOODN,
    BGM_TYPE_MANHUNTN,
    BGM_TYPE_COUNT
} bgm_type_t;

typedef enum sfx_type {
    SFX_TYPE_SHOOT,
    SFX_TYPE_DOOR_SFX_HANDLES,
    SFX_TYPE_ITEM,
    SFX_TYPE_JUMP,
    SFX_TYPE_SLASH,
    SFX_TYPE_MECHANISMN,
    SFX_TYPE_ONEDEATHN,
    SFX_TYPE_COUNT
} sfx_type_t;

void sound_mgr_init(void);
void sound_mgr_deinit(void);

void sound_mgr_sfx_play(sfx_type_t sfx_type);

bool sound_mgr_bgm_playing(void);
void sound_mgr_bgm_play(bgm_type_t bgm_type, bool loop);
void sound_mgr_bgm_pause(void);
void sound_mgr_bgm_unpause(void);
void sound_mgr_bgm_stop(void);

#endif /* SOUND_MANAGER_H_ */

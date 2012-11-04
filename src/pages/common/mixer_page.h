#ifndef _MIXER_PAGE_H_
#define _MIXER_PAGE_H_

#include "mixer.h"
#include "gui/gui.h"
#include "buttons.h"
#define NUM_COMPLEX_MIXERS 10
#define LONG_PRESS_STEP 5
#define SUBTRIM_RANGE 500  // subtrim <100 is insufficient

struct curve_edit {
    struct buttonAction action;
    struct Curve curve;
    struct Curve *curveptr;
    void(*parent)(void);
    s8 pointnum;
    guiObject_t *graph;
    guiObject_t *value;
    guiObject_t *pointsel;
};

struct mixer_page {
    struct buttonAction action;
    struct LabelDesc labelDesc;
    u8 are_limits_changed;
    u8 top_channel;
    u8 max_scroll;
    guiObject_t *firstObj;
    guiObject_t *scroll_bar;
    guiObject_t *itemObj[NUM_OUT_CHANNELS *2 + NUM_VIRT_CHANNELS];
    guiObject_t *trimObj;
    guiObject_t *expoObj[10];
    struct Mixer mixer[NUM_COMPLEX_MIXERS];
    struct Mixer *cur_mixer;
    struct Limit limit;
    guiObject_t *graphs[3];
    u8 channel;
    u8 num_mixers;
    u8 num_complex_mixers;
    u8 link_curves;
    u8 entries_per_page;
    char tmpstr[30];
    s16 raw[NUM_SOURCES + 1];
    u8 list[NUM_CHANNELS > NUM_COMPLEX_MIXERS ? NUM_CHANNELS : NUM_COMPLEX_MIXERS];

    enum TemplateType cur_template;

    struct curve_edit edit;
};

extern const char *channel_name[];

const char *PAGEMIXER_SetNumberCB(guiObject_t *obj, int dir, void *data);
void MIXPAGE_EditCurves(struct Curve *curve, void *data);
const char *MIXPAGE_TemplateName(enum TemplateType template);
const char *MIXPAGE_ChannelNameCB(guiObject_t *obj, const void *data);
const char *MIXPAGE_ChanNameProtoCB(guiObject_t *obj, const void *data);
void MIXPAGE_ChangeTemplate(int show_header);
void MIXPAGE_EditLimits();

#endif


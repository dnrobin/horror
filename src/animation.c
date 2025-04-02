#include "shared.h"
#include "animation.h"



static animator_t main_animator;

void update_animations(float timeStep)
{
    static float internal_time = 0;

    for (int i = 0; i < MAX_ANIMATION_TRACKS; ++i) {

        animation_t *anim = &main_animator.animation_tracks[i];

        if (anim->is_done) {
            continue;
        }

        if (anim->next_update == -1 
            || internal_time >= anim->next_update) {

            switch (anim->type) {

                case ANIM_TYPE_CALLBACK:
                    anim->props.callback_0p();
                    break;
                
                case ANIM_TYPE_KEYFRAME:
                    // skip for now
                    break;
            }

            anim->next_update = internal_time + anim->interval;

            // check if anim done
            if (0) {
                anim->is_done = true;
            }
        }
    }

    internal_time += timeStep;
}
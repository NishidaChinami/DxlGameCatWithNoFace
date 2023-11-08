#include "../dxlib_ext/dxlib_ext.h"
#include"Story.h"


void Story::Draw() {
	text = story_sentence.substr(0, letter_count_);
	if (story_sentence.length() > letter_count_) {
		letter_count_ += full_width_;
	}
	if (chara_side_ == 0)DrawStringEx(MOB_SERIF.x, MOB_SERIF.y, -1, "%s", text.c_str());
	if (chara_side_ == 1)DrawStringEx(PLAYER_SERIF.x, PLAYER_SERIF.y, -1, "%s", text.c_str());
}

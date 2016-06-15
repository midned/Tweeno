
#pragma once

#include "Tweeno/Repeat.h"
#include "Tweeno/Tween.h"
#include "Tweeno/Easing/Type.h"

#include <map>
#include <functional>

namespace Tweeno {

class Tween;

class TweenList {
public:
	TweenList();
	~TweenList();

	Tween* add();
	Tween* add(float from, float to);
	Tween* add(const char* tween_name);
	Tween* add(const char* tween_name, float from, float to);

	void start();
	void invert();
	void update(float delta);

	TweenList* easing(easing_function fn);
	TweenList* easing_back(easing_function fn);

	TweenList* repeat(Repeat r);
	TweenList* repeat_delay(float seconds);

	TweenList* set_duration(float duration);
	float get_duration();

	TweenList* seek(float seconds);
	float current_time();

	bool is_finished();
	bool is_completed();

	void pause();
	void resume();
	bool is_paused();


	float get_progress();
	TweenList* set_progress(float progress);

	float get_timescale();
	TweenList* set_timescale(float t);

	void on_update(std::function<void (std::map<const char*, Tween*>&)> callback);
	void on_complete(std::function<void ()> callback);

	typedef std::map<const char*, Tween*> list_type;
private:
	const char* create_key();
	void apply_defaults(Tween* t);

	list_type tweens;

	std::function<void (list_type&)> on_update_callback;

	// defaults
	float _default_timescale;
	float _default_duration;
	easing_function _default_easing;
	easing_function _default_easing_back;
	float _default_repeat_delay;
	Repeat _default_repeat;
};

}

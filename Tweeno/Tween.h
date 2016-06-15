
#pragma once

#include "Tweeno/TweenList.h"
#include "Tweeno/Repeat.h"
#include "Tweeno/Easing/Type.h"

#include <functional>

namespace Tweeno {

class TweenList;

class Tween {
public:
	Tween(float from, float to);
	Tween();
	~Tween();

	void start();
	void invert();
	void update(float delta);

	Tween* from(float from);
	Tween* to(float to);

	Tween* easing(easing_function easing);
	Tween* easing_back(easing_function easing_back);

	Tween* repeat(Repeat r);
	Tween* repeat_delay(float seconds);

	Tween* set_duration(float seconds);
	float get_duration();

	Tween* seek(float seconds);
	float current_time();

	bool is_finished();
	bool is_completed();

	Tween* target(float* target);
	Tween* target(int* target);

	float value();

	void pause();
	void resume();
	bool is_paused();


	float get_progress();
	Tween* set_progress(float progress);

	float get_timescale();
	Tween* set_timescale(float t);

	void on_update(std::function<void (float)> callback);
	void on_complete(std::function<void ()> callback);
private:
	float start_value;
	float current_value;
	float end_value;

	float duration;
	float timescale;
	float _current_time;
	float* _f_target;
	int* _i_target;

	float _repeat_delay;
	float _repeat_delay_elapsed;

	easing_function _easing;
	easing_function _easing_back;

	Repeat _repeat;

	bool paused;

	std::function<void (float)> on_update_callback;
	std::function<void ()> on_complete_callback;
};

}

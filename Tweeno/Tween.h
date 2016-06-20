
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
	bool is_running();

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
	float _start_value;
	float _current_value;
	float _end_value;

	float _duration;
	float _timescale;
	float _current_time;
	float* _f_target;
	int* _i_target;

	float _repeat_delay;
	float _repeat_delay_elapsed;

	easing_function _easing;
	easing_function _easing_back;

	Repeat _repeat;

	bool _paused;

	std::function<void (float)> _on_update_callback;
	std::function<void ()> _on_complete_callback;
};

}


#include "Tweeno/Tween.h"
#include "Tweeno/Repeat.h"
#include "Tweeno/Easing/Linear.h"
#include "Tweeno/Easing/Type.h"

#include <iostream>

/**
 * @namespace Tweeno
 * @brief The tweeno namespace
 */
namespace Tweeno {

/**
 * @brief Create a new tween object
 *
 * @param from Initial value of the tween
 * @param to End value of the tween
 */
Tween::Tween(float from, float to): _start_value(from), _current_value(from), _end_value(to), _duration(0), _timescale(1.f), _f_target(nullptr), _i_target(nullptr), _easing(Easing::Linear::easeNone), _repeat(Repeat::NONE) {
	start();
}

/**
 * @brief Create a tween without values
 * @details Create a new tween with empty values that may be set later
 */
Tween::Tween(): Tween(0, 0) { }

/**
 * @brief Set the tween to it initial values
 * @details Restarts the tween
 */
void Tween::start() {
	_paused = false;
	_current_time = 0.f;
	_current_value = _start_value;
	_repeat_delay_elapsed = 0;
}

/**
 * @brief Invert values of the tween
 * @details Invert values of the tween, used when Tween::repeat() is set as Repeat::YOYO
 */
void Tween::invert() {
	_current_time = _duration-_current_time;

	std::swap(_start_value, _end_value);

	if (_easing_back) {
		std::swap(_easing_back, _easing);
	}
}

/**
 * @brief Update the tween
 * @details Update the tween using delta time
 *
 * @param delta The delta time to update in seconds
 */
void Tween::update(float delta) {
	// Do not update if tween is paused or already finished
	if (is_paused() || is_finished()) {
		return;
	}
	// see Tween::set_timescale()
	_current_time = _current_time+delta*_timescale;

	// If current tween just finished
	if (is_finished()) {
		// and _repeat is set to YOYO or LOOP
        if (_repeat != Repeat::NONE) {
    		// wait the delay to repeat
    		if (_repeat_delay_elapsed < _repeat_delay) {
    			_repeat_delay_elapsed += delta*_timescale;
    		}
    		// when delay time is reached
    		else {
    			// Invert values and restart in case of YOYO repeat type
    			if (_repeat == Repeat::YOYO) {
    				invert();
    				start();
    			}
    			// Only restart, in case of Repeat::LOOP
    			else {
    				start();
    			}
    		}
    	}
	}

	// Update the tween value using the specified easing function
	_current_value = _easing(_current_time, _start_value, _end_value-_start_value, _duration);

	// if is set a target (either int or float)
	// update it with the current value
	if (_f_target != nullptr) {
		*_f_target = _current_value;
	}
	if (_i_target != nullptr) {
		*_i_target = _current_value;
	}

	// if is set a function to call in each update
	if (_on_update_callback) {
		// call it
		_on_update_callback(_current_value);
	}
	// check again if is finished so it is called once
	// and if is set a function to call when the tween ends
	if (is_finished() && _on_complete_callback) {
		// call it
		_on_complete_callback();
	}
}

/**
 * @brief Set the initial value of the tween
 *
 * @param from Initial value
 * @return The tween object, for method chaining
 */
Tween* Tween::from(float from) {
	_start_value = from;
	_current_value = _start_value;

	return this;
}

/**
 * @brief Set the end value of the tween
 *
 * @param to End value
 * @return The tween object, for method chaining
 */
Tween* Tween::to(float to) {
	_end_value = to;

	return this;
}

/**
 * @brief Set the easing function
 * @details Set the easing function to use
 *
 * @code
 * using namespace Tweeno;
 * Tween* t1 = new Tween(0, 150); // from 0 to 150 (float)
 *
 * // default easings included
 * t1->easing(Easing::Linear::easeNone);
 * t1->easing(Easing::Bounce::easeOut);
 *
 * // or you can create your own
 * t1->easing([](float t,float b , float c, float d) {
 * 		//stuff
 * });
 * @endcode
 *
 * @param easing Easing function, can be one of the included ones of created manually using std::function<float (float, float, float, float)>
 * @return The tween object, for method chaining
 */
Tween* Tween::easing(easing_function easing) {
	_easing = easing;

	return this;
}

/**
 * @brief Set the easing function when the tween is going back
 * @details Set the easing function when the tween is going back, used only when repeat is set to Repeat::YOYO
 *
 * @param easing_back Easing function, can be one of the included ones of created manually using std::function<float (float, float, float, float)>
 * @return The tween object, for method chaining
 */
Tween* Tween::easing_back(easing_function easing_back) {
	_easing_back = easing_back;

	return this;
}

/**
 * @brief Set the repeat type
 *
 * @param r The repeat type
 * - Tweeno::Repeat::NONE to not repeat
 * - Tweeno::Repeat::LOOP to repeat
 * - Tweeno::Repeat::YOYO to repeat back and forward
 *
 * @return The tween object, for method chaining
 */
Tween* Tween::repeat(Repeat r) {
	_repeat = r;

	return this;
}

/**
 * @brief Set delay time to wait until the tween repeats
 *
 * @param seconds Time to wait, in seconds
 * @return The tween object, for method chaining
 */
Tween* Tween::repeat_delay(float seconds) {
	_repeat_delay = seconds;

	return this;
}

/**
 * @brief Set the duration of the tween
 *
 * @param seconds The duration, in seconds
 * @return The tween object, for method chaining
 */
Tween* Tween::set_duration(float seconds) {
	_duration = seconds;

	return this;
}

/**
 * @brief Get the _duration of the tween
 *
 * @return The _duration
 */
float Tween::get_duration() {
	return _duration;
}

/**
 * @brief Set the current time of the tween
 *
 * @param seconds The current time to be set
 * @return The tween object, for method chaining
 */
Tween* Tween::seek(float seconds) {
	_current_time = seconds;
	update(0);
	return this;
}

/**
 * @brief Get the current time of the tween
 *
 * @return The current time (float), in seconds
 */
float Tween::current_time() {
	return _current_time;
}

/**
 * @brief Check if the tween is already finished
 *
 * @return True if already finished, false otherwise
 */
bool Tween::is_finished() {
	return _current_time > _duration;
}

/**
 * @brief Alias to Tween::is_finished()
 */
bool Tween::is_completed() {
	return is_finished();
}

/**
 * @brief Check if tween is still running
 *
 * @return True if tween is running, false otherwise
 */
bool Tween::is_running() {
	return ! is_finished();
}

/**
 * @brief Set the target float variable to update
 *
 * @code
 * using namespace Tweeno;
 * Tween* t1 = new Tween(100, 150);
 *
 * float x; // the variable we want to update
 *
 * t1->target(&x); // now on every update the variable x will change
 * @endcode
 *
 * @param target Pointer to the float variable
 * @return The tween object, for method chaining
 */
Tween* Tween::target(float* target) {
	_f_target = target;

	return this;
}

/**
 * @brief Set the target int variable to update
 *
 * @param target Pointer to the int variable
 * @return The tween object, for method chaining
 */
Tween* Tween::target(int* target) {
	_i_target = target;

	return this;
}

/**
 * @brief Get the current value of the twee
 *
 * @return The current value
 */
float Tween::value() {
	return _current_value;
}

/**
 * @brief Pauses the tween
 */
void Tween::pause() {
	_paused = true;
}

/**
 * @brief Resumes the tween
 */
void Tween::resume() {
	_paused = false;
}

/**
 * @brief Checks if the tween is _paused
 *
 * @return True if is _paused, false otherwise
 */
bool Tween::is_paused() {
	return _paused;
}

/**
 * @brief Get current progress of tween
 *
 * @return The current progress, going from 0.f to 1.f
 */
float Tween::get_progress() {
	return _current_time / _duration;
}

/**
 * @brief Set the progress of the tween
 *
 * @param progress The progress, going from 0.f to 1.f
 * @return The tween object, for method chaining
 */
Tween* Tween::set_progress(float progress) {
	_current_time = _duration*progress;
	update(0);
	return this;
}

/**
 * @brief Get the time scale
 *
 * @return The time scale set
 */
float Tween::get_timescale() {
	return _timescale;
}

/**
 * @brief Set the time scale of the tween (default 1)
 * @details The time scale modifies the delta time passed to Tween::update(dt), making dt = dt*_timescale
 *
 * @param t The time scale to be set
 * @return The tween object, for method chaining
 */
Tween* Tween::set_timescale(float t) {
	_timescale = t;
	return this;
}

/**
 * @brief Set the function to be called in each update
 *
 * @code
 * using namespace Tweeno;
 * Tween* t1 = new Tween();
 *
 * t1->on_update([](float value) {
 * 		// this will be called on each update
 * 		// you can log the value or manually update a variable using the new value
 * });
 * @endcode
 *
 * @param callback The callback
 */
void Tween::on_update(std::function<void (float)> callback) {
	_on_update_callback = callback;
}

/**
 * @brief Set the callback to be called when the tween finishes
 *
 * @code
 * using namespace Tweeno;
 * Tween* t1 = new Tween();
 *
 * t1->on_complete([](){
 * 		// will be called when the tweening ends
 * });
 *
 * @endcode
 *
 * @param callback The callback
 */
void Tween::on_complete(std::function<void ()> callback) {
	_on_complete_callback = callback;
}

}

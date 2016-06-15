
#include "Tweeno/TweenList.h"
#include "Tweeno/Repeat.h"
#include "Tweeno/Easing/Type.h"
#include "Tweeno/Easing/Linear.h"
#include "Tweeno/Tween.h"

#include <iostream>
#include <tuple>
#include <functional>
#include <string>

/**
 * @namespace Tweeno
 * @brief The tweeno namespace
 */
namespace Tweeno {

const char* TweenList::create_key() {
	return (std::string("tween_") + std::to_string(tweens.size())).c_str();
}

void TweenList::apply_defaults(Tween* t) {
	t->set_duration(_default_duration);
	t->easing(_default_easing);
	t->repeat(_default_repeat);
	t->repeat_delay(_default_repeat_delay);
	t->set_timescale(_default_timescale);
}

/**
 * @brief Create a new tween list
 *
 * @details Tween list are used to have multiple tweens grouped with same properties, updating variables at the same time.
 *
 */
TweenList::TweenList(): _default_timescale(1.f), _default_duration(0), _default_easing(Easing::Linear::easeNone), _default_repeat_delay(0), _default_repeat(Repeat::NONE) {

}

TweenList::~TweenList() {
	tweens.clear();
}

/**
 * @brief Add a new tween
 * @details Creates a new tween with empty values and return it so we can set them
 *
 * @return The created tween object
 */
Tween* TweenList::add() {
	return add(create_key(), 0,  0);
}

/**
 * @brief Add a new tween
 * @details Creates a new tween using values
 *
 * @param from The initial value of the tween
 * @param to The end value of the tween
 *
 * @return The created tween object
 */
Tween* TweenList::add(float from, float to) {
	return add(create_key(), from, to);
}

/**
 * @brief Add a new tween
 * @details Creates a new tween and adds it to the list by using an identifier that we can use in TweenList::on_update()
 *
 * @param tween_name The identifier of the tween
 * @return The created tween object
 */
Tween* TweenList::add(const char* tween_name) {
	return add(tween_name, 0, 0);
}

/**
 * @brief Add a new tween
 * @details Creates a new tween with the specified identifier and initial/end values
 *
 * @param tween_name The identifier of the tween
 * @param from The initial value of the tween
 * @param to The end value of the tween
 * @return The created tween object
 */
Tween* TweenList::add(const char* tween_name, float from, float to) {
	Tween* t = new Tween(from, to);

	apply_defaults(t);

	tweens[tween_name] = t;
	return t;
}

/**
 * @brief Set all tweens to they initial values
 */
void TweenList::start() {
	for (auto & it : tweens) {
		it.second->start();
	}
}

/**
 * @brief Invert all the tweens
 */
void TweenList::invert() {
	for (auto & it : tweens) {
		it.second->invert();
	}
}


/**
 * @brief Update all the tweens
 * @details Update all the tweens with the given delta time
 *
 * @param delta Elapsed time in seconds (float)
 */
void TweenList::update(float delta) {
	for (auto & it : tweens) {
		it.second->update(delta);
	}
	if (on_update_callback) {
		on_update_callback(tweens);
	}
}

/**
 * @brief Set the easing function of all tweens
 *
 * @param fn The easing function (can be created manually, see Tween::easing() )
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::easing(easing_function fn) {
	for (auto & it : tweens) {
		it.second->easing(fn);
	}
	_default_easing = fn;

	return this;
}

/**
 * @brief Set the easing function for when the tweens go back
 *
 * @param fn The easing function (can be created manually, see Tween::easing_back() )
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::easing_back(easing_function fn) {
	for (auto & it : tweens) {
		it.second->easing_back(fn);
	}
	_default_easing_back = fn;

	return this;
}

/**
 * @brief Set the repeat type
 *
 * @param r - The repeat type
 * - Tweeno::Repeat::NONE to not repeat
 * - Tweeno::Repeat::LOOP to repeat
 * - Tweeno::Repeat::YOYO to repeat back and forward
 *
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::repeat(Repeat r) {
	for (auto & it : tweens) {
		it.second->repeat(r);
	}
	_default_repeat = r;

	return this;
}

/**
 * @brief Set delay time to wait until all the tweens repeat
 *
 * @param seconds Time to wait, in seconds
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::repeat_delay(float seconds) {
	for (auto & it : tweens) {
		it.second->repeat_delay(seconds);
	}
	_default_repeat_delay = seconds;

	return this;
}

/**
 * @brief Set the duration of all the tweens
 *
 * @param seconds The duration, in seconds
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::set_duration(float duration) {
	for (auto & it : tweens) {
		it.second->set_duration(duration);
	}
	_default_duration = duration;

	return this;
}

/**
 * @brief Get the duration of all the tweens
 * @details Get the default duration used when adding a new tween to the list
 *
 * @return The duration
 */
float TweenList::get_duration() {
	return _default_duration;
}

/**
 * @brief Set the current time of all the tweens
 *
 * @param seconds The current time to be set
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::seek(float seconds) {
	for (auto & it : tweens) {
		it.second->seek(seconds);
	}
	on_update_callback(tweens);
	return this;
}

/**
 * @brief Get the current time of the tweens
 * @details Get the current time of the tweens, using the first one as actually all of them are updated at the same time
 *
 * @return The current time (float), in seconds
 */
float TweenList::current_time() {
	if (tweens.empty()) {
		return 0.f;
	}
	return (*tweens.begin()).second->current_time();
}

/**
 * @brief Check if all tweens are already finished
 * @details Check if all tweens are already finished, using the first one as actually all of them are supposed to end at the same time
 *
 * @return True if already finished, false otherwise
 */
bool TweenList::is_finished() {
	if (tweens.empty()) {
		return true;
	}

	return (*tweens.begin()).second->is_finished();
}

/**
 * @brief Alias to TweenList::is_finished()
 */
bool TweenList::is_completed() {
	return is_finished();
}

/**
 * @brief Pauses all tweens
 */
void TweenList::pause() {
	for (auto & it : tweens) {
		it.second->pause();
	}
}

/**
 * @brief Resumes all tweens
 */
void TweenList::resume() {
	for (auto & it : tweens) {
		it.second->resume();
	}
}

/**
 * @brief Check if all tweens are paused
 * @details Check if tweens are paused, actually only check the first one, as actually, they all have to be at the same state
 * @return True if tweens are paused, false otherwise
 */
bool TweenList::is_paused() {
	if (tweens.empty()) {
		return true;
	}

	return (*tweens.begin()).second->is_paused();
}

/**
 * @brief Get progress of tweens
 * @details Get the progress of all the tweens, returning the progress of the first one actually as they all update at the same time with the same delta time
 * @return The current progress, going from 0.f to 1.f
 */
float TweenList::get_progress() {
	if (tweens.empty()) {
		return 0;
	}
	return (*tweens.begin()).second->get_progress();
}

/**
 * @brief Set the progress of all the tweens
 *
 * @param progress The progress, going from 0.f to 1.f
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::set_progress(float progress) {
	for (auto & it : tweens) {
		it.second->set_progress(progress);
	}
	on_update_callback(tweens);
	return this;
}

/**
 * @brief Get the time scale
 *
 * @return The time scale set
 */
float TweenList::get_timescale() {
	return _default_timescale;
}

/**
 * @brief Set the time scale of all tweens (default 1)
 * @details The time scale modifies the delta time passed to Tween::update(dt), making dt = dt*timescale
 *
 * @param t The time scale to be set
 * @return The actual tweenlist, for method chaining
 */
TweenList* TweenList::set_timescale(float t) {
	for (auto & it : tweens) {
		it.second->set_timescale(t);
	}
	_default_timescale = t;

	return this;
}

/**
 * @brief Set the update callback
 * @details Set the callback to be called on each update, it will be passed the std::map containing all the tweens, so one could get any value of any tween
 *
 * @code
 * using namespace Tweeno;
 * TweenList* tweens = new TweenList();
 *
 * tweens->add("x")->from(0)->to(150);
 *
 * tweens->on_update([](TweenList::list_type& tweens) {
 * 		float value = tweens["x"]->value();
 * });
 * @endcode
 *
 * @param callback The callback
 */
void TweenList::on_update(std::function<void (list_type&)> callback) {
	on_update_callback = callback;
}

/**
 * @brief Set the complete callback
 * @details Set the callback to be called when all tweens are completed (actually set the on_complete callback on the last tween, so it will be called when actually all of them are complete)
 *
 * @param callback The callback
 */
void TweenList::on_complete(std::function<void ()> callback) {
	if (tweens.size() > 0) {
		(*tweens.rbegin()).second->on_complete(callback);
	}
}

}

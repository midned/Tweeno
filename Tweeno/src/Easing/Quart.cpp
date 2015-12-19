
#include "Easing/Quart.h"

#include "Easing/Type.h"

namespace Tweeno {

namespace Easing {

easing_function Quart::easeIn = [](float t,float b , float c, float d) {
	return c*(t/=d)*t*t*t + b;
};

easing_function Quart::easeOut = [](float t,float b , float c, float d) {
	return -c * ((t=t/d-1)*t*t*t - 1) + b;
};

easing_function Quart::easeInOut = [](float t,float b , float c, float d) {
	if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
	return -c/2 * ((t-=2)*t*t*t - 2) + b;
};

}

}
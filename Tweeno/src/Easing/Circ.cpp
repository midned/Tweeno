
#include "Easing/Circ.h"

#include "Easing/Type.h"

#include <math.h>

namespace Tweeno {

namespace Easing {

easing_function Circ::easeIn = [](float t,float b , float c, float d) {
	return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
};

easing_function Circ::easeOut = [](float t,float b , float c, float d) {
	return c * sqrt(1 - (t=t/d-1)*t) + b;
};

easing_function Circ::easeInOut = [](float t,float b , float c, float d) {
	if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
	return c/2 * (sqrt(1 - t*(t-=2)) + 1) + b;
};

}

}
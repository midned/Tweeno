
#include "Easing/Sine.h"

#include "Easing/Type.h"

#include <math.h>

namespace Tweeno {

namespace Easing {

easing_function Sine::easeIn = [](float t,float b , float c, float d) {
	return -c * cos(t/d * (PI/2)) + c + b;
};

easing_function Sine::easeOut = [](float t,float b , float c, float d) {	
	return c * sin(t/d * (PI/2)) + b;	
};

easing_function Sine::easeInOut = [](float t,float b , float c, float d) {
	return -c/2 * (cos(PI*t/d) - 1) + b;
};

}

}
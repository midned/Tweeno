
#include "Tweeno/Easing/Cubic.h"

#include "Tweeno/Easing/Type.h"

namespace Tweeno {

namespace Easing {

easing_function Cubic::easeIn = [](float t,float b , float c, float d) {
	return c*(t/=d)*t*t + b;
};

easing_function Cubic::easeOut = [](float t,float b , float c, float d) {
	return c*((t=t/d-1)*t*t + 1) + b;
};

easing_function Cubic::easeInOut = [](float t,float b , float c, float d) {
	if ((t/=d/2) < 1) return c/2*t*t*t + b;
	return c/2*((t-=2)*t*t + 2) + b;
};

}

}

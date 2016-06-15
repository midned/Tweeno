
#include "Tweeno/Easing/Expo.h"

#include "Tweeno/Easing/Type.h"

#include <math.h>

namespace Tweeno {

namespace Easing {

easing_function Expo::easeIn = [](float t,float b , float c, float d) {
	return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
};

easing_function Expo::easeOut = [](float t, float b, float c, float d) -> float {
	return (float)((t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b);
};

easing_function Expo::easeInOut = [](float t,float b , float c, float d) {
	if (t==0) return b;
	if (t==d) return b+c;
	if ((t/=d/2) < 1) return (float)(c/2 * pow(2, 10 * (t - 1)) + b);
	return (float)(c/2 * (-pow(2, -10 * --t) + 2) + b);
};

}

}

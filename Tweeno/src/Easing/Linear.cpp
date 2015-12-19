
#include "Easing/Linear.h"

#include "Easing/Type.h"

namespace Tweeno {

namespace Easing {

easing_function Linear::easeNone = [](float t,float b , float c, float d) {
	return c*t/d + b;
};

easing_function Linear::easeIn = [](float t,float b , float c, float d) {
	return c*t/d + b;
};

easing_function Linear::easeOut = [](float t,float b , float c, float d) {	
	return c*t/d + b;
};

easing_function Linear::easeInOut = [](float t,float b , float c, float d) {
	return c*t/d + b;
};

}

}

#include "Easing/Quad.h"

#include "Easing/Type.h"

namespace Tweeno {

namespace Easing {

easing_function Quad::easeIn = [](float t,float b , float c, float d) {
	return c*(t/=d)*t + b;
};

easing_function Quad::easeOut = [](float t,float b , float c, float d) {
	return -c *(t/=d)*(t-2) + b;
};

easing_function Quad::easeInOut = [](float t,float b , float c, float d) {
	if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
	return -c/2 * (((t-2)*(--t)) - 1) + b;
	/*
	originally return -c/2 * (((t-2)*(--t)) - 1) + b;
	
	I've had to swap (--t)*(t-2) due to diffence in behaviour in 
	pre-increment operators between java and c++, after hours
	of joy
	*/
	
};

}

}
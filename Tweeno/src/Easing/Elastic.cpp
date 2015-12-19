
#include "Easing/Elastic.h"

#include "Easing/Type.h"

#include <math.h>

namespace Tweeno {

namespace Easing {

easing_function Elastic::easeIn = [](float t,float b , float c, float d) {
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
	return (float)(-(postFix * sin((t*d-s)*(2*PI)/p )) + b);
};

easing_function Elastic::easeOut = [](float t,float b , float c, float d) {
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	return (float)(a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);	
};

easing_function Elastic::easeInOut = [](float t,float b , float c, float d) {
	if (t==0) return b;  if ((t/=d/2)==2) return b+c; 
	float p=d*(.3f*1.5f);
	float a=c; 
	float s=p/4;
	 
	if (t < 1) {
		float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
		return (float)(-.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b);
	} 
	float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
	return (float)(postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b);
};

}

}
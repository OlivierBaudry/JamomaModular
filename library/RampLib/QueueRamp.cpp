/* 
 * Jamoma RampUnit: linear.queue
 * Linear ramping function using the Max queue
 *
 * By Tim Place, Copyright � 2006, 2007
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "Jamoma.h"
#include "QueueRamp.h"

// called by the Max queue, and provided to the qelem -- needs to have a C interface
void queueramp_qfn(QueueRamp *x)
{
	x->tick();
}


QueueRamp::QueueRamp(RampUnitCallback aCallbackMethod, void *aBaton)
	: RampUnit("ramp.queue", aCallbackMethod, aBaton)
{
	active = 0;
	qelem = qelem_new(this, (method)queueramp_qfn);	// install the queue element
}


QueueRamp::~QueueRamp()
{
	qelem_unset(qelem);
	qelem_free(qelem);
}


void QueueRamp::go(TTUInt32 inNumValues, TTFloat64 *inValues, TTFloat64 time)
{
	TTUInt32 i;
	
	ramptime 	= time;
	startTime	= systime_ms();
	targetTime	= startTime + time;

	setNumValues(inNumValues);
	for (i=0; i<numValues; i++) {
		targetValue[i] = inValues[i];
		startValue[i] = currentValue[i];
	}
	normalizedValue = 0.0;	// set the ramp to the beginning
	active = 1;
	qelem_set(qelem);		// Start the ramp!
}


void QueueRamp::stop()
{
	active = 0;
	qelem_unset(qelem);
}


void QueueRamp::tick()
{
	unsigned long 	currentTime = systime_ms();
	TTUInt32		i;
	double			mapped;
	double			*current = currentValue;
	double			*target = targetValue;
	double			*start = startValue;
	float			ratio;
	
	if (active && functionUnit) {
		if (currentTime > targetTime) {
			active = 0;
			for (i=0; i < numValues; i++)
				currentValue[i] = targetValue[i];
		}
		else {
			ratio = (currentTime - startTime) / (float)ramptime;
			functionUnit->calculate(ratio, mapped);
			for (i=0; i < numValues; i++)
				current[i] = (target[i] * mapped) + (start[i] * (1 - mapped));
			qelem_set(qelem);							// set the qelem element to run again
		}
		(callback)(baton, numValues, currentValue);		// send the value to the host
	}
}


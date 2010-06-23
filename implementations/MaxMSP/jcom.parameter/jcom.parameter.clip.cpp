/* 
 * jcom.param - clipping and range methods
 * By Tim Place, Copyright � 2006
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "jcom.parameter.h"		// everything we need is in here
#include "TTAudioObject.h"	// use the ttblue clipping functions


// Attempt to limit the range of values on generic input
bool param_clip_generic(t_param *x)
{
	if (x->list_size > 1)
		return param_clip_list(x);
	else if (x->atom_list[0].a_type == A_LONG)
		return param_clip_int(x);
	else if (x->atom_list[0].a_type == A_FLOAT)
		return param_clip_float(x);
	else
		return false;
}


// range limiting on int input
bool param_clip_int(t_param *x)
{
	long val = atom_getlong(&x->attr_value);
	long clipped;
	
	if (x->common.attr_clipmode == jps_low)
		clipped = TTLimitMin(val, (long)x->common.attr_range[0]);
	else if (x->common.attr_clipmode == jps_high)
		clipped = TTLimitMax(val, (long)x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_both)
		clipped = TTClip(val, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_wrap)
		clipped = TTInfWrap(val, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_fold)
		clipped = TTFold(val, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
	else
		clipped = val;

	atom_setlong(&x->attr_value, clipped);	// must be set for all cases to cast the jps_none type correctly too
	return clipped != val;
}


// range limiting on float input
bool param_clip_float(t_param *x)
{
	float val = atom_getfloat(&x->attr_value);
	float clipped;

	if (x->common.attr_clipmode == jps_low)
		clipped = TTLimitMin(val, x->common.attr_range[0]);
	else if (x->common.attr_clipmode == jps_high)
		clipped = TTLimitMax(val, x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_both)
		clipped = TTClip(val, x->common.attr_range[0], x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_wrap)
		clipped = TTInfWrap(val, x->common.attr_range[0], x->common.attr_range[1]);
	else if (x->common.attr_clipmode == jps_fold)
		clipped = TTFold(val, x->common.attr_range[0], x->common.attr_range[1]);
	else
	clipped = val;

	atom_setfloat(&x->attr_value, clipped);	// must be set for all cases to cast the jps_none type correctly too
	
	// cannot just compare the two floats here, unfortunately, because of rounding errors from the clipping functions [TAP]
	if (fabs(clipped-val) < 0.0001)
		return false;	// did not clip, or difference was so small that we assume we didn't.
	else
		return true;	// did clip
}


// range limiting on list input
bool param_clip_list(t_param *x)
{
	short	i;
	float	fclipped;
	long	iclipped;
	//bool	didClipAll = false;
	
	// the code regarding didClipAll is supposed to return true when every member of the list has been clipped to its limit
	// that way ramping can be terminated prematurely if it was trying to ramp to something out of range
	// however, this code as it is doesn't work, and it doesn't buy us much anyway
	// so I'm just commenting it out for the time being [TAP]
	
	for (i=0; i < x->list_size; i++) {
		if (x->atom_list[i].a_type == A_LONG) {
			if (x->common.attr_clipmode == jps_low)
				iclipped = TTLimitMin(x->atom_list[i].a_w.w_long, (long)x->common.attr_range[0]);
			else if (x->common.attr_clipmode == jps_high)
				iclipped = TTLimitMax(x->atom_list[i].a_w.w_long, (long)x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_both)
				iclipped = TTClip(x->atom_list[i].a_w.w_long, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_wrap)
				iclipped = TTInfWrap(x->atom_list[i].a_w.w_long, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_fold)
				iclipped = TTFold(x->atom_list[i].a_w.w_long, (long)x->common.attr_range[0], (long)x->common.attr_range[1]);
			else
				iclipped = x->atom_list[i].a_w.w_long;

			//if (didClipAll && !(iclipped == x->atom_list[i].a_w.w_long))
			//	didClipAll = false;
			x->atom_list[i].a_w.w_long = iclipped;
		}
		else if (x->atom_list[i].a_type == A_FLOAT) {
			if (x->common.attr_clipmode == jps_low)
				fclipped = TTLimitMin(x->atom_list[i].a_w.w_float, x->common.attr_range[0]);
			else if (x->common.attr_clipmode == jps_high)
				fclipped = TTLimitMax(x->atom_list[i].a_w.w_float, x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_both)
				fclipped = TTClip(x->atom_list[i].a_w.w_float, x->common.attr_range[0], x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_wrap)
				fclipped = TTInfWrap(x->atom_list[i].a_w.w_float, x->common.attr_range[0], x->common.attr_range[1]);
			else if (x->common.attr_clipmode == jps_fold)
				fclipped = TTFold(x->atom_list[i].a_w.w_float, x->common.attr_range[0], x->common.attr_range[1]);
			else
				fclipped = x->atom_list[i].a_w.w_float;

			//if (didClipAll && !(fclipped == x->atom_list[i].a_w.w_float))
			//	didClipAll = false;
			x->atom_list[i].a_w.w_float = fclipped;
		}
	}
	//return didClipAll;
	return false;
}

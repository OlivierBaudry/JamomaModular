/* 
 * Jamoma DataspaceLib: GainDataspace
 * Copyright � 2007, Trond Lossius
 * 
 * License: This code is licensed under the terms of the "New BSD License"
 * http://creativecommons.org/licenses/BSD/
 *
 * Neutral unit is linear amplitude
 */

#include "GainDataspace.h"
#include <math.h>



LinearAmplitudeUnit::LinearAmplitudeUnit()
	: DataspaceUnit("linear")
{;}


LinearAmplitudeUnit::~LinearAmplitudeUnit()
{;}


void LinearAmplitudeUnit::convertToNeutral(long inputNumArgs, t_atom *inputAtoms, long *outputNumArgs, double *output)
{
	*outputNumArgs = 1;
	
	*output = atom_getfloat(inputAtoms);
	// avoid negative valus that might blow up some convertions
	if (*output<0)
		*output = 0;

}


void LinearAmplitudeUnit::convertFromNeutral(long inputNumArgs, double *input, long *outputNumArgs, t_atom **outputAtoms)
{
	*outputNumArgs = 1;
	atom_setfloat(*outputAtoms, *input);
}


/***********************************************************************************************/
MidiGainUnit::MidiGainUnit()
	: DataspaceUnit("midi")
{;}


MidiGainUnit::~MidiGainUnit()
{;}
		

void MidiGainUnit::convertToNeutral(long inputNumArgs, t_atom *inputAtoms, long *outputNumArgs, double *output)
{
	*outputNumArgs = 1;
	// This is the old formula behaving the same as the gain~ object:
	// *output =  pow(10., (atom_getfloat(inputAtoms)-127.)*0.03);
	// Now substituted for:
	*output = pow(atom_getfloat(inputAtoms)*0.01,kGainMidiPower);
}


void MidiGainUnit::convertFromNeutral(long inputNumArgs, double *input, long *outputNumArgs, t_atom **outputAtoms)
{
	*outputNumArgs = 1;
	// This is the old formula behaving the same as the gain~ object:
	// atom_setfloat(*outputAtoms, log10(*input)*33.333333333333+127.);
	// Now substituted for:
	atom_setfloat(*outputAtoms, 100.*pow((*input),kGainMidiPowerInv));
}


/***********************************************************************************************/
DecibelUnit::DecibelUnit()
	: DataspaceUnit("dB")
{;}


DecibelUnit::~DecibelUnit()
{;}
		
		
void DecibelUnit::convertToNeutral(long inputNumArgs, t_atom *inputAtoms, long *outputNumArgs, double *output)
{
	*outputNumArgs = 1;
	*output = pow(10., atom_getfloat(inputAtoms)*0.05);
}


void DecibelUnit::convertFromNeutral(long inputNumArgs, double *input, long *outputNumArgs, t_atom **outputAtoms)
{
	*outputNumArgs = 1;	
	atom_setfloat(*outputAtoms, log10(*input)*20.);
}


/***********************************************************************************************/
GainDataspace::GainDataspace()
	: DataspaceLib("gain", "linear")
{
	// Create one of each kind of unit, and cache them in a hash
	registerUnit(new LinearAmplitudeUnit,	SymbolGen("linear"));
	registerUnit(new MidiGainUnit,			SymbolGen("midi"));
	registerUnit(new DecibelUnit,			SymbolGen("dB"));
	registerUnit(new DecibelUnit,			SymbolGen("db"));

	// Now that the cache is created, we can create a set of default units
	setInputUnit(neutralUnit);
	setOutputUnit(neutralUnit);
}


GainDataspace::~GainDataspace()
{
	;
}

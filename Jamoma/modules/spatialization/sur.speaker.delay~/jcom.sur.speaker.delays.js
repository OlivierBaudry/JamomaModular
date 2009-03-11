// Javascript for Jamoma: scripting and setting delays to adjust
// for speaker layout when distance to speakers differs.
// By Trond Lossius, ©2006
// License: GNU LGPL


/*******************************************************************
 * SETUP
 *******************************************************************/

autowatch = 1;

// CONSTANTS

SPEED_OF_SOUND = 343.8;                // Speed of sound at 20°C (m/s)
SPEED_OF_SOUND_FEET = 1127.95;        // Speed of sound at 20°C (feet)
MAX_VOICES = 32;                    // Maximum number of speakers

// VARIABLES

var sample_rate = 44100;
var sample_rate_ms = sample_rate * 0.001;
var DSP_running = 0;
var distance = new Array(MAX_VOICES);
var delaySamples = new Array(MAX_VOICES);
var num_voices = 0;                    // Current number of voices
var num_voices_prev = 0;            // Previous number of voices
var hold_voices = 0;                // If audio is running, voices will not be changed
                                    // Instead the message is held until audio is turned off
var hold_flag = 0;                    // Flag indicating if change in number of voices 
                                    // is currently on hold
var i                                // A counter


// INLETS AND OUTLETS

outlets = 1+MAX_VOICES;

setinletassist(0,"Messages: position, numSpeakers, sr, dspstate");
setoutletassist(0,"Scripting messages");

for (i=0; i<MAX_VOICES; i++)
{
    setoutletassist(i+1, "Delay in samples for voice "+(i+1));
    distance[i]=1;
}    

function sr(value)
{
    if (sample_rate==value) return;
    
    sample_rate = value;
    sample_rate_ms = value * 0.001;
    calculate_delays();
}

function dspstate(value)
{
    DSP_running = value;
    
    if (value==0)
    {
        if (hold_flag==1)
            numSpeakers(hold_voices);
    }
}

function position()
{
    var a = arrayfromargs(messagename,arguments);
    
    distance[(a[1]-1)] = a[4];
    calculate_delays();
}

function numSpeakers(value)
{
    // Put change in number of voices on hold if audio is running
    if (DSP_running==1)
    {
        hold_voices = value;
        hold_flag = 1;
        
        post("jmod.sur.speaker.delays~: Audio is currently running.");
        post();
        post("Number of voices will be updated next time audio is turned off.");
        post();
    }
    
    else
    {    
        // Only perform scripting if the number of voices actually change
        if (value==num_voices) return;    

        num_voices_prev = num_voices;
        num_voices = value;
        
        if (num_voices > MAX_VOICES)
            num_voices = MAX_VOICES;
        if (num_voices < 0)
            num_voices = 0;
        
        for (i=0; i<num_voices_prev; i++)
        {
            outlet(0, "script", "delete", "delay["+(i+1)+"]");
        }
        for (i=0; i<num_voices; i++)
        {
            outlet(0, "script", "new", "delay["+(i+1)+"]", "newex", (220+40*i), (220+25*i), 73, 196617, "delay~", 44100);
            outlet(0, "script", "connect", "multiout", i, "delay["+(i+1)+"]", 0);
            outlet(0, "script", "connect", "delay["+(i+1)+"]", 0, "multiin", i);
            outlet(0, "script", "connect", "javascript", (i+1), "delay["+(i+1)+"]", 1);
        }
    }
}

function calculate_delays()
{
    var i;
    var max_dist = 0;
    
    for (i=0; i<num_voices; i++)
    {
        if (distance[i]>max_dist)
            max_dist = distance[i];
    }
    for (i=0; i<num_voices; i++)
    {   delaySamples[i] = (max_dist - distance[i]) * (sample_rate / SPEED_OF_SOUND);
        outlet(i+1, delaySamples[i]);
    }
}

// the following procedures were added by Nils Peters on March 10, 2009
// TODO: if SR changes, the state of the current delays are wrong. 
function delay()   
{
    var a = arrayfromargs(messagename,arguments);    
        
    if (a[1] <= num_voices)
    { 
      delaySamples[a[1]-1] = (a[2] * sample_rate_ms); // we expect a time delay in ms
      outlet(a[1], delaySamples[a[1]-1]); 
     
     //post("outlet: ",a[1],"delay :", a[2],"samples: ", a[2] * sample_rate_ms);
     //post();
    }
}

function bypass(toggle)
{
    if (toggle == 0)
    {
     for (i=0; i<num_voices; i++)
        {
        outlet(i+1, delaySamples[i]);
        }
    }
    else if (toggle == 1)
        {
        for (i=0; i<num_voices; i++)
        {
        outlet(i+1, 0 );
        }
    }
}



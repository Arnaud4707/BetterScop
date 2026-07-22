#ifndef AUDIOSTATS_HPP
#define AUDIOSTATS_HPP

struct AudioStats
{
    float minRms;
    float maxRms;

    float minBass;
    float maxBass;

    float minMid;
    float maxMid;

    float minHigh;
    float maxHigh;

    float minCentroid;
    float maxCentroid;
};

#endif
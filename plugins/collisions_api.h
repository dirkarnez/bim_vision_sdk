#ifndef collisions_apiH
#define collisions_apiH

#include "ifc_plugin_api.h"

namespace collisions
{

enum MessageType
{
    mt_disable_intersections,  // do not display intersections (red objects) til next user action with plugin
                               // returns:
                               //     result = 1

};

//NOTE: if plugin is in demo mode and reach its demmo limitation conditions result will be 0


}

#endif

#ifndef ifc_comments_apiH
#define ifc_comments_apiH

#include "ifc_plugin_api.h"

namespace ifc_comments
{

enum MessageType
{
    mt_clear,           // clear all topics added by plugin (no params)
                        // returns:
                        //     result = 1

    mt_add_topic,       // add topic:
                        //     param1.string = name
                        //     param2.string = description
                        // returns:
                        //      result = 1
                        //      param1.pointer = topic handle

    mt_set_components,  // add components used in BCF file (selected elements are taken by default):
                        //      param1.pointer = topic handle
                        //      param2.count = number of components in array
                        //      param3.buffer = pointer to array of object id (components)
                        // returns:
                        //     result = 1 - ok
                        //            = 2 - invalid topic handle

    mt_refresh,         // refresh user interface (after finishing add topics and set components)
                        // returns:
                        //     result = 1
};


//NOTE: if plugin is in demo mode and reach its demmo limitation conditions result will be 0
}

#endif

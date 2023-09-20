#ifndef ifc_gallery_apiH
#define ifc_gallery_apiH

#include "ifc_plugin_api.h"

namespace ifc_gallery
{

enum MessageType
{
    mt_clear,           // clear all views added by plugin (no params)
                        // returns:
                        //     result = 1

    mt_add_view,        // add view:
                        //     param1.string = category name
                        //     param2.string = name
                        //     param3.string = description
                        // returns:
                        //     result = 1
                        //     param1.pointer = view handle
};

//NOTE: if plugin is in demo mode and reach its demmo limitation conditions result will be 0


}

#endif

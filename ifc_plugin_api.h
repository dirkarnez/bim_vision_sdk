//this file is a part of BIMvision Plugin SDK

#ifndef ifc_plugin_apiH
#define ifc_plugin_apiH
#define WIN32_LEAN_AND_MEAN

#include "windows.h"


// only for BIMvision developers (in Datacomp IT):
//   sdk i przyklady wtyczek: /svn_db/ifc_plugins
//   nie zmieniac funkcji i struktur (jak juz co to dodawac nowe)
//   nie zmieniac kolejnosci enumow, nowe wartosci dodawac na koncu
//   uwaga na aligment struktur


//#if defined VIEWER
#ifdef IFC_PLUGIN_SERVER
   #error This file is for ifc plugins only
//    #define VIEWERDECL  __declspec(dllexport)
//    #define PLUGINDECL  __declspec(dllimport)
#else
    #define VIEWERDECL
    #define PLUGINDECL  __declspec(dllexport)

    void load_viewer_functions();
#endif

#define CALL __stdcall


// data aligin 8

#ifdef __cplusplus
namespace viewer
{
extern "C" {
#endif

// plugins (DLL libraries) should be in subdirectory "plugins" of directory with exe of viewer
//
// api functions can be used earliest in 'on_plugin_load()' or after its occurence
//
// plugin DLL is always loaded - DLLMain() and functions 'get_api_verion()',
// 'get_plugin_name()' and 'get_plugin_key()' will be called even if user disable
//  plugin (in plugin manager), if plugin is disabled no 'on_plugin_load()' will
//  be caled and DLL will be unloaded
//
// types of how plugin can work:
//
// 1)
// plugins can do operations in response to events from viewwer
// eg after push button, select object, etc...
//
//
// 2)
// functions can be also invoked from another thread/application
//
// 2.a)
// in DLL file You can create a window with its own GUI (in viewer thread or separate thread)
//
// 2.b)
// dll file can create a hidden window (in viewer thread or separete thread) to communicate
// with any running application using Windows interprocess communication mechanisms
// eg: by shared memory (Named Shared Memory) with notify synchronization via
// SendMessage WM_COPYDATA (+PostMessage to own message queue to avois blocking)


// plugin exports ////////////////////////////////////////////////////////////

// there are two numbers of api version major an minor
//
// major version changes when api is incompatible with pervious version (function
//  names, params, params maenings or how api work changes in the way that can
//  cause unexcepted behavior and errors) and You need recompile plugins
//
// minor version changes when new function added or how api work changes a little
//  that api is still compatible and You dont need to recompile plugin


#define API_VERSION_MAJOR       5
#define API_VERSION_MINOR       46
//Minimal BIMvision version: 2.27.6.0


struct ApiVersion   // never changed
{
    int     major;
    int     minor;
};

// first called (and never changed) method of plugin, gets version of api with
//  which plugin was compiled (and also passes version of viewer api)
//
// 'viewer' - version of viewer api
// 'plugin' - version of api with which plugin was compiled, put there API_VERSION_MAJOR
//             and API_VERSION_MINOR defines from this file
//
// plugin will be loaded when:
//  'viewer->major' == 'plugin->major' (which is API_VERSION_MAJOR)  - api is compatible
//  and 'viewer->minor' >= 'plugin->minor' (which is API_VERSION_MINOR) - api has all function used by plugin
// otherwise only 'get_plugin_info()' will be called and plugin dll will be unloaded
PLUGINDECL void CALL get_api_verion(const ApiVersion *viewer, ApiVersion *plugin);


struct PluginInfo           // never changed
{
    const wchar_t   *name;          // plugin name, one line of text
    const wchar_t   *producer;      // producer/company name, one line of text
    const wchar_t   *www;           // adress of producer/plugin site, one line of text
    const wchar_t   *email;         // email of producer/plugin contact, one line of text
    const wchar_t   *description;   // default short plugin description, can contain multiple lines,
                                    // (use also description file see below)
    const wchar_t   *help_directory;// directory where are help files and description file (se below)
    const wchar_t   *update_url;    // link to optional plugin actualization info, set it to NULL (see below)
};
// help_directory is the path where viewer find help files and description file,
// which can be shown in plugin manager (ever plugin is not loaded)
//
// HELP FILES:
// - viewer try to find in this folder first file named: help_[language_id].*
//   where "[language_id]" is viewer language (see Localization section in this file)
// - if there is no such file it try to load (default help) files: finds first file
//   named help.* or if there is no such file it tries to find first file named: help_en.*
// - if help file is found - viewer will do windows shell "open" command on it
//
// help file name examples (english, polish, default): help_en.plf, help_pl.pdf, help.pdf
// You can also add help button/menu to Your plugin IF you want
//
// DESCRIPTION FILE:
// - if help_directory contains file named "plugin_description.lang" viewer loads it
//   and gets from there plugin description for current language
// - the file format is same as used by function 'load_texts()' (see Localization section in this file)
// - is schould contain entries:
//   [languege_id1] = dectription in this language
//   [languege_id2] = dectription in this language
//    ...
// example:
//   en = English description
//   pl = Polish description
//   ...
//
// if there is no "plugin_description.lang" file or file has no entry for current language
// plugin uses field 'description' from PluginInfo structure
//
// PLUGIN ACTUALIZATION
// if You set "update_url" filed to NULL, viewer checks plugin store server for
// version information, downloads and runs update (installer in silient mode) from there.
//
// You may put in "update_url" addres to tex/ini file with plugin version information
// ie: http://my_company_url/my_plugin.txt
// this file shoud have ini format and contains entries as in below example:
//
//  [version]
//  major=1
//  minor=0
//  release=0
//  build=0
//  download_url=http://my_company_url/my_plugin_setup.exe
//
// viewer will try download this file in background, checks if version in this file
// is greater than version of Your plugin dll (only 'major' and 'minor' numbers
// are used to compare), if is greater then shows update
// posibility to user and when user click for update viewer downloads file
// from "download_url"
//
// Update file shoud be normall setup/installer created (evolved) from template
// in "setup" directory of SDK, BIMvision runs it in silient mode.
//



// second called (and never changed) method of plugin
// fill plugin info texts for plugin manager
// pointers must exists and contains data until on_plugin_load call
// called once in the begining after 'get_api_verion()'
// plugin version should be in DLL Version Information (resources)
PLUGINDECL void CALL get_plugin_info(PluginInfo *pi);


// return plugin key, always called once in the begining
// returned pinter must exist and contain data until on_plugin_load call
// if You return NULL or invalid key plugin will be in unregistered mode
// if some other plugin has same key this plugin wont be loaded
PLUGINDECL const char* CALL get_plugin_key();


// plugin identifiter
typedef void* PLUGIN_ID;

// "object id"
// represent ifc object (ifc entity) in viewer (created from unique id in ifc file - not number)
// object may contain other objects (childs)
typedef unsigned long long OBJECT_ID;

// plugin initialization, from here plugin may refer to the viewer api
// 'pid' - identifiter of plugin given by the viewer, plugin must pass it in
//  all api calls, if 'pid' is different from zero You can use api (always is for now)
// if 'registered' == false - plugin is in unregistered mode (invalid or empty
//  plugin key or key is not activated)
//
// if 'pid' is different from zero and 'registered'==false plugin is in demo mode
//
// in demo mode You have 100 calls limit for all api functions marked: DEMO LIMITATION
// in 100st call viewer call 'on_call_limit()' if plugin has this function
//  so Yu should handle it (end Your demo / prompt user / etc...)
//  if there is no 'on_call_limit()' function, viewer display prompt with demo mode
//  inforamtaion, removes all plugin GUI and stops passing events
// after 100st call viewer stops handling calls
//
// 'viewer_hwnd' - You can use it in messagebox (will be modal) and in creation of
//  your plugin gui windows (ToolWindow) (they will cooperate with viewer; minimize, restowe, hide, stay on top etc...)
PLUGINDECL void CALL on_plugin_load(PLUGIN_ID pid, bool registered, HWND viewer_hwnd);

// if plugin is in demo mode and contain this function it will be called in 100st
// call, You shuld end Your demo here / prompt user / etc...
PLUGINDECL void CALL on_call_limit();   // optional

// plugin deinitialization
// after leaving this function plugin already can not use the api
// GUI elements and events are automatically removed by viewer
PLUGINDECL void CALL on_plugin_unload();

// function called after ifc/bfv/etc file is loaded and plugin should read its data
// returns true if implemented and data has been readed
// returns false if funcion is unimplemented or unenabled to read data,
//               in this case on_model_load() will be called
PLUGINDECL bool CALL on_model_load_v2(bool is_bvf_file);
// function called when user should save his files to BVF
PLUGINDECL void CALL on_model_save_v2(void);

// for now plugin is loaded and unloaded only once (when viewer runs and unloaded when viwer is closed)
//  but in future activated plugins my be loaded and unloaded from plugin manager many times


// called after user changes color scheme in viewer
// or after switch between normal nad touch mode
PLUGINDECL void CALL on_gui_colors_change();   // optional


// when user drags from BIMvision (from structure/object grid or from model in drag mode)
// it drags and drops text: "2CC50DFB-AC97-45C7-92C3-704F54AA6572"

// drop effect type (flags)
#define DROP_EFFECT_NONE   0
#define DROP_EFFECT_MOVE   1
#define DROP_EFFECT_COPY   2

// drop text events (ascii)
// to work corectly with many plugins use own unique id (e.g guuid) as drop text
// and check it in your plugin

// return drop effect type, if DROP_EFFECT_NONE plugin does not recieve drag_over and drop effect
PLUGINDECL int CALL on_drag_enter(const char *text, int x, int y);   // optional

// return drop effect type
PLUGINDECL int CALL on_drag_over(int x, int y, int effect);   // optional

// return drop effect type
PLUGINDECL int CALL on_drop(const char *text, int x, int y, int effect); // optional

// use in on on_drag_over() and on_drop() events
// returns 'object id' or 'all id' if no element is below mouse
VIEWERDECL OBJECT_ID CALL get_object_below_mouse(PLUGIN_ID pid, int x, int y);

enum UNDO_REDO_type
{
   PLG_UNDO   =0,
   PLG_REDO   =1,
   PLG_REMOVE =2
};
// called after user calls undo, redo or remove action
// action_id: value returned by register_undo_action()
// undo_redo_reset==0 -> undo; undo_redo_reset==1 -> redo; undo_redo_reset==2 -> remove;
PLUGINDECL void CALL on_undo_redo_action(unsigned int action_id, int undo_redo_reset); // optional
// viewer api: register action whitch can be later undo/redo by user
// and after that, on_undo_redo_action() will be called by the viewer
// returns action_id
VIEWERDECL unsigned int CALL register_undo_action(PLUGIN_ID pid, wchar_t *action_name);



/// viewer api /////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// functions
//------------------------------------------------------------------------------
// during the function call events generated by this function are not sent to the
// caller (eg loading ifc file dond send evend to plugin which call this function,
// this event will be send to other plugins)
// if the function is called from a different thread than the viewer GUI plugin can
// recive other events generated by the remaining threads (viewer GUI or other plugins)
// (functions are blocking)


// callback function used for events
typedef void (CALL *callback_fun)();
typedef bool (CALL *bool_callback_fun)();
typedef void (CALL *callback_fun_str_vct)(unsigned int size, wchar_t **str_vct);

struct TabSheetPlacement
{
    int  id;         // tab id
    HWND handle;     // tab sheet window handle
    int  width;      // tab sheet width
    int  height;     // tab sheet height
};

// callback function for on_tab_sheet_placement
typedef void (CALL *callback_tab_sheet_placement)(TabSheetPlacement *placement);

enum TabSheetState
{
    ts_activate,    // tab sheet activated
    ts_deactivate,  // tab sheet deactivated
    ts_close,       // tab sheet closed
};

struct TabSheetChange
{
    int id;
    int state;
};

// callback function for on_tab_sheet_change
typedef void (CALL *callback_tab_sheet_change)(TabSheetChange *change);



// "selected id"
// get special id, which represent 'selected objects'
// it changes when file is readed ( could be different for ifc files )
VIEWERDECL OBJECT_ID CALL get_selected_id(PLUGIN_ID pid);

// "all id"
// get special id, which represent 'all objects'
// (it is used also as parent for project or to say that there is no object to return for some functions)
// it changes when file is readed ( could be different for ifc files )
VIEWERDECL OBJECT_ID CALL get_all_objects_id(PLUGIN_ID pid);


// object color
union ColorRGB
{
    unsigned int    cl;
    struct
    {
        unsigned char   r, g, b;
    };
};

// draw selected objects with different color (green) - dafault behavior,
// use in plugin context, remember to restore this (set to true)
VIEWERDECL void CALL use_selection_color(PLUGIN_ID pid, bool b);

// if set to 'true' openings will be drawn as other normal objects (not only when active and selected)
VIEWERDECL void CALL treat_openings_as_normal_objects(PLUGIN_ID pid, bool b);


enum VisibleType
{
    vis_invisible = 0,      // invisible
    vis_visible = 1,        // visible
    vis_transparent = 2,    // visible but transparent
                            //  (regardless of thier orginal color alpha,
                            //   edges also will be transparent)
};

// for object we suggest to se a = 255 or about  a > 10 and a < 100
union Color
{
   struct
   {
      unsigned char   r, g, b, a;
   };
   unsigned int   rgba;

   #ifdef __cplusplus
   explicit Color(unsigned char r=255, unsigned char g=255, unsigned char b=255, unsigned char a=255) : r(r), g(g), b(b), a(a) {}
   #endif
};

// change object color (faces and edges - darker)
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children);

// change object color (faces and edges - darker) without changing transparency
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_color_rgb(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool with_all_children);

// restore object default colors (faces and edges - darker)
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children);

// return object color (if changed from default)
// if object has own color returns true and put in it 'cl'
VIEWERDECL bool CALL get_object_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl);

// return object default color
VIEWERDECL bool CALL get_object_deafult_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl, int index);

//returns transparency level
VIEWERDECL unsigned char CALL get_transparency(PLUGIN_ID pid);

//sets element on transparency map
VIEWERDECL void CALL add_color_to_transparency_list(PLUGIN_ID pid, OBJECT_ID id, Color *cl);

// change object edge color
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_edge_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children);

// restore object edge default colors
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_edge_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children);


// show/hide objects
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type, bool with_all_children);

// activate/deactivate objects
// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_object_active(PLUGIN_ID pid, OBJECT_ID id, bool active, bool with_all_children);



// select/unselect objects
// when User or API selects an object all its childs and descendants will be
// also selected (without openiongs in User case)
// selecting object by the User in viewer (eg wall) does not selets its openings
// this function selects with openings in childs
// 'id' could be:  all id | selected id | object id
VIEWERDECL void CALL select(PLUGIN_ID pid, OBJECT_ID id, bool b);

// unselect all openings in childs
// 'id' could be:  all id | selected id | object id
VIEWERDECL void CALL unselect_openings(PLUGIN_ID pid, OBJECT_ID id);

// select/unselect many objects - much faster than select() in loop
// 'type'
// 0 - unselect with openings
// 1 - select with openings in childs
// 2 - select without openings in childs
// 'id' could contain: object id
// select with childs so no need to add childs because will be slower
VIEWERDECL void CALL select_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int type);

// apply viewer 'Center view' and 'Keep state' options to selection
// call optionally after all selection operations
// viewer api by default does not use/take care of this options
VIEWERDECL void CALL apply_select_rules(PLUGIN_ID pid);

// go to object,
// to zoom to more objects You can make it selected, zoom to selected_id and unselect then
// 'id' could be:  all id  | selected id | object id
VIEWERDECL void CALL zoom_to(PLUGIN_ID pid, OBJECT_ID id);


// fit object to be displayed in the view dimensions of 'width' and 'height' e.g. to take later screenshot of that size
// 'id' could be:  all id  | selected id | object id
VIEWERDECL void CALL zoom_to_in_view(PLUGIN_ID pid, OBJECT_ID id, int width, int height);

// position elative to element bounding box
struct RelativePos
{
    OBJECT_ID   element_id; // 'element_id' could be:  object id
    double      x, y, z;    // distances in meters from bounding box start corner (with smaller coortinates)

    #ifdef __cplusplus
    RelativePos() : element_id(0), x(0), y(0), z(0) {}
    #endif
};

// 'a', 'b' - opposite corners of the cuboid (bounding box)
VIEWERDECL void CALL zoom_to_box(PLUGIN_ID pid, const RelativePos *a, const RelativePos *b);

// camera position, do not modify its data
struct CameraPos
{
    double  internal_data[10];
    char    type;                   // 0 - perspective(65), 1 - 2D, 2 - ortho, 3 - obligue
};                                  // >= 30 && <= 90 - perspective(fov as type)

// get camera pos
VIEWERDECL void CALL get_camera_pos(PLUGIN_ID pid, CameraPos *pos);

// set camera pos
VIEWERDECL void CALL set_camera_pos(PLUGIN_ID pid, const CameraPos *pos);


struct Vector3d
{
    double x, y, z;

    #ifdef __cplusplus
    Vector3d() : x(0), y(0), z(0) {}

    Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

    void clear()
    {
        x = y = z = 0;
    }
    #endif
};

typedef Vector3d Vertex;


struct DirectionCamera
{
    Vector3d    eye, direction, up;
    double      scale;
    int         fov;
};

// get camera
VIEWERDECL void CALL get_direction_camera(PLUGIN_ID pid, DirectionCamera *cam);

// set camera
VIEWERDECL void CALL set_direction_camera(PLUGIN_ID pid, const DirectionCamera *cam);


struct CuttingPlane
{
   Vector3d normal;
   Vertex point;
};


// works if cutting is enabled
VIEWERDECL unsigned int CALL get_cutting_planes(PLUGIN_ID pid, CuttingPlane *buf, unsigned int count);

// enables also cutting
VIEWERDECL void CALL set_cutting_planes(PLUGIN_ID pid, const CuttingPlane *buf, unsigned int count);


struct Segment
{
    Vector3d first, second;
};

// repaint 3d view and GUI (update viewer grids and buttons), executed at idle time
// DEMO LIMITATION
VIEWERDECL void CALL invalidate(PLUGIN_ID pid);

// get approximate drawing time of last drawing entire model in seconds,
// use to avoid program freeze/blinking when You need done many invalidates and
// large file was opened (ie updating label text when changing it in edit box)
// we suggest You not to do many invalidates when this time is greater than 0.2 s
VIEWERDECL float CALL get_draw_time(PLUGIN_ID pid);

// recive objects
// 'buf' - where data will be stored ( can be NULL )
// 'count' - how many objects can contain 'buf', ommited whene 'buf'==NULL
// return number of objects to recive / recived

// get all objects in order of grid tree structure dfs
// You can use it to dedetermine max bufer size to use with other functions like
//  'get_selected()' without need to call two times (first asking for count)
VIEWERDECL unsigned int CALL get_all_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);

// get list of selected objects, unspecified order
// object can be selected and childs may be not or vice versa
// sometimes object may not have selected property, so if You select then viewer
// select only its childs
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_selected(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);

// get list of visible objects (whosde visible_type 'vis_visible' or 'vis_transparent'
//  and object is active)
// unspecified order
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_visible(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);

// get list of active objects
// unspecified order
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_active(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);

// get current product selected in grid
VIEWERDECL OBJECT_ID CALL get_current_product(PLUGIN_ID pid);

struct ObjectState
{
    int     visible_type;   // values from 'VisibleType'
    bool    active;
    bool    selected;
};


// inactive objects should be not ussed in plugins in most cases, because the
//  meaning ot this state is that they are included/excluded from viewer
//  user can change acvive state in first row of grid with objects


// get status of objects in 'id'
// 'id' could contain:  object id
// DEMO LIMITATION
VIEWERDECL void CALL get_object_state(PLUGIN_ID pid, const OBJECT_ID *id, ObjectState *state, unsigned int count);


// get object info
// 'id' could be:  object id

// returns true if visible or transparent (active is not considered)
VIEWERDECL bool CALL is_visible(PLUGIN_ID pid, OBJECT_ID id);   // not fast in demo mode
// returns true if visible and transparent (active is not considered)
VIEWERDECL bool CALL is_transparent(PLUGIN_ID pid, OBJECT_ID id);
VIEWERDECL bool CALL is_selected(PLUGIN_ID pid, OBJECT_ID id);  // not fast in demo mode
VIEWERDECL bool CALL is_active(PLUGIN_ID pid, OBJECT_ID id);
// returns true if object has graphical representation
VIEWERDECL bool CALL has_representation(PLUGIN_ID pid, OBJECT_ID id);


struct Bounds
{
    double x_min, y_min, z_min;
    double x_max, y_max, z_max;

    #ifdef __cplusplus
    void clear()
    {
        x_min = y_min = z_min = 0;
        x_max = y_max = z_max = 0;
    }
    #endif
};


// 'id' could be: object id
VIEWERDECL bool CALL get_bounds(PLUGIN_ID pid, OBJECT_ID id, Bounds *bounds);

// 'id' could be: object id
VIEWERDECL void CALL get_offset(PLUGIN_ID pid, OBJECT_ID id, Vector3d *offset);

// 'id' could be: object id
VIEWERDECL void CALL set_offset(PLUGIN_ID pid, OBJECT_ID id, const Vector3d *offset);


// get object's children list
// 'id' could be:  all id | object id
// if 'id' = all id, returns project(s)
VIEWERDECL unsigned int CALL get_childs(PLUGIN_ID pid, OBJECT_ID id, OBJECT_ID *buf, unsigned int count);


//typical hierarchy in IFC file:
//  project have site and building
//  site could have building
//  biulding have storey
//  storey have element
//
//  in BIMvision elements are additionally grouped ( doors, windows, walls ) etc.
//  but plugin return elements without grouping


// viewer classification of objects
enum ObjectType
{
    ot_no_such_id,
    ot_project,
    ot_site,
    ot_building,
    ot_storey,
    ot_element, // has ElementType
};

// deprecated, use 'ifc_entity_name' instead
// viewer classification of elements
enum ElementType
{
    et_others,
    et_opening,
    et_beam,
    et_building_element_part,
    et_building_element_proxy,
    et_central_heating,
    et_roof,
    et_door,
    et_elektricity,
    et_gas,
    et_footing,
    et_furniture,
    et_space,
    et_window,
    et_subsoil,
    et_slab,
    et_wall,
    et_curtain_vall,
    et_stair,
    et_column,
    et_air_fitting,
    et_plumbing_drainage,
    et_reinforctment,
    et_pile,
    et_plate,
    et_compound,
    et_components
};


struct ObjectInfo
{
    int             object_type;        // value from 'ObjectType'
    int             element_type;       // value from 'ElementType'
    const wchar_t   *name;              // can be NULL
    const wchar_t   *description;       // can be NULL
    const char      *ifc_entity_name;   // e.g. IfcWall
    unsigned int    ifc_entity_number;
    OBJECT_ID       parent;
};

// get information for 'count' objects given by 'id' to 'info'
// 'id' could contain:  object id
VIEWERDECL void CALL get_object_info(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo *info, unsigned int count);


// 'id' could be:  all id | selected id | object id
// 'with_all_children' used only if 'id' is object id
VIEWERDECL void CALL set_user_data(PLUGIN_ID pid, OBJECT_ID id, void *user_data, bool with_all_children);


// 'id' could be:  object id
VIEWERDECL void* CALL get_user_data(PLUGIN_ID pid, OBJECT_ID id);


// get object's project
// if object is a project it returns its id
// 'id' could be:  object id
VIEWERDECL OBJECT_ID CALL get_project(PLUGIN_ID pid, OBJECT_ID id);


// get object's building
// if object is a building it returns its id
// if object has no building ie IfcSite, it returns "all id"
// 'id' could be:  object id
VIEWERDECL OBJECT_ID CALL get_building(PLUGIN_ID pid, OBJECT_ID id);


// get object's storey
// if object is a storey it returns its id
// if object has no storey ie IfcSite, it returns "all id"
// 'id' could be:  object id
VIEWERDECL OBJECT_ID CALL get_storey(PLUGIN_ID pid, OBJECT_ID id);


// get object's parent
// if object has no parent ie IfcProject it returns "all id"
// 'id' could be:  object id
VIEWERDECL OBJECT_ID CALL get_parent(PLUGIN_ID pid, OBJECT_ID id);


struct ObjectInfo2
{
    OBJECT_ID   project;
    OBJECT_ID   building;
    OBJECT_ID   storey;
    wchar_t     *tag;      // IFC element tag, can be NULL
    void        *user_data;
    wchar_t     *global_id; // IFC entity global id
};

// if object is a building or storey returns its id in appropriate field etc...
// if object has no storey or building ie IfcProject, fields contain "all id" etc...
// if no such objedt all id fields will have "all id"
// 'id' could contain:  object id
VIEWERDECL void CALL get_object_info2(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo2 *info2, unsigned int count);


// reference of object's material, unlike as "object id" it changes everytime file is reloaded
typedef unsigned long long MATERIAL_REF;


struct Material
{
   MATERIAL_REF   ref;
   wchar_t        *name;
   wchar_t        *description;
};



// get materials of object (child items from IFC Structrue grid)
// 'id' could contain:  object id
VIEWERDECL unsigned int CALL get_object_materials(PLUGIN_ID pid, OBJECT_ID id, Material *buf, unsigned int count);


struct Material2
{
   MATERIAL_REF   ref;
   wchar_t        *name;
   wchar_t        *description;
   const char     *ifc_entity_name;
};


// get materials of object (child items from IFC Structrue grid)
// 'id' could contain:  object id
VIEWERDECL unsigned int CALL get_object_materials2(PLUGIN_ID pid, OBJECT_ID id, Material2 *buf, unsigned int count);


struct Material3
{
   MATERIAL_REF   ref;
   wchar_t        *name;
   wchar_t        *description;
   const char     *ifc_entity_name;
   double         layer_thickness;
   bool           is_ventilated;
};


// get materials of object (child items from IFC Structrue grid)
// 'id' could contain:  object id
VIEWERDECL unsigned int CALL get_object_materials3(PLUGIN_ID pid, OBJECT_ID id, Material3 *buf, unsigned int count);


typedef unsigned long long OBJECT_TYPE_STYLE_REF;

struct ObjectTypeStyle
{
   OBJECT_TYPE_STYLE_REF    ref;
   wchar_t                  *name;
   wchar_t                  *description;
   const char               *ifc_entity_name;
};

// get object type (style of Door and Window for IFC2x3) i.e.
// return false if there is not element type or style
VIEWERDECL bool CALL get_object_type_style(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle *result);


struct ObjectTypeStyle2
{
   #ifdef __cplusplus
   explicit ObjectTypeStyle2(OBJECT_TYPE_STYLE_REF rf = 0, wchar_t* nm = NULL, wchar_t* desc = NULL,
                    const char *ent = NULL, wchar_t* id = NULL)
                    : ref(rf), name(nm), description(desc), ifc_entity_name(ent), global_id(id)
   {   }
   #endif
   OBJECT_TYPE_STYLE_REF    ref;
   wchar_t                  *name;
   wchar_t                  *description;
   const char               *ifc_entity_name;
   wchar_t                  *global_id;
};

// get object type (style of Door and Window for IFC2x3) i.e.
// return false if there is not element type or style
VIEWERDECL bool CALL get_object_type_style2(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle2 *result);


// reference to layer, unlike as "object id" it changes everytime file is reloaded
// so you should identity layers by name
typedef unsigned long long LAYER_REF;

struct Layer
{
   LAYER_REF      layer_ref;
   const wchar_t  *name;
   const wchar_t  *description;
};

// get list of layers
VIEWERDECL unsigned int CALL get_layers(PLUGIN_ID pid, Layer *buf, unsigned int count);

// get objects on specyfic layer
VIEWERDECL unsigned int CALL get_layer_objects(PLUGIN_ID pid, LAYER_REF ref, OBJECT_ID *buf, unsigned int count);

// reference to zone, unlike as "object id" it changes everytime file is reloaded
// so you should identity zeones by name
typedef unsigned long long ZONE_REF;

struct Zone
{
   ZONE_REF       zone_ref;
   const wchar_t  *name;
   const wchar_t  *description;
};

// get list of zones
VIEWERDECL unsigned int CALL get_zones(PLUGIN_ID pid, Zone *buf, unsigned int count);


struct Zone2
{
   ZONE_REF       zone_ref;
   const wchar_t  *name;
   const wchar_t  *description;
   const wchar_t  *object_type;
   wchar_t        *global_id;
};

// get list of zones
VIEWERDECL unsigned int CALL get_zones2(PLUGIN_ID pid, Zone2 *buf, unsigned int count);


// get objects in specyfic zone
VIEWERDECL unsigned int CALL get_zone_objects(PLUGIN_ID pid, ZONE_REF ref, OBJECT_ID *buf, unsigned int count);


typedef unsigned long long SYSTEM_REF;

struct System
{
   SYSTEM_REF     system_ref;
   const wchar_t  *name;
   const wchar_t  *description;
   const wchar_t  *object_type;
   wchar_t        *global_id;
};

// get list of zones
VIEWERDECL unsigned int CALL get_systems(PLUGIN_ID pid, System *buf, unsigned int count);


// get objects in specyfic zone
VIEWERDECL unsigned int CALL get_system_objects(PLUGIN_ID pid, SYSTEM_REF ref, OBJECT_ID *buf, unsigned int count);


typedef unsigned long long GROUP_REF;

struct Group
{
   GROUP_REF      group_ref;
   const wchar_t  *name;
   const wchar_t  *description;
   const wchar_t  *object_type;
   wchar_t        *global_id;
};

// get list of groups
VIEWERDECL unsigned int CALL get_groups(PLUGIN_ID pid, Group *buf, unsigned int count);


// get objects in specyfic group
VIEWERDECL unsigned int CALL get_group_objects(PLUGIN_ID pid, GROUP_REF ref, OBJECT_ID *buf, unsigned int count);


struct PropertySet
{
    int            nr;     // number, >= 0, may be diferent each time ifc loaded and depend on grid sorting
    const wchar_t *name;  // could be null
};

// get property names of property sets (and its positions)
// 'id' could be:  object id
VIEWERDECL unsigned int CALL get_property_sets(PLUGIN_ID pid, OBJECT_ID id, PropertySet *buf, unsigned int count);


enum ValueType
{
    vt_string,
    vt_double,
    vt_int,
    vt_bool,
};


struct Property
{
    int           set_nr;         // number of property set, >= 0, may be diferent each time ifc loaded and depend on grid sorting
    int           nr;             // number in property set, >= 0, may be diferent each time ifc loaded and depend on grid sorting
    const wchar_t *name;          // could be null
    int           value_type;     // ValueType

    union
    {
        const wchar_t  *value_str;     // read if 'ValueType'==vt_string, could be null
        double         value_num;      // read if 'value_type'!=vt_string (int or double or bool)
    };
};


struct PropertyGet
{
    OBJECT_ID       id;     // 'id' could be:  object id
    unsigned int    set_nr; // position of PropertySet in buf returned fron get_property_sets
};

// get properties from property set
VIEWERDECL unsigned int CALL get_properties(PLUGIN_ID pid, const PropertyGet *pg, Property *buf, unsigned int count);


struct Property2
{
    int           set_nr;         // number of property set, >= 0, may be diferent each time ifc loaded and depend on grid sorting
    int           nr;             // number in property set, >= 0, may be diferent each time ifc loaded and depend on grid sorting
    const wchar_t *name;          // could be null
    int           value_type;     // ValueType

    union
    {
        const wchar_t  *value_str;     // read if 'ValueType'==vt_string, could be null
        double         value_num;      // read if 'value_type'!=vt_string (int or double or bool)
    };

    const char *unit;
    void       *reserved;
};


VIEWERDECL unsigned int CALL get_properties2(PLUGIN_ID pid, const PropertyGet *pg, Property2 *buf, unsigned int count);


struct PropertyFilter
{
    OBJECT_ID       id;             // 'id' could be:  object id
    const wchar_t   *set_name;      // name of property sets, case insensitive, != NULL
    const wchar_t   *property_name; // optional name of properties, case insensitive, if NULL get all Properties
};

// get filtered properties
// (if You want faster get all properties and do it own way)
VIEWERDECL unsigned int CALL filter_properties(PLUGIN_ID pid, const PropertyFilter *pf, Property *buf, unsigned int count);


// select in property grid (of selected object) if You select object call this fucntion after
// 'set_nr' - number of property set >= 0
// 'property_nr' - number of property in property set if < 0 -  only property set will be selected
// 'select_value' - if true and property is valid column Value will be focused
// if 'set_nr' or 'property_nr' is invalid (ie too big) selection actual does not change
// property will be selected after invalidate()
VIEWERDECL void CALL select_property(PLUGIN_ID pid, int set_nr, int property_nr, bool select_value);



typedef void* REF;

enum PropertyType
{
    pt_property,
    pt_property_set,
};

struct PropertySetData
{
    int type;           // PropertyType: 0 - property, 1 - property set
    REF property_ref;   // internal references (not releted with ifc entities)
    REF set_ref;        // internal reference to set

    // fields valid only for property  and property set (type == 0 or type == 1):

    const wchar_t *name;         // could be null
    const wchar_t *description;  // could be null

    // fields valid only* for property (type == 0):

    int           value_type;    // enum ValueType
    const wchar_t *value_str;    // read if 'ValueType'==vt_string, could be null
                                 //  *for property set it contains global_id (GUID)
    double        value_num;     // read if 'value_type'!=vt_string (int or double or bool)

    const char *unit;
};

struct PropertySetData2
{
    int type;           // PropertyType: 0 - property, 1 - property set
    REF property_ref;   // internal references (not releted with ifc entities)
    REF set_ref;        // internal reference to set

    // fields valid only for property  and property set (type == 0 or type == 1):

    const wchar_t *name;         // could be null
    const wchar_t *description;  // could be null

    // fields valid only* for property (type == 0):

    int           value_type;    // enum ValueType
    const wchar_t *value_str;    // read if 'ValueType'==vt_string, could be null
                                 //  *for property set it contains global_id (GUID)
    double        value_num;     // read if 'value_type'!=vt_string (int or double or bool)

    const char *unit;
    int         level;           // indentation level
};

enum GetPropertyType
{
    gp_all,
    gp_only_sets,
    gp_all_with_nested,
};

// get property and or property sets in flat list (childs of level 0)
//  if 'flag' == 0 - get property sets and their properties, only first level
//  if 'flag' == 1 - get only property sets
//  if 'flag' == 2 - get property sets and their properties, all levels
//
// e.g (flag == 0):
//  Set1
//  PropertyOfSet1
//  AnotherProperytOfSet1
//  Set2
//  PopertyOfSet2
//  AnotherPopertyOfSet2
// etc...
//
VIEWERDECL unsigned int CALL get_object_properties(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData *buf, unsigned int count);
VIEWERDECL unsigned int CALL get_object_properties2(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData2 *buf, unsigned int count);
VIEWERDECL unsigned int CALL get_material_properties(PLUGIN_ID pid, MATERIAL_REF ref, int flag, PropertySetData *buf, unsigned int count);
VIEWERDECL unsigned int CALL get_type_style_properties(PLUGIN_ID pid, OBJECT_TYPE_STYLE_REF ref, int flag, PropertySetData *buf, unsigned int count);


struct PropertyDef
{
    OBJECT_ID        object_id;
    const wchar_t    *set_name;  // cannot be NULL
    const wchar_t    *name;      // if NULL take property set

    #ifdef __cplusplus
    PropertyDef() : object_id(0), set_name(NULL), name(NULL) {}
    #endif
};


struct PropertyData
{
    const wchar_t    *name;          // if NULL it will be not changed
    const wchar_t    *description;   // if NULL it will be not changed

    // used only when PropertyDef::name is not NULL
    int              value_type;    // enum ValueType
    const wchar_t   *value_str;     // if NULL and value_type == ValueType::vt_string, value type and value of property will be not changed
    double           value_num;
    const char      *unit;          // it will be not changed

    #ifdef __cplusplus
    PropertyData() : name(NULL), description(NULL), value_type(vt_string), value_str(NULL), value_num(0), unit(NULL) {}
    #endif
};

// returns true if there was such property set and/or property
// call invalidate when you finished changing, adding and deleting properties or sets
// to inform other plugins that property were changed
VIEWERDECL bool CALL delete_object_property_or_set(PLUGIN_ID pid, const PropertyDef *def);

// change property or property set or add set and/or property
// call invalidate when you finished changing, adding and deleting properties or sets
// to inform other plugins that property were changed
VIEWERDECL void CALL add_or_change_object_property(PLUGIN_ID pid, const PropertyDef *def,
                                                   const PropertyData *data);

// event fired when properties were changed
VIEWERDECL void CALL on_property_change(PLUGIN_ID pid, callback_fun fun);


struct Classification  // base ofor references
{
   REF ref;
   const wchar_t *source;
   const wchar_t *edition;
   const wchar_t *edition_date;
   const wchar_t *name;
   const wchar_t *description;
   const wchar_t *location;
   const void    *reserved;
};


struct ClassificationReference
{
   REF ref;
   REF base;    // ref to Classification or ClassificationReference
   const wchar_t *location;
   const wchar_t *identification;
   const wchar_t *name;
   const wchar_t *description;
   const wchar_t *sort;
};

// get top level classifications for all objects
VIEWERDECL unsigned int CALL get_classifications(PLUGIN_ID pid, Classification *buf, unsigned int count);


VIEWERDECL unsigned int CALL get_classification_references(PLUGIN_ID pid, wchar_t *classification_name,
                                                           ClassificationReference *references, unsigned int count);



// get classification references of an object
// 'id' could be: object id
VIEWERDECL unsigned int CALL get_object_classification_references(PLUGIN_ID pid, OBJECT_ID id, ClassificationReference *buf, unsigned int count);

// get classification details, returns false if 'cl' is not valid reference
VIEWERDECL bool CALL get_classification_data(PLUGIN_ID pid, REF cl, Classification *classification);

// get classification reference details, returns false if 'cl_ref' is not valid reference
VIEWERDECL bool CALL get_classification_reference_data(PLUGIN_ID pid, REF cl_ref, ClassificationReference *classification_reference);


struct ProjectOffset
{
   OBJECT_ID project_id;
   Vector3d offset;
};

// return offsets for all projects
VIEWERDECL int CALL get_projects_offsets(PLUGIN_ID pid, ProjectOffset *offsets, int count);


// get factor need to be applied (multipled by) to have geometry in meters
VIEWERDECL double CALL get_unit_factor(PLUGIN_ID pid);


struct Face
{
    Vertex  v1, v2, v3;
    Vector3d normal;
};

struct Edge
{
    Vertex v1;
    Vertex v2;
};

// returns true if object has a geometry (initialize iterator)
VIEWERDECL bool CALL first_geometry(PLUGIN_ID pid, OBJECT_ID id);

// gee bounds of all geometries, use after  'first_geometry()'
VIEWERDECL void CALL get_total_geometry_bounds(PLUGIN_ID pid, Bounds *bounds);

// gets current geometry (from iterator)
VIEWERDECL unsigned int CALL get_geometry(PLUGIN_ID pid, Face *faces, unsigned int count);

// get color of the current geometry
VIEWERDECL void CALL get_geometry_color(PLUGIN_ID pid, Color *face_color, Color *line_color);

// gets current geometry edges (from iterator)
VIEWERDECL unsigned int CALL get_geometry_edges(PLUGIN_ID pid, Edge *edges, unsigned int count);


// returns true if object has aditional geometry (move iterator), DEMO LIMITATION
VIEWERDECL bool CALL next_geometry(PLUGIN_ID pid);

//return true if abonament version
VIEWERDECL bool CALL is_online_licence(PLUGIN_ID pid);



enum MeasureType
{
    mt_volume,
    mt_area,
    mt_edge,
    mt_vertex,
    mt_centroid,
    mt_surface_distance,
    mt_weight,
    mt_counting,
    mt_coordinates,
    mt_area_curved,
    mt_area_same_normal,
    mt_area_total,
    mt_largest_edge,
    mt_offset,
    mt_point_plane,
    mt_point_edge,
    mt_polygon_area,
    mt_angle_plane,
    mt_angle_edge,
    mt_angle_vertex,
    mt_diameter
};

// actual measure might change
VIEWERDECL void CALL on_measure_change(PLUGIN_ID pid, callback_fun fun);

VIEWERDECL void CALL on_tab_sheet_placement(PLUGIN_ID pid, callback_tab_sheet_placement fun);

VIEWERDECL void CALL on_tab_sheet_change(PLUGIN_ID pid, callback_tab_sheet_change fun);

struct Measure
{
   int     measure_type;   // value from 'MeasureType'
   double  value;
                           // projections used only with 'mt_area', 'mt_edge', 'mt_vertex', 'mt_gravity_center', 'mt_coordinates' or 'mt_offset'
   double  projection_1;   // X axis or XY plane or X coordinate
   double  projection_2;   // Y axis or YZ plane or Y coordinate
   double  projection_3;   // Z axis or XZ plane or Z coordinate

   double  weight_destiny; // used only with 'mt_weight'
   double  weight_units;   // used only with 'mt_weight', 1 - kilos, 1000 - tons
};

//Extention for Measure struct with unit_conv_type
struct Measure_v1
{
   Measure measure;
   int     unit_conv_type; // measure unit type id
};

struct MeasuredArea
{
   double max0_area;      // out
   double max1_area;      // out
   double min1_area;      // out
   double min0_area;      // out
   double total_area;     // out
};


// for corners_vct==NULL returns only corners_count
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_object_corners(PLUGIN_ID pid, OBJECT_ID obj_id,
                                                Vector3d *corners_vct, unsigned int corners_count);

// for edge_vct==NULL returns only edge_count
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_object_edges(PLUGIN_ID pid, OBJECT_ID obj_id,
                                              Edge *edge_vct, unsigned int edge_count);

// DEMO LIMITATION
VIEWERDECL bool CALL get_object_area(PLUGIN_ID pid, OBJECT_ID obj_id, MeasuredArea *measure);

// get actual measure
// DEMO LIMITATION
VIEWERDECL void CALL get_measure(PLUGIN_ID pid, Measure *measure);

// get actual measure_v1
// DEMO LIMITATION
VIEWERDECL void CALL get_measure_v1(PLUGIN_ID pid, Measure_v1 *measure_v1);

// get list of objects in measure
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_measure_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);

// get list of elements of measure value (elements of the sum)
// DEMO LIMITATION
VIEWERDECL unsigned int CALL get_measure_elements(PLUGIN_ID pid, double *buf, unsigned int count);

// clear measure
VIEWERDECL void CALL clear_measure(PLUGIN_ID pid);

enum MeasureTypeFlags
{
    mtf_dont_change_tab = 0x0001,
};

// change current tab to measure and select measure 'type'
// 'flags' = MeasureTypeFlags
VIEWERDECL void CALL set_measure_type(PLUGIN_ID pid, int type, int flags);

// 'id' could be:  object id
VIEWERDECL double CALL get_volume(PLUGIN_ID pid, OBJECT_ID id);

// 'id' could be:  object id return centroid point and total weight
VIEWERDECL void CALL get_centroid(PLUGIN_ID pid, OBJECT_ID id, Vector3d *centroid, double *weight);

// 'id' could be:  object id
VIEWERDECL double CALL get_total_area(PLUGIN_ID pid, OBJECT_ID id);

// get only measure state
VIEWERDECL unsigned int CALL get_measure_state(PLUGIN_ID pid, void *buf, unsigned int buf_size);

// 'flags'
// 0 - defaault do not set measure mode 
// 1 - set measure mode
VIEWERDECL void CALL set_measure_state(PLUGIN_ID pid, int flags, const void *buf, unsigned int buf_size);


struct MeasureDetail
{
   double value;
   int unit_conv_type;
   union
   {
      OBJECT_ID object_id;
      struct
      {
         OBJECT_ID object_id_a;
         OBJECT_ID object_id_b;
      };
   };
};

VIEWERDECL unsigned int CALL get_measure_count(PLUGIN_ID pid);
VIEWERDECL unsigned int CALL get_detailed_measure_state(PLUGIN_ID pid, unsigned int measure_nr,
                                                        void *buf, unsigned int buf_size,
                                                        MeasureDetail *details);

enum DetailedMeasureFlag
{
    dm_none = 0,
    dm_clear = 1,
    dm_refresh = 2,
    dm_different_measures = 4,   // if this flag is passed, measures are selected but label (measure value) isn't shown
};
VIEWERDECL void CALL set_detailed_measure_state(PLUGIN_ID pid, int flags, const void *state, unsigned int size);


struct Plane
{
    Vector3d normal;
    double d;
};

struct ConstructMeasureState
{
    MeasureType type;

    OBJECT_ID id;
    Plane plane;
    Segment segment;
};

VIEWERDECL void CALL change_measure_state_density(PLUGIN_ID pid, void *state, double density);


VIEWERDECL unsigned int CALL construct_measure_state(PLUGIN_ID pid, ConstructMeasureState *construct, void *buf, unsigned int buf_size);

// get loaded IFC/BVF file path
// i.e.
//  C:\data\file.ifc
//  C:\data\other_file.BVF
VIEWERDECL const wchar_t* CALL get_loaded_ifc_path(PLUGIN_ID pid);


// get file
//  C:\data\file.ifc
//  C:\data\file.ifczip
//  C:\data\other_file.BVF|project1.ifc
VIEWERDECL const wchar_t* CALL get_project_path(PLUGIN_ID pid, OBJECT_ID project_id);

// extract *ifc file of project to external file
VIEWERDECL bool CALL extract_file_from_bvf(PLUGIN_ID pid, OBJECT_ID project_id,
                                           const wchar_t *to_ifc_file_name);


// load IFC/BVF file
// return false, if function fails
// use load_ifc() not sooner than first event/callback on_draw() is called
VIEWERDECL bool CALL load_ifc(PLUGIN_ID pid, const wchar_t *path);

// load IFC file from buffer
// return false, if function fails
// use load_ifc_from_buffer() not sooner than first event/callback on_draw() is called
VIEWERDECL bool CALL load_ifc_from_buffer(PLUGIN_ID pid, const wchar_t *file_name,
                                          char *buffer, unsigned int buf_size);

// add IFC file
// return false, if function fails
VIEWERDECL bool CALL add_ifc(PLUGIN_ID pid, const wchar_t *path);

// calculate object id from unique id in ifc file
VIEWERDECL OBJECT_ID CALL calculate_object_id(PLUGIN_ID pid, const char *ifc_id);

// get loaded file count
VIEWERDECL unsigned int CALL get_loaded_ifc_files_count(PLUGIN_ID pid);
// get loaded filename
VIEWERDECL const wchar_t* CALL get_loaded_ifc_filename(PLUGIN_ID pid, unsigned int file_index);


enum PluginStatusEnum
{
    ps_non_exist,   // there is no such plugin installed
    ps_not_loaded,  // plugin is installed but disabled
    ps_demo_mode,   // plugin is loaded and in demo mode
    ps_full_version,// plugin is loaded and in full mode
};

struct PluginStatus
{
    int status; // PluginStatusEnum
    int v_major, v_minor;
};

// get status of other plugin
VIEWERDECL void CALL get_plugin_status(PLUGIN_ID pid, const wchar_t *dll_name, PluginStatus *status);


struct PluginMessage
{
    union
    {
        int type;
        int result;
    };

    union MsgParam
    {
        OBJECT_ID id;

        const wchar_t *string;

        unsigned int count;
        const OBJECT_ID *objects;

        const void *pointer;
        unsigned int size;
    } param1, param2, param3;

    #ifdef __cplusplus
    PluginMessage()
    {
        clear();
    }

    void clear(int result = 0)
    {
        this->result = result;
        param1.id = 0;
        param2.id = 0;
        param3.id = 0;
    }
   #endif
};


// send message to other plugin, returns true if message was delivered
VIEWERDECL bool CALL send_plugin_massage(PLUGIN_ID pid, const wchar_t *dll_name, PluginMessage *message);

typedef bool (CALL *callback_plugin_message)(const wchar_t *dll_from, PluginMessage *message);

// 'fun' called when poteher plugin sends message
VIEWERDECL void CALL on_plugin_message(PLUGIN_ID pid, callback_plugin_message fun);


//------------------------------------------------------------------------------
// events
//------------------------------------------------------------------------------
// (events are blocking)

// before clear model
VIEWERDECL void CALL on_model_clear(PLUGIN_ID pid, callback_fun fun);


// --------------------- READING/WRITING TO BVF files v2 -----------------------

// start reading file 'name' from curently opened BVF file & sudir "plugin_name"
// use only in 'on_model_load_v2'
VIEWERDECL bool CALL begin_read_bvf_v2(PLUGIN_ID pid, const wchar_t *name);
// read portion of data from file in curently opened BVF sub_file
// use only in 'on_model_load_v2'
VIEWERDECL unsigned long long CALL read_bvf_v2(PLUGIN_ID pid, void *buf,
                                               unsigned long long size);
// save curently opened(by begin_read_bvf_v2() BVF plagin file, as save_file_name
// as save_file_name outside zip_file, return true if successful
// use only in 'on_model_load_v2'
VIEWERDECL bool CALL save_bvf_sub_file_v2(PLUGIN_ID pid, wchar_t *save_as_file_name);
// get list of all file in plagin directory, last string i vector contains NULL
// use only in 'on_model_load_v2'
VIEWERDECL wchar_t** CALL get_bvf_dir_file_list_v2(PLUGIN_ID pid);
// get file size from curently opened BVF sub_file
// use only in 'on_model_load_v2'
VIEWERDECL unsigned long long CALL get_bvf_size_v2(PLUGIN_ID pid);
// chcek if file was added or completly new was loaded
//  use only in 'on_model_load_v2'
VIEWERDECL bool CALL file_was_added(PLUGIN_ID pid);
//
// write ...
// writing to BVF file

// start writing file 'name' to curently opened BVF file & sudir "plugin_name"
// use only in 'on_model_save_v2'
VIEWERDECL bool CALL begin_write_bvf_v2(PLUGIN_ID pid, const wchar_t *name);
// read portion of data from file in curently opened BVF sub_file
// use only in 'on_model_save_v2'
VIEWERDECL bool CALL write_bvf_v2(PLUGIN_ID pid, void *buf, unsigned long long size);
// save external_file_name to bvf as begin_write_bvf_v2() file name
// return true if successful
// use only in 'on_model_save_v2'
VIEWERDECL bool CALL write_file_to_bvf_v2(PLUGIN_ID pid, wchar_t *external_file_name);


//------------------------------------------------------------------------------
// viewer asks plugin if it can clear model (before open new file or closing application)
// return true to proceed or false to cancel loadaing new file or closing application
// use when you need apply own changes or ask user for something
VIEWERDECL void CALL can_clear_model(PLUGIN_ID pid, bool_callback_fun fun);

// inform viewer that plugin needs to save changes to BVF
// viewer will ask user to save BVF before close application and before load a new file
// flag is reset by viewer if user says no (dees not want to save) or after file was saved
VIEWERDECL void CALL need_save_bvf(PLUGIN_ID pid, bool flag);

// request BIMvision to immediately save file,
// if there is an opened file and plugin has unsaved changes notified by 'need_save_bvf()'
//  it returns true if file was seved, otherwise return false
// we recomended to use it only when you need actual BVF, use 'need_save_bvf()' instead
VIEWERDECL bool CALL save_file(PLUGIN_ID pid);

// inform viewer if there are unsaved data in plugin,
// viewer will inform user that data will be lost and ask him if want to procced
// before close application and before load a new file,
// flag is reset by viewer ONLY if user says yes
// use in situations when you want to save user data to other file than bvf
// (or you have more posibilities)
// viewer first checks state set by 'need_save_bvf()'
VIEWERDECL void CALL need_save_changes(PLUGIN_ID pid, bool flag);



//------------------------------------------------------------------------------
// 'fun' - callback when object list was changed i.e. when usre splits/merges objects by plane
// or changed the "loaded" status in "File list" window (but not in on model load/clear)
VIEWERDECL void CALL on_object_list_changed(PLUGIN_ID pid, callback_fun fun);



// selection changed (rather when may be changed)
// 'fun' - callback function called when selection is changed and before refresh
//  of view and grid
// You dont need call invalidate here (it will be called by viewer)
VIEWERDECL void CALL on_selection_change(PLUGIN_ID pid, callback_fun fun);

// returns true if user clicked element on 3d view, gets element id and mouse pos
// (relative to element bounding box)
// works only in on_selection_change event
VIEWERDECL bool CALL get_clicked_pos(PLUGIN_ID pid, RelativePos *pos);

// get normal at point 'pos', usse to add some offset to points i.e  0.02 when you draw icon
// works only in on_selection_change event
VIEWERDECL bool CALL get_clicked_normal(PLUGIN_ID pid, Vector3d *normal);

VIEWERDECL void CALL on_hover(PLUGIN_ID pid, callback_fun fun);
VIEWERDECL void CALL set_hover_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
VIEWERDECL void CALL get_hovered_pos(PLUGIN_ID pid, RelativePos *pos);
VIEWERDECL void CALL get_dropped_pos(PLUGIN_ID pid, RelativePos *pos);

// You can draw aditional things here
VIEWERDECL void CALL on_draw(PLUGIN_ID pid, callback_fun fun);


// set the id of objects being currently drawed to get feedback when user
//  clicked on it - this id will be available in on_draw_object_click() event
// You can set one id for drawing multiple objects - they will be treated as one
//  object druing on click event
// if you do not use this function or set 'id' to 0 object will be not "clickable"
// use values from 1 to 10000
// use in on_draw() event
VIEWERDECL void CALL set_draw_object_id(PLUGIN_ID pid, unsigned int id);

// register event when user clicks (LMB, MMB) on object painted by You in on_draw()
VIEWERDECL void CALL on_draw_object_click(PLUGIN_ID pid, callback_fun fun);

// get id of clicked object which was drawed in on_draw() and set by set_draw_object_id()
// use in on_draw_object_click() or in on_context_menu() event
VIEWERDECL unsigned int CALL get_draw_object_id(PLUGIN_ID pid);


struct Point
{
    RelativePos     pos;
    Color           color;
    unsigned int    size;           // 1 - 16
    int             draw_style;     // 0 - always drawn even if covered but with 50% more alpha
                                    // 1 - alvays drawn even if covered,
                                    // 2 - drawn only if not covered
};

// use in on_draw() event
VIEWERDECL void CALL draw_point(PLUGIN_ID pid, const Point *point);


struct Line
{
    RelativePos     start, end;
    Color           color;
    unsigned int    width;      // 1, 2, 3, 4, 5
    int             style;      // 0 - normal, 1 - dot, 2 - dash, 3 - larger dash
    int             draw_style; // 0
};

struct Bitmap{
	 Vector3d up;
	 Vector3d normal;
	 const wchar_t* reference;
	 const wchar_t* format;
	 RelativePos location;
	 double height;
};

// use in on_draw() event
VIEWERDECL void CALL draw_line(PLUGIN_ID pid, const Line *line);


struct Sphere
{
    RelativePos     pos;
    Color           color;
    float           radius;
    int             segments;   // 16
    int             draw_style; // 0
};

// use in on_draw() event
VIEWERDECL void CALL draw_sphere(PLUGIN_ID pid, const Sphere *sphere);



struct Pyramid
{
    RelativePos apex;               // position
    float       pan_angle;  //yaw   // in degree
    float       tilt_angle; //pitch // in degree
    float       roll_angle;
    float       height;             // in meters

    float       horizontal_angle;   // in degree
    float       vertical_angle;     // in degree

    int         style;              // 0
    int         draw_style;         // 0
    Color       face_color;
    Color       line_color;
};

// use in on_draw() event
VIEWERDECL void CALL draw_pyramid(PLUGIN_ID pid, const Pyramid *pyramid);

// "solid id"
// represent user generated object
typedef unsigned long long SOLID_ID;

VIEWERDECL SOLID_ID CALL create_intersection_solid(PLUGIN_ID pid, OBJECT_ID object_a, OBJECT_ID object_b);
VIEWERDECL void CALL delete_solid(PLUGIN_ID pid, SOLID_ID solid_id);
VIEWERDECL void CALL draw_solid(PLUGIN_ID pid, SOLID_ID solid_id, Color color);
VIEWERDECL double CALL get_solid_volume(PLUGIN_ID pid, SOLID_ID solid_id);
VIEWERDECL double CALL get_solid_area(PLUGIN_ID pid, SOLID_ID solid_id);
VIEWERDECL void CALL get_solid_center_point(PLUGIN_ID pid, SOLID_ID solid_id, Vertex *center);
VIEWERDECL void CALL zoom_to_solids(PLUGIN_ID, const SOLID_ID *id, unsigned int count);
VIEWERDECL void CALL zoom_to_objects(PLUGIN_ID, const OBJECT_ID *id, unsigned int count);


// load image used in 'draw_icon()', load several images in 'on_plugin_load()'
// each function call add next number (counting from 0) to the icon
// icon must be png file should be 32 bit color (with alpha/transparency)
VIEWERDECL void CALL load_icon_image(PLUGIN_ID pid, const wchar_t *image_path);


struct Icon
{
    RelativePos     pos;
    int             image_nr;   // number of loaded icon
    unsigned int    size;       // size of icon to be drawn (may be larger or smaller form original icon image)
    int             draw_style; // 0 - draw covered part of icon with 50% alpha
                                // 1 - draw covered part of icon without alpha
                                // 2 - draw only not covered part of icon
};

// use in on_draw() event
VIEWERDECL void CALL draw_icon(PLUGIN_ID pid, const Icon *icon);


struct Label
{
    ColorRGB        bkg_color;      // use light pastel colors, eg 255,255,175
    RelativePos     pos;            // position
    const wchar_t   *caption;       // optional, bold font, one line
    const wchar_t   *txt;           // optional, normal font, one line for now
    int             style;          // se below
    int             side;           // se below
};

// 'style'
// 0 - label with point and line, (line and point dissapears if they are hidden)
// 1 - ballon
//
// 'side'
// 0 - bottom
// 1 - top
//
// use in on_draw() event
VIEWERDECL void CALL draw_label(PLUGIN_ID pid, const Label *label);



// get element pos relative to its bounding box
// [in] 'pos.element_id' could be:  object id
// [in/out] 'pos.x' 'pos.y' 'pos.z':  0 - min, 1 - max
//          (0,0,0) - lower left corner,
//          (1,1,1) - upper right corner
//          (0.5,0.5,0.5) - center
// pos will be returned in: 'pos.x' 'pos.y' 'pos.z'
VIEWERDECL void CALL get_element_pos(PLUGIN_ID pid, RelativePos *pos);

// LMB + mouse move causes drag operation instead move/rotate model
VIEWERDECL void CALL set_drag_mode(PLUGIN_ID pid, bool set);


// create new user object
// ifc_entity_name: correct (eg. IfcWindow) if not correct copy name from parent
// name:, desc: string
// call invalidate when you finished
// return OBJECT_ID or 0 if error
VIEWERDECL OBJECT_ID CALL create_user_object(PLUGIN_ID pid, OBJECT_ID parent, const char* ifc_entity_name, const wchar_t* name, const wchar_t* desc);

// only works for objects created function create_user_object function
// call invalidate when you finished
// return true or false if error
VIEWERDECL bool CALL delete_user_object(PLUGIN_ID pid, OBJECT_ID id);

// check triangle geometry
// return true or false
VIEWERDECL bool CALL check_triangle(PLUGIN_ID pid, const Face *face);

// only works for objects created function create_user_object function
// cl can be null
// call invalidate when you finished
// return true or false if error
VIEWERDECL bool CALL add_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id, const Face *faces, unsigned int count, const viewer::Color *cl);

// only works for objects created function create_user_object function
// delete geometry from user object
// call invalidate when you finished
// return true or false if error
VIEWERDECL bool CALL delete_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id);

// only works for objects created function create_user_object function
// call invalidate when you finished
// return true or false if error
VIEWERDECL bool CALL set_geometry_edges_user_object(PLUGIN_ID pid, OBJECT_ID id, const Edge *edges, unsigned int count);

enum SaveType
{
   st_bvf = 0,
   st_cache,
};

// save loaded ifc file with specified file name
// st_bvf - save as bvf (BIMvision File)
// st_cache - save cached geometry (faster file loading)
// return true or false if error
VIEWERDECL bool CALL save_file_as(PLUGIN_ID pid, const wchar_t *name, int save_type);


//------------------------------------------------------------------------------
// Localization
//------------------------------------------------------------------------------
// localization of plugin You can do in any way You want
// or you can use our mechanism 'load_text()' or 'get_text()'

// returns viewer language (ISO 639-1 code), i.e. L"pl", L"en"
// (from viewer current language file, field '.language.id')
VIEWERDECL const wchar_t* CALL get_language(PLUGIN_ID pid);

// load localization table, unicode txt file in format:
//
// text id = some text
// text other id = other text
// //for one line comment
//
// escape chars: \n - new line, \\ - backslash, \s - space (at begin or end of text)
//
// returns false if there is no file or if error in file format
// text ids and texts are white space trimmed, case sensitive
// use language code from 'get_language()' in file name, i.e. "language.pl", "language.en"
//  so anybody can eaisly translate the plugin adding such files
VIEWERDECL bool CALL load_texts(PLUGIN_ID pid, const wchar_t *file_name);

// get text from loacalization table if no such text or 'load_text()' returned false
// this function returns txt_id (as string)
VIEWERDECL const wchar_t* CALL get_text(PLUGIN_ID pid, const char *txt_id);

VIEWERDECL const wchar_t* CALL get_text_global(PLUGIN_ID pid, const char *txt_id);

// get entity type name text (colum Type in grid IFC Structure) in current viewer language
// from ifc entity name e.g. for "IfcBuilding" returns L"Building" in english
// You do not need include translations of types in your language files (it uses viewer
// langiuage file), if returned text is the same (include "Ifc") is not translated
// (not super fast in case large amount of calls)
VIEWERDECL const wchar_t* CALL get_entity_type_name(PLUGIN_ID pid, const char *ifc_entity_name);

//------------------------------------------------------------------------------
// GUI
//------------------------------------------------------------------------------
// plugins could add groups and buttons to own or default (provided for plugins) tabs/groups
// plugins can change only their own tasbs groups and buttons
// you don't need call invalidate()


// create tab sheet at properties panel
// return tab sheet id, always > 0
VIEWERDECL int CALL create_tab_sheet(PLUGIN_ID pid, const wchar_t *name, bool allow_close);

// activate tab sheet with id
// 'id' - tab sheet id created by plugin
VIEWERDECL void CALL activate_tab_sheet(PLUGIN_ID pid, int id);

// close (hide and delete) tab sheet with id
// 'id' - tab sheet id created by plugin
VIEWERDECL void CALL close_tab_sheet(PLUGIN_ID pid, int id);

// show/hide tab sheet with id
// 'id' - tab sheet id created by plugin
VIEWERDECL void CALL show_tab_sheet(PLUGIN_ID pid, int id, bool show);

// return if tab sheet is active
VIEWERDECL bool CALL is_active_tab_sheet(PLUGIN_ID pid, int id);

// create tab at ribbon
// return tab id, always > 0
VIEWERDECL int CALL create_tab(PLUGIN_ID pid, const wchar_t *name);

// create group of buttons
// 'tab_id" - tab id created by plugin
// if tab doesn't exist or 'tab_id' == 0 - create at default tab provided for plugins
// return group id, always > 0
VIEWERDECL int CALL create_group(PLUGIN_ID pid, int tab_id, const wchar_t *name);
// show or hide group
VIEWERDECL void CALL show_group(PLUGIN_ID pid, int group_id, bool visible);

// create button (large)
// 'group_id' - group id
// if 'group_id' == -1 button will be not added to any group (You can use it with
//  context menu, buttons with drop down list, gallery buttons etc...)
// otherwise if group doesn't exist or 'group_id' == 0 - create at default global
//  group for plugins
// 'fun' - callback function triggered when button is clicked
// return button id, always > 0
VIEWERDECL int CALL create_button(PLUGIN_ID pid, int group_id, callback_fun fun);
// small button
VIEWERDECL int CALL create_small_button(PLUGIN_ID pid, int group_id, callback_fun fun);
// checkbox
VIEWERDECL int CALL create_checkbox(PLUGIN_ID pid, int group_id, callback_fun fun);
// radio button
VIEWERDECL int CALL create_radio_button(PLUGIN_ID pid, int group_id, callback_fun fun);

// button with dropdown list, clickable - You can click/set down botton or element from its list
VIEWERDECL int CALL create_dropdown_button(PLUGIN_ID pid, int group_id, callback_fun fun);
// button with dropdown list, no checkable, no clickable - You can click/set down only elements from its list
VIEWERDECL int CALL create_sub_button(PLUGIN_ID pid, int group_id, bool small);
// button with dropdown list like abowe but You have event click on dropdown on it
VIEWERDECL int CALL create_sub_button2(PLUGIN_ID pid, int group_id, bool small, callback_fun fun);
// add button to dropdown list, 'parent_button_id' - dropdown_button, gallery or sub_button
// added button wil be shown as small
VIEWERDECL void CALL add_button(PLUGIN_ID pid, int parent_button_id, int button_id);
// add separator to dropdown list, 'parent_button_id' - dropdown_button or sub_button,
//  'caption' - text, if NULL then simple (one line) separator
VIEWERDECL void CALL add_separator(PLUGIN_ID pid, int parent_button_id, const wchar_t *caption);

// set button parameters, if 'hint'==NULL button tooltip text will be not changed
VIEWERDECL void CALL set_button_text(PLUGIN_ID pid, int button_id, const wchar_t *caption, const wchar_t *hint);
// PNG image, max size 32x32px (RGBA)
VIEWERDECL void CALL set_button_image(PLUGIN_ID pid, int button_id, const wchar_t *large_img_path);
// PNG image, max size 16x16px (RGBA)
VIEWERDECL void CALL set_button_small_image(PLUGIN_ID pid, int button_id, const wchar_t *small_img_path);
// set button shortcut, e.g. "Ctrl+D"
VIEWERDECL void CALL set_button_shortcut(PLUGIN_ID pid, int button_id, const wchar_t *shortcut);

// if button is checkbox or radio button 'down' is its checked property
VIEWERDECL void CALL set_button_state(PLUGIN_ID pid, int button_id, bool enabled, bool down);//deprecated
// if button is checkbox or radio button 'down' is its checked property
VIEWERDECL void CALL set_button_down(PLUGIN_ID pid, int button_id, bool down);
// set button guid
// if button has a guid it will be alwas properly remembered when user adds it to
// ribbon quick acces toolbar and closes BIMvision
// if You change guid (in new plugin version) button will be remowed from quick acces toolbar
// 'str' string that contain GUID in hex without braces and hyphens
// i.e. for GUID: {F71619BC-D638-467D-B6C4-6187EBB442A0}
//      'str' will be: F71619BCD638467DB6C46187EBB442A0
//
// if You do not use this function, BIMvision adds unique identifiters to buttons
// based on button creation order
//
// if user disable or uninsall plugin, icons from quick acces toolbar will be not remembered
VIEWERDECL void CALL set_button_guid(PLUGIN_ID pid, int button_id, const char *str);
// enable or disable button
VIEWERDECL void CALL enable_button(PLUGIN_ID pid, int button_id, bool enable);
// show or hide button, by default buttons are shown
VIEWERDECL void CALL show_button(PLUGIN_ID pid, int button_id, bool show);

// get clicked button/gallery item id
// works only in button click, gallery item click (callback 'fun') and in on_gallery_item_context_menu events
VIEWERDECL int CALL clicked_button(PLUGIN_ID pid);

// next added control to group will be separated with horizontal line (only on ribbon)
VIEWERDECL void CALL begin_control_group(PLUGIN_ID pid);

// 'fun' - callback function called when viewer context menu will be shown (on model view),
// menu is always empty, you can add menu items here
VIEWERDECL void CALL on_context_menu(PLUGIN_ID pid, callback_fun fun);

// add button to context menu, use in on_context_menu and in on_gallery_item_context_menu events
// menu is alvays empty (contains only viewer items), buttons in menu will be
// shown as small
VIEWERDECL void CALL add_context_button(PLUGIN_ID pid, int button_id);
// remove from contex menyu buttons aded by BIMvision
// use in on_context_menu
VIEWERDECL void CALL clear_context_menu(PLUGIN_ID pid);

// ribbon gallery
// return gallery id, always > 0
VIEWERDECL int CALL create_gallery_button(PLUGIN_ID pid, int group_id, bool small, callback_fun fun);
// 'style' = 0
VIEWERDECL void CALL set_gallery_style(PLUGIN_ID pid, int gallery_id, int min_col_count, int style);
VIEWERDECL int CALL create_gallery_category(PLUGIN_ID pid, int gallery_id);
VIEWERDECL void CALL set_gallery_category_text(PLUGIN_ID pid, int gallery_category_id, const wchar_t *caption);
// 'display_texts' dsplay igallery item texts: 0 - none, 1 - caption, 2 - caption and description
// 'texts_posistion' 0 - top, 1 - right, 2 - bottom, 3 - left
VIEWERDECL void CALL set_gallery_category_style(PLUGIN_ID pid, int gallery_category_id, int display_texts, int texts_posistion);
// delete category only if is empty (has deleted items)
VIEWERDECL void CALL delete_gallery_category(PLUGIN_ID pid, int gallery_category_id);
VIEWERDECL int CALL create_gallery_item(PLUGIN_ID pid, int gallery_category_id, callback_fun fun);
VIEWERDECL void CALL set_gallery_item_text(PLUGIN_ID pid, int gallery_item_id, const wchar_t *caption, const wchar_t *descrption);
VIEWERDECL void CALL set_gallery_item_image(PLUGIN_ID pid, int gallery_item_id, const wchar_t *path);
VIEWERDECL void CALL delete_gallery_item(PLUGIN_ID pid, int gallery_item_id);
// clear all items and categories
VIEWERDECL void CALL clear_gallery(PLUGIN_ID pid, int gallery_id);
// 'fun' - callback function called when user right click on gallery item
// menu is always empty, you can add menu items here
VIEWERDECL void CALL on_gallery_item_context_menu(PLUGIN_ID pid, callback_fun fun);

// returns if checkobox center view on tab Objects group Selected is checked
VIEWERDECL bool CALL is_center_view(PLUGIN_ID pid);


// get actual tab from ribbon, return:
// 0    default tab for plugins
// > 0  tab number added by plugin ('tab_id')
// -1   tab "View"
// -2   tab "Objects"
// -3   tab "Advanced"
// -11  tab "Measurement"
// -12  tab "Changes"
// -13  other tabs of viewer or other plugins
//
// plugins shouldn't work at background or react at events when tab < 0 is selected 
// ( this could disturb working internal functions in viewer, especially when tab < -10 )
// if plugin want to do something at background or react at events, it should have own tab
// and react to it changes or have a button on/off ( activate/deactivate function )
VIEWERDECL int CALL get_active_tab(PLUGIN_ID pid);

// event - tab changed at ribbon
VIEWERDECL void CALL on_tab_change(PLUGIN_ID pid, callback_fun fun);


enum GuiColorId
{
    // window
    cl_window_light,
    cl_window_medium,       // default tool window background
    cl_window_dark,
    cl_window_super_dark,

    // panels etc
    cl_border_light,
    cl_border_dark,

    // grid
    cl_grid_bkg,
    cl_grid_lines,
    cl_grid_fixed_border_light,
    cl_grid_fixed_border_dark,
    cl_grid_header_text,

    // gradients
    cl_grid_fixed_top,
    cl_grid_fixed_bottom,

    cl_grid_focused_top,
    cl_grid_focused_middle,
    cl_grid_focused_bottom,

    cl_grid_selected_top,
    cl_grid_selected_middle,
    cl_grid_selected_bottom,
};

// return color used by curent viewer color scheme
VIEWERDECL ColorRGB CALL get_gui_color(PLUGIN_ID pid, int gui_color_id);


enum GuiTheme
{
   gt_modern_white,
   gt_classic_blue,
   gt_graphite_gray,
};

// get color theme
VIEWERDECL int CALL get_gui_theme(PLUGIN_ID pid);

// windows modal message box
VIEWERDECL int CALL message_box(PLUGIN_ID pid, const wchar_t *caption, const wchar_t *message, int flags);

// set initial directory and fileter for open file dialog (can be NULL)
// filter example: "IFC files|*.ifc;*.ifcZIP"
VIEWERDECL void CALL set_open_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory);

// returns true if user have selected file(s) and pressed open in dialog
VIEWERDECL bool CALL open_file_dialog(PLUGIN_ID pid, bool multiple_files);

// get number of files chossoen to open in the dialog (only one  when 'multiple_files' was set to false)
VIEWERDECL unsigned int CALL get_open_dialog_file_count(PLUGIN_ID pid);

// get path to file
VIEWERDECL const wchar_t* CALL get_open_dialog_file_nr(PLUGIN_ID pid, unsigned int nr);


// set initial directory, filter and file name for the save dialog
VIEWERDECL void CALL set_save_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory, const wchar_t *file_name);

// set default extension e.g "xml",
// NOTE always use this function to work filter properly
VIEWERDECL void CALL set_save_dialog_default_extension(PLUGIN_ID pid, const wchar_t *extension);

// returns true if user have choosen file(s) and pressed save in dialog
VIEWERDECL bool CALL save_dialog(PLUGIN_ID pid, bool select_directory_only);

// get path to the file to be saved or a directory when 'select_directory_only' was true
VIEWERDECL const wchar_t* CALL get_save_dialog_name(PLUGIN_ID pid);

// show or hidde progress bar (or change its title)
// 'style': 0 - one bar and text, 1 - two bars and texts
VIEWERDECL void CALL show_progress_bar(PLUGIN_ID pid, bool show, int style, const wchar_t *title);

// update progress bar, returns false if user clicked abort/cancel
// use after 'show_progress_bar'
// if 'message' is NULL it will not be changed
// if 'second_message' is NULL it will not be changed
VIEWERDECL bool CALL update_progress_bar(PLUGIN_ID pid, int percent, const wchar_t *message, int second_percent, const wchar_t *second_message);


// return rectangle of model view area in screen coordinates
VIEWERDECL void CALL get_view_rect(PLUGIN_ID pid, RECT *rect);

// shows IFC Structure grid, if 'force_show_properties'=true forces to show Properties grid
// if false does not change property grid visibility
VIEWERDECL void CALL show_ifc_structure_grid(PLUGIN_ID pid, bool force_show_properties);

// change visibility status of the ribbon
// 0 - invisible
// 1 - visible
VIEWERDECL void CALL set_ribbon_state(PLUGIN_ID pid, int state);

// change visibility status of the panel with grids and properties
// 0 - invisible
// 1 - visible
VIEWERDECL void CALL set_grids_state(PLUGIN_ID pid, int state);
// get visibility status of the pannel with grids and properties
VIEWERDECL bool CALL get_grids_state(PLUGIN_ID pid);


// do gui action, usefull also for basics custom mapping of ribbon to own controls
// 'item_name' - name of an item, obtained from its hint/tootip when the viewer is launched with "-item_names" parameter
//                e.g "btn_view_front"
// 'command' can be one of folowing:
//    "click"        - if item is enabled and visible returns true and performs click on it
//    "check"        - if item is enabled and visible returns true and performs checking it if is not checked
//    "uncheck"      - if item is enabled and visible returns true and performs unchecking it if is checked
//    "is_enabled"   - returns true if the item is enabled
//    "is_visible"   - returns true if the item is enabled
//    "is_checked"   - returns true if the item is checked/down
//    "is_checkable" - returns true if the item has ability to be checked/down
//    "is_item"      - returns true if the there is item of given name
VIEWERDECL bool CALL item_command(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *command);

//set: edit value, spin edit value, track bar position, combo item index
// for setting units rounded value use name: "round_picker"
// for btn_container_unsel_transparency, btn_container_sel_transparency use values <0:100>
VIEWERDECL void CALL set_item_value(PLUGIN_ID pid, const wchar_t *item_name, double value);

// 'item_name' = NULL - gets: edit value, spin edit value, track bar position, combo item index
// 'item_name' = "min" - gets: spin edit min value, track bar min position
// 'item_name' = "max" - gets: spin edit max value, track bar max position
// 'item_name' = "count" - gets: combo item count
// 'item_name' = "round_picker" - gets: round of the measure
VIEWERDECL double CALL get_item_value(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *value_type);

//
// 'item_name' - name of an viewer button, obtained from its hint/tootip when the viewer is launched with "-item_names" parameter
//                e.g "btn_view_front"
// fun         - fun will be called after viewer button.OnClick()
VIEWERDECL bool CALL register_on_button_click(PLUGIN_ID pid, const wchar_t *item_name, callback_fun fun);



// returns true if viewer is in touch mode (largest gui)
VIEWERDECL bool CALL is_touch_mode(PLUGIN_ID pid);

// get (save) current view and place it info 'buf' if 'buf_size' match current state size
// (main display options, camera position, cutting planes, colors of objects, selection, visible,
// hidden, active objects, measurement)
// if 'buf' = NULL returns needed buf (state) size (size depends of state of the objects)
// set 'flags' = 0
VIEWERDECL unsigned int CALL get_view_state(PLUGIN_ID pid, int flags, void *buf, unsigned int buf_size);

// set (change) current view ith data from 'get_view_state()'
// 'flags' = 0
VIEWERDECL void CALL set_view_state(PLUGIN_ID pid, int flags, const void *buf, unsigned int buf_size);


// returns screenshot, 'w' and 'h' should be not greater than view rect, 'buf' contain array of RGB values
// ( You shoud allocate: buf = new unsigned char [ w * h * 3];  where w,h < view_rect )
// returns true if ok
// DEMO LIMITATION
VIEWERDECL bool CALL render_screenshot(PLUGIN_ID pid, unsigned int w, unsigned int h, unsigned char *buf);

// 'style'
// 0 - with current bkg (white or gradient) and plugins, this is default seting
// 1 - with white bkg and without plugins
// 2 - with current bkg (white or gradient) and without plugins
// or combinastion of screen shot flags below:

// screen shoot flags:
#define SSF_WHITE_BACKGROUND        0x4
#define SSF_WITHOUT_PLUGINS         0x8
#define SSF_DISABLE_ANTIALIASING    0x10
#define SSF_BOLD_LINES              0x20
#define SSF_DISABLE_LIGHTING        0x40

VIEWERDECL void CALL set_screenshot_style(PLUGIN_ID pid, int style_or_flags);


// get 2D bounding box of objects in the screen coordinates ('x', 'y')
//  'z' value indicating the number how much of the object is visible,
//      the bigger value the more of object is visible,
//      0 if object is all covered by other model elements or object is off screen
//      (this 'z' work properly with opengl 3.3 and above)
// 'flags'
//    0 - use current view/screen size
//    1 - use last screenshot size (bounds will be recieved as rendered to that size)
VIEWERDECL void CALL get_2d_bounds(PLUGIN_ID pid, const OBJECT_ID *obj, Bounds *bounds, unsigned int count, int flags);

// get 2D positions of the points in 'pos' array
//  'z' coordinate is 0 if object is covered by other model elements or is off screen,
//      otherwise is > 0
// 'flags'
//    0 - use current view/screen size
//    1 - use last screenshot size (bounds will be recieved as rendered to that size)
VIEWERDECL void CALL project_to_2d(PLUGIN_ID pid, const RelativePos *pos, Vector3d *pos_2d, unsigned int count, int flags);//

// recaluclate cross sections ussing current cutting plane set
// cross sections are drawn from this moments
// 'flags' = 0
VIEWERDECL void CALL recalc_cross_sections(PLUGIN_ID pid, int flags);


enum CrossSetionColor
{
   csc_object = 0,
   csc_original = 1,
   csc_own = 2,
};

VIEWERDECL void CALL set_cross_sections_style(PLUGIN_ID pid, int color_type, ColorRGB color, bool bold);

VIEWERDECL void CALL close_application(PLUGIN_ID pid);

extern bool end_demo;




//------------------------------------------------------------------------------
//----------------------------DEPRECATED----------------------------------------
//------------------------------------------------------------------------------

// set color
// if 'transparent'==true color alpha will be set to 40% (0.4*255)
// spaces are always transparent, edges are not transparent
// 'id' could be:  all id | selected id | object id
// if 'id' is object id function will be applied to object and to its descendants
VIEWERDECL void CALL set_color(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent);

// 'id' could be: object id
// function will be applied only to object but not to its descendants
VIEWERDECL void CALL set_color_object(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent);

// set default color and transparency (by type, defined in viewer)
// 'id' could be:  all id | selected id | object id
// if 'id' is object id function will be applied to object and to its descendants
VIEWERDECL void CALL set_default_color(PLUGIN_ID pid, OBJECT_ID id);

// show/hide objects
// 'visible_type' - value from 'VisibleType'
// 'id' could be:  all id | selected id | object id
// openings are draw only if they are selected and visible
// if 'id' is object id function will be applied to object and to its descendants
VIEWERDECL void CALL set_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type);

// 'id' could be:  object id
// function will be applied only to object but not to its descendants
VIEWERDECL void CALL set_visible_object(PLUGIN_ID pid, OBJECT_ID id, int visible_type);

// show/hide many objects
// 'visible_type' - value from 'VisibleType'
// 'id' could contain:  object id
// function will be applied to objects and to its descendants
VIEWERDECL void CALL set_visible_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type);

// 'id' could contain:  object id
// function will be applied only to objects but not to its descendants
VIEWERDECL void CALL set_visible_many_objects(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type);

VIEWERDECL void* CALL debug_test(PLUGIN_ID pid, int nr);


// reading BVF file
// 'fun' - callback function called when BVF file is loaded
VIEWERDECL void CALL on_model_load(PLUGIN_ID pid, callback_fun fun);
// open and start read file 'name' from curently loaded BVF file
// use only in 'on_model_load'
VIEWERDECL bool CALL begin_read_bvf(PLUGIN_ID pid, const wchar_t *name);
// read portion of data from file in curently loaded BVF file
// use only in 'on_model_load'
VIEWERDECL unsigned int CALL read_bvf(PLUGIN_ID pid, void *buf, unsigned int size);
// get file size from curently loaded BVF file
// use only in 'on_model_load'
VIEWERDECL unsigned int CALL get_bvf_size(PLUGIN_ID pid);

// writing to BVF file
// 'fun' event called when user should save his files to BVF
VIEWERDECL void CALL on_save_bvf(PLUGIN_ID pid, callback_fun fun);
// create and begin write data to file 'name' in curently being saved BVF file
// use only in 'on_save_bvf'
VIEWERDECL bool CALL begin_write_bvf(PLUGIN_ID pid, const wchar_t *name);
// write portion of data to file in curently being saved BVF file
// use only in 'on_save_bvf'
VIEWERDECL bool CALL write_bvf(PLUGIN_ID pid, void *buf, unsigned int size);




#ifdef __cplusplus
} // extern "C"
} // namespace viewer
#endif


#endif // ifc_plugin_apiH

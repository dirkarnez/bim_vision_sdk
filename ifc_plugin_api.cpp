#include "ifc_plugin_api.h"


namespace viewer
{

bool end_demo;


typedef OBJECT_ID CALL fun_get_selected_id(PLUGIN_ID pid);
typedef OBJECT_ID CALL fun_get_all_objects_id(PLUGIN_ID pid);

typedef void CALL fun_set_color(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent);
typedef void CALL fun_set_color_object(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent);
typedef void CALL fun_set_default_color(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_use_selection_color(PLUGIN_ID pid, bool b);
typedef void CALL fun_treat_openings_as_normal_objects(PLUGIN_ID pid, bool b);
typedef void CALL fun_set_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type);
typedef void CALL fun_set_visible_object(PLUGIN_ID pid, OBJECT_ID id, int visible_type);
typedef void CALL fun_set_visible_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type);
typedef void CALL fun_set_visible_many_objects(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type);

typedef void CALL fun_set_object_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children);
typedef void CALL fun_set_object_color_rgb(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool with_all_children);
typedef void CALL fun_set_object_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children);
typedef bool CALL fun_get_object_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl);
typedef bool CALL fun_get_object_deafult_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl, int index);
typedef void CALL fun_add_color_to_transparency_list(PLUGIN_ID pid, OBJECT_ID id, Color *cl);
typedef unsigned char CALL fun_get_transparency(PLUGIN_ID pid);
typedef void CALL fun_set_object_edge_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children);
typedef void CALL fun_set_object_edge_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children);

typedef void CALL fun_set_object_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type, bool with_all_children);
typedef void CALL fun_set_object_active(PLUGIN_ID pid, OBJECT_ID id, bool active, bool with_all_children);

typedef void CALL fun_select(PLUGIN_ID pid, OBJECT_ID id, bool b);
typedef void CALL fun_select_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int type);
typedef void CALL fun_apply_select_rules(PLUGIN_ID pid);
typedef void CALL fun_unselect_openings(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_zoom_to(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_zoom_to_in_view(PLUGIN_ID pid, OBJECT_ID id, int width, int height);
typedef void CALL fun_zoom_to_box(PLUGIN_ID pid, const RelativePos *a, const RelativePos *b);
typedef void CALL fun_get_camera_pos(PLUGIN_ID pid, CameraPos *pos);
typedef void CALL fun_set_camera_pos(PLUGIN_ID pid, const CameraPos *pos);
typedef void CALL fun_get_direction_camera(PLUGIN_ID pid, DirectionCamera *cam);
typedef void CALL fun_set_direction_camera(PLUGIN_ID pid, const DirectionCamera *cam);

typedef unsigned int CALL fun_get_cutting_planes(PLUGIN_ID pid, CuttingPlane *buf, unsigned int count);
typedef void CALL fun_set_cutting_planes(PLUGIN_ID pid, const CuttingPlane *buf, unsigned int count);

typedef void CALL fun_invalidate(PLUGIN_ID pid);
typedef float CALL fun_get_draw_time(PLUGIN_ID pid);

typedef unsigned int CALL fun_get_all_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_selected(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_visible(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_active(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef OBJECT_ID CALL fun_get_current_product(PLUGIN_ID pid);
typedef void CALL fun_get_object_state(PLUGIN_ID pid, const OBJECT_ID *id, ObjectState *state, unsigned int count);

typedef bool CALL fun_is_visible(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_is_transparent(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_is_selected(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_is_active(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_has_representation(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_get_bounds(PLUGIN_ID pid, OBJECT_ID id, Bounds *bounds);
typedef void CALL fun_get_offset(PLUGIN_ID pid, OBJECT_ID id, Vector3d *offset);
typedef void CALL fun_set_offset(PLUGIN_ID pid, OBJECT_ID id, const Vector3d *offset);

typedef unsigned int CALL fun_get_childs(PLUGIN_ID pid, OBJECT_ID id, OBJECT_ID *buf, unsigned int count);
typedef void CALL fun_get_object_info(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo *info, unsigned int count);

typedef void CALL fun_set_user_data(PLUGIN_ID pid, OBJECT_ID id, void *user_data, bool with_all_children);
typedef void* CALL fun_get_user_data(PLUGIN_ID pid, OBJECT_ID id);
typedef OBJECT_ID CALL fun_get_project(PLUGIN_ID pid, OBJECT_ID id);
typedef OBJECT_ID CALL fun_get_building(PLUGIN_ID pid, OBJECT_ID id);
typedef OBJECT_ID CALL fun_get_storey(PLUGIN_ID pid, OBJECT_ID id);
typedef OBJECT_ID CALL fun_get_parent(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_get_object_info2(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo2 *info2, unsigned int count);

typedef unsigned int CALL fun_get_object_materials(PLUGIN_ID pid, OBJECT_ID id, Material *buf, unsigned int count);
typedef unsigned int CALL fun_get_object_materials2(PLUGIN_ID pid, OBJECT_ID id, Material2 *buf, unsigned int count);
typedef unsigned int CALL fun_get_object_materials3(PLUGIN_ID pid, OBJECT_ID id, Material3 *buf, unsigned int count);
typedef bool CALL fun_get_object_type_style(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle *result);
typedef bool CALL fun_get_object_type_style2(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle2 *result);

typedef unsigned int CALL fun_get_layers(PLUGIN_ID pid, Layer *buf, unsigned int count);
typedef unsigned int CALL fun_get_layer_objects(PLUGIN_ID pid, LAYER_REF id, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_zones(PLUGIN_ID pid, Zone *buf, unsigned int count);
typedef unsigned int CALL fun_get_zones2(PLUGIN_ID pid, Zone2 *buf, unsigned int count);
typedef unsigned int CALL fun_get_zone_objects(PLUGIN_ID pid, ZONE_REF id, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_systems(PLUGIN_ID pid, System *buf, unsigned int count);
typedef unsigned int CALL fun_get_system_objects(PLUGIN_ID pid, ZONE_REF id, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_groups(PLUGIN_ID pid, Group *buf, unsigned int count);
typedef unsigned int CALL fun_get_group_objects(PLUGIN_ID pid, GROUP_REF id, OBJECT_ID *buf, unsigned int count);

typedef unsigned int CALL fun_get_property_sets(PLUGIN_ID pid, OBJECT_ID id, PropertySet *buf, unsigned int count);
typedef unsigned int CALL fun_get_properties(PLUGIN_ID pid, const PropertyGet *pg, Property *buf, unsigned int count);
typedef unsigned int CALL fun_get_properties2(PLUGIN_ID pid, const PropertyGet *pg, Property2 *buf, unsigned int count);
typedef unsigned int CALL fun_filter_properties(PLUGIN_ID pid, const PropertyFilter *pf, Property *buf, unsigned int count);
typedef void CALL fun_select_property(PLUGIN_ID pid, int set_nr, int property_nr, bool select_value);

typedef unsigned int CALL fun_get_object_properties(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData *buf, unsigned int count);
typedef unsigned int CALL fun_get_object_properties2(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData2 *buf, unsigned int count);
typedef unsigned int CALL fun_get_material_properties(PLUGIN_ID pid, MATERIAL_REF ref, int flag, PropertySetData *buf, unsigned int count);
typedef unsigned int CALL fun_get_type_style_properties(PLUGIN_ID pid, OBJECT_TYPE_STYLE_REF ref, int flag, PropertySetData *buf, unsigned int count);

typedef bool CALL fun_delete_object_property_or_set(PLUGIN_ID pid, const PropertyDef *def);
typedef void CALL fun_add_or_change_object_property(PLUGIN_ID pid, const PropertyDef *def, const PropertyData *data);
typedef void CALL fun_on_property_change(PLUGIN_ID pid, callback_fun fun);

typedef unsigned int CALL fun_get_classifications(PLUGIN_ID pid, Classification *buf, unsigned int count);
typedef unsigned int CALL fun_get_classification_references(PLUGIN_ID pid, wchar_t *classification_name, ClassificationReference *references, unsigned int count);

typedef unsigned int CALL fun_get_object_classification_references(PLUGIN_ID pid, OBJECT_ID id, ClassificationReference *buf, unsigned int count);
typedef bool CALL fun_get_classification_data(PLUGIN_ID pid, REF cl, Classification *classification);
typedef bool CALL fun_get_classification_reference_data(PLUGIN_ID pid, REF cl_ref, ClassificationReference *classification_reference);

typedef int CALL fun_get_projects_offsets(PLUGIN_ID pid, ProjectOffset *offsets, int count);

typedef double CALL fun_get_unit_factor(PLUGIN_ID pid);
typedef bool CALL fun_first_geometry(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_get_total_geometry_bounds(PLUGIN_ID pid, Bounds *bounds);
typedef unsigned int CALL fun_get_geometry(PLUGIN_ID pid, Face *faces, unsigned int count);
typedef void CALL fun_get_geometry_color(PLUGIN_ID pid, Color *face_color, Color *line_color);
typedef unsigned int CALL fun_get_geometry_edges(PLUGIN_ID pid, Edge *edges, unsigned int count);
typedef bool CALL fun_next_geometry(PLUGIN_ID pid);
typedef bool CALL fun_is_online_licence(PLUGIN_ID pid);

typedef void CALL fun_on_measure_change(PLUGIN_ID pid, callback_fun fun);
typedef void CALL fun_on_tab_sheet_placement(PLUGIN_ID pid, callback_tab_sheet_placement fun);
typedef void CALL fun_on_tab_sheet_change(PLUGIN_ID pid, callback_tab_sheet_change fun);
typedef void CALL fun_get_measure(PLUGIN_ID pid, Measure *measure);
typedef void CALL fun_get_measure_v1(PLUGIN_ID pid, Measure_v1 *measure_v1);
typedef unsigned int CALL fun_get_object_corners(PLUGIN_ID pid, OBJECT_ID obj_id,
                                                 Vector3d *corners_vct, unsigned int corners_count);
typedef unsigned int CALL fun_get_object_edges(PLUGIN_ID pid, OBJECT_ID obj_id,
                                               Edge *edge_vct, unsigned int edge_count);
typedef bool CALL fun_get_object_area(PLUGIN_ID pid, OBJECT_ID obj_id, MeasuredArea *measure);
typedef unsigned int CALL fun_get_measure_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef unsigned int CALL fun_get_measure_elements(PLUGIN_ID pid, double *buf, unsigned int count);
typedef void CALL fun_clear_measure(PLUGIN_ID pid);
typedef void CALL fun_set_measure_type(PLUGIN_ID pid, int type, int param);
typedef double CALL fun_get_volume(PLUGIN_ID pid, OBJECT_ID id);
typedef void CALL fun_get_centroid(PLUGIN_ID pid, OBJECT_ID id, Vector3d *centroid, double *weight);
typedef double CALL fun_get_total_area(PLUGIN_ID pid, OBJECT_ID id);
typedef unsigned int CALL fun_get_measure_state(PLUGIN_ID pid, void *buf, unsigned int buf_size);
typedef void CALL fun_set_measure_state(PLUGIN_ID pid, int flags, const void *buf, unsigned int buf_size);

typedef unsigned int CALL fun_get_measure_count(PLUGIN_ID pid);
typedef unsigned int CALL fun_get_detailed_measure_state(PLUGIN_ID pid, int index, void *buf, unsigned int buf_size, MeasureDetail *details);
typedef void CALL fun_set_detailed_measure_state(PLUGIN_ID pid, int flags, const void *state, unsigned int size);
typedef unsigned int CALL fun_construct_measure_state(PLUGIN_ID pid, ConstructMeasureState *construct, void *buf, unsigned int buf_size);
typedef void CALL fun_change_measure_state_density(PLUGIN_ID pid, void *state, double density);

typedef void CALL fun_get_plugin_status(PLUGIN_ID pid, const wchar_t *dll_name, PluginStatus *status);
typedef bool CALL fun_send_plugin_massage(PLUGIN_ID pid, const wchar_t *dll_name, PluginMessage *message);
typedef void CALL fun_on_plugin_message(PLUGIN_ID pid, callback_plugin_message fun);

typedef const wchar_t* CALL fun_get_loaded_ifc_path(PLUGIN_ID pid);
typedef const wchar_t* CALL fun_get_project_path(PLUGIN_ID pid, OBJECT_ID project_id);
typedef bool           CALL fun_extract_file_from_bvf(PLUGIN_ID pid, OBJECT_ID project_id, const wchar_t *to_ifc_file_name);
typedef unsigned int CALL fun_get_loaded_ifc_files_count(PLUGIN_ID pid);
typedef const wchar_t* CALL fun_get_loaded_ifc_filename(PLUGIN_ID pid, unsigned int file_index);
typedef bool CALL fun_load_ifc(PLUGIN_ID pid, const wchar_t *path);
typedef bool CALL fun_load_ifc_from_buffer(PLUGIN_ID pid, const wchar_t *path, char *buffer, unsigned int buf_size);
typedef bool CALL fun_add_ifc(PLUGIN_ID pid, const wchar_t *path);
typedef OBJECT_ID CALL fun_calculate_object_id(PLUGIN_ID pid, const char *ifc_id);

typedef void CALL fun_on_model_load(PLUGIN_ID pid, callback_fun fun);
typedef void CALL fun_on_model_clear(PLUGIN_ID pid, callback_fun fun);
typedef bool CALL fun_file_was_added(PLUGIN_ID pid);

typedef bool CALL fun_begin_read_bvf(PLUGIN_ID pid, const wchar_t *name);
typedef unsigned int CALL fun_read_bvf(PLUGIN_ID pid, void *buf, unsigned int size);
typedef unsigned int CALL fun_get_bvf_size(PLUGIN_ID pid);

typedef void CALL fun_on_save_bvf(PLUGIN_ID pid, callback_fun fun);
typedef bool CALL fun_begin_write_bvf(PLUGIN_ID pid, const wchar_t *name);
typedef bool CALL fun_write_bvf(PLUGIN_ID pid, void *buf, unsigned int size);

typedef bool CALL fun_begin_write_bvf_v2(PLUGIN_ID pid, const wchar_t *name);
typedef bool CALL fun_write_bvf_v2(PLUGIN_ID pid, void *buf, unsigned long long size);
typedef bool CALL fun_write_file_to_bvf_v2(PLUGIN_ID pid, wchar_t *external_file_name);

typedef void CALL fun_can_clear_model(PLUGIN_ID pid, bool_callback_fun fun);

typedef bool CALL fun_begin_read_bvf_v2(PLUGIN_ID pid, const wchar_t *name);
typedef unsigned long long CALL fun_read_bvf_v2(PLUGIN_ID pid, void *buf, unsigned long long size);
typedef bool CALL fun_save_bvf_sub_file_v2(PLUGIN_ID pid, wchar_t *save_as_file_name);
typedef wchar_t**          CALL fun_get_bvf_dir_file_list_v2(PLUGIN_ID pid);
typedef unsigned long long CALL fun_get_bvf_size_v2(PLUGIN_ID pid);

typedef void CALL fun_need_save_bvf(PLUGIN_ID pid, bool flag);
typedef bool CALL fun_save_file(PLUGIN_ID pid);
typedef void CALL fun_need_save_changes(PLUGIN_ID pid, bool flag);
typedef void CALL fun_on_object_list_changed(PLUGIN_ID pid, callback_fun fun);

typedef void CALL fun_on_selection_change(PLUGIN_ID pid, callback_fun fun);
typedef void CALL fun_on_hover(PLUGIN_ID pid, callback_fun fun);
typedef bool CALL fun_get_clicked_pos(PLUGIN_ID pid, RelativePos *pos);
typedef bool CALL fun_get_clicked_normal(PLUGIN_ID pid, Vector3d *normal);
typedef void CALL fun_get_hovered_pos(PLUGIN_ID pid, RelativePos *pos);
typedef void CALL fun_get_dropped_pos(PLUGIN_ID pid, RelativePos *pos);
typedef void CALL fun_set_hover_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count);
typedef void CALL fun_on_draw(PLUGIN_ID pid, callback_fun fun);
typedef void CALL fun_set_draw_object_id(PLUGIN_ID pid, unsigned int id);
typedef void CALL fun_on_draw_object_click(PLUGIN_ID pid, callback_fun fun);
typedef unsigned int CALL fun_get_draw_object_id(PLUGIN_ID pid);
typedef void CALL fun_draw_point(PLUGIN_ID pid, const Point *point);
typedef void CALL fun_draw_line(PLUGIN_ID pid, const Line *line);
typedef void CALL fun_draw_sphere(PLUGIN_ID pid, const Sphere *sphere);

typedef SOLID_ID CALL fun_create_intersection_solid(PLUGIN_ID pid, OBJECT_ID object_a, OBJECT_ID object_b);
typedef void CALL fun_delete_solid(PLUGIN_ID pid, SOLID_ID solid_id);
typedef void CALL fun_draw_solid(PLUGIN_ID pid, SOLID_ID solid_id, Color color);
typedef double CALL fun_get_solid_volume(PLUGIN_ID pid, SOLID_ID solid_id);
typedef double CALL fun_get_solid_area(PLUGIN_ID pid, SOLID_ID solid_id);
typedef void CALL fun_get_solid_center_point(PLUGIN_ID pid, SOLID_ID solid_id, Vertex *center);
typedef void CALL fun_zoom_to_solids(PLUGIN_ID pid, const SOLID_ID *id, unsigned int count);
typedef void CALL fun_zoom_to_objects(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count);

typedef void CALL fun_load_icon_image(PLUGIN_ID pid, const wchar_t *image_path);
typedef void CALL fun_draw_icon(PLUGIN_ID pid, const Icon *icon);

typedef void CALL fun_draw_label(PLUGIN_ID pid, const Label *label);
typedef void CALL fun_get_element_pos(PLUGIN_ID pid, RelativePos *pos);
typedef void CALL fun_set_drag_mode(PLUGIN_ID pid, bool set);

typedef const wchar_t* CALL fun_get_language(PLUGIN_ID pid);
typedef const OBJECT_ID CALL fun_create_user_object(PLUGIN_ID pid, OBJECT_ID parent, const char* ifc_entity_name, const wchar_t* name, const wchar_t* desc);
typedef bool CALL fun_delete_user_object(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_check_triangle(PLUGIN_ID pid, const Face* face);
typedef bool CALL fun_add_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id, const Face *faces, unsigned int count, const viewer::Color *cl);
typedef bool CALL fun_delete_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id);
typedef bool CALL fun_set_geometry_edges_user_object(PLUGIN_ID pid, OBJECT_ID id, const Edge *edges, unsigned int count);
typedef bool CALL fun_save_file_as(PLUGIN_ID pid, const wchar_t *name, int save_type);
typedef bool CALL fun_load_texts(PLUGIN_ID pid, const wchar_t *file_name);
typedef const wchar_t* CALL fun_get_text(PLUGIN_ID pid, const char *txt_id);
typedef const wchar_t* CALL fun_get_text_global(PLUGIN_ID pid, const char *txt_id);
typedef const wchar_t* CALL fun_get_entity_type_name(PLUGIN_ID pid, const char *ifc_entity_name);

typedef OBJECT_ID CALL fun_get_object_below_mouse(PLUGIN_ID pid, int x, int y);

typedef int CALL fun_create_tab_sheet(PLUGIN_ID pid, const wchar_t *name, bool allow_close);
typedef void CALL fun_activate_tab_sheet(PLUGIN_ID pid, int id);
typedef void CALL fun_close_tab_sheet(PLUGIN_ID pid, int id);
typedef void CALL fun_show_tab_sheet(PLUGIN_ID pid, int id, bool show);
typedef bool CALL fun_is_active_tab_sheet(PLUGIN_ID pid, int id);
typedef int CALL fun_create_tab(PLUGIN_ID pid, const wchar_t *name);
typedef int CALL fun_create_group(PLUGIN_ID pid, int tab_id, const wchar_t *name);
typedef void CALL fun_show_group(PLUGIN_ID pid, int group_id, bool visible);
typedef int CALL fun_create_button(PLUGIN_ID pid, int group_id, callback_fun fun);
typedef int CALL fun_create_small_button(PLUGIN_ID pid, int group_id, callback_fun fun);
typedef int CALL fun_create_checkbox(PLUGIN_ID pid, int group_id, callback_fun fun);
typedef int CALL fun_create_radio_button(PLUGIN_ID pid, int group_id, callback_fun fun);

typedef int CALL fun_create_dropdown_button(PLUGIN_ID pid, int group_id, callback_fun fun);
typedef int CALL fun_create_sub_button(PLUGIN_ID pid, int group_id, bool small);
typedef int CALL fun_create_sub_button2(PLUGIN_ID pid, int group_id, bool small, callback_fun fun);
typedef void CALL fun_add_button(PLUGIN_ID pid, int parent_button_id, int button_id);
typedef void CALL fun_add_separator(PLUGIN_ID pid, int parent_button_id, const wchar_t *caption);

typedef void CALL fun_set_button_text(PLUGIN_ID pid, int button_id, const wchar_t *caption, const wchar_t *hint);
typedef void CALL fun_set_button_image(PLUGIN_ID pid, int button_id, const wchar_t *large_img_path);
typedef void CALL fun_set_button_small_image(PLUGIN_ID pid, int button_id, const wchar_t *samll_img_path);
typedef void CALL fun_set_button_shortcut(PLUGIN_ID pid, int button_id, const wchar_t *shortcut);
typedef void CALL fun_set_button_state(PLUGIN_ID pid, int button_id, bool enabled, bool down);
typedef void CALL fun_set_button_down(PLUGIN_ID pid, int button_id, bool down);
typedef void CALL fun_set_button_guid(PLUGIN_ID pid, int button_id, const char *str);
typedef void CALL fun_enable_button(PLUGIN_ID pid, int button_id, bool enabled);
typedef void CALL fun_show_button(PLUGIN_ID pid, int button_id, bool show);
typedef int CALL fun_clicked_button(PLUGIN_ID pid);
typedef void CALL fun_begin_control_group(PLUGIN_ID pid);

typedef void CALL fun_on_context_menu(PLUGIN_ID pid, callback_fun fun);
typedef void CALL fun_add_context_button(PLUGIN_ID pid, int button_id);
typedef void CALL fun_clear_context_menu(PLUGIN_ID pid);

typedef int CALL fun_create_gallery_button(PLUGIN_ID pid, int group_id, bool small, callback_fun fun);
typedef void CALL fun_set_gallery_style(PLUGIN_ID pid, int gallery_id, int min_col_count, int style);
typedef int CALL fun_create_gallery_category(PLUGIN_ID pid, int gallery_id);
typedef void CALL fun_set_gallery_category_text(PLUGIN_ID pid, int gallery_category_id, const wchar_t *caption);
typedef void CALL fun_set_gallery_category_style(PLUGIN_ID pid, int gallery_category_id, int display_texts, int texts_posistion);
typedef void CALL fun_delete_gallery_category(PLUGIN_ID pid, int gallery_category_id);
typedef int CALL fun_create_gallery_item(PLUGIN_ID pid, int gallery_category_id, callback_fun fun);
typedef void CALL fun_set_gallery_item_text(PLUGIN_ID pid, int gallery_item_id, const wchar_t *caption, const wchar_t *descrption);
typedef void CALL fun_set_gallery_item_image(PLUGIN_ID pid, int gallery_item_id, const wchar_t *path);
typedef void CALL fun_delete_gallery_item(PLUGIN_ID pid, int gallery_item_id);
typedef void CALL fun_clear_gallery(PLUGIN_ID pid, int gallery_id);
typedef void CALL fun_on_gallery_item_context_menu(PLUGIN_ID pid, callback_fun fun);

typedef bool CALL fun_is_center_view(PLUGIN_ID pid);

typedef int CALL fun_get_active_tab(PLUGIN_ID pid);
typedef void CALL fun_on_tab_change(PLUGIN_ID pid, callback_fun fun);

typedef ColorRGB CALL fun_get_gui_color(PLUGIN_ID pid, int gui_color_id);
typedef int CALL fun_get_gui_theme(PLUGIN_ID pid);

typedef int CALL fun_message_box(PLUGIN_ID pid, const wchar_t *caption, const wchar_t *message, int flags);
typedef void CALL fun_set_open_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory);
typedef bool CALL fun_open_file_dialog(PLUGIN_ID pid, bool multiple_files);
typedef unsigned int CALL fun_get_open_dialog_file_count(PLUGIN_ID pid);
typedef const wchar_t* CALL fun_get_open_dialog_file_nr(PLUGIN_ID pid, unsigned int nr);
typedef void CALL fun_set_save_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory, const wchar_t *file_name);
typedef void CALL fun_set_save_dialog_default_extension(PLUGIN_ID pid, const wchar_t *extension);
typedef bool CALL fun_save_dialog(PLUGIN_ID pid, bool select_directory_only);
typedef const wchar_t* CALL fun_get_save_dialog_name(PLUGIN_ID pid);
typedef void CALL fun_show_progress_bar(PLUGIN_ID pid, bool show, int style, const wchar_t *title);
typedef bool CALL fun_update_progress_bar(PLUGIN_ID pid, int percent, const wchar_t *message, int second_percent, const wchar_t *second_message);

typedef void CALL fun_get_view_rect(PLUGIN_ID pid, RECT *rect);
typedef void CALL fun_show_ifc_structure_grid(PLUGIN_ID pid, bool force_show_properties);
typedef void CALL fun_set_ribbon_state(PLUGIN_ID pid, int state);
typedef void CALL fun_set_grids_state(PLUGIN_ID pid, int state);
typedef bool CALL fun_get_grids_state(PLUGIN_ID pid);
typedef bool CALL fun_item_command(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *command);
typedef void CALL fun_set_item_value(PLUGIN_ID pid, const wchar_t *item_name, double value);
typedef double CALL fun_get_item_value(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *value_type);
typedef bool   CALL fun_register_on_button_click(PLUGIN_ID pid, const wchar_t *item_name, callback_fun fun);

typedef bool CALL fun_is_touch_mode(PLUGIN_ID pid);
typedef unsigned int CALL fun_get_view_state(PLUGIN_ID pid, int flags, void *state, unsigned int size);
typedef void CALL fun_set_view_state(PLUGIN_ID pid, int flags, const void *state, unsigned int size);

typedef bool CALL fun_render_screenshot(PLUGIN_ID pid, unsigned int w, unsigned int h, unsigned char *buf);
typedef void CALL fun_set_screenshot_style(PLUGIN_ID pid, int style);

typedef void CALL fun_get_2d_bounds(PLUGIN_ID pid, const OBJECT_ID *obj, Bounds *bounds, unsigned int count, int flags);
typedef void CALL fun_project_to_2d(PLUGIN_ID pid, const RelativePos *pos, Vector3d *pos_2d, unsigned int count, int flags);//
typedef void CALL fun_recalc_cross_sections(PLUGIN_ID pid, int flags);
typedef void CALL fun_cross_sections_style(PLUGIN_ID pid, int color_type, ColorRGB color, bool bold);
typedef void CALL fun_close_application(PLUGIN_ID pid);
typedef unsigned int CALL fun_register_undo_action(PLUGIN_ID pid, wchar_t *action_name);


typedef void* CALL fun_debug_test(PLUGIN_ID pid, int nr);

// wskazniki do funkcji

fun_get_selected_id                 *p_get_selected_id;
fun_get_all_objects_id              *p_get_all_objects_id;

fun_set_color                       *p_set_color;
fun_set_color_object                *p_set_color_object;
fun_set_default_color               *p_set_default_color;
fun_use_selection_color             *p_use_selection_color;
fun_treat_openings_as_normal_objects *p_treat_openings_as_normal_objects;
fun_set_visible                     *p_set_visible;
fun_set_visible_object              *p_set_visible_object;
fun_set_visible_many                *p_set_visible_many;
fun_set_visible_many_objects        *p_set_visible_many_objects;

fun_set_object_color                *p_set_object_color;
fun_set_object_color_rgb            *p_set_object_color_rgb;
fun_set_object_default_color        *p_set_object_default_color;
fun_get_object_color                *p_get_object_color;
fun_get_object_deafult_color        *p_get_object_deafult_color;
fun_add_color_to_transparency_list  *p_add_color_to_transparency_list;
fun_get_transparency                *p_get_transparency;
fun_set_object_edge_color           *p_set_object_edge_color;
fun_set_object_edge_default_color   *p_set_object_edge_default_color;
fun_set_object_visible              *p_set_object_visible;
fun_set_object_active               *p_set_object_active;

fun_select                          *p_select;
fun_select_many                     *p_select_many;
fun_apply_select_rules              *p_apply_select_rules;
fun_unselect_openings               *p_unselect_openings;
fun_zoom_to                         *p_zoom_to;
fun_zoom_to_in_view                 *p_zoom_to_in_view;
fun_zoom_to_box                     *p_zoom_to_box;
fun_get_camera_pos                  *p_get_camera_pos;
fun_set_camera_pos                  *p_set_camera_pos;
fun_get_direction_camera            *p_get_direction_camera;
fun_set_direction_camera            *p_set_direction_camera;

fun_get_cutting_planes              *p_get_cutting_planes;
fun_set_cutting_planes              *p_set_cutting_planes;

fun_calculate_object_id             *p_calculate_object_id;
fun_invalidate                      *p_invalidate;
fun_get_draw_time                   *p_get_draw_time;

fun_get_all_objects                 *p_get_all_objects;
fun_get_selected                    *p_get_selected;
fun_get_visible                     *p_get_visible;
fun_get_active                      *p_get_active;
fun_get_current_product             *p_get_current_product;
fun_get_object_state                *p_get_object_state;

fun_is_visible                      *p_is_visible;
fun_is_transparent                  *p_is_transparent;
fun_is_selected                     *p_is_selected;
fun_is_active                       *p_is_active;
fun_has_representation              *p_has_representation;
fun_get_bounds                      *p_get_bounds;
fun_get_offset                      *p_get_offset;
fun_set_offset                      *p_set_offset;

fun_get_childs                      *p_get_childs;
fun_get_object_info                 *p_get_object_info;

fun_set_user_data                   *p_set_user_data;
fun_get_user_data                   *p_get_user_data;
fun_get_project                     *p_get_project;
fun_get_building                    *p_get_building;
fun_get_storey                      *p_get_storey;
fun_get_parent                      *p_get_parent;
fun_get_object_info2                *p_get_object_info2;

fun_get_object_materials            *p_get_object_materials;
fun_get_object_materials2           *p_get_object_materials2;
fun_get_object_materials3           *p_get_object_materials3;
fun_get_object_type_style           *p_get_object_type_style;
fun_get_object_type_style2          *p_get_object_type_style2;

fun_get_layers                      *p_get_layers;
fun_get_layer_objects               *p_get_layer_objects;
fun_get_zones                       *p_get_zones;
fun_get_zones2                      *p_get_zones2;
fun_get_zone_objects                *p_get_zone_objects;
fun_get_systems                     *p_get_systems;
fun_get_system_objects              *p_get_system_objects;
fun_get_groups                      *p_get_groups;
fun_get_group_objects               *p_get_group_objects;

fun_get_property_sets               *p_get_property_sets;
fun_get_properties                  *p_get_properties;
fun_get_properties2                 *p_get_properties2;
fun_filter_properties               *p_filter_properties;
fun_select_property                 *p_select_property;

fun_get_object_properties           *p_get_object_properties;
fun_get_object_properties2          *p_get_object_properties2;
fun_get_material_properties         *p_get_material_properties;
fun_get_type_style_properties       *p_get_type_style_properties;

fun_delete_object_property_or_set         *p_delete_object_property_or_set;
fun_add_or_change_object_property         *p_add_or_change_object_property;
fun_on_property_change                    *p_on_property_change;

fun_get_classifications                   *p_get_classifications;
fun_get_classification_references         *p_get_classification_references;
fun_get_object_classification_references  *p_get_object_classification_references;
fun_get_classification_data               *p_get_classification_data;
fun_get_classification_reference_data     *p_get_classification_reference_data;
fun_get_projects_offsets            *p_get_projects_offsets;
fun_get_unit_factor                 *p_get_unit_factor;
fun_first_geometry                  *p_first_geometry;
fun_get_total_geometry_bounds       *p_get_total_geometry_bounds;
fun_get_geometry                    *p_get_geometry;
fun_get_geometry_color              *p_get_geometry_color;
fun_get_geometry_edges              *p_get_geometry_edges;
fun_next_geometry                   *p_next_geometry;
fun_is_online_licence               *p_is_online_licence;

fun_on_tab_sheet_placement          *p_on_tab_sheet_placement;
fun_on_tab_sheet_change             *p_on_tab_sheet_change;
fun_on_measure_change               *p_on_measure_change;
fun_get_object_corners              *p_get_object_corners;
fun_get_object_edges                *p_get_object_edges;
fun_get_object_area                 *p_get_object_area;
fun_get_measure                     *p_get_measure;
fun_get_measure_v1                  *p_get_measure_v1;
fun_get_measure_objects             *p_get_measure_objects;
fun_get_measure_elements            *p_get_measure_elements;
fun_clear_measure                   *p_clear_measure;
fun_set_measure_type                *p_set_measure_type;
fun_get_volume                      *p_get_volume;
fun_get_centroid                    *p_get_centroid;
fun_get_total_area                  *p_get_total_area;
fun_get_measure_state               *p_get_measure_state;
fun_set_measure_state               *p_set_measure_state;

fun_get_measure_count               *p_get_measure_count;
fun_get_detailed_measure_state      *p_get_detailed_measure_state;
fun_set_detailed_measure_state      *p_set_detailed_measure_state;
fun_change_measure_state_density    *p_change_measure_state_density;
fun_construct_measure_state         *p_construct_measure_state;



fun_get_plugin_status               *p_get_plugin_status;
fun_send_plugin_massage             *p_send_plugin_massage;
fun_on_plugin_message               *p_on_plugin_message;

fun_get_loaded_ifc_path             *p_get_loaded_ifc_path;
fun_get_project_path                *p_get_project_path;
fun_extract_file_from_bvf           *p_extract_file_from_bvf;
fun_get_loaded_ifc_files_count		*p_get_loaded_ifc_files_count;
fun_get_loaded_ifc_filename         *p_get_loaded_ifc_filename;
fun_load_ifc                        *p_load_ifc;
fun_load_ifc_from_buffer            *p_load_ifc_from_buffer;
fun_add_ifc                         *p_add_ifc;

fun_on_model_load                   *p_on_model_load;
fun_on_model_clear                  *p_on_model_clear;
fun_file_was_added                  *p_file_was_added;

fun_begin_read_bvf                  *p_begin_read_bvf;
fun_read_bvf                        *p_read_bvf;
fun_get_bvf_size                    *p_get_bvf_size;

fun_begin_read_bvf_v2               *p_begin_read_bvf_v2;
fun_save_bvf_sub_file_v2            *p_save_bvf_sub_file_v2;
fun_get_bvf_dir_file_list_v2        *p_get_bvf_dir_file_list_v2;
fun_read_bvf_v2                     *p_read_bvf_v2;
fun_get_bvf_size_v2                 *p_get_bvf_size_v2;

fun_on_save_bvf                     *p_on_save_bvf;
fun_begin_write_bvf                 *p_begin_write_bvf;
fun_write_bvf                       *p_write_bvf;
fun_begin_write_bvf_v2              *p_begin_write_bvf_v2;
fun_write_bvf_v2                    *p_write_bvf_v2;
fun_write_file_to_bvf_v2            *p_write_file_to_bvf_v2;

fun_can_clear_model                 *p_can_clear_model;

fun_need_save_bvf                   *p_need_save_bvf;
fun_save_file                       *p_save_file;
fun_need_save_changes               *p_need_save_changes;
fun_on_object_list_changed          *p_on_object_list_changed;

fun_on_selection_change             *p_on_selection_change;
fun_on_hover                        *p_on_hover;
fun_get_clicked_pos                 *p_get_clicked_pos;
fun_get_clicked_normal              *p_get_clicked_normal;
fun_get_hovered_pos                 *p_get_hovered_pos;
fun_get_dropped_pos                 *p_get_dropped_pos;
fun_set_hover_objects               *p_set_hover_objects;
fun_on_draw                         *p_on_draw;
fun_set_draw_object_id              *p_set_draw_object_id;
fun_on_draw_object_click            *p_on_draw_object_click;
fun_get_draw_object_id              *p_get_draw_object_id;
fun_draw_point                      *p_draw_point;
fun_draw_line                       *p_draw_line;
fun_draw_sphere                     *p_draw_sphere;
fun_create_intersection_solid       *p_create_intersection_solid;
fun_delete_solid                    *p_delete_solid;
fun_draw_solid                      *p_draw_solid;
fun_get_solid_volume                *p_get_solid_volume;
fun_get_solid_area                  *p_get_solid_area;
fun_get_solid_center_point          *p_get_solid_center_point;
fun_zoom_to_solids                  *p_zoom_to_solids;
fun_zoom_to_objects                 *p_zoom_to_objects;

fun_load_icon_image                 *p_load_icon_image;
fun_draw_icon                       *p_draw_icon;

fun_draw_label                      *p_draw_label;
fun_get_element_pos                 *p_get_element_pos;
fun_set_drag_mode                   *p_set_drag_mode;

fun_get_language                    *p_get_language;
fun_create_user_object              *p_create_user_object;
fun_delete_user_object              *p_delete_user_object;
fun_check_triangle                  *p_check_triangle;
fun_add_geometry_user_object        *p_add_geometry_user_object;
fun_delete_geometry_user_object     *p_delete_geometry_user_object;
fun_set_geometry_edges_user_object  *p_set_geometry_edges_user_object;
fun_save_file_as                    *p_save_file_as; 
fun_load_texts                      *p_load_texts;
fun_get_text                        *p_get_text;
fun_get_text_global                 *p_get_text_global;
fun_get_entity_type_name            *p_get_entity_type_name;

fun_get_object_below_mouse          *p_get_object_below_mouse;

fun_create_tab_sheet                *p_create_tab_sheet;
fun_activate_tab_sheet              *p_activate_tab_sheet;
fun_close_tab_sheet                 *p_close_tab_sheet;
fun_show_tab_sheet                  *p_show_tab_sheet;
fun_is_active_tab_sheet             *p_is_active_tab_sheet;

fun_create_tab                      *p_create_tab;
fun_create_group                    *p_create_group;
fun_show_group                      *p_show_group;
fun_create_button                   *p_create_button;
fun_create_small_button             *p_create_small_button;
fun_create_checkbox                 *p_create_checkbox;
fun_create_radio_button             *p_create_radio_button;

fun_create_dropdown_button          *p_create_dropdown_button;
fun_create_sub_button               *p_create_sub_button;
fun_create_sub_button2              *p_create_sub_button2;
fun_add_button                      *p_add_button;
fun_add_separator                   *p_add_separator;

fun_set_button_text                 *p_set_button_text;
fun_set_button_image                *p_set_button_image;
fun_set_button_small_image          *p_set_button_small_image;
fun_set_button_shortcut             *p_set_button_shortcut;
fun_set_button_state                *p_set_button_state;
fun_set_button_down                 *p_set_button_down;
fun_set_button_guid                 *p_set_button_guid;
fun_enable_button                   *p_enable_button;
fun_show_button                     *p_show_button;
fun_clicked_button                  *p_clicked_button;
fun_begin_control_group             *p_begin_control_group;

fun_on_context_menu                 *p_on_context_menu;
fun_add_context_button              *p_add_context_button;
fun_clear_context_menu              *p_clear_context_menu;

fun_create_gallery_button           *p_create_gallery_button;
fun_set_gallery_style               *p_set_gallery_style;
fun_create_gallery_category         *p_create_gallery_category;
fun_set_gallery_category_text       *p_set_gallery_category_text;
fun_set_gallery_category_style      *p_set_gallery_category_style;
fun_delete_gallery_category         *p_delete_gallery_category;
fun_create_gallery_item             *p_create_gallery_item;
fun_set_gallery_item_text           *p_set_gallery_item_text;
fun_set_gallery_item_image          *p_set_gallery_item_image;
fun_delete_gallery_item             *p_delete_gallery_item;
fun_clear_gallery                   *p_clear_gallery;
fun_on_gallery_item_context_menu    *p_on_gallery_item_context_menu;

fun_is_center_view                  *p_is_center_view;

fun_get_active_tab                  *p_get_active_tab;
fun_on_tab_change                   *p_on_tab_change;

fun_get_gui_color                   *p_get_gui_color;
fun_get_gui_theme                   *p_get_gui_theme;

fun_message_box                     *p_message_box;
fun_set_open_dialog_params          *p_set_open_dialog_params;
fun_open_file_dialog                *p_open_file_dialog;
fun_get_open_dialog_file_count      *p_get_open_dialog_file_count;
fun_get_open_dialog_file_nr         *p_get_open_dialog_file_nr;
fun_set_save_dialog_params          *p_set_save_dialog_params;
fun_set_save_dialog_default_extension  *p_set_save_dialog_default_extension;
fun_save_dialog                     *p_save_dialog;
fun_get_save_dialog_name            *p_get_save_dialog_name;
fun_show_progress_bar               *p_show_progress_bar;
fun_update_progress_bar             *p_update_progress_bar;

fun_get_view_rect                   *p_get_view_rect;
fun_show_ifc_structure_grid         *p_show_ifc_structure_grid;
fun_set_ribbon_state                *p_set_ribbon_state;
fun_set_grids_state                 *p_set_grids_state;
fun_get_grids_state                 *p_get_grids_state;
fun_item_command                    *p_item_command;
fun_set_item_value                  *p_set_item_value;
fun_get_item_value                  *p_get_item_value;
fun_register_on_button_click        *p_register_on_button_click;

fun_is_touch_mode                   *p_is_touch_mode;
fun_get_view_state                  *p_get_view_state;
fun_set_view_state                  *p_set_view_state;

fun_render_screenshot               *p_render_screenshot;
fun_set_screenshot_style            *p_set_screenshot_style;
fun_get_2d_bounds                   *p_get_2d_bounds;
fun_project_to_2d                   *p_project_to_2d;
fun_recalc_cross_sections           *p_recalc_cross_sections;
fun_cross_sections_style            *p_cross_sections_style;
fun_close_application               *p_close_application;
fun_register_undo_action            *p_register_undo_action;

fun_debug_test                      *p_debug_test;


OBJECT_ID CALL get_selected_id(PLUGIN_ID pid)
{
    if(p_get_selected_id)
        return p_get_selected_id(pid);
    return 0;
}


OBJECT_ID CALL get_all_objects_id(PLUGIN_ID pid)
{
    if(p_get_all_objects_id)
        return p_get_all_objects_id(pid);
    return 0;
}


void CALL set_color(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent)
{
    if(p_set_color)
        p_set_color(pid, id, cl, transparent);
}


void CALL set_color_object(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool transparent)
{
    if(p_set_color_object)
        p_set_color_object(pid, id, cl, transparent);
}


void CALL set_default_color(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_set_default_color)
        p_set_default_color(pid, id);
}


void CALL use_selection_color(PLUGIN_ID pid, bool b)
{
    if(p_use_selection_color)
        p_use_selection_color(pid, b);
}


void CALL treat_openings_as_normal_objects(PLUGIN_ID pid, bool b)
{
    if(p_treat_openings_as_normal_objects)
        p_treat_openings_as_normal_objects(pid, b);
}


void CALL set_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type)
{
    if(p_set_visible)
        p_set_visible(pid, id, visible_type);
}


void CALL set_visible_object(PLUGIN_ID pid, OBJECT_ID id, int visible_type)
{
    if(p_set_visible_object)
        p_set_visible_object(pid, id, visible_type);
}


void CALL set_visible_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type)
{
    if(p_set_visible_many)
        p_set_visible_many(pid, id, count, visible_type);
}


void CALL set_visible_many_objects(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int visible_type)
{
    if(p_set_visible_many_objects)
        p_set_visible_many_objects(pid, id, count, visible_type);
}


void CALL set_object_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children)
{
    if(p_set_object_color)
        p_set_object_color(pid, id, cl, with_all_children);
}


void CALL set_object_color_rgb(PLUGIN_ID pid, OBJECT_ID id, ColorRGB cl, bool with_all_children)
{
    if(p_set_object_color_rgb)
        p_set_object_color_rgb(pid, id, cl, with_all_children);
}


void CALL set_object_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children)
{
    if(p_set_object_default_color)
        p_set_object_default_color(pid, id, with_all_children);
}


bool CALL get_object_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl)
{
    if(p_get_object_color)
        return p_get_object_color(pid, id, cl);
    return false;
}

bool CALL get_object_deafult_color(PLUGIN_ID pid, OBJECT_ID id, Color *cl, int index)
{
	if(p_get_object_deafult_color)
		return p_get_object_deafult_color(pid, id, cl, index);
	return false;
}

void CALL add_color_to_transparency_list(PLUGIN_ID pid, OBJECT_ID id, Color *cl)
{
	 if(p_add_color_to_transparency_list)
        p_add_color_to_transparency_list(pid, id, cl);
}

unsigned char CALL get_transparency(PLUGIN_ID pid)
{
	if(p_get_transparency)
		return p_get_transparency(pid);
	return false;
}

void CALL set_object_edge_color(PLUGIN_ID pid, OBJECT_ID id, Color cl, bool with_all_children)
{
   if(p_set_object_edge_color)
        p_set_object_edge_color(pid, id, cl, with_all_children);
}


void CALL set_object_edge_default_color(PLUGIN_ID pid, OBJECT_ID id, bool with_all_children)
{
   if(p_set_object_edge_default_color)
        p_set_object_edge_default_color(pid, id, with_all_children);
}


void CALL set_object_visible(PLUGIN_ID pid, OBJECT_ID id, int visible_type, bool with_all_children)
{
    if(p_set_object_visible)
        p_set_object_visible(pid, id, visible_type, with_all_children);
}


void CALL set_object_active(PLUGIN_ID pid, OBJECT_ID id, bool active, bool with_all_children)
{
    if(p_set_object_active)
        p_set_object_active(pid, id, active, with_all_children);
}


void CALL select(PLUGIN_ID pid, OBJECT_ID id, bool b)
{
    if(p_select)
        p_select(pid, id, b);
}


void CALL unselect_openings(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_unselect_openings)
        p_unselect_openings(pid, id);
}


void CALL select_many(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count, int type)
{
    if(p_select_many)
        p_select_many(pid, id, count, type);
}


void CALL apply_select_rules(PLUGIN_ID pid)
{
    if(p_apply_select_rules)
        p_apply_select_rules(pid);
}


void CALL zoom_to(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_zoom_to)
        p_zoom_to(pid, id);
}


void CALL zoom_to_in_view(PLUGIN_ID pid, OBJECT_ID id, int width, int height)
{
    if(p_zoom_to_in_view)
        zoom_to_in_view(pid, id, width, height);
}


void CALL zoom_to_box(PLUGIN_ID pid, const RelativePos *a, const RelativePos *b)
{
    if(p_zoom_to_box)
        p_zoom_to_box(pid, a, b);
}


void CALL get_camera_pos(PLUGIN_ID pid, CameraPos *pos)
{
    if(p_get_camera_pos)
        p_get_camera_pos(pid, pos);
}


void CALL set_camera_pos(PLUGIN_ID pid, const CameraPos *pos)
{
    if(p_set_camera_pos)
        p_set_camera_pos(pid, pos);
}


void CALL get_direction_camera(PLUGIN_ID pid, DirectionCamera *cam)
{
    if(p_get_direction_camera)
        p_get_direction_camera(pid, cam);
}


void CALL set_direction_camera(PLUGIN_ID pid, const DirectionCamera *cam)
{
    if(p_set_direction_camera)
        p_set_direction_camera(pid, cam);
}


unsigned int CALL get_cutting_planes(PLUGIN_ID pid, CuttingPlane *buf, unsigned int count)
{
   if(p_get_cutting_planes)
      return p_get_cutting_planes(pid, buf, count);
   return 0;
}


void CALL set_cutting_planes(PLUGIN_ID pid, const CuttingPlane *buf, unsigned int count)
{
   if(p_set_cutting_planes)
      p_set_cutting_planes(pid, buf, count);
}


void CALL invalidate(PLUGIN_ID pid)
{
    if(p_invalidate)
        p_invalidate(pid);
}


float CALL get_draw_time(PLUGIN_ID pid)
{
    if(p_get_draw_time)
        return p_get_draw_time(pid);
    return 0;
}


unsigned int CALL get_all_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_all_objects)
        return p_get_all_objects(pid, buf, count);
    return 0;
}


unsigned int CALL get_selected(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_selected)
        return p_get_selected(pid, buf, count);
    return 0;
}


unsigned int CALL get_visible(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_visible)
        return p_get_visible(pid, buf, count);
    return 0;
}


unsigned int CALL get_active(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_active)
        return p_get_active(pid, buf, count);
    return 0;
}


OBJECT_ID CALL get_current_product(PLUGIN_ID pid)
{
    if(p_get_current_product)
        return p_get_current_product(pid);
    return 0;
}


void CALL get_object_state(PLUGIN_ID pid, const OBJECT_ID *id, ObjectState *state, unsigned int count)
{
   if(p_get_object_state)
      p_get_object_state(pid, id, state, count);
}


bool CALL is_visible(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_is_visible)
        return p_is_visible(pid, id);
    return false;
}


bool CALL is_transparent(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_is_transparent)
        return p_is_transparent(pid, id);
    return false;
}


bool CALL is_selected(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_is_selected)
        return p_is_selected(pid, id);
    return false;
}


bool CALL is_active(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_is_active)
        return p_is_active(pid, id);
    return false;
}


bool CALL has_representation(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_has_representation)
        return p_has_representation(pid, id);
    return false;
}


bool CALL get_bounds(PLUGIN_ID pid, OBJECT_ID id, Bounds *bounds)
{
    if(p_get_bounds)
        return p_get_bounds(pid, id, bounds);
    return false;
}


void CALL get_offset(PLUGIN_ID pid, OBJECT_ID id, Vector3d *offset)
{
   if(p_get_offset)
      p_get_offset(pid, id, offset);
}


void CALL set_offset(PLUGIN_ID pid, OBJECT_ID id, const Vector3d *offset)
{
   if(p_set_offset)
      p_set_offset(pid, id, offset);
}


unsigned int CALL get_childs(PLUGIN_ID pid, OBJECT_ID id, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_childs)
        return p_get_childs(pid, id, buf, count);
    return 0;
}


void CALL get_object_info(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo *info, unsigned int count)
{
    if(p_get_object_info)
        p_get_object_info(pid, id, info, count);
}


void CALL set_user_data(PLUGIN_ID pid, OBJECT_ID id, void *user_data, bool with_all_children)
{
    if(p_set_user_data)
        p_set_user_data(pid, id, user_data, with_all_children);
}


void* CALL get_user_data(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_user_data)
        return p_get_user_data(pid, id);
    return NULL;
}


OBJECT_ID CALL get_project(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_project)
        return p_get_project(pid, id);
    return 0;
}


OBJECT_ID CALL get_building(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_building)
        return p_get_building(pid, id);
    return 0;
}


OBJECT_ID CALL get_storey(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_storey)
        return p_get_storey(pid, id);
    return 0;
}


OBJECT_ID CALL get_parent(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_parent)
        return p_get_parent(pid, id);
    return 0;
}


void CALL get_object_info2(PLUGIN_ID pid, const OBJECT_ID *id, ObjectInfo2 *info2, unsigned int count)
{
    if(p_get_object_info2)
        p_get_object_info2(pid, id, info2, count);
}


unsigned int CALL get_object_materials(PLUGIN_ID pid, OBJECT_ID id, Material *buf, unsigned int count)
{
   if(p_get_object_materials)
      return p_get_object_materials(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_object_materials2(PLUGIN_ID pid, OBJECT_ID id, Material2 *buf, unsigned int count)
{
   if(p_get_object_materials2)
      return p_get_object_materials2(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_object_materials3(PLUGIN_ID pid, OBJECT_ID id, Material3 *buf, unsigned int count)
{
   if(p_get_object_materials3)
      return p_get_object_materials3(pid, id, buf, count);
   return 0;
}


bool CALL get_object_type_style(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle *result)
{
    if(p_get_object_type_style)
        return p_get_object_type_style(pid, id, result);
    return false;
}


bool CALL get_object_type_style2(PLUGIN_ID pid, OBJECT_ID id, ObjectTypeStyle2 *result)
{
    if(p_get_object_type_style2)
        return p_get_object_type_style2(pid, id, result);
    return false;
}


unsigned int CALL get_layers(PLUGIN_ID pid, Layer *buf, unsigned int count)
{
   if(p_get_layers)
      return p_get_layers(pid, buf, count);
   return 0;
}


unsigned int CALL get_layer_objects(PLUGIN_ID pid, LAYER_REF id, OBJECT_ID *buf, unsigned int count)
{
   if(p_get_layer_objects)
      return p_get_layer_objects(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_zones(PLUGIN_ID pid, Zone *buf, unsigned int count)
{
   if(p_get_zones)
      return p_get_zones(pid, buf, count);
   return 0;
}


unsigned int CALL get_zones2(PLUGIN_ID pid, Zone2 *buf, unsigned int count)
{
   if(p_get_zones2)
      return p_get_zones2(pid, buf, count);
   return 0;
}


unsigned int CALL get_zone_objects(PLUGIN_ID pid, ZONE_REF id, OBJECT_ID *buf, unsigned int count)
{
   if(p_get_zone_objects)
      return p_get_zone_objects(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_systems(PLUGIN_ID pid, System *buf, unsigned int count)
{
   if(p_get_systems)
      return p_get_systems(pid, buf, count);
   return 0;
}


unsigned int CALL get_system_objects(PLUGIN_ID pid, ZONE_REF id, OBJECT_ID *buf, unsigned int count)
{
   if(p_get_system_objects)
      return p_get_system_objects(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_groups(PLUGIN_ID pid, Group *buf, unsigned int count)
{
   if(p_get_groups)
      return p_get_groups(pid, buf, count);
   return 0;
}


unsigned int CALL get_group_objects(PLUGIN_ID pid, GROUP_REF id, OBJECT_ID *buf, unsigned int count)
{
   if(p_get_group_objects)
      return p_get_group_objects(pid, id, buf, count);
   return 0;
}


unsigned int CALL get_property_sets(PLUGIN_ID pid, OBJECT_ID id, PropertySet *buf, unsigned int count)
{
    if(p_get_property_sets)
        return p_get_property_sets(pid, id, buf, count);
    return 0;
}


unsigned int CALL get_properties(PLUGIN_ID pid, const PropertyGet *pg, Property *buf, unsigned int count)
{
    if(p_get_properties)
        return p_get_properties(pid, pg, buf, count);
    return 0;
}


unsigned int CALL get_properties2(PLUGIN_ID pid, const PropertyGet *pg, Property2 *buf, unsigned int count)
{
    if(p_get_properties2)
        return p_get_properties2(pid, pg, buf, count);
    return 0;
}


unsigned int CALL filter_properties(PLUGIN_ID pid, const PropertyFilter *pf, Property *buf, unsigned int count)
{
    if(p_filter_properties)
        return p_filter_properties(pid, pf, buf, count);
    return 0;
}


void CALL select_property(PLUGIN_ID pid, int set_nr, int property_nr, bool select_value)
{
    if(p_select_property)
        p_select_property(pid, set_nr, property_nr, select_value);
}


unsigned int CALL get_object_properties(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData *buf, unsigned int count)
{
    if(p_get_object_properties)
        return p_get_object_properties(pid, id, flag, buf, count);
    return 0;
}


unsigned int CALL get_object_properties2(PLUGIN_ID pid, OBJECT_ID id, int flag, PropertySetData2 *buf, unsigned int count)
{
    if(p_get_object_properties2)
        return p_get_object_properties2(pid, id, flag, buf, count);
    return 0;
}


unsigned int CALL get_material_properties(PLUGIN_ID pid, MATERIAL_REF ref, int flag, PropertySetData *buf, unsigned int count)
{
    if(p_get_material_properties)
        return p_get_material_properties(pid, ref, flag, buf, count);
    return 0;
}


unsigned int CALL get_type_style_properties(PLUGIN_ID pid, OBJECT_TYPE_STYLE_REF ref, int flag, PropertySetData *buf, unsigned int count)
{
    if(p_get_type_style_properties)
        return p_get_type_style_properties(pid, ref, flag, buf, count);
    return 0;
}


bool CALL delete_object_property_or_set(PLUGIN_ID pid, const PropertyDef *def)
{
   if(p_delete_object_property_or_set)
        return p_delete_object_property_or_set(pid, def);
    return false;
}


void CALL add_or_change_object_property(PLUGIN_ID pid, const PropertyDef *def, const PropertyData *data)
{
   if(p_add_or_change_object_property)
       p_add_or_change_object_property(pid, def, data);
}


void CALL on_property_change(PLUGIN_ID pid, callback_fun fun)
{
   if(p_on_property_change)
       p_on_property_change(pid, fun);
}


unsigned int CALL get_classifications(PLUGIN_ID pid, Classification *buf, unsigned int count)
{
   if(p_get_classifications)
      return p_get_classifications(pid, buf, count);
   return 0;
}


unsigned int CALL get_classification_references(PLUGIN_ID pid, wchar_t *classification_name, ClassificationReference *references, unsigned int count)
{
   if(p_get_classification_references)
      return p_get_classification_references(pid, classification_name, references, count);
   return 0;
}


unsigned int CALL get_object_classification_references(PLUGIN_ID pid, OBJECT_ID id, ClassificationReference *buf, unsigned int count)
{
   if(p_get_object_classification_references)
      return p_get_object_classification_references(pid, id, buf, count);
   return 0;
}


bool CALL get_classification_data(PLUGIN_ID pid, REF cl, Classification *classification)
{
   if(p_get_classification_data)
      return p_get_classification_data(pid, cl, classification);
   return false;
}


bool CALL get_classification_reference_data(PLUGIN_ID pid, REF cl_ref, ClassificationReference *classification_reference)
{
   if(p_get_classification_reference_data)
      return p_get_classification_reference_data(pid, cl_ref, classification_reference);
   return false;
}

int CALL get_projects_offsets(PLUGIN_ID pid, ProjectOffset *offsets, int count)
{
   if(p_get_projects_offsets)
      return p_get_projects_offsets(pid, offsets, count);
   return 0;
}

double CALL get_unit_factor(PLUGIN_ID pid)
{
    if(p_get_unit_factor)
        return p_get_unit_factor(pid);
    return 1;
}


bool CALL first_geometry(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_first_geometry)
        return p_first_geometry(pid, id);
    return false;
}


void CALL get_total_geometry_bounds(PLUGIN_ID pid, Bounds *bounds)
{
    if(p_get_total_geometry_bounds)
        p_get_total_geometry_bounds(pid, bounds);
}


unsigned int CALL get_geometry(PLUGIN_ID pid, Face *faces, unsigned int count)
{
    if(p_get_geometry)
        return p_get_geometry(pid, faces, count);
    return 0;
}


void CALL get_geometry_color(PLUGIN_ID pid, Color *face_color, Color *line_color)
{
    if(p_get_geometry_color)
        p_get_geometry_color(pid, face_color, line_color);
}


unsigned int CALL get_geometry_edges(PLUGIN_ID pid, Edge *edges, unsigned int count)
{
    if(p_get_geometry_edges)
        return p_get_geometry_edges(pid, edges, count);
    return 0;
}




bool CALL next_geometry(PLUGIN_ID pid)
{
    if(p_next_geometry)
        return p_next_geometry(pid);
    return false;
}


bool CALL is_online_licence(PLUGIN_ID pid)
{
    if(p_is_online_licence)
        return p_is_online_licence(pid);
    return false;
}


void CALL on_measure_change(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_measure_change)
        p_on_measure_change(pid, fun);
}


void CALL on_tab_sheet_placement(PLUGIN_ID pid, callback_tab_sheet_placement fun)
{
    if(p_on_tab_sheet_placement)
        p_on_tab_sheet_placement(pid, fun);
}


void CALL on_tab_sheet_change(PLUGIN_ID pid, callback_tab_sheet_change fun)
{
    if(p_on_tab_sheet_change)
        p_on_tab_sheet_change(pid, fun);
}

unsigned int CALL get_object_corners(PLUGIN_ID pid, OBJECT_ID obj_id,
                                     Vector3d *corners_vct, unsigned int corners_count)
{
    if(p_get_object_corners)
        return p_get_object_corners(pid, obj_id, corners_vct, corners_count);
    return 0;
}


unsigned int CALL get_object_edges(PLUGIN_ID pid, OBJECT_ID obj_id,
                                   Edge *edge_vct, unsigned int edge_count)
{
    if(p_get_object_edges)
        return p_get_object_edges(pid, obj_id, edge_vct, edge_count);
    return 0;
}


bool CALL get_object_area(PLUGIN_ID pid, OBJECT_ID obj_id, MeasuredArea *measure)
{
   if(p_get_object_area)
      return p_get_object_area(pid, obj_id, measure);
   return false;
}


void CALL get_measure(PLUGIN_ID pid, Measure *measure)
{
    if(p_get_measure)
        p_get_measure(pid, measure);
}

void CALL get_measure_v1(PLUGIN_ID pid, Measure_v1 *measure)
{
    if(p_get_measure_v1)
        p_get_measure_v1(pid, measure);
}

unsigned int CALL get_measure_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_get_measure_objects)
        return p_get_measure_objects(pid, buf, count);
    return 0;
}


unsigned int CALL get_measure_elements(PLUGIN_ID pid, double *buf, unsigned int count)
{
   if(p_get_measure_elements)
      return p_get_measure_elements(pid, buf, count);
   return 0;
}


void CALL clear_measure(PLUGIN_ID pid)
{
    if(p_clear_measure)
        p_clear_measure(pid);
}


void CALL set_measure_type(PLUGIN_ID pid, int type, int param)
{
    if(p_set_measure_type)
        p_set_measure_type(pid, type, param);
}


double CALL get_volume(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_volume)
        return p_get_volume(pid, id);
    return 0;
}


void CALL get_centroid(PLUGIN_ID pid, OBJECT_ID id, Vector3d *centroid, double *weight)
{
    if (p_get_centroid)
        return p_get_centroid(pid, id, centroid, weight);
}

double CALL get_total_area(PLUGIN_ID pid, OBJECT_ID id)
{
    if(p_get_total_area)
        return p_get_total_area(pid, id);
    return 0;
}


unsigned int CALL get_measure_state(PLUGIN_ID pid, void *buf, unsigned int buf_size)
{
    if(p_get_measure_state)
        return p_get_measure_state(pid, buf, buf_size);
    return 0;
}


void CALL set_measure_state(PLUGIN_ID pid, int flags, const void *buf, unsigned int buf_size)
{
    if(p_set_measure_state)
        p_set_measure_state(pid, flags, buf, buf_size);
}


unsigned int CALL get_measure_count(PLUGIN_ID pid)
{
    if(p_get_measure_count)
        return p_get_measure_count(pid);
    return 0;
}


unsigned int CALL get_detailed_measure_state(PLUGIN_ID pid, unsigned int index, void *buf,
                                             unsigned int buf_size, MeasureDetail *details)
{
    if(p_get_detailed_measure_state)
        return p_get_detailed_measure_state(pid, index, buf, buf_size, details);
    return 0;
}


void CALL set_detailed_measure_state(PLUGIN_ID pid, int flags, const void *state, unsigned int size)
{
    if(p_set_detailed_measure_state)
        p_set_detailed_measure_state(pid, flags, state, size);
}


void CALL change_measure_state_density(PLUGIN_ID pid, void *state, double density)
{
    if(p_change_measure_state_density)
        p_change_measure_state_density(pid, state, density);
}

unsigned int CALL construct_measure_state(PLUGIN_ID pid, ConstructMeasureState *construct, void *buf, unsigned int buf_size)
{
    if(p_construct_measure_state)
        return p_construct_measure_state(pid, construct, buf, buf_size);
    return 0;
}


void CALL get_plugin_status(PLUGIN_ID pid, const wchar_t *dll_name, PluginStatus *status)
{
    if(p_get_plugin_status)
        p_get_plugin_status(pid, dll_name, status);
}


bool CALL send_plugin_massage(PLUGIN_ID pid, const wchar_t *dll_name, PluginMessage *message)
{
    if(p_send_plugin_massage)
        return p_send_plugin_massage(pid, dll_name, message);
    return false;
}


void CALL on_plugin_message(PLUGIN_ID pid, callback_plugin_message fun)
{
    if(p_on_plugin_message)
        p_on_plugin_message(pid, fun);
}


const wchar_t* CALL get_loaded_ifc_path(PLUGIN_ID pid)
{
    if(p_get_loaded_ifc_path)
        return p_get_loaded_ifc_path(pid);
    return NULL;
}


const wchar_t* CALL get_project_path(PLUGIN_ID pid, OBJECT_ID project_id)
{
   if(p_get_project_path)
      return p_get_project_path(pid, project_id);
   return NULL;
}


bool CALL extract_file_from_bvf(PLUGIN_ID pid, OBJECT_ID project_id, const wchar_t *to_ifc_file_name)
{
   if(p_extract_file_from_bvf)
      return p_extract_file_from_bvf(pid, project_id, to_ifc_file_name);
   return false;
}


unsigned int CALL get_loaded_ifc_files_count(PLUGIN_ID pid)
{
    if(p_get_loaded_ifc_files_count)
        return p_get_loaded_ifc_files_count(pid);
    return 0;
}


const wchar_t* CALL get_loaded_ifc_filename(PLUGIN_ID pid, unsigned int file_index)
{
    if(p_get_loaded_ifc_filename)
        return p_get_loaded_ifc_filename(pid, file_index);
    return NULL;
}


bool CALL load_ifc(PLUGIN_ID pid, const wchar_t *path)
{
    if(p_load_ifc)
        return p_load_ifc(pid, path);
    return false;
}


bool CALL load_ifc_from_buffer(PLUGIN_ID pid, const wchar_t *file_name, char *buffer, unsigned int buf_size)
{
    if(p_load_ifc_from_buffer)
        return p_load_ifc_from_buffer(pid, file_name, buffer, buf_size);
    return false;
}


bool CALL add_ifc(PLUGIN_ID pid, const wchar_t *path)
{
    if(p_add_ifc)
        return p_add_ifc(pid, path);
    return false;
}


OBJECT_ID CALL calculate_object_id(PLUGIN_ID pid, const char *ifc_id)
{
    if(p_calculate_object_id)
        return p_calculate_object_id(pid, ifc_id);
    return 0;
}


void CALL on_model_load(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_model_load)
        p_on_model_load(pid, fun);
}


void CALL on_model_clear(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_model_clear != NULL)
        p_on_model_clear(pid, fun);
}


bool CALL file_was_added(PLUGIN_ID pid)
{
    if(p_file_was_added)
        return p_file_was_added(pid);
    return false;
}

bool CALL begin_read_bvf(PLUGIN_ID pid, const wchar_t *name)
{
   if(p_begin_read_bvf)
      return p_begin_read_bvf(pid, name);
   return false;
}

bool CALL begin_read_bvf_v2(PLUGIN_ID pid, const wchar_t *name)
{
   if(p_begin_read_bvf_v2)
      return p_begin_read_bvf_v2(pid, name);
   return false;
}// end__begin_read_bvf_v2()

unsigned long long CALL read_bvf_v2(PLUGIN_ID pid, void *buf, unsigned long long size)
{
   if(p_read_bvf_v2)
      return p_read_bvf_v2(pid, buf, size);
   return 0;
}// end__read_bvf_v2()

bool CALL save_bvf_sub_file_v2(PLUGIN_ID pid, wchar_t *save_as_file_name)
{
   if(p_save_bvf_sub_file_v2)
      return p_save_bvf_sub_file_v2(pid, save_as_file_name);
   return 0;
}// end__save_bvf_sub_file_v2()

wchar_t** CALL get_bvf_dir_file_list_v2(PLUGIN_ID pid)
{
   if(p_get_bvf_dir_file_list_v2)
      return p_get_bvf_dir_file_list_v2(pid);
   return NULL;
}// end__get_bvf_dir_file_list_v2()

unsigned long long CALL get_bvf_size_v2(PLUGIN_ID pid)
{
   if(p_get_bvf_size_v2)
      return p_get_bvf_size_v2(pid);
   return 0;
}// end__get_bvf_size_v2()


unsigned int CALL read_bvf(PLUGIN_ID pid, void *buf, unsigned int size)
{
   if(p_read_bvf)
      return p_read_bvf(pid, buf, size);
   return 0;
}


unsigned int CALL get_bvf_size(PLUGIN_ID pid)
{
   if(p_get_bvf_size)
      return p_get_bvf_size(pid);
   return 0;
}


void CALL on_save_bvf(PLUGIN_ID pid, callback_fun fun)
{
   if(p_on_save_bvf)
      p_on_save_bvf(pid, fun);
}


bool CALL begin_write_bvf(PLUGIN_ID pid, const wchar_t *name)
{
   if(p_begin_write_bvf)
      return p_begin_write_bvf(pid, name);
   return false;
}


bool CALL write_bvf(PLUGIN_ID pid, void *buf, unsigned int size)
{
   if(p_write_bvf)
      return p_write_bvf(pid, buf, size);
   return false;
}


bool CALL begin_write_bvf_v2(PLUGIN_ID pid, const wchar_t *name)
{
   if(p_begin_write_bvf_v2)
      return p_begin_write_bvf_v2(pid, name);
   return false;
}


bool CALL write_bvf_v2(PLUGIN_ID pid, void *buf, unsigned long long size)
{
   if(p_write_bvf_v2)
      return p_write_bvf_v2(pid, buf, size);
   return false;
}


bool CALL write_file_to_bvf_v2(PLUGIN_ID pid, wchar_t *external_file_name)
{
   if(p_write_file_to_bvf_v2)
      return p_write_file_to_bvf_v2(pid, external_file_name);
   return false;
}


void CALL can_clear_model(PLUGIN_ID pid, bool_callback_fun fun)
{
   if(p_can_clear_model)
      p_can_clear_model(pid, fun);
}


void CALL need_save_bvf(PLUGIN_ID pid, bool flag)
{
   if(p_need_save_bvf)
      p_need_save_bvf(pid, flag);
}


bool CALL save_file(PLUGIN_ID pid)
{
   if(p_save_file)
      return p_save_file(pid);
   return false;
}


void CALL need_save_changes(PLUGIN_ID pid, bool flag)
{
   if(p_need_save_changes)
      p_need_save_changes(pid, flag);
}


void CALL on_object_list_changed(PLUGIN_ID pid, callback_fun fun)
{
   if(p_on_object_list_changed)
      p_on_object_list_changed(pid, fun);
}


void CALL on_selection_change(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_selection_change)
        p_on_selection_change(pid, fun);
}


void CALL on_hover(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_hover)
        p_on_hover(pid, fun);
}


bool CALL get_clicked_pos(PLUGIN_ID pid, RelativePos *pos)
{
   if(p_get_clicked_pos)
      return p_get_clicked_pos(pid, pos);
   return false;
}


bool CALL get_clicked_normal(PLUGIN_ID pid, Vector3d *normal)
{
    if(p_get_clicked_normal)
        return p_get_clicked_normal(pid, normal);
    return false;
}


void CALL get_hovered_pos(PLUGIN_ID pid, RelativePos *pos)
{
    if(p_get_hovered_pos)
        p_get_hovered_pos(pid, pos);
}


void CALL get_dropped_pos(PLUGIN_ID pid, RelativePos *pos)
{
    if(p_get_dropped_pos)
        p_get_dropped_pos(pid, pos);
}


void CALL set_hover_objects(PLUGIN_ID pid, OBJECT_ID *buf, unsigned int count)
{
    if(p_set_hover_objects)
        p_set_hover_objects(pid, buf, count);
}


void CALL on_draw(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_draw)
        p_on_draw(pid, fun);
}


void CALL set_draw_object_id(PLUGIN_ID pid, unsigned int id)
{
    if(p_set_draw_object_id)
        p_set_draw_object_id(pid, id);
}


void CALL on_draw_object_click(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_draw_object_click)
        p_on_draw_object_click(pid, fun);
}


unsigned int CALL get_draw_object_id(PLUGIN_ID pid)
{
    if(p_get_draw_object_id)
        return p_get_draw_object_id(pid);
    return 0;
}


void CALL draw_point(PLUGIN_ID pid, const Point *point)
{
    if(p_draw_point)
        p_draw_point(pid, point);
}


void CALL draw_line(PLUGIN_ID pid, const Line *line)
{
    if(p_draw_line)
        p_draw_line(pid, line);
}


void CALL draw_sphere(PLUGIN_ID pid, const Sphere *sphere)
{
    if(p_draw_sphere)
        p_draw_sphere(pid, sphere);
}


SOLID_ID CALL create_intersection_solid(PLUGIN_ID pid, OBJECT_ID object_a, OBJECT_ID object_b)
{
    if(p_create_intersection_solid)
        return p_create_intersection_solid(pid, object_a, object_b);
    return 0i64;
}


void CALL delete_solid(PLUGIN_ID pid, SOLID_ID solid_id)
{
    if(p_delete_solid)
        p_delete_solid(pid, solid_id);
}


void CALL draw_solid(PLUGIN_ID pid, SOLID_ID solid_id, Color color)
{
    if(p_draw_solid)
        p_draw_solid(pid, solid_id, color);
}


double CALL get_solid_volume(PLUGIN_ID pid, SOLID_ID solid_id)
{
    if(p_get_solid_volume)
        return p_get_solid_volume(pid, solid_id);
    return 0.0;
}


double CALL get_solid_area(PLUGIN_ID pid, SOLID_ID solid_id)
{
    if(p_get_solid_area)
        return p_get_solid_area(pid, solid_id);
    return 0.0;
}


void CALL get_solid_center_point(PLUGIN_ID pid, SOLID_ID solid_id, Vertex *center)
{
    if(p_get_solid_center_point)
        p_get_solid_center_point(pid, solid_id, center);
}


void CALL zoom_to_solids(PLUGIN_ID pid, const SOLID_ID *id, unsigned int count)
{
    if(p_zoom_to_solids != NULL)
        p_zoom_to_solids(pid, id, count);
}


void CALL zoom_to_objects(PLUGIN_ID pid, const OBJECT_ID *id, unsigned int count)
{
    if(p_zoom_to_objects != NULL)
        p_zoom_to_objects(pid, id, count);
}


void CALL load_icon_image(PLUGIN_ID pid, const wchar_t *image_path)
{
    if(p_load_icon_image)
        p_load_icon_image(pid, image_path);
}


void CALL draw_icon(PLUGIN_ID pid, const Icon *icon)
{
    if(p_draw_icon)
        p_draw_icon(pid, icon);
}


void CALL draw_label(PLUGIN_ID pid, const Label *label)
{
    if(p_draw_label)
        p_draw_label(pid, label);
}


void CALL get_element_pos(PLUGIN_ID pid, RelativePos *pos)
{
    if(p_get_element_pos)
        p_get_element_pos(pid, pos);
}


void CALL set_drag_mode(PLUGIN_ID pid, bool set)
{
   if(p_set_drag_mode)
      p_set_drag_mode(pid, set);
}


const wchar_t* CALL get_language(PLUGIN_ID pid)
{
   if(p_get_language)
      return p_get_language(pid);
   return NULL;
}


OBJECT_ID CALL create_user_object(PLUGIN_ID pid, OBJECT_ID parent, const char* ifc_entity_name, const wchar_t* name, const wchar_t* desc)
{
   if(p_create_user_object)
      return p_create_user_object(pid, parent, ifc_entity_name, name, desc);
   return 0;
}


bool CALL delete_user_object(PLUGIN_ID pid, OBJECT_ID id)
{
   if(p_delete_user_object)
      return p_delete_user_object(pid, id);
   return false;
}

bool CALL check_triangle(PLUGIN_ID pid, const Face *face)
{
   if(p_check_triangle)
      return p_check_triangle(pid, face);
   return false;
}


bool CALL add_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id, const Face *faces, unsigned int count, const viewer::Color *cl)
{
   if(p_add_geometry_user_object)
      return p_add_geometry_user_object(pid, id, faces, count, cl);
   return false;
}


bool CALL delete_geometry_user_object(PLUGIN_ID pid, OBJECT_ID id)
{
   if(p_delete_geometry_user_object)
      return p_delete_geometry_user_object(pid, id);
   return false;
}

bool CALL set_geometry_edges_user_object(PLUGIN_ID pid, OBJECT_ID id, const Edge *edges, unsigned int count)
{
   if(p_set_geometry_edges_user_object)
      return p_set_geometry_edges_user_object(pid, id, edges, count);
   return false;
}


bool CALL save_file_as(PLUGIN_ID pid, const wchar_t *name, int save_type)
{
   if(p_save_file_as)
      return p_save_file_as(pid, name, save_type);
   return false;
}

bool CALL load_texts(PLUGIN_ID pid, const wchar_t *file_name)
{
    if(p_load_texts)
        return p_load_texts(pid, file_name);
    return false;
}


const wchar_t* CALL get_text(PLUGIN_ID pid, const char *txt_id)
{
    if(p_get_text)
        return p_get_text(pid, txt_id);
    return NULL;
}


const wchar_t* CALL get_text_global(PLUGIN_ID pid, const char *txt_id)
{
    if(p_get_text_global)
        return p_get_text_global(pid, txt_id);
    return NULL;
}


const wchar_t* CALL get_entity_type_name(PLUGIN_ID pid, const char *ifc_entity_name)
{
    if(p_get_entity_type_name)
        return p_get_entity_type_name(pid, ifc_entity_name);
    return NULL;
}


OBJECT_ID CALL get_object_below_mouse(PLUGIN_ID pid, int x, int y)
{
   if(p_get_object_below_mouse)
      return p_get_object_below_mouse(pid, x, y);
   return 0;
}


int CALL create_tab_sheet(PLUGIN_ID pid, const wchar_t *name, bool allow_close)
{
    if(p_create_tab_sheet)
        return p_create_tab_sheet(pid, name, allow_close);
    return 0;
}


void CALL activate_tab_sheet(PLUGIN_ID pid, int id)
{
    if(p_activate_tab_sheet)
        p_activate_tab_sheet(pid, id);
}


void CALL close_tab_sheet(PLUGIN_ID pid, int id)
{
    if(p_close_tab_sheet)
        p_close_tab_sheet(pid, id);
}


void CALL show_tab_sheet(PLUGIN_ID pid, int id, bool show)
{
    if(p_show_tab_sheet)
        p_show_tab_sheet(pid, id, show);
}


bool CALL is_active_tab_sheet(PLUGIN_ID pid, int id)
{
    if(p_is_active_tab_sheet)
        return p_is_active_tab_sheet(pid, id);
      return 0;
}


int CALL create_tab(PLUGIN_ID pid, const wchar_t *name)
{
    if(p_create_tab)
        return p_create_tab(pid, name);
    return 0;
}


int CALL create_group(PLUGIN_ID pid, int tab_id, const wchar_t *name)
{
    if(p_create_group)
        return p_create_group(pid, tab_id, name);
    return 0;
}


void CALL show_group(PLUGIN_ID pid, int group_id, bool visible)
{
    if(p_show_group)
        p_show_group(pid, group_id, visible);
}


int CALL create_button(PLUGIN_ID pid, int group_id, callback_fun fun)
{
    if(p_create_button)
        return p_create_button(pid, group_id, fun);
    return 0;
}


int CALL create_small_button(PLUGIN_ID pid, int group_id, callback_fun fun)
{
    if(p_create_small_button)
        return p_create_small_button(pid, group_id, fun);
    return 0;
}


int CALL create_checkbox(PLUGIN_ID pid, int group_id, callback_fun fun)
{
    if(p_create_checkbox)
        return p_create_checkbox(pid, group_id, fun);
    return 0;
}


int CALL create_radio_button(PLUGIN_ID pid, int group_id, callback_fun fun)
{
    if(p_create_radio_button)
        return p_create_radio_button(pid, group_id, fun);
    return 0;
}


int CALL create_dropdown_button(PLUGIN_ID pid, int group_id, callback_fun fun)
{
    if(p_create_dropdown_button)
        return p_create_dropdown_button(pid, group_id, fun);
    return 0;
}


int CALL create_sub_button(PLUGIN_ID pid, int group_id, bool small)
{
    if(p_create_sub_button)
        return p_create_sub_button(pid, group_id, small);
    return 0;
}


int CALL create_sub_button2(PLUGIN_ID pid, int group_id, bool small, callback_fun fun)
{
    if(p_create_sub_button2)
        return p_create_sub_button2(pid, group_id, small, fun);
    return 0;
}


void CALL add_button(PLUGIN_ID pid, int parent_button_id, int button_id)
{
    if(p_add_button)
        p_add_button(pid, parent_button_id, button_id);
}


void CALL add_separator(PLUGIN_ID pid, int parent_button_id, const wchar_t *caption)
{
    if(p_add_separator)
        p_add_separator(pid, parent_button_id, caption);
}


void CALL set_button_text(PLUGIN_ID pid, int button_id, const wchar_t *caption, const wchar_t *hint)
{
    if(p_set_button_text)
        p_set_button_text(pid, button_id, caption, hint);
}


void CALL set_button_image(PLUGIN_ID pid, int button_id, const wchar_t *large_img_path)
{
    if(p_set_button_image)
        p_set_button_image(pid, button_id, large_img_path);
}


void CALL set_button_small_image(PLUGIN_ID pid, int button_id, const wchar_t *small_img_path)
{
    if(p_set_button_small_image)
        p_set_button_small_image(pid, button_id, small_img_path);
}


void CALL set_button_shortcut(PLUGIN_ID pid, int button_id, const wchar_t *shortcut)
{
   if(p_set_button_shortcut)
      p_set_button_shortcut(pid, button_id, shortcut);
}


void CALL set_button_state(PLUGIN_ID pid, int button_id, bool enabled, bool down)
{
    if(p_set_button_state)
        p_set_button_state(pid, button_id, enabled, down);
}


void CALL set_button_down(PLUGIN_ID pid, int button_id, bool down)
{
    if(p_set_button_down)
        p_set_button_down(pid, button_id, down);
}


void CALL set_button_guid(PLUGIN_ID pid, int button_id, const char *str)
{
    if(p_set_button_guid)
        p_set_button_guid(pid, button_id, str);
}


void CALL enable_button(PLUGIN_ID pid, int button_id, bool enable)
{
    if(p_enable_button)
        p_enable_button(pid, button_id, enable);
}


void CALL show_button(PLUGIN_ID pid, int button_id, bool show)
{
    if(p_show_button)
        p_show_button(pid, button_id, show);
}


int CALL clicked_button(PLUGIN_ID pid)
{
    if(p_clicked_button)
        return p_clicked_button(pid);
    return 0;
}


void CALL begin_control_group(PLUGIN_ID pid)
{
    if(p_begin_control_group)
        p_begin_control_group(pid);
}


void CALL on_context_menu(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_context_menu)
        p_on_context_menu(pid, fun);
}


void CALL add_context_button(PLUGIN_ID pid, int button_id)
{
   if(p_add_context_button)
      p_add_context_button(pid, button_id);
}


void CALL clear_context_menu(PLUGIN_ID pid)
{
   if(p_clear_context_menu)
      p_clear_context_menu(pid);
}


int CALL create_gallery_button(PLUGIN_ID pid, int group_id, bool small, callback_fun fun)
{
    if(p_create_gallery_button)
        return p_create_gallery_button(pid, group_id, small, fun);
    return 0;
}


void CALL set_gallery_style(PLUGIN_ID pid, int gallery_id, int min_col_count, int style)
{
    if(p_set_gallery_style)
        p_set_gallery_style(pid, gallery_id, min_col_count, style);
}


int CALL create_gallery_category(PLUGIN_ID pid, int gallery_id)
{
    if(p_create_gallery_category)
        return p_create_gallery_category(pid, gallery_id);
    return 0;
}


void CALL set_gallery_category_text(PLUGIN_ID pid, int gallery_category_id, const wchar_t *caption)
{
    if(p_set_gallery_category_text)
        p_set_gallery_category_text(pid, gallery_category_id, caption);
}


void CALL set_gallery_category_style(PLUGIN_ID pid, int gallery_category_id, int display_texts, int texts_posistion)
{
    if(p_set_gallery_category_style)
        p_set_gallery_category_style(pid, gallery_category_id, display_texts, texts_posistion);
}


void CALL delete_gallery_category(PLUGIN_ID pid, int gallery_category_id)
{
    if(p_delete_gallery_category)
        p_delete_gallery_category(pid, gallery_category_id);
}


int CALL create_gallery_item(PLUGIN_ID pid, int gallery_category_id, callback_fun fun)
{
    if(p_create_gallery_item)
        return p_create_gallery_item(pid, gallery_category_id, fun);
    return 0;
}


void CALL set_gallery_item_text(PLUGIN_ID pid, int gallery_item_id, const wchar_t *caption, const wchar_t *descrption)
{
    if(p_set_gallery_item_text)
        p_set_gallery_item_text(pid, gallery_item_id, caption, descrption);
}


void CALL set_gallery_item_image(PLUGIN_ID pid, int gallery_item_id, const wchar_t *path)
{
    if(p_set_gallery_item_image)
        p_set_gallery_item_image(pid, gallery_item_id, path);
}


void CALL delete_gallery_item(PLUGIN_ID pid, int gallery_item_id)
{
    if(p_delete_gallery_item)
        p_delete_gallery_item(pid, gallery_item_id);
}


void CALL clear_gallery(PLUGIN_ID pid, int gallery_id)
{
    if(p_clear_gallery)
        p_clear_gallery(pid, gallery_id);
}


void CALL on_gallery_item_context_menu(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_gallery_item_context_menu)
        p_on_gallery_item_context_menu(pid, fun);
}


bool CALL is_center_view(PLUGIN_ID pid)
{
    if(p_is_center_view)
        return p_is_center_view(pid);
    return false;
}


int CALL get_active_tab(PLUGIN_ID pid)
{
    if(p_get_active_tab)
        return p_get_active_tab(pid);
    return 0;
}


void CALL on_tab_change(PLUGIN_ID pid, callback_fun fun)
{
    if(p_on_tab_change)
        p_on_tab_change(pid, fun);
}


ColorRGB CALL get_gui_color(PLUGIN_ID pid, int gui_color_id)
{
    if(p_get_gui_color)
        return p_get_gui_color(pid, gui_color_id);

    ColorRGB    c;
    c.cl = 0;
    return c;
}


int CALL get_gui_theme(PLUGIN_ID pid)
{
    if(p_get_gui_theme)
        return p_get_gui_theme(pid);
    return 0;
}


int CALL message_box(PLUGIN_ID pid, const wchar_t *caption, const wchar_t *message, int flags)
{
    if(p_message_box)
        return p_message_box(pid, caption, message, flags);
    return 0;
}


void CALL set_open_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory)
{
    if(p_set_open_dialog_params)
        p_set_open_dialog_params(pid, filter, directory);
}


bool CALL open_file_dialog(PLUGIN_ID pid, bool multiple_files)
{
    if(p_open_file_dialog)
        return p_open_file_dialog(pid, multiple_files);
    return false;
}


unsigned int CALL get_open_dialog_file_count(PLUGIN_ID pid)
{
    if(p_get_open_dialog_file_count)
        return p_get_open_dialog_file_count(pid);
    return 0;
}


const wchar_t* CALL get_open_dialog_file_nr(PLUGIN_ID pid, unsigned int nr)
{
    if(p_get_open_dialog_file_nr)
        return p_get_open_dialog_file_nr(pid, nr);
    return NULL;
}


void CALL set_save_dialog_params(PLUGIN_ID pid, const wchar_t *filter, const wchar_t *directory, const wchar_t *file_name)
{
    if(p_set_save_dialog_params)
        p_set_save_dialog_params(pid, filter, directory, file_name);
}


void CALL set_save_dialog_default_extension(PLUGIN_ID pid, const wchar_t *extension)
{
    if(p_set_save_dialog_default_extension)
        p_set_save_dialog_default_extension(pid, extension);
}


bool CALL save_dialog(PLUGIN_ID pid, bool select_directory_only)
{
    if(p_save_dialog)
        return p_save_dialog(pid, select_directory_only);
    return false;
}


const wchar_t* CALL get_save_dialog_name(PLUGIN_ID pid)
{
    if(p_get_save_dialog_name)
        return p_get_save_dialog_name(pid);
    return NULL;
}


void CALL show_progress_bar(PLUGIN_ID pid, bool show, int style, const wchar_t *title)
{
    if(p_show_progress_bar)
        p_show_progress_bar(pid, show, style, title);
}


bool CALL update_progress_bar(PLUGIN_ID pid, int percent, const wchar_t *message, int second_percent, const wchar_t *second_message)
{
    if(p_update_progress_bar)
        return p_update_progress_bar(pid, percent, message, second_percent, second_message);
    return false;
}


void CALL get_view_rect(PLUGIN_ID pid, RECT *rect)
{
    if(p_get_view_rect)
        p_get_view_rect(pid, rect);
}


void CALL show_ifc_structure_grid(PLUGIN_ID pid, bool force_show_properties)
{
    if(p_show_ifc_structure_grid)
        p_show_ifc_structure_grid(pid, force_show_properties);
}


void CALL set_ribbon_state(PLUGIN_ID pid, int state)
{
   if(p_set_ribbon_state)
        p_set_ribbon_state(pid, state);
}


void CALL set_grids_state(PLUGIN_ID pid, int state)
{
   if(p_set_grids_state)
        p_set_grids_state(pid, state);
}// end__set_grids_state()


bool CALL get_grids_state(PLUGIN_ID pid)
{
   if(p_get_grids_state)
      return p_get_grids_state(pid);
   return false;
}// end__get_grids_state()


bool CALL item_command(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *command)
{
   if(p_item_command)
      return p_item_command(pid, item_name, command);
   return false;
}


void CALL set_item_value(PLUGIN_ID pid, const wchar_t *item_name, double value)
{
   if(p_set_item_value)
      p_set_item_value(pid, item_name, value);
}


double CALL get_item_value(PLUGIN_ID pid, const wchar_t *item_name, const wchar_t *value_type)
{
   if(p_get_item_value)
      return p_get_item_value(pid, item_name, value_type);
   return 0.0;
}


bool CALL register_on_button_click(PLUGIN_ID pid, const wchar_t *item_name, callback_fun fun)
{
   if(p_register_on_button_click)
      return p_register_on_button_click(pid, item_name, fun);
   return false;
}


bool CALL is_touch_mode(PLUGIN_ID pid)
{
    if(p_is_touch_mode)
        return p_is_touch_mode(pid);
    return false;
}


unsigned int CALL get_view_state(PLUGIN_ID pid, int flags, void *state, unsigned int size)
{
   if(p_get_view_state)
      return p_get_view_state(pid, flags, state, size);
   return 0;
}


void CALL set_view_state(PLUGIN_ID pid, int flags, const void *state, unsigned int size)
{
    if(p_set_view_state)
        p_set_view_state(pid, flags, state, size);
}


bool CALL render_screenshot(PLUGIN_ID pid, unsigned int w, unsigned int h, unsigned char *buf)
{
    if(p_render_screenshot)
        return p_render_screenshot(pid, w, h, buf);
    return false;
}


void CALL set_screenshot_style(PLUGIN_ID pid, int style)
{
    if(p_set_screenshot_style)
        p_set_screenshot_style(pid, style);
}


void CALL get_2d_bounds(PLUGIN_ID pid, const OBJECT_ID *obj, Bounds *bounds, unsigned int count, int flags)
{
    if(p_get_2d_bounds)
        p_get_2d_bounds(pid, obj, bounds, count, flags);
}


void CALL project_to_2d(PLUGIN_ID pid, const RelativePos *pos, Vector3d *pos_2d, unsigned int count, int flags)
{
    if(p_project_to_2d)
        p_project_to_2d(pid, pos, pos_2d, count, flags);
}


void CALL recalc_cross_sections(PLUGIN_ID pid, int flags)
{
    if(p_recalc_cross_sections)
        p_recalc_cross_sections(pid, flags);
}


void CALL cross_sections_style(PLUGIN_ID pid, int color_type, ColorRGB color, bool bold)
{
   if(p_cross_sections_style)
      p_cross_sections_style(pid, color_type, color, bold);
}


void CALL close_application(PLUGIN_ID pid)
{
    if (p_close_application)
        p_close_application(pid);
}


unsigned int CALL register_undo_action(PLUGIN_ID pid, wchar_t *action_name)
{
   if(p_register_undo_action)
      return p_register_undo_action(pid, action_name);
   return 0;
}


 void* CALL debug_test(PLUGIN_ID pid, int nr)
 {
    if(p_debug_test)
        return p_debug_test(pid, nr);
    return NULL;
 }


}// namespace viewer


using namespace viewer;


// zaladuj funkcje z exe
void load_viewer_functions()
{
    static bool initialized;

    if(!initialized)
    {
        initialized = true;

        HMODULE hExe = GetModuleHandle(NULL);

        p_get_selected_id = (fun_get_selected_id*)GetProcAddress(hExe, "get_selected_id");
        p_get_all_objects_id = (fun_get_all_objects_id*)GetProcAddress(hExe, "get_all_objects_id");

        p_set_color = (fun_set_color*)GetProcAddress(hExe, "set_color");
        p_set_color_object = (fun_set_color_object*)GetProcAddress(hExe, "set_color_object");
        p_set_default_color = (fun_set_default_color*)GetProcAddress(hExe, "set_default_color");     
        p_use_selection_color = (fun_use_selection_color*)GetProcAddress(hExe, "use_selection_color");
        p_treat_openings_as_normal_objects = (fun_treat_openings_as_normal_objects*)GetProcAddress(hExe, "treat_openings_as_normal_objects");
        p_set_visible = (fun_set_visible*)GetProcAddress(hExe, "set_visible");
        p_set_visible_object = (fun_set_visible_object*)GetProcAddress(hExe, "set_visible_object");
        p_set_visible_many = (fun_set_visible_many*)GetProcAddress(hExe, "set_visible_many");
        p_set_visible_many_objects = (fun_set_visible_many_objects*)GetProcAddress(hExe, "set_visible_many_objects");

        p_set_object_color = (fun_set_object_color*)GetProcAddress(hExe, "set_object_color");
        p_set_object_color_rgb = (fun_set_object_color_rgb*)GetProcAddress(hExe, "set_object_color_rgb");
        p_set_object_default_color = (fun_set_object_default_color*)GetProcAddress(hExe, "set_object_default_color");
        p_get_object_color = (fun_get_object_color*)GetProcAddress(hExe, "get_object_color");
        p_get_object_deafult_color = (fun_get_object_deafult_color*)GetProcAddress(hExe, "get_object_deafult_color");
        p_add_color_to_transparency_list = (fun_add_color_to_transparency_list*)GetProcAddress(hExe, "add_color_to_transparency_list");
        p_get_transparency = (fun_get_transparency*)GetProcAddress(hExe, "get_transparency");
        p_set_object_edge_color = (fun_set_object_edge_color*)GetProcAddress(hExe, "set_object_edge_color");
        p_set_object_edge_default_color = (fun_set_object_edge_default_color*)GetProcAddress(hExe, "set_object_edge_default_color");
        p_set_object_visible = (fun_set_object_visible*)GetProcAddress(hExe, "set_object_visible");
        p_set_object_active = (fun_set_object_active*)GetProcAddress(hExe, "set_object_active");

        p_select = (fun_select*)GetProcAddress(hExe, "select");          
        p_unselect_openings = (fun_unselect_openings*)GetProcAddress(hExe, "unselect_openings");
        p_select_many = (fun_select_many*)GetProcAddress(hExe, "select_many");
        p_apply_select_rules = (fun_apply_select_rules*)GetProcAddress(hExe, "apply_select_rules");
        p_zoom_to = (fun_zoom_to*)GetProcAddress(hExe, "zoom_to");
        p_zoom_to_in_view = (fun_zoom_to_in_view*)GetProcAddress(hExe, "zoom_to_in_view");
        p_zoom_to_box = (fun_zoom_to_box*)GetProcAddress(hExe, "zoom_to_box");
        p_get_camera_pos = (fun_get_camera_pos*)GetProcAddress(hExe, "get_camera_pos");
        p_set_camera_pos = (fun_set_camera_pos*)GetProcAddress(hExe, "set_camera_pos");
        p_get_direction_camera = (fun_get_direction_camera*)GetProcAddress(hExe, "get_direction_camera");
        p_set_direction_camera = (fun_set_direction_camera*)GetProcAddress(hExe, "set_direction_camera");

        p_get_cutting_planes = (fun_get_cutting_planes*)GetProcAddress(hExe, "get_cutting_planes");
        p_set_cutting_planes = (fun_set_cutting_planes*)GetProcAddress(hExe, "set_cutting_planes");

        p_invalidate = (fun_invalidate*)GetProcAddress(hExe, "invalidate");
        p_get_draw_time = (fun_get_draw_time*)GetProcAddress(hExe, "get_draw_time");

        p_get_all_objects = (fun_get_all_objects*)GetProcAddress(hExe, "get_all_objects");
        p_get_selected = (fun_get_selected*)GetProcAddress(hExe, "get_selected");           
        p_get_visible = (fun_get_visible*)GetProcAddress(hExe, "get_visible");
        p_get_active = (fun_get_active*)GetProcAddress(hExe, "get_active");
        p_get_current_product = (fun_get_current_product*)GetProcAddress(hExe, "get_current_product");
        p_get_object_state = (fun_get_object_state*)GetProcAddress(hExe, "get_object_state");

        p_is_visible = (fun_is_visible*)GetProcAddress(hExe, "is_visible");
        p_is_transparent = (fun_is_transparent*)GetProcAddress(hExe, "is_transparent");
        p_is_selected = (fun_is_selected*)GetProcAddress(hExe, "is_selected");
        p_is_active = (fun_is_active*)GetProcAddress(hExe, "is_active");
        p_has_representation = (fun_has_representation*)GetProcAddress(hExe, "has_representation");
        p_get_bounds = (fun_get_bounds*)GetProcAddress(hExe, "get_bounds");
        p_get_offset = (fun_get_offset*)GetProcAddress(hExe, "get_offset");
        p_set_offset = (fun_set_offset*)GetProcAddress(hExe, "set_offset");

        p_get_childs = (fun_get_childs*)GetProcAddress(hExe, "get_childs");
        p_get_object_info = (fun_get_object_info*)GetProcAddress(hExe, "get_object_info");

        p_set_user_data = (fun_set_user_data*)GetProcAddress(hExe, "set_user_data");
        p_get_user_data = (fun_get_user_data*)GetProcAddress(hExe, "get_user_data");
        p_get_project = (fun_get_project*)GetProcAddress(hExe, "get_project");
        p_get_building = (fun_get_building*)GetProcAddress(hExe, "get_building");
        p_get_storey = (fun_get_storey*)GetProcAddress(hExe, "get_storey");
        p_get_parent = (fun_get_parent*)GetProcAddress(hExe, "get_parent");
        p_get_object_info2 = (fun_get_object_info2*)GetProcAddress(hExe, "get_object_info2");

        p_get_object_materials = (fun_get_object_materials*)GetProcAddress(hExe, "get_object_materials");
        p_get_object_materials2 = (fun_get_object_materials2*)GetProcAddress(hExe, "get_object_materials2");
        p_get_object_materials3 = (fun_get_object_materials3*)GetProcAddress(hExe, "get_object_materials3");
        p_get_object_type_style = (fun_get_object_type_style*)GetProcAddress(hExe, "get_object_type_style");
        p_get_object_type_style2 = (fun_get_object_type_style2*)GetProcAddress(hExe, "get_object_type_style2");

        p_get_layers = (fun_get_layers*)GetProcAddress(hExe, "get_layers");
        p_get_layer_objects = (fun_get_layer_objects*)GetProcAddress(hExe, "get_layer_objects");
        p_get_zones = (fun_get_zones*)GetProcAddress(hExe, "get_zones");
        p_get_zones2 = (fun_get_zones2*)GetProcAddress(hExe, "get_zones2");
        p_get_zone_objects = (fun_get_zone_objects*)GetProcAddress(hExe, "get_zone_objects");
        p_get_systems = (fun_get_systems*)GetProcAddress(hExe, "get_systems");
        p_get_system_objects = (fun_get_system_objects*)GetProcAddress(hExe, "get_system_objects");
        p_get_groups = (fun_get_groups*)GetProcAddress(hExe, "get_groups");
        p_get_group_objects = (fun_get_group_objects*)GetProcAddress(hExe, "get_group_objects");

        p_get_property_sets = (fun_get_property_sets*)GetProcAddress(hExe, "get_property_sets");
        p_get_properties = (fun_get_properties*)GetProcAddress(hExe, "get_properties");
        p_get_properties2 = (fun_get_properties2*)GetProcAddress(hExe, "get_properties2");
        p_filter_properties = (fun_filter_properties*)GetProcAddress(hExe, "filter_properties");
        p_select_property = (fun_select_property*)GetProcAddress(hExe, "select_property");

        p_get_object_properties = (fun_get_object_properties*)GetProcAddress(hExe, "get_object_properties");
        p_get_object_properties2 = (fun_get_object_properties2*)GetProcAddress(hExe, "get_object_properties2");
        p_get_material_properties = (fun_get_material_properties*)GetProcAddress(hExe, "get_material_properties");
        p_get_type_style_properties = (fun_get_type_style_properties*)GetProcAddress(hExe, "get_type_style_properties");

        p_delete_object_property_or_set = (fun_delete_object_property_or_set*)GetProcAddress(hExe, "delete_object_property_or_set");
        p_add_or_change_object_property = (fun_add_or_change_object_property*)GetProcAddress(hExe, "add_or_change_object_property");
        p_on_property_change = (fun_on_property_change*)GetProcAddress(hExe, "on_property_change");

        p_get_classifications = (fun_get_classifications*)GetProcAddress(hExe, "get_classifications");
        p_get_classification_references = (fun_get_classification_references*)GetProcAddress(hExe, "get_classification_references");
        p_get_object_classification_references = (fun_get_object_classification_references*)GetProcAddress(hExe, "get_object_classification_references");
        p_get_classification_data = (fun_get_classification_data*)GetProcAddress(hExe, "get_classification_data");
        p_get_classification_reference_data = (fun_get_classification_reference_data*)GetProcAddress(hExe, "get_classification_reference_data");
        p_get_projects_offsets = (fun_get_projects_offsets*)GetProcAddress(hExe, "get_projects_offsets");

        p_get_unit_factor = (fun_get_unit_factor*)GetProcAddress(hExe, "get_unit_factor");
        p_first_geometry = (fun_first_geometry*)GetProcAddress(hExe, "first_geometry");
        p_get_total_geometry_bounds = (fun_get_total_geometry_bounds*)GetProcAddress(hExe, "get_total_geometry_bounds");
        p_get_geometry = (fun_get_geometry*)GetProcAddress(hExe, "get_geometry");
        p_get_geometry_color = (fun_get_geometry_color*)GetProcAddress(hExe, "get_geometry_color");
        p_get_geometry_edges = (fun_get_geometry_edges*)GetProcAddress(hExe, "get_geometry_edges");
        p_next_geometry = (fun_next_geometry*)GetProcAddress(hExe, "next_geometry");
        p_is_online_licence = (fun_is_online_licence*)GetProcAddress(hExe, "is_online_licence");

        p_on_tab_sheet_placement = (fun_on_tab_sheet_placement*)GetProcAddress(hExe, "on_tab_sheet_placement");
        p_on_tab_sheet_change = (fun_on_tab_sheet_change*)GetProcAddress(hExe, "on_tab_sheet_change");
        
        p_on_measure_change = (fun_on_measure_change*)GetProcAddress(hExe, "on_measure_change");
        p_get_object_corners = (fun_get_object_corners*)GetProcAddress(hExe, "get_object_corners");
        p_get_object_edges = (fun_get_object_edges*)GetProcAddress(hExe, "get_object_edges");
        p_get_object_area = (fun_get_object_area*)GetProcAddress(hExe, "get_object_area");
        p_get_measure = (fun_get_measure*)GetProcAddress(hExe, "get_measure");
        p_get_measure_v1 = (fun_get_measure_v1*)GetProcAddress(hExe, "get_measure_v1");
        p_get_measure_objects = (fun_get_measure_objects*)GetProcAddress(hExe, "get_measure_objects");
        p_get_measure_elements = (fun_get_measure_elements*)GetProcAddress(hExe, "get_measure_elements");
        p_clear_measure = (fun_clear_measure*)GetProcAddress(hExe, "clear_measure");
        p_set_measure_type = (fun_set_measure_type*)GetProcAddress(hExe, "set_measure_type");
        p_get_volume = (fun_get_volume*)GetProcAddress(hExe, "get_volume");
        p_get_centroid = (fun_get_centroid*)GetProcAddress(hExe, "get_centroid");
        p_get_total_area = (fun_get_total_area*)GetProcAddress(hExe, "get_total_area");
        p_get_measure_state = (fun_get_measure_state*)GetProcAddress(hExe, "get_measure_state");
        p_set_measure_state = (fun_set_measure_state*)GetProcAddress(hExe, "set_measure_state");

        p_get_measure_count = (fun_get_measure_count*)GetProcAddress(hExe, "get_measure_count");
        p_get_detailed_measure_state = (fun_get_detailed_measure_state*)GetProcAddress(hExe, "get_detailed_measure_state");
        p_set_detailed_measure_state = (fun_set_detailed_measure_state*)GetProcAddress(hExe, "set_detailed_measure_state");
        p_construct_measure_state = (fun_construct_measure_state*)GetProcAddress(hExe, "construct_measure_state");
        p_change_measure_state_density = (fun_change_measure_state_density*)GetProcAddress(hExe, "change_measure_state_density");


        p_get_plugin_status = (fun_get_plugin_status*)GetProcAddress(hExe, "get_plugin_status");
        p_send_plugin_massage = (fun_send_plugin_massage*)GetProcAddress(hExe, "send_plugin_massage");
        p_on_plugin_message = (fun_on_plugin_message*)GetProcAddress(hExe, "on_plugin_message");

        p_get_loaded_ifc_path = (fun_get_loaded_ifc_path*)GetProcAddress(hExe, "get_loaded_ifc_path");
        p_get_project_path = (fun_get_project_path*)GetProcAddress(hExe, "get_project_path");
        p_extract_file_from_bvf= (fun_extract_file_from_bvf*)GetProcAddress(hExe, "extract_file_from_bvf");
        p_get_loaded_ifc_files_count = (fun_get_loaded_ifc_files_count*)GetProcAddress(hExe, "get_loaded_ifc_files_count");
        p_get_loaded_ifc_filename = (fun_get_loaded_ifc_filename*)GetProcAddress(hExe, "get_loaded_ifc_filename");
        p_load_ifc = (fun_load_ifc*)GetProcAddress(hExe, "load_ifc");
        p_load_ifc_from_buffer= (fun_load_ifc_from_buffer*)GetProcAddress(hExe, "load_ifc_from_buffer");
        p_add_ifc = (fun_add_ifc*)GetProcAddress(hExe, "add_ifc");
        p_calculate_object_id = (fun_calculate_object_id*)GetProcAddress(hExe, "calculate_object_id");

        p_on_model_load = (fun_on_model_load*)GetProcAddress(hExe, "on_model_load");
        p_on_model_clear = (fun_on_model_clear*)GetProcAddress(hExe, "on_model_clear");

        p_file_was_added = (fun_file_was_added*)GetProcAddress(hExe, "file_was_added");

        p_begin_read_bvf = (fun_begin_read_bvf*)GetProcAddress(hExe, "begin_read_bvf");
        p_read_bvf = (fun_read_bvf*)GetProcAddress(hExe, "read_bvf");
        p_get_bvf_size = (fun_get_bvf_size*)GetProcAddress(hExe, "get_bvf_size");
        p_on_save_bvf = (fun_on_save_bvf*)GetProcAddress(hExe, "on_save_bvf");
        p_begin_write_bvf = (fun_begin_write_bvf*)GetProcAddress(hExe, "begin_write_bvf");
        p_write_bvf = (fun_write_bvf*)GetProcAddress(hExe, "write_bvf");

        p_begin_read_bvf_v2 = (fun_begin_read_bvf_v2*)GetProcAddress(hExe, "begin_read_bvf_v2");
        p_read_bvf_v2 = (fun_read_bvf_v2*)GetProcAddress(hExe, "read_bvf_v2");
        p_save_bvf_sub_file_v2 = (fun_save_bvf_sub_file_v2*)GetProcAddress(hExe, "save_bvf_sub_file_v2");
        p_get_bvf_dir_file_list_v2 = (fun_get_bvf_dir_file_list_v2*)GetProcAddress(hExe, "get_bvf_dir_file_list_v2");
        p_get_bvf_size_v2 = (fun_get_bvf_size_v2*)GetProcAddress(hExe, "get_bvf_size_v2");

        p_begin_write_bvf_v2 = (fun_begin_write_bvf_v2*)GetProcAddress(hExe, "begin_write_bvf_v2");
        p_write_bvf_v2 = (fun_write_bvf_v2*)GetProcAddress(hExe, "write_bvf_v2");
        p_write_file_to_bvf_v2 = (fun_write_file_to_bvf_v2*)GetProcAddress(hExe, "write_file_to_bvf_v2");

        p_can_clear_model = (fun_can_clear_model*)GetProcAddress(hExe, "can_clear_model");
        p_need_save_bvf = (fun_need_save_bvf*)GetProcAddress(hExe, "need_save_bvf");
        p_save_file = (fun_save_file*)GetProcAddress(hExe, "save_file");
        p_need_save_changes = (fun_need_save_changes*)GetProcAddress(hExe, "need_save_changes");
        p_on_object_list_changed =(fun_on_object_list_changed*)GetProcAddress(hExe, "on_object_list_changed");

        p_on_selection_change = (fun_on_selection_change*)GetProcAddress(hExe, "on_selection_change");
        p_on_hover = (fun_on_hover*)GetProcAddress(hExe, "on_hover");
        p_get_clicked_pos = (fun_get_clicked_pos*)GetProcAddress(hExe, "get_clicked_pos");
        p_get_clicked_normal = (fun_get_clicked_normal*)GetProcAddress(hExe, "get_clicked_normal");
        p_get_hovered_pos = (fun_get_hovered_pos*)GetProcAddress(hExe, "get_hovered_pos");
        p_get_dropped_pos = (fun_get_dropped_pos*)GetProcAddress(hExe, "get_dropped_pos");
        p_set_hover_objects = (fun_set_hover_objects*)GetProcAddress(hExe, "set_hover_objects");
        p_on_draw = (fun_on_draw*)GetProcAddress(hExe, "on_draw");
        p_set_draw_object_id = (fun_set_draw_object_id*)GetProcAddress(hExe, "set_draw_object_id");
        p_on_draw_object_click = (fun_on_draw_object_click*)GetProcAddress(hExe, "on_draw_object_click");
        p_get_draw_object_id = (fun_get_draw_object_id*)GetProcAddress(hExe, "get_draw_object_id");
        p_draw_point = (fun_draw_point*)GetProcAddress(hExe, "draw_point");
        p_draw_line = (fun_draw_line*)GetProcAddress(hExe, "draw_line");
        p_draw_sphere = (fun_draw_sphere*)GetProcAddress(hExe, "draw_sphere");

        p_create_intersection_solid = (fun_create_intersection_solid*)GetProcAddress(hExe, "create_intersection_solid");
        p_delete_solid = (fun_delete_solid*)GetProcAddress(hExe, "delete_solid");
        p_draw_solid = (fun_draw_solid*)GetProcAddress(hExe, "draw_solid");
        p_get_solid_volume = (fun_get_solid_volume*)GetProcAddress(hExe, "get_solid_volume");
        p_get_solid_area = (fun_get_solid_area*)GetProcAddress(hExe, "get_solid_area");
        p_get_solid_center_point = (fun_get_solid_center_point*)GetProcAddress(hExe, "get_solid_center_point");
        p_zoom_to_solids = (fun_zoom_to_solids*)GetProcAddress(hExe, "zoom_to_solids");
        p_zoom_to_objects = (fun_zoom_to_objects*)GetProcAddress(hExe, "zoom_to_objects");

        p_load_icon_image = (fun_load_icon_image*)GetProcAddress(hExe, "load_icon_image");
        p_draw_icon = (fun_draw_icon*)GetProcAddress(hExe, "draw_icon");

        p_draw_label = (fun_draw_label*)GetProcAddress(hExe, "draw_label");
        p_get_element_pos = (fun_get_element_pos*)GetProcAddress(hExe, "get_element_pos");
        p_set_drag_mode = (fun_set_drag_mode*)GetProcAddress(hExe, "set_drag_mode");

        p_get_language = (fun_get_language*)GetProcAddress(hExe, "get_language");
        p_create_user_object = (fun_create_user_object*)GetProcAddress(hExe, "create_user_object");
        p_delete_user_object = (fun_delete_user_object*)GetProcAddress(hExe, "delete_user_object");
        p_check_triangle = (fun_check_triangle*)GetProcAddress(hExe, "check_triangle");
        p_add_geometry_user_object = (fun_add_geometry_user_object*)GetProcAddress(hExe, "add_geometry_user_object");
        p_delete_geometry_user_object = (fun_delete_geometry_user_object*)GetProcAddress(hExe, "delete_geometry_user_object");
        p_set_geometry_edges_user_object = (fun_set_geometry_edges_user_object*)GetProcAddress(hExe, "set_geometry_edges_user_object");
        p_save_file_as = (fun_save_file_as*)GetProcAddress(hExe, "save_file_as");
        p_load_texts = (fun_load_texts*)GetProcAddress(hExe, "load_texts");
        p_get_text = (fun_get_text*)GetProcAddress(hExe, "get_text");
        p_get_text_global = (fun_get_text_global*)GetProcAddress(hExe, "get_text_global");
        p_get_entity_type_name = (fun_get_entity_type_name*)GetProcAddress(hExe, "get_entity_type_name");

        p_get_object_below_mouse = (fun_get_object_below_mouse*)GetProcAddress(hExe, "get_object_below_mouse");

        p_create_tab_sheet = (fun_create_tab_sheet*)GetProcAddress(hExe, "create_tab_sheet");
        p_activate_tab_sheet = (fun_activate_tab_sheet*)GetProcAddress(hExe, "activate_tab_sheet");
        p_close_tab_sheet = (fun_close_tab_sheet*)GetProcAddress(hExe, "close_tab_sheet");
        p_show_tab_sheet = (fun_show_tab_sheet*)GetProcAddress(hExe, "show_tab_sheet");
        p_is_active_tab_sheet = (fun_is_active_tab_sheet*)GetProcAddress(hExe, "is_active_tab_sheet");

        p_create_tab = (fun_create_tab*)GetProcAddress(hExe, "create_tab");
        p_create_group = (fun_create_group*)GetProcAddress(hExe, "create_group");
        p_show_group = (fun_show_group*)GetProcAddress(hExe, "show_group");
        p_create_button = (fun_create_button*)GetProcAddress(hExe, "create_button");
        p_create_small_button = (fun_create_small_button*)GetProcAddress(hExe, "create_small_button");
        p_create_checkbox = (fun_create_checkbox*)GetProcAddress(hExe, "create_checkbox");
        p_create_radio_button = (fun_create_radio_button*)GetProcAddress(hExe, "create_radio_button");

        p_create_dropdown_button = (fun_create_dropdown_button*)GetProcAddress(hExe, "create_dropdown_button");
        p_create_sub_button = (fun_create_sub_button*)GetProcAddress(hExe, "create_sub_button");
        p_create_sub_button2 = (fun_create_sub_button2*)GetProcAddress(hExe, "create_sub_button2");
        p_add_button = (fun_add_button*)GetProcAddress(hExe, "add_button");
        p_add_separator = (fun_add_separator*)GetProcAddress(hExe, "add_separator");

        p_set_button_text = (fun_set_button_text*)GetProcAddress(hExe, "set_button_text");        
        p_set_button_image = (fun_set_button_image*)GetProcAddress(hExe, "set_button_image");
        p_set_button_small_image = (fun_set_button_small_image*)GetProcAddress(hExe, "set_button_small_image");
        p_set_button_shortcut = (fun_set_button_shortcut*)GetProcAddress(hExe, "set_button_shortcut");
        p_set_button_state = (fun_set_button_state*)GetProcAddress(hExe, "set_button_state");
        p_set_button_down = (fun_set_button_down*)GetProcAddress(hExe, "set_button_down");
        p_set_button_guid = (fun_set_button_guid*)GetProcAddress(hExe, "set_button_guid");
        p_enable_button = (fun_enable_button*)GetProcAddress(hExe, "enable_button");
        p_show_button = (fun_show_button*)GetProcAddress(hExe, "show_button");
        p_clicked_button = (fun_clicked_button*)GetProcAddress(hExe, "clicked_button");
        p_begin_control_group = (fun_begin_control_group*)GetProcAddress(hExe, "begin_control_group");

        p_on_context_menu = (fun_on_context_menu*)GetProcAddress(hExe, "on_context_menu");
        p_add_context_button = (fun_add_context_button*)GetProcAddress(hExe, "add_context_button");
        p_clear_context_menu = (fun_clear_context_menu*)GetProcAddress(hExe, "clear_context_menu");

        p_create_gallery_button = (fun_create_gallery_button*)GetProcAddress(hExe, "create_gallery_button");
        p_set_gallery_style = (fun_set_gallery_style*)GetProcAddress(hExe, "set_gallery_style");
        p_create_gallery_category = (fun_create_gallery_category*)GetProcAddress(hExe, "create_gallery_category");
        p_set_gallery_category_text = (fun_set_gallery_category_text*)GetProcAddress(hExe, "set_gallery_category_text");
        p_set_gallery_category_style = (fun_set_gallery_category_style*)GetProcAddress(hExe, "set_gallery_category_style");
        p_delete_gallery_category = (fun_delete_gallery_category*)GetProcAddress(hExe, "delete_gallery_category");
        p_create_gallery_item = (fun_create_gallery_item*)GetProcAddress(hExe, "create_gallery_item");
        p_set_gallery_item_text = (fun_set_gallery_item_text*)GetProcAddress(hExe, "set_gallery_item_text");
        p_set_gallery_item_image = (fun_set_gallery_item_image*)GetProcAddress(hExe, "set_gallery_item_image");
        p_delete_gallery_item = (fun_delete_gallery_item*)GetProcAddress(hExe, "delete_gallery_item");
        p_clear_gallery = (fun_clear_gallery*)GetProcAddress(hExe, "clear_gallery");
        p_on_gallery_item_context_menu = (fun_on_gallery_item_context_menu*)GetProcAddress(hExe, "on_gallery_item_context_menu");

        p_is_center_view = (fun_is_center_view*)GetProcAddress(hExe, "is_center_view");

        p_get_active_tab = (fun_get_active_tab*)GetProcAddress(hExe, "get_active_tab");
        p_on_tab_change = (fun_on_tab_change*)GetProcAddress(hExe, "on_tab_change");

        p_get_gui_color = (fun_get_gui_color*)GetProcAddress(hExe, "get_gui_color");
        p_get_gui_theme = (fun_get_gui_theme*)GetProcAddress(hExe, "get_gui_theme");

        p_message_box = (fun_message_box*)GetProcAddress(hExe, "message_box");
        p_set_open_dialog_params = (fun_set_open_dialog_params*)GetProcAddress(hExe, "set_open_dialog_params");
        p_open_file_dialog = (fun_open_file_dialog*)GetProcAddress(hExe, "open_file_dialog");
        p_get_open_dialog_file_count = (fun_get_open_dialog_file_count*)GetProcAddress(hExe, "get_open_dialog_file_count");
        p_get_open_dialog_file_nr = (fun_get_open_dialog_file_nr*)GetProcAddress(hExe, "get_open_dialog_file_nr");
        p_set_save_dialog_params = (fun_set_save_dialog_params*)GetProcAddress(hExe, "set_save_dialog_params");
        p_set_save_dialog_default_extension = (fun_set_save_dialog_default_extension*)GetProcAddress(hExe, "set_save_dialog_default_extension");
        p_save_dialog = (fun_save_dialog*)GetProcAddress(hExe, "save_dialog");
        p_get_save_dialog_name = (fun_get_save_dialog_name*)GetProcAddress(hExe, "get_save_dialog_name");
        p_show_progress_bar = (fun_show_progress_bar*)GetProcAddress(hExe, "show_progress_bar");
        p_update_progress_bar = (fun_update_progress_bar*)GetProcAddress(hExe, "update_progress_bar");

        p_get_view_rect = (fun_get_view_rect*)GetProcAddress(hExe, "get_view_rect");
        p_show_ifc_structure_grid = (fun_show_ifc_structure_grid*)GetProcAddress(hExe, "show_ifc_structure_grid");
        p_set_ribbon_state = (fun_set_ribbon_state*)GetProcAddress(hExe, "set_ribbon_state");
        p_set_grids_state  = (fun_set_grids_state*) GetProcAddress(hExe, "set_grids_state");
        p_get_grids_state  = (fun_get_grids_state*) GetProcAddress(hExe, "get_grids_state");
        p_item_command = (fun_item_command*)GetProcAddress(hExe, "item_command");
        p_set_item_value = (fun_set_item_value*)GetProcAddress(hExe, "set_item_value");
        p_get_item_value = (fun_get_item_value*)GetProcAddress(hExe, "get_item_value");
        p_register_on_button_click = (fun_register_on_button_click*)GetProcAddress(hExe, "register_on_button_click");

        p_is_touch_mode  = (fun_is_touch_mode*)GetProcAddress(hExe, "is_touch_mode");
        p_get_view_state = (fun_get_view_state*)GetProcAddress(hExe, "get_view_state");
        p_set_view_state = (fun_set_view_state*)GetProcAddress(hExe, "set_view_state");

        p_render_screenshot = (fun_render_screenshot*)GetProcAddress(hExe, "render_screenshot");
        p_set_screenshot_style = (fun_set_screenshot_style*)GetProcAddress(hExe, "set_screenshot_style");

        p_get_2d_bounds = (fun_get_2d_bounds*)GetProcAddress(hExe, "get_2d_bounds");
        p_project_to_2d = (fun_project_to_2d*)GetProcAddress(hExe, "project_to_2d");
        p_recalc_cross_sections = (fun_recalc_cross_sections*)GetProcAddress(hExe, "recalc_cross_sections");
        p_cross_sections_style = (fun_cross_sections_style*)GetProcAddress(hExe, "cross_sections_style");
        p_close_application = (fun_close_application*)GetProcAddress(hExe, "close_application");
        p_register_undo_action = (fun_register_undo_action*)GetProcAddress(hExe, "register_undo_action");

        p_debug_test = (fun_debug_test*)GetProcAddress(hExe, "debug_test");
    }
}// end__load_viewer_functions()

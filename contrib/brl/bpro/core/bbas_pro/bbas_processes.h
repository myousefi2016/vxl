#ifndef bbas_processes_h_
#define bbas_processes_h_

#include <bprb/bprb_macros.h>
#include <bprb/bprb_func_process.h>


DECLARE_FUNC_CONS(brad_display_sun_index_process);
DECLARE_FUNC_CONS(brad_sun_dir_bin_process);
DECLARE_FUNC_CONS(brad_save_sun_index_process);

DECLARE_FUNC_CONS(bbas_atmospheric_corr_process);
DECLARE_FUNC_CONS(bbas_estimate_irradiance_process);
DECLARE_FUNC_CONS(bbas_sun_angles_process);
DECLARE_FUNC_CONS(bbas_camera_angles_process);
DECLARE_FUNC_CONS(brad_create_eigenspace_process);
DECLARE_FUNC_CONS(brad_load_eigenspace_process);
DECLARE_FUNC_CONS(brad_save_eigenspace_process);
DECLARE_FUNC_CONS(brad_describe_eigenspace_process);
DECLARE_FUNC_CONS(brad_compute_eigenspace_process);

DECLARE_FUNC_CONS(brad_train_histograms_process);
DECLARE_FUNC_CONS_FIN(bbas_string_array_process);
DECLARE_FUNC_CONS(bbas_merge_string_array_process);

DECLARE_FUNC_CONS(bsta_load_joint_hist_3d_process);
DECLARE_FUNC_CONS(bsta_save_joint_hist_3d_process);
DECLARE_FUNC_CONS(bsta_joint_hist_3d_vrml_process);
DECLARE_FUNC_CONS(bsta_clone_joint_hist_3d_process);
DECLARE_FUNC_CONS(brad_update_joint_hist_3d_process);
DECLARE_FUNC_CONS(brad_classify_image_process);
DECLARE_FUNC_CONS(brad_classify_image_pixel_process);


DECLARE_FUNC_CONS(brad_estimate_phongs_model_process);
DECLARE_FUNC_CONS(brad_estimate_synoptic_function_1d_process);
DECLARE_FUNC_CONS(brad_estimate_empty_process);

DECLARE_FUNC_CONS(brad_estimate_shadow_model_process);
DECLARE_FUNC_CONS(brad_classify_image_pixel_process);
DECLARE_FUNC_CONS(brad_eigenimage_pixel_process);
DECLARE_FUNC_CONS(bbas_remove_from_db_process);

DECLARE_FUNC_CONS(brad_nitf_abs_radiometric_calibration_process);
DECLARE_FUNC_CONS(brad_estimate_radiance_values_process);

#endif // bbas_processes_h_

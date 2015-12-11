# CMake generated Testfile for 
# Source directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples
# Build directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/rpl/rgrl/examples
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(rgrl_registration1_test "./registration1" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.txt")
add_test(rgrl_registration2_test "./registration2" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0003.pgm.txt")
add_test(rgrl_registration3_test "./registration3" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002_low.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0003.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0003_low.pgm.txt")
add_test(rgrl_registration_simple_shapes_test "./registration_simple_shapes")
add_test(rgrl_registration_simple_shapes_outliers_test "./registration_simple_shapes_outliers")
add_test(rgrl_registration_blackbox "./registration_blackbox")
add_test(rgrl_registration_landmark_test "./registration_landmark" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0004.pgm.landmarks.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.landmarks.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/mask.png")
add_test(rgrl_registration_retina_no_view_test "./registration_retina_no_view" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.landmarks.invariant.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0004.pgm.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0004.pgm.landmarks.invariant.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/mask.png")
add_test(rgrl_registration_range_data_test "./registration_range_data" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/bun000.txt.out" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/bun045.txt.out")
add_test(rgrl_registration_blackbox_range_data_test "./registration_range_data_blackbox" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/dragonStandRight_0_normals.txt")
add_test(rgrl_estimate_normals_3d_test "./estimate_normals_3d" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/IMG0002.pgm.txt" "IMG0002.pgm.out.txt")
add_test(rgrl_pseudo_match_2d_test "./match_2d" "1" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube1_face_features.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube1.png" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube2.png" "-init" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/init_xform_flipped_y.txt" "-model" "affine")
add_test(rgrl_pseudo_match_2d_mult_test "./match_2d_multi" "1" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube1_face_features.txt" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube1.png" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/sigcube2.png" "-init" "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rgrl/examples/init_xform_flipped_y.txt" "-model" "affine")

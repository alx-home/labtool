# This is mul/fhs/tools/CMakeLists.txt

LINK_LIBRARIES( fhs mbl vimt_algo vimt vil_algo vil vnl vgl vul )

ADD_EXECUTABLE( find_matches find_matches.cxx )
ADD_EXECUTABLE( mr_find_matches mr_find_matches.cxx )
ADD_EXECUTABLE( fhs_match_tree_model fhs_match_tree_model.cxx )

file(REMOVE_RECURSE
  "build/libDSALabs-2024.pdb"
  "build/libDSALabs-2024.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/DSALabs-2024.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

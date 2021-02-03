# Building with CMake

    cmake -S coresoftware -B coresoftware-build \
        -DBOOST_ROOT=$OPT_SPHENIX/boost-1.70.0 \
        -DGSL_ROOT_DIR=$OPT_SPHENIX/gsl-2.6/ \
        -DCMAKE_BUILD_TYPE=RelWithDebInfo

    cmake --build coresoftware-build -j $(nproc)
    cmake --install coresoftware-build --prefix coresoftware-install

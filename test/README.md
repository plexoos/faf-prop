`tdiff` is a small utility program that can be used to verify that the data
saved in the "DST#G4TruthInfo" branch has not changed with respect to some
reference as, for example, one would expect after a code refactoring.

After cloning `coresoftware` build and run `tdiff` as:

    cmake -S coresoftware/test/ -B build-test
    cmake --build build-test
    ./build-test/tdiff path/to/file1.root path/to/file2.root

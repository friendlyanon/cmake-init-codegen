# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(codegenTests LANGUAGES CXX)

add_executable(codegen_test source/codegen_test.cpp)
target_link_libraries(codegen_test PRIVATE codegen_lib)
target_compile_features(codegen_test PRIVATE cxx_std_17)

add_test(NAME codegen_test COMMAND codegen_test)

add_folders(Test)

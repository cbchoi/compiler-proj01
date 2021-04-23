project(mycom)

set(ROOT ..)
set(SRC_DIR ./src)

set(SOURCE ${SRC_DIR}/mycom.cpp 
${SRC_DIR}/scanner.cpp 
${SRC_DIR}/utils.cpp 
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin)

add_executable(tmc.out ${SOURCE})

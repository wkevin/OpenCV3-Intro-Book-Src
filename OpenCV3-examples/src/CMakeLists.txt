cmake_minimum_required(VERSION 2.8)
project( main )

set(OpenCV_ROOT "/home/kevin/workspace/opencv/install/u4u")
set(OpenCV_INCLUDE_DIRS "${OpenCV_ROOT}/include")
set(OpenCV_LINK_DIRS "${OpenCV_ROOT}/lib")
#set(OpenCV_LIBS  "opencv_world")
set(OpenCV_LIBS  "opencv_calib3d" "opencv_core" "opencv_dnn" "opencv_features2d" "opencv_flann" "opencv_highgui" "opencv_imgcodecs" "opencv_imgproc" "opencv_ml" "opencv_objdetect" "opencv_photo" "opencv_shape" "opencv_stitching" "opencv_superres" "opencv_video" "opencv_videoio" "opencv_videostab")

set (EXTRA_LIBS ${EXTRA_LIBS} ${OpenCV_LIBS})

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Find all source files in current directory
aux_source_directory (../ SRC_LIST)

# get source files holding main() function
execute_process (
#  COMMAND echo ${SRC_LIST}
  COMMAND find . -path ./build -prune -o -name "*.cpp"
  COMMAND xargs egrep " main[ \t]*(.*)[ \t]*$" -l
  WORKING_DIRECTORY ..     # NOTICE: Assumed build directory is ${SOURCE_DIR}/build, so You may change the value of WORKING_DIRECTORY to suit your needs
  OUTPUT_VARIABLE TARGET_LIST
  )
message (====TARGET_LIST==== "\n" ${TARGET_LIST} "===================")
string (REGEX REPLACE "\n$" "" TARGET_LIST ${TARGET_LIST})

# count number of targets
execute_process (
  COMMAND echo "TARGET_LIST: " ${TARGET_LIST}
  COMMAND wc -l
  OUTPUT_VARIABLE TARGET_NUM
  )
message (====TARGET_NUM==== "\n" ${TARGET_NUM} "===================")

# convert string from "./$1\n./$2\n..." to "$1 $2 ..."
string (REGEX REPLACE "[.]/" "" TARGET_LIST ${TARGET_LIST})
string (REGEX REPLACE "\n" " " TARGET_LIST ${TARGET_LIST})
#message (====TARGET_LIST==== "\n" ${TARGET_LIST} "\n===================")

#enable_testing ()
foreach ( i RANGE 1 ${TARGET_NUM})
  execute_process (
    COMMAND echo "${TARGET_LIST}"
    COMMAND cut -d " " -f ${i}
    OUTPUT_VARIABLE SRC
  )
  string (REGEX REPLACE "\n" "" SRC ${SRC})
  string (REGEX REPLACE "[.]cpp$" ".bin" ELF ${SRC})
  
  string (REGEX REPLACE "[^/]*.bin$" "" ELF_PATH ${ELF})
  string (REGEX MATCH "[^/]*.bin$" ELF_FILE ${ELF})

  # message (">>>> Start Build ")
  # message ("SRC:" ${SRC})
  # message ("ELF:" ${ELF})
  # message ("ELF_PATH:" ${ELF_PATH})
  # message ("ELF_FILE:" ${ELF_FILE})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${ELF_PATH})
  
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  link_directories( ${OpenCV_LINK_DIRS})
  add_executable (${ELF_FILE} ${SRC})
  target_link_libraries (${ELF_FILE} ${EXTRA_LIBS})
#  add_test (${ELF}_Runs ${ELF})
endforeach (i)

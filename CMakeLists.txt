########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 3.0.0 ) 

project( Taurus )

set( CMAKE_DEBUG_POSTFIX "d" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/package )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_extras" )

set( TAURUS_MAJOR_VERSION 0 )
set( TAURUS_MINOR_VERSION 1 )
set( TAURUS_REVISION_VERSION 0 )
set( TAURUS_FULL_VERSION ${TAURUS_MAJOR_VERSION}.${TAURUS_MINOR_VERSION}.${TAURUS_REVISION_VERSION} )
set( TAURUS_CODE_NAME Taurus )

#########################################################

add_subdirectory( src/ )

function(configure_target NAME INCLUDE_DIR HEADER_LIST LINK_LIBS)
    ## check if already exists
    set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE           CXX)
    set_target_properties(${NAME} PROPERTIES CXX_EXTENSIONS            OFF)
   #set_target_properties(${GAME} PROPERTIES POSITION_INDEPENDENT_CODE FALSE)

    target_include_directories(${NAME} PUBLIC ${INCLUDE_DIR})
    target_compile_features(${NAME} PUBLIC cxx_std_20)
    source_group(TREE "${INCLUDE_DIR}" PREFIX "Header Files" FILES ${HEADER_LIST})

    ## logging levels for target ##
    target_compile_definitions(
            ${NAME} PRIVATE
            "$<$<CONFIG:Debug>:LOGGING_LEVEL_DEBUG>"
            "$<$<CONFIG:Release>:LOGGING_LEVEL_ERROR>")

    ## enable compiler warnings and debug flags ##
    set_target_build_flags(${NAME})

    foreach(LIBRARY ${LINK_LIBS})
        add_dependencies(${NAME} ${LIBRARY})
        target_link_libraries(${NAME} PRIVATE ${LIBRARY})
    endforeach()

    ## hide console unless debug build ##
    if (CXX_COMPILER_ID:GNU AND CMAKE_BUILD_TYPE MATCHES "[Rr]elease" AND WIN32)
        target_compile_options(${NAME} PRIVATE -mwindows)
    endif()

    ## enable static linking against gcc build
    if (WIN32 AND NOT BUILD_SHARED_LIBS AND NOT MSVC)
        target_link_libraries(${NAME} PRIVATE -static)
    endif()

    ## fix issue with arch enabling gcc pie by default
    ## https://stackoverflow.com/questions/43367427/32-bit-absolute-addresses-no-longer-allowed-in-x86-64-linux
    if(CMAKE_COMPILER_IS_GNUCC)
        target_link_libraries(${NAME} PRIVATE -no-pie pthread)
    endif()

endfunction()
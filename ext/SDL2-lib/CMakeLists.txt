set(SDL_STATIC ON)

# Define DX SDK on Windows 10
if (WIN32)
    # Set DXSDK_DIR if not already set
    if(NOT DEFINED ENV{DXSDK_DIR})
        set(ENV{DXSDK_DIR} "C:/Program Files (x86)/Windows Kits/10")
    endif()
endif (WIN32)

add_subdirectory(SDL-2-2.30.5)
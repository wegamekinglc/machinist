file(GLOB_RECURSE MACHINIST_FILES "*.h" "*.hpp" "*.cpp")
list(FILTER MACHINIST_FILES EXCLUDE REGEX ".*Storable.cpp$")
list(FILTER MACHINIST_FILES EXCLUDE REGEX ".*Pattern.cpp$")

add_library(maclib STATIC ${MACHINIST_FILES})

install(DIRECTORY . DESTINATION include/machinist
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

install(TARGETS maclib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )
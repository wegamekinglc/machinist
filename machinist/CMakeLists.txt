file(GLOB_RECURSE MACHINIST_FILES "*.hpp" "*.cpp")
add_executable(machinist ${MACHINIST_FILES})

target_link_libraries(machinist maclib)

install(TARGETS machinist
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )
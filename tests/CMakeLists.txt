add_executable(linkedlist_test linkedlist_test.cpp)
set_target_properties(linkedlist_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
target_include_directories(linkedlist_test PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(linkedlist_test ${Boost_LIBRARIES} linkedlist)

add_test(NAME "Linked list tests" COMMAND linkedlist_test)

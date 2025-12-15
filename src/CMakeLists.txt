# If you have a program that's just a .c file and it has a main method, define
# an executable. If it has both a .c and .h file, make it a library. Also, link
# libraries appropriately here. Targets should be added in dependency order - if
# executable bar needs library foo, then you should do
#   add_library(foo foo.c foo.h)
#   add_executable(bar bar.c)
#   target_link_libraries(bar PRIVATE foo)
# or similar. The PRIVATE/INTERFACE/PUBLIC keyword will depend on whether the
# library is used only in function bodies (PRIVATE), only in function
# signatures/types (INTERFACE), or both (PUBLIC).
# Libraries for .c/.h pairs
# Libraries
add_library(deck deck.c deck.h)
add_library(game_logic game_logic.c game_logic.h)
add_library(bot_decision bot_decision.c bot_decision.h)
add_library(terminal_ui terminal_ui.c terminal_ui.h)

# Executable
add_executable(main main.c)

# Link libraries in dependency order
target_link_libraries(main PRIVATE game_logic deck bot_decision terminal_ui ncurses)



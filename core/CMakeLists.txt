add_library(engine STATIC
    src/channel.cpp
    src/dsp.c
    src/filters.cpp
    src/fixed_point_math.c
    src/modulator.cpp
    src/receiver.cpp
    src/utils.cpp
)
target_include_directories(engine PUBLIC include)
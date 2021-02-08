cmake_minimum_required(VERSION 3.15)
project(grawing_way)

set(CMAKE_CXX_STANDARD 17)


add_executable(grawing_way
        Character.hpp
        Character.cpp
        Interfaces/IAttackThrow.hpp
        Skill/Skill.hpp
        Skill/Skill.cpp
        CharacterType/Ranger.hpp
        CharacterType/Ranger.cpp



        )


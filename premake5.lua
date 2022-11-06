-- premake5.lua
workspace "CircComp"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "CircComp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "CircComp"


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ocean)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/atmo)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/forest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/terrain)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/graph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/edit)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/river)

include_directories(${CMAKE_SOURCE_DIR}/tiff-4.0.8/libtiff)
include_directories(${CMAKE_BINARY_DIR}/tiff-4.0.8)
include_directories(${CMAKE_SOURCE_DIR}/AntTweakBar/include)

file(GLOB math "core/proland/math/*.h" 
			   "core/proland/math/*.cpp")
file(GLOB particles "core/proland/particles/*.h"
					 "core/proland/particles/*.cpp"
					"core/proland/particles/screen/*.h"
					 "core/proland/particles/screen/*.cpp"
					 "core/proland/particles/terrain/*.h"
					 "core/proland/particles/terrain/*.cpp"
					)
file(GLOB producer "core/proland/producer/*.h" 
				   "core/proland/producer/*.cpp")
file(GLOB terrain "core/proland/producer/*.h" 
				  "core/proland/terrain/*.cpp")
file(GLOB ui "core/proland/ui/*.h" 
			 "core/proland/ui/*.cpp"
			 "core/proland/ui/twbar/*.h" 
			 "core/proland/ui/twbar/*.cpp"
			 )
file(GLOB util "core/proland/util/*.h" "core/proland/util/*.cpp")

file(GLOB ocean "ocean/proland/*.h" 
				"ocean/proland/*.cpp" 
				"ocean/proland/ocean/*.h"
				"ocean/proland/ocean/*.cpp")

file(GLOB atom "atmo/proland/preprocess/atmo/*.h" 
			   "atmo/proland/preprocess/atmo/*.cpp"
			   "atmo/proland/preprocess/atmo/*.glsl"
			   )

file(GLOB forest "forest/proland/preprocess/trees/*.h" 
			   "forest/proland/preprocess/trees/*.cpp"
			   "forest/proland/preprocess/trees/*.glsl"
			   "forest/proland/preprocess/trees/*.xml"
			   "forest/proland/preprocess/trees/*.glhl"
			   "forest/proland/preprocess/trees/*.mesh"
			   "forest/proland/plants/*.h"
			   "forest/proland/plants/*.cpp"
			   "forest/proland/*.h"
			   "forest/proland/*.cpp"
			   )

file(GLOB graph "graph/proland/*.h" 
			    "graph/proland/*.cpp"
				"graph/proland/ortho/*.h" 
				"graph/proland/ortho/*.cpp"
				"graph/proland/graph/*.h" 
				"graph/proland/graph/*.cpp"
				"graph/proland/graph/producer/*.h" 
				"graph/proland/graph/producer/*.cpp"
				"graph/proland/dem/*.h" 
				"graph/proland/dem/*.cpp"
			   )

file(GLOB pterrain
	"terrain/proland/*.h" 
	"terrain/proland/*.cpp"

	"terrain/proland/dem/*.h" 
	"terrain/proland/dem/*.cpp"

	"terrain/proland/ortho/*.h" 
	"terrain/proland/ortho/*.cpp"


	"terrain/proland/preprocess/terrain/*.h" 
	"terrain/proland/preprocess/terrain/*.cpp"

)

file(GLOB edit
	"edit/proland/*.h" 
	"edit/proland/*.cpp"
	"edit/proland/edit/*.h"
	"edit/proland/edit/*.cpp"
	"edit/proland/ui/twbar/*.h"
	"edit/proland/ui/twbar/*.cpp"
)

file(GLOB river
	"river/proland/*.h" 
	"river/proland/*.cpp"

	"river/proland/ui/twbar/*.h" 
	"river/proland/ui/twbar/*.cpp"

	"river/proland/rivers/*.h" 
	"river/proland/rivers/*.cpp"

	"river/proland/rivers/graph/*.h" 
	"river/proland/rivers/graph/*.cpp"
)



source_group(math
	FILES
	${math}
)
source_group(particles
	FILES
	${particles}
)
source_group(producer
	FILES
	${producer}
)

source_group(terrain
	FILES
	${terrain}
)

source_group(ui
	FILES
	${ui}
)

source_group(util
	FILES
	${util}
)

add_definitions(-DORK_API=)
add_definitions(-DPROLAND_API=)
add_definitions(-DTIXML_USE_STL)
add_library(proland_core STATIC ${math} ${particles}  ${producer} ${terrain} ${ui} ${util})
set_property(TARGET  proland_core PROPERTY FOLDER "proland")


add_library(proland_ocean STATIC ${ocean})
set_property(TARGET  proland_ocean PROPERTY FOLDER "proland")


add_library(proland_atom STATIC ${atom})
set_property(TARGET  proland_atom PROPERTY FOLDER "proland")

add_library(proland_forest STATIC ${forest})
set_property(TARGET  proland_forest PROPERTY FOLDER "proland")

add_library(proland_terrain STATIC ${pterrain})
set_property(TARGET  proland_terrain PROPERTY FOLDER "proland")


add_library(proland_graph STATIC ${graph})
set_property(TARGET  proland_graph PROPERTY FOLDER "proland")

add_library(proland_edit STATIC ${edit})
set_property(TARGET  proland_edit PROPERTY FOLDER "proland")

add_library(proland_river STATIC ${river})
set_property(TARGET  proland_river PROPERTY FOLDER "proland")




add_dependencies(proland_core ork anttweakbar)
target_link_libraries(proland_core ork glu32 anttweakbar)

add_dependencies(proland_atom ork)
target_link_libraries(proland_atom ork)

add_dependencies(proland_terrain ork proland_core libtiff )
target_link_libraries(proland_terrain ork proland_core libtiff)

add_dependencies(proland_ocean ork proland_core  )
target_link_libraries(proland_ocean ork proland_core)

add_dependencies(proland_forest ork proland_core libtiff )
target_link_libraries(proland_forest ork proland_core libtiff)

add_dependencies(proland_graph ork proland_core proland_terrain )
target_link_libraries(proland_graph ork proland_core proland_terrain)

add_dependencies(proland_edit ork proland_core  proland_terrain proland_graph anttweakbar )
target_link_libraries(proland_edit ork proland_core proland_terrain proland_graph anttweakbar)


add_dependencies(proland_river ork proland_core  proland_graph anttweakbar)
target_link_libraries(proland_river ork proland_core proland_graph anttweakbar)
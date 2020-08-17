set(core
    "include/core/core.h"
    "include/core/point2.h"
    "include/core/rect.h"
    "include/core/vector2.h"
    "include/core/unsafe_vector.h"
	"include/core/vec.h" 
    "include/core/mat.h"
)
source_group("core" FILES ${core})

set(core__defines
    "include/core/defines/basic_defines.h"
    "include/core/defines/defines.h"
    "include/core/defines/struct_defines.h"
)
source_group("core\\defines" FILES ${core__defines})

set(core__ecs
    "include/core/ecs/ecs.h"
    "include/core/ecs/entity.h"
)
source_group("core\\ecs" FILES ${core__ecs})

set(core__ecs__components
    "include/core/ecs/components/componentmanager.h"
)
source_group("core\\ecs\\components" FILES ${core__ecs__components})

set(core__ecs__system
    "include/core/ecs/system/system.h"
)
source_group("core\\ecs\\system" FILES ${core__ecs__system})

set(core__exceptions
    "include/core/exceptions/exceptions.h"
)
source_group("core\\exceptions" FILES ${core__exceptions})

set(core__utilities
    "include/core/utilities/math.h"
    "include/core/utilities/timer.h"
	"include/core/utilities/hash/emp_hash.h"
	"include/core/utilities/hash/sha256.h"

)
source_group("core\\utilities" FILES ${core__utilities})

set( core_all_files
	
	${core}
	${core__defines}
	${core__ecs}
	${core__ecs__components}
	${core__ecs__system}
	${core__exceptions}
    ${core__utilities}

)



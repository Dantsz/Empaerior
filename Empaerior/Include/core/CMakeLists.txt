set(core
    "Include/core/core.h"
    "Include/core/point2.h"
    "Include/core/rect.h"
    "Include/core/vector2.h"
    "Include/core/unsafe_vector.h"
	"Include/core/vec.h" 
    "Include/core/mat.h"
)
source_group("core" FILES ${core})

set(core__defines
    "Include/core/defines/basic_defines.h"
    "Include/core/defines/defines.h"
    "Include/core/defines/struct_defines.h"
)
source_group("core\\defines" FILES ${core__defines})

set(core__ecs
    "Include/core/ecs/ecs.h"
    "Include/core/ecs/entity.h"
)
source_group("core\\ecs" FILES ${core__ecs})

set(core__ecs__components
    "Include/core/ecs/components/componentmanager.h"
)
source_group("core\\ecs\\components" FILES ${core__ecs__components})

set(core__ecs__system
    "Include/core/ecs/system/system.h"
)
source_group("core\\ecs\\system" FILES ${core__ecs__system})

set(core__exceptions
    "Include/core/exceptions/exceptions.h"
)
source_group("core\\exceptions" FILES ${core__exceptions})

set(core__utilities
    "Include/core/utilities/math.h"
    "Include/core/utilities/timer.h"
	"Include/core/utilities/hash/emp_hash.h"
	"Include/core/utilities/hash/sha256.h"

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



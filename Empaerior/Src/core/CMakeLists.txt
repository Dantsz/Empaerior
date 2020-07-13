set(core
    "Src/core/core.h"
    "Src/core/point2.h"
    "Src/core/rect.h"
    "Src/core/vector2.h"
    "Src/core/unsafe_vector.h"
	"Src/core/vec.h" 
    "Src/core/mat.h"
)
source_group("core" FILES ${core})

set(core__defines
    "Src/core/defines/basic_defines.h"
    "Src/core/defines/defines.h"
    "Src/core/defines/struct_defines.h"
)
source_group("core\\defines" FILES ${core__defines})

set(core__ecs
    "Src/core/ecs/ecs.h"
    "Src/core/ecs/entity.h"
)
source_group("core\\ecs" FILES ${core__ecs})

set(core__ecs__components
    "Src/core/ecs/components/componentmanager.h"
)
source_group("core\\ecs\\components" FILES ${core__ecs__components})

set(core__ecs__system
    "Src/core/ecs/system/system.h"
)
source_group("core\\ecs\\system" FILES ${core__ecs__system})

set(core__exceptions
    "Src/core/exceptions/exceptions.h"
)
source_group("core\\exceptions" FILES ${core__exceptions})

set(core__utilities
    "Src/core/utilities/math.h"
    "Src/core/utilities/timer.h"
	"Src/core/utilities/hash/emp_hash.h"
	"Src/core/utilities/hash/sha256.h"

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



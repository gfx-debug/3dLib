project(pthread)
set(
	SRC
	implement.h
	pthread.h
	sched.h
	semaphore.h
	pthread.c
)
source_group(SRC FILES ${SRC})
add_definitions(-D_USRDLL)
add_definitions(-DPTW32_BUILD)


add_library(${PROJECT_NAME} SHARED  ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "3dLib")
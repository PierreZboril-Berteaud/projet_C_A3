cmake_minimum_required(VERSION 3.25)
project(projet_C_A3)

set(CMAKE_C_STANDARD 11)


set(SRCS
		main_sim.c
	affichage.c
	fichiers.c
	fir.c
	iir.c
	mesure.c
		autotests.c
)
set(HEADERS
	affichage.h
	fichiers.h
	fir.h
	iir.h
	mesure.h
	define.h
)
add_executable(main ${SRCS} ${HEADERS})



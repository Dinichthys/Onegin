CXXFLAGS= -D _DEBUG  -ggdb -g3 -D_FORTIFY_SOURCES=3 -std=c++17 -Og -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: onegin

onegin: main.o my_io.o print_error.o sort.o logging.o qsort.o parse_argv.o
	@g++ $(CXXFLAGS) main.o my_io.o print_error.o sort.o logging.o qsort.o parse_argv.o -o onegin

main.o: main.cpp
	@g++ $(CXXFLAGS) -c main.cpp

my_io.o: my_io.cpp
	@g++ $(CXXFLAGS) -c my_io.cpp

print_error.o: print_error.cpp
	@g++ $(CXXFLAGS) -c print_error.cpp

sort.o: sort.cpp
	@g++ $(CXXFLAGS) -c sort.cpp

logging.o: logging.cpp
	@g++ $(CXXFLAGS) -c logging.cpp

qsort.o: qsort.cpp
	@g++ $(CXXFLAGS) -c qsort.cpp

parse_argv.o: parse_argv.cpp
	@g++ $(CXXFLAGS) -c parse_argv.cpp

clean:
	rm -rf *.o onegin

CCFLAGS = clang -std=c99 -g -Werror -pedantic -D_DEFAULT_SOURCE
BIN     = ./recognize

default: $(BIN)

clean:
	rm -f  ./src/*.o
	rm -f  pretreatment_demo
	rm -rf *.dSYM
	rm -f  *.png
	rm -f recognize

debug: CCFLAGS += -g
debug: clean default
	valgrind --leak-check=yes --dsymutil=yes --suppressions=objc.supp $(BIN) oui.wav

$(BIN): ./src/mfcc.o ./src/gnuplot.o ./src/narr.o ./src/dtw.o ./src/main.c
	$(CCFLAGS) -o $(BIN) $^	-lsndfile -lm

feature: ./src/mfcc.o ./src/narr.o ./src/feature.c
	$(CCFLAGS) -o ./gui/feature $^ -lsndfile -lm


distance: ./src/dtw.o ./src/narr.o ./src/distance.c
	$(CCFLAGS) -o ./gui/distance $^ -lm

./src/gnuplot.o: ./src/gnuplot.c
	$(CCFLAGS) -o $@ -c $<

./src/mfcc.o: ./src/mfcc.c
	$(CCFLAGS) -o $@ -c $<

./src/narr.o: ./NArr/src/narr.c
	$(CCFLAGS) -o $@ -c $<

./src/dtw.o: ./src/dtw.c
	$(CCFLAGS) -o $@ -c $<


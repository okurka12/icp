##################
##  Vit Pavlik  ##
##   xpavli0a   ##
##    251301    ##
##     2024     ##
##################

TARGET_BINARY=icp
GENERATED_MF=generated_makefile

.PHONY: all
all: $(TARGET_BINARY)

$(TARGET_BINARY):
	qmake -o $(GENERATED_MF)
	make -f $(GENERATED_MF)

.PHONY: clean
clean:
	if [ -f $(GENERATED_MF) ]; then make -f $(GENERATED_MF) clean; fi
	rm -rf *.o $(TARGET_BINARY) doc/html doc/latex

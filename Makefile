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
	make -f $(GENERATED_MF) clean
	rm -f *.o $(TARGET_BINARY)

##################
##  Vit Pavlik  ##
##   xpavli0a   ##
##    251301    ##
##     2024     ##
##################

TARGET_BINARY=icp
GENERATED_MF=generated_makefile
DOXY_MAINPAGE=mainpage.dox
ZIP_FILENAME=xpavli0a-xxxxxx00.zip

.PHONY: all
all: $(TARGET_BINARY)

$(TARGET_BINARY):
	qmake -o $(GENERATED_MF)
	make -f $(GENERATED_MF)

.PHONY: doxygen
doxygen:

	echo "" > $(DOXY_MAINPAGE)
	echo "/**" >> $(DOXY_MAINPAGE)
	echo "\mainpage" >> $(DOXY_MAINPAGE)
	cat doc/README.txt >> $(DOXY_MAINPAGE)
	echo "*/" >> $(DOXY_MAINPAGE)
	doxygen
	rm mainpage.dox

.PHONY: clean
clean:
	if [ -f $(GENERATED_MF) ]; then make -f $(GENERATED_MF) clean; fi
	rm -rf *.o $(TARGET_BINARY) doc/html doc/latex *.zip

.PHONY: pack
pack: clean  # notice that zipping is performed only after clean
	zip -r $(ZIP_FILENAME) *

.PHONY: run
run: all
	./$(TARGET_BINARY)

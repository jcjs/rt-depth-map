# Wadim Mueller
# central makefile to build the app,
# all objects are build and placed in the corresponding subdirs by Makefile.build and then linked here
# currently i am not able to build relocatable files in the subdirs with g++ -r, thats the reason i need to search all objects via find
include Makefile.include

subdirs := filter/ decoder/ stereo-matcher/ stream/ utils/
clean_subdirs := $(addsuffix __clean,$(subdirs))
calibration_files := extrinsics.yml intrinsics.yml

obj-y += main.o estimator.o

target := rt-depth-map.elf

all-obj = $(sort $(patsubst ./%,%,$(shell find . -type f -name \*.o)))

.PHONY: all clean $(clean_subdirs)

all: $(target)
	
copy_to_target: clean all
ifeq ($(CROSS_COMPILE),)
	@echo "need a cross compile build"
else
	@echo "[CP] $(target) $(calibration_files) to $(ROOTFS)"
	@cp $(target) $(calibration_files) $(ROOTFS)
endif
	
$(target): $(subdirs) $(obj-y)
	@echo "[LD] $@ from $(all-obj)"
	@$(CC) $(CFLAGS) -o $@ $(all-obj) $(LIBS)
	
clean: $(clean_subdirs)
	@echo "[RM] /" 
	@rm -f *.o *.elf *.d

$(clean_subdirs):
	@make $(SUBMAKE_ARGS) -f $(BUILD_MAKEFILE) obj=$(patsubst %__clean,%,$@) _clean
	
.PHONY: $(subdirs)

$(subdirs): 
	@make $(SUBMAKE_ARGS) -f $(BUILD_MAKEFILE) obj=$@ _all
	
%.o: %.cpp
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.d : ;

.PRECIOUS: %.d

-include $(obj-y:.o=.d)
-include ../../Makefile.rules

INCLUDE_DIRS := ../include ../include/conf ../../jtc/include ../../EIBStdLib/include
INCLUDE_LIBS := ../../jtc/linux ../../EIBStdLib/linux
OUT_EXE := EIBServer

# All of the sources participating in the build are defined here
-include objects.mk
DEPS := $(OBJS:%.o=%.d)
-include $(DEPS)

# All Target
all: $(OUT_EXE)

conf/%.o: ../src/conf/%.cpp
	@mkdir -p conf
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP_COMPILER) $(INCLUDE_DIRS:%=-I"%") -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $@'
	@echo 

%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP_COMPILER) $(INCLUDE_DIRS:%=-I"%") -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $@'
	@echo 

$(OUT_EXE): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CPP_LINKER) $(INCLUDE_LIBS:%=-L"%") -o"$(OUT_EXE)" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
install:
	@$(CP) $(OUT_EXE) $(INSTALL_DIR)

clean:
	-$(RM) $(OBJS) $(OBJS:%.o=%.d) $(OUT_EXE)
	-$(RM) conf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:


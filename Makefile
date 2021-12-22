CXXFLAGS += \
	-ffreestanding -fno-builtin -fno-exceptions -fno-rtti \
	-Wall -Wextra -mno-red-zone -m32 -Os -pipe

LDFLAGS  += -Tlinker.ld -nostdinc -nostdlib

Tinx: kernel.cc string.cc boot.s
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^

clean:
	$(RM) Tinx
.PHONY: clean

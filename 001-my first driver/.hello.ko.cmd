savedcmd_/home/ibrahim/deviceDriver/002-mysecond_driver/hello.ko := ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/ibrahim/deviceDriver/002-mysecond_driver/hello.ko /home/ibrahim/deviceDriver/002-mysecond_driver/hello.o /home/ibrahim/deviceDriver/002-mysecond_driver/hello.mod.o;  make -f ./arch/x86/Makefile.postlink /home/ibrahim/deviceDriver/002-mysecond_driver/hello.ko
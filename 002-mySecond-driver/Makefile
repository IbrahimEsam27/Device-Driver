#sudo apt-get install linux-headers-$(uname -r)
# sudo ln -s asm-generic asm
# sudo chmod 777 -R include
obj-m = mydriver.o
BDIR=/lib/modules/6.5.0-26-generic/build
all:
	make -C ${BDIR} M=${PWD} modules

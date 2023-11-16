# SO - Sistema Operativo

You probably can translate the project name to your own language, but SO stands for Sistema Operacional in Portuguese, when translated it means Operating System or OS.

## Build:

Requirements:

- qemu-system-i386
- nasm
- texinfo
- mpc (On Ubuntu is libmpc-dev)
- make

**NOTE:** If you already have built the cross compiler you just need to change the GCC and LD variables in the `Makefile`. This means no need to exec `./toolchain.sh`

```bash
# Clone this repo
cd so
./toolchain.sh
make
make run
```
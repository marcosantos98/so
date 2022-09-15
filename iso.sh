set -e

if grub-file --is-x86-multiboot $1/so.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi

mkdir -p $1/iso/boot/grub
cp $1/so.bin $1/iso/boot/so.bin
cp $1/grub.cfg $1/iso/boot/grub/grub.cfg
grub-mkrescue -o $1/so.iso $1/iso
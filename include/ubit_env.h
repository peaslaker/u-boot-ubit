#define CONFIG_PREBOOT "setenv preboot 'run ubi_start silent_boot; run nc_test nc_start; run usb_start'; saveenv; run ubi_start silent_boot; run nc_test nc_start; run usb_start"

#define CONFIG_EXTRA_ENV_SETTINGS \
  "ubi_start=ubi part root\0" \
  "usb_start=usb start\0" \
  \
  "nc_test=ping $ncip\0" \
  "nc_start=setenv stdin nc; setenv stdout nc; setenv stderr nc; version\0" \
  \
  "silent_boot=run silent_rd ubi_args ubi_fallback\0" \
  "fast_boot=run fast_rd ubi_args ubi_fallback\0" \
  \
  "usb_boot=run usb_args ext2_kern ext2_boot; run ext2_rd ubi_fallback; run fat_kern fat_boot; run fat_rd ubi_fallback\0" \
  "usb_args=setenv boot_dev usb 0:1; setenv dev_args root=/dev/sda1 rootdelay=10; run set_bootargs\0" \
  \
  "hd_boot=ide reset; run hd_args ext2_kern ext2_boot; run ext2_rd ubi_fallback\0" \
  "hd_args=setenv boot_dev ide 0:1; setenv dev_args root=/dev/sda1; run set_bootargs\0" \
  \
  "ubi_boot=run ubi_rd ubi_args ubi_fallback\0" \
  "ubi_args=setenv dev_args ubi.mtd=root; run set_bootargs\0" \
  \
  "preboot_boot=run preboot_rd preboot_args ubi_fallback\0" \
  "preboot_args=setenv dev_args ubi.mtd=root rootfstype=preboot; run set_bootargs\0" \
  \
  "chain=nand read.e 0x800000 0x480000 0x80000; go 0x800200\0" \
  \
  "ethact=egiga0\0" \
  \
  "console=ttyS0,115200\0" \
  "mtdids=nand0=orion_nand\0" \
  "mtdparts=mtdparts=orion_nand:1M(u-boot),4M(uImage),32M(pogoplug),-(root)\0" \
  \
  "set_bootargs=setenv bootargs console=$console $mtdparts $dev_args netconsole=@$ipaddr/eth0,@$ncipk/\0" \
  \
  "ext2_kern=ext2load $boot_dev $addr_kern /boot/uImage\0" \
  "ext2_rd=ext2load $boot_dev $addr_rd /uInitrd\0" \
  "ext2_boot=run ext2_rd boot_rd; run boot_kern\0" \
  \
  "fat_kern=fatload $boot_dev $addr_kern /boot/uImage\0" \
  "fat_rd=fatload $boot_dev $addr_rd /uInitrd\0" \
  "fat_boot=run fat_rd boot_rd\0" \
  \
  "ubi_kern=ubifsmount boot; ubifsload $addr_kern /boot/uImage\0" \
  "ubi_rd=ubifsmount ramdisk; ubifsload $addr_rd /uInitrd\0" \
  "ubi_fallback=run ubi_kern boot_rd\0" \
  \
  "silent_rd=ubifsmount silent; ubifsload $addr_rd /uInitrd\0" \
  "fast_rd=ubifsmount fast; ubifsload $addr_rd /uInitrd\0" \
  "preboot_rd=ubifsmount preboot; ubifsload $addr_rd /uInitrd\0" \
  \
  "boot_kern=bootm $addr_kern\0" \
  "boot_rd=bootm $addr_kern $addr_rd\0" \
  \
  "addr_kern=0x680000\0" \
  "addr_rd=0x1100000\0" \
  \
  "ipaddr=10.10.10.6\0" \
  "ncip=10.10.10.5\0" \
  "ncipk=10.10.10.4\0" \
  "serverip=10.10.10.3\0" \
  \
  "led_init=green blinking\0" \
  "led_exit=green off\0" \
  "led_error=orange blinking\0"


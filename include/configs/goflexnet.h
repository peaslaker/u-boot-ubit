/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef _CONFIG_GOFLEXNET_H
#define _CONFIG_GOFLEXNET_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nUBIT v0.5 for Seagate GoFlex Net by Peter Carmichael"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_MARVELL		1
#define CONFIG_ARM926EJS	1	/* Basic Architecture */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_GOFLEXNET	/* Machine type */

#define CONFIG_MD5	/* get_random_hex on krikwood needs MD5 support */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */
#define CONFIG_KIRKWOOD_EGIGA_INIT	/* Enable GbePort0/1 for kernel */
#define CONFIG_KIRKWOOD_RGMII_PAD_1V8	/* Set RGMII Pad voltage to 1.8V */

/*
 * CLKs configurations
 */
#define CONFIG_SYS_HZ		1000

/*
 * NS16550 Configuration
 */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		CONFIG_SYS_TCLK
#define CONFIG_SYS_NS16550_COM1		KW_UART0_BASE

/*
 * Serial Port configuration
 * The following definitions let you select what serial you want to use
 * for your console driver.
 */

#define CONFIG_CONS_INDEX	1	/*Console on UART0 */
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, \
					  115200,230400, 460800, 921600 }
/* auto boot */
#define CONFIG_BOOTDELAY	3	/* default enable autoboot */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_CMDLINE_TAG	1	/* enable passing of ATAGs  */
#define CONFIG_INITRD_TAG	1	/* enable INITRD tag */
#define CONFIG_SETUP_MEMORY_TAGS 1	/* enable memory tag */

#define	CONFIG_SYS_PROMPT	"Marvell>> "	/* Command Prompt */
#define	CONFIG_SYS_CBSIZE	1024	/* Console I/O Buff Size */
#define	CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE \
		+sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print Buff */

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#include <config_cmd_default.h>
#define CONFIG_CMD_AUTOSCRIPT
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "
#define CONFIG_CMD_IDE
/*
 * NAND configuration
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_KIRKWOOD
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define NAND_MAX_CHIPS			1
#define CONFIG_SYS_NAND_BASE		0xD8000000	/* KW_DEFADR_NANDF */
#define NAND_ALLOW_ERASE_ALL		1
#endif

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000	/* 128K */
#else
#define CONFIG_ENV_IS_NOWHERE		1	/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0x60000
#define CONFIG_ENV_OFFSET		0x60000	/* env starts here */

/*
 * Default environment variables
 */

#define CONFIG_EXTRA_ENV_SETTINGS \
  "nc_test=ping $ncip\0" \
  "nc_start=setenv stdin nc; setenv stdout nc; setenv stderr nc; version\0" \
  \
  "bootcmd_fast=run ubi_boot; run usb_boot; run hd_boot\0" \
  "bootcmd_go=run usb_boot; run hd_boot; run ubi_boot\0" \
  \
  "usb_boot=run usb_args ext2_kern ext2_boot; run ext2_rd ubi_fallback\0" \
  "usb_args=setenv ext2_dev usb 0:1; setenv dev_args root=/dev/sda3 rootdelay=10 rootfstype=ext3; run set_bootargs\0" \
  \
  "hd_boot=ide reset; run hd_args ext2_kern ext2_boot; run ext2_rd ubi_fallback\0" \
  "hd_args=setenv ext2_dev ide 0:1; setenv dev_args root=/dev/sda3 rootfstype=ext3; run set_bootargs\0" \
  \
  "ubi_boot=run $ubi_args ubi_rd ubi_fallback\0" \
  "ubi_args=ubi_args_default\0" \
  "ubi_args_default=setenv dev_args ubi.mtd=root root=/dev/sda1; run set_bootargs\0" \
  "ubi_args_tmpfs=setenv dev_args ubi.mtd=root rootfstype=tmpfs; run set_bootargs\0" \
  \
  "mtdids=nand0=orion_nand\0" \
  "partition=nand0,2\0" \
  "ethact=egiga0\0" \
  \
  "console=ttyS0,115200\0" \
  "mtdparts=mtdparts=orion_nand:1M(u-boot),4M(uImage),32M(pogoplug),-(root)\0" \
  \
  "set_bootargs=setenv bootargs console=$console $mtdparts $dev_args netconsole=@$ipaddr/eth0,@$ncipk/\0" \
  \
  "ext2_kern=ext2load $ext2_dev $addr_kern /boot/uImage\0" \
  "ext2_rd=ext2load $ext2_dev $addr_rd /uInitrd\0" \
  "ext2_boot=run ext2_rd boot_rd; run boot_kern\0" \
  \
  "ubi_kern=ubifsmount boot; ubifsload $addr_kern /boot/uImage\0" \
  "ubi_rd=ubifsmount ramdisk; ubifsload $addr_rd /uInitrd\0" \
  "ubi_fallback=run ubi_kern boot_rd\0" \
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


#define CONFIG_BOOTCOMMAND "ubi part root; run bootcmd_go"
#define CONFIG_PREBOOT "setenv preboot 'usb start; run nc_test nc_start'; saveenv; usb start; run nc_test nc_start"

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN	(1024 * 1024) /* 1 MiB for malloc() */
/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_SIZE	128

/*
 * Other required minimal configurations
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_ARCH_CPU_INIT	/* call arch_cpu_init() */
#define CONFIG_ARCH_MISC_INIT	/* call arch_misc_init() */
#define CONFIG_DISPLAY_CPUINFO	/* Display cpu info */
#define CONFIG_NR_DRAM_BANKS	4
#define CONFIG_STACKSIZE	0x00100000	/* regular stack- 1M */
#define CONFIG_SYS_LOAD_ADDR	0x00800000	/* default load adr- 8M */
#define CONFIG_SYS_MEMTEST_START 0x00400000	/* 4M */
#define CONFIG_SYS_MEMTEST_END	0x007fffff	/*(_8M -1) */
#define CONFIG_SYS_RESET_ADDRESS 0xffff0000	/* Rst Vector Adr */
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_NETCONSOLE	/* include NetConsole support   */
#define CONFIG_NET_MULTI	/* specify more that one ports available */
#define	CONFIG_MII		/* expose smi ove miiphy interface */
#define CONFIG_MVGBE		/* Enable Marvell Gbe Controller Driver */
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN	/* detect link using phy */
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#define CONFIG_ENV_OVERWRITE	/* ethaddr can be reprogrammed */
#define CONFIG_RESET_PHY_R	/* use reset_phy() to init mv8831116 PHY */
#endif /* CONFIG_CMD_NET */

/*
 * USB/EHCI
 */
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI			/* Enable EHCI USB support */
#define CONFIG_USB_EHCI_KIRKWOOD	/* on Kirkwood platform	*/
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_EHCI_IS_TDI
#define CONFIG_USB_STORAGE
#define CONFIG_DOS_PARTITION
#define CONFIG_ISO_PARTITION
#define CONFIG_SUPPORT_VFAT
#endif /* CONFIG_CMD_USB */

/*
 * IDe Support on SATA port0
 */
#ifdef CONFIG_CMD_IDE
#define __io
#define CONFIG_IDE_ONE_LUN_PER_CHANNEL
#define CONFIG_MVSATA_IDE
#define CONFIG_IDE_PREINIT
#define CONFIG_MVSATA_IDE_USE_PORT1
/* Needs byte-swapping for ATA data register */
#define CONFIG_IDE_SWAP_IO
/* Data, registers and alternate blocks are at the same offset */
#define CONFIG_SYS_ATA_DATA_OFFSET     (0x0100)
#define CONFIG_SYS_ATA_REG_OFFSET      (0x0100)
#define CONFIG_SYS_ATA_ALT_OFFSET      (0x0100)
/* Each 8-bit ATA register is aligned to a 4-bytes address */
#define CONFIG_SYS_ATA_STRIDE          4
/* Controller supports 48-bits LBA addressing */
#define CONFIG_LBA48
/* CONFIG_CMD_IDE requires some #defines for ATA registers */
#define CONFIG_SYS_IDE_MAXBUS          2
#define CONFIG_SYS_IDE_MAXDEVICE       2
/* ATA registers base is at SATA controller base */
#define CONFIG_SYS_ATA_BASE_ADDR       KW_SATA_BASE
/* ATA bus 0 is Kirkwood port 0 on openrd */
#define CONFIG_SYS_ATA_IDE0_OFFSET     KW_SATA_PORT0_OFFSET
/* ATA bus 1 is Kirkwood port 1 on openrd */
#define CONFIG_SYS_ATA_IDE1_OFFSET     KW_SATA_PORT1_OFFSET
#endif /* CONFIG_CMD_IDE */

/*
 * File system
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_JFFS2
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO

#define CONFIG_STATUS_LED
#define CONFIG_BOARD_SPECIFIC_LED

#undef CONFIG_SYS_FAULT_ECHO_LINK_DOWN // Fix

#define STATUS_LED_GREEN   0
#define STATUS_LED_RED     1

#define STATUS_LED_BIT     STATUS_LED_GREEN
#define STATUS_LED_STATE   STATUS_LED_OFF
#define STATUS_LED_PERIOD  (CONFIG_SYS_HZ /4)

#define STATUS_LED_BIT1    STATUS_LED_RED
#define STATUS_LED_STATE1  STATUS_LED_OFF
#define STATUS_LED_PERIOD1 (CONFIG_SYS_HZ /4)

#endif /* _CONFIG_GOFLEXNET_H */

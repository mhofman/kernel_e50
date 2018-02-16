#ifndef __RALINK_FLASH_H__
#define __RALINK_FLASH_H__

/* 
 * UBNT flash layout
 * --------------------
 * | bootloader 512K  |
 * --------------------
 * | config 384K      |
 * --------------------
 * | factory 384K     |
 * --------------------
 * | kernel 3072K     |
 * --------------------
 * | kernel2 3072K    |
 * --------------------
 * | rootfs 253696K   |
 * | or               |
 * | rootfs 512768K   |
 * --------------------
 * | badblock 4096K   |
 * --------------------
 *
 */

#define MTD_BOOT_PART_SIZE  0x80000 /* 512KB */
#define MTD_CONFIG_PART_SIZE    0x60000 /* 384KB */
#define MTD_FACTORY_PART_SIZE   0x60000 /* 384KB */

#define CONFIG_MTD_KERNEL_PART_SIZ 0x300000 /* 3072KB */
#define MTD_KERN_PART_QTY 2 /* two kernel MTD partitions */
#define MTD_KERN_PART_SIZE CONFIG_MTD_KERNEL_PART_SIZ
#define MTD_ROOTFS_PART_SIZE 0x1f4c0000 /* 512768KB */

#define IMAGE1_SIZE \
	(MTD_BOOT_PART_SIZE + MTD_CONFIG_PART_SIZE + MTD_FACTORY_PART_SIZE \
     + (MTD_KERN_PART_SIZE * MTD_KERN_PART_QTY) + MTD_ROOTFS_PART_SIZE)
#define MTD_ROOTFS_START_OFF \
	(MTD_BOOT_PART_SIZE + MTD_CONFIG_PART_SIZE + MTD_FACTORY_PART_SIZE \
     + (MTD_KERN_PART_SIZE * MTD_KERN_PART_QTY))
#define MTD_ROOTFS_END_OFF IMAGE1_SIZE

#if 0
#if defined (CONFIG_RT2880_FLASH_32M)
#define MTD_BOOT_PART_SIZE	0x40000
#define	MTD_CONFIG_PART_SIZE	0x20000
#define	MTD_FACTORY_PART_SIZE	0x20000
#else
#if defined (RECONFIG_PARTITION_SIZE)
#if !defined (MTD_BOOT_PART_SIZE)
#error "Please define MTD_BOOT_PART_SIZE"
#endif
#if !defined (MTD_CONFIG_PART_SIZE)
#error "Please define MTD_CONFIG_PART_SIZE"
#endif
#if !defined (MTD_FACTORY_PART_SIZE)
#error "Please define MTD_FACTORY_PART_SIZE"
#endif
#else
#define MTD_BOOT_PART_SIZE	0x30000
#define	MTD_CONFIG_PART_SIZE	0x10000
#define	MTD_FACTORY_PART_SIZE	0x10000
#endif
#endif


#ifdef CONFIG_RT2880_ROOTFS_IN_FLASH
#ifdef CONFIG_ROOTFS_IN_FLASH_NO_PADDING
#define CONFIG_MTD_KERNEL_PART_SIZ 0
#endif
#define MTD_ROOTFS_PART_SIZE	IMAGE1_SIZE - (MTD_BOOT_PART_SIZE + MTD_CONFIG_PART_SIZE \
					+ MTD_FACTORY_PART_SIZE + CONFIG_MTD_KERNEL_PART_SIZ)
#define	MTD_KERN_PART_SIZE	CONFIG_MTD_KERNEL_PART_SIZ
#else
#define MTD_KERN_PART_SIZE	IMAGE1_SIZE - (MTD_BOOT_PART_SIZE + MTD_CONFIG_PART_SIZE \
					+ MTD_FACTORY_PART_SIZE)
#endif


#ifdef CONFIG_DUAL_IMAGE
#if defined (CONFIG_RT2880_FLASH_2M)
#define IMAGE1_SIZE		0x100000
#elif defined (CONFIG_RT2880_FLASH_4M)
#define IMAGE1_SIZE		0x200000
#elif defined (CONFIG_RT2880_FLASH_8M)
#define IMAGE1_SIZE		0x400000
#elif defined (CONFIG_RT2880_FLASH_16M)
#define IMAGE1_SIZE		0x800000
#elif defined (CONFIG_RT2880_FLASH_32M)
#define IMAGE1_SIZE		0x1000000
#endif

#define MTD_KERN2_PART_SIZE	MTD_KERN_PART_SIZE
#define MTD_KERN2_PART_OFFSET	IMAGE1_SIZE + (MTD_BOOT_PART_SIZE + MTD_CONFIG_PART_SIZE \
					+ MTD_FACTORY_PART_SIZE)

#ifdef CONFIG_RT2880_ROOTFS_IN_FLASH
#define MTD_ROOTFS2_PART_SIZE 	MTD_ROOTFS_PART_SIZE	
#define MTD_ROOTFS2_PART_OFFSET (MTD_KERN2_PART_OFFSET + MTD_KERN2_PART_SIZE)
#endif

#else // Non Dual Image
#if defined (CONFIG_RT2880_FLASH_2M)
#define IMAGE1_SIZE		0x200000
#elif defined (CONFIG_RT2880_FLASH_4M)
#define IMAGE1_SIZE		0x400000
#elif defined (CONFIG_RT2880_FLASH_8M)
#define IMAGE1_SIZE		0x800000
#elif defined (CONFIG_RT2880_FLASH_16M)
#define IMAGE1_SIZE		0x1000000
#elif defined (CONFIG_RT2880_FLASH_32M)
#define IMAGE1_SIZE		0x2000000
#else
#define IMAGE1_SIZE		CONFIG_MTD_PHYSMAP_LEN
#endif
#endif
#endif /* 0 */

#define BOOT_FROM_NOR	0
#define BOOT_FROM_NAND	2
#define BOOT_FROM_SPI	3

int ra_check_flash_type(void);

#endif //__RALINK_FLASH_H__

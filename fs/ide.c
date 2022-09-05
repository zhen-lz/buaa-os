/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurrs during the read of the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
/*** exercise 5.2 ***/
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int read_offset;
	int read_status = 0;
	int disk_status;
	int r;

	while (offset_begin + offset < offset_end) {
		// Your code here
		// error occurred, then panic.
		if ((r = syscall_write_dev(&diskno, 0x13000010, 4)) != 0) {
			user_panic("write diskno failed!\n");
		}
		read_offset = offset_begin + offset;
		if ((r = syscall_write_dev(&read_offset, 0x13000000, 4)) != 0) {
			user_panic("write offset failed!\n");
		}
		if ((r = syscall_write_dev(&read_status, 0x13000020, 4)) != 0) {
			user_panic("write read status failed!\n");
		}
		if ((r = syscall_read_dev(&disk_status, 0x13000030, 4)) != 0) {
			user_panic("read the return value failed!\n");
		}
		if (disk_status == 0) {
			user_panic("ide read failed!\n");
		}
		if ((r = syscall_read_dev(dst + offset, 0x13004000, 512)) != 0) {
			user_panic("read 512 bytes data failed!\n");
		}
		offset += 0x200;
	}
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurrs during the read of the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
/*** exercise 5.2 ***/
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
	// Your code here
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int write_offset;
	int write_status = 1;
	int disk_status;
	int r;
	// DO NOT DELETE WRITEF !!!
	writef("diskno: %d\n", diskno);

	while (offset_begin + offset < offset_end) {
		// copy data from source array to disk buffer.
		if ((r = syscall_write_dev(&diskno, 0x13000010, 4)) != 0) {
            user_panic("write diskno failed!\n");
        }
		write_offset = offset_begin + offset;
        if ((r = syscall_write_dev(&write_offset, 0x13000000, 4)) != 0) {
            user_panic("write offset failed!\n");
        }
		if ((r = syscall_write_dev(src + offset, 0x13004000, 512)) != 0) {
            user_panic("write 512 bytes data failed!\n");
        }
        if ((r = syscall_write_dev(&write_status, 0x13000020, 4)) != 0) {
            user_panic("write write status failed!\n");
        }
        if ((r = syscall_read_dev(&disk_status, 0x13000030, 4)) != 0) {
            user_panic("read the return value failed!\n");
        }
        if (disk_status == 0) {
            user_panic("ide read failed!\n");
        }
        offset += 0x200;
		// if error occur, then panic.
	}
}

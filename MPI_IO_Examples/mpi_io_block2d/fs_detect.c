#include <stdio.h>
#include <sys/statfs.h>
// File system types are listed in system include directory in linux/magic.h
// You will need to add any additional parallel file system magic codes
#define LUSTRE_MAGIC1    0x858458f6
#define LUSTRE_MAGIC2    0xbd00bd0
#define GPFS_SUPER_MAGIC 0x47504653
#define PVFS2_SUPER_MAGIC 0x20030528
#define PAN_KERNEL_FS_CLIENT_SUPER_MAGIC  0xAAD7AAEA

int main(int argc, char *argv[])
{
  struct statfs buf;
  statfs("./fs_detect", &buf);
  printf("File system type is %lx\n",buf.f_type);
}

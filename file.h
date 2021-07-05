#ifndef __FILE_H__
#define __FILE_H__

typedef struct filelist {
	struct File *info;
	struct filelist *next;
} filelist;
typedef struct dirlist {
	struct Directory *info;
	struct dirlist *next;
} dirlist;
typedef struct Directory {

	char *name;

	filelist *l;

	dirlist *d;

	struct Directory *parentDir;
} Directory;

typedef struct File {

	char *name;

	int size;

	char *data;

	Directory *dir;
} File;

#endif /* __FILE_H__ */


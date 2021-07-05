#include <stdio.h>

#include "file.h"

#include <stdlib.h>

#include <string.h>

void create_fs(Directory **a)
{
	char c[4];

	scanf("%s", c);
	if (strcmp(c, "fs") == 0) {
		(*a) = (Directory *) malloc(sizeof(Directory));
		(*a)->name = (char *) malloc(2 * sizeof(char));
		strcpy((*a)->name, "/");
		(*a)->parentDir = NULL;
		(*a)->d = NULL;
		(*a)->l = NULL;
	}
}
void delete_fs2(Directory **a)
{
	if ((*a)->parentDir == NULL) {
		free((*a)->name);
		free(*a);
	}
}
void delete_fs(Directory **a)
{
	dirlist *dir = (*a)->d;

	filelist *file = (*a)->l;

	filelist *aux = file;

	dirlist *aux2 = dir;

	while ((dir != NULL || file != NULL)) {
		while (file != NULL) {
			free(file->info->name);
			free(file->info->data);
			free(file->info);
			aux = file;
			file = file->next;
			free(aux);
		}
		while (dir != NULL) {
			if (dir->info->d != NULL || dir->info->l != NULL) {
				delete_fs(&dir->info);
				free(dir->info->name);
				free(dir->info);
				free(dir);
			} else {
				free(dir->info->name);
				free(dir->info);
				aux2 = dir;

				free(aux2);
			}
			dir = dir->next;
		}
	}
}
void touch(Directory **a)
{
	filelist *c = NULL;
	filelist *q = NULL;
	filelist *aux = NULL;
	char nume[10];

	scanf("%s", nume);
	if ((*a)->l == NULL || strcmp((*a)->l->info->name, nume) > 0) {
		if ((*a)->l == NULL) {
			(*a)->l = (filelist *) malloc(sizeof(filelist));
			(*a)->l->info = (File *) malloc(sizeof(File));
			(*a)->l->info->name = (char *)malloc(sizeof(char) * 20);
			(*a)->l->info->data = (char *)malloc(sizeof(char) * 10);
			strcpy((*a)->l->info->name, nume);
			scanf("%d", &(*a)->l->info->size);
			scanf("%s", (*a)->l->info->data);
			(*a)->l->info->dir = *a;
			(*a)->l->next = NULL;
		}
		if (strcmp((*a)->l->info->name, nume) > 0) {
			c = (filelist *) malloc(sizeof(filelist));
			c->info = (File *) malloc(sizeof(File));
			c->info->name = (char *)malloc(sizeof(char) * 20);
			c->info->data = (char *)malloc(sizeof(char) * 10);
			strcpy(c->info->name, nume);
			scanf("%d", &c->info->size);
			scanf("%s", c->info->data);
			c->info->dir = *a;
			c->next = NULL;
			c->next = (*a)->l;
			(*a)->l = c;
		}
	} else {
		q = (*a)->l;
		c = (filelist *) malloc(sizeof(filelist));
		c->info = (File *) malloc(sizeof(File));
		c->info->name = (char *)malloc(sizeof(char) * 20);
		c->info->data = (char *)malloc(sizeof(char) * 10);
		strcpy(c->info->name, nume);
		scanf("%d", &c->info->size);
		scanf("%s", c->info->data);
		c->info->dir = *a;
		while (q->next != NULL
&& strcmp(q->next->info->name, c->info->name) < 0)
			q = q->next;
		aux = q->next;
		q->next = c;
		c->next = aux;
	}
}
void mkdir(Directory **a)
{
	dirlist *c = NULL;
	dirlist *q = NULL;
	dirlist *aux = NULL;
	char nume[10];

	scanf("%s", nume);
	if ((*a)->d == NULL || strcmp((*a)->d->info->name, nume) > 0) {
		if ((*a)->d == NULL) {
			(*a)->d = (dirlist *) malloc(sizeof(dirlist));
			(*a)->d->info = (Directory *)malloc(sizeof(Directory));
			(*a)->d->info->name = (char *)malloc(sizeof(char) * 10);
			strcpy((*a)->d->info->name, nume);
			(*a)->d->info->l = NULL;
			(*a)->d->info->d = NULL;
			(*a)->d->info->parentDir = *a;
			(*a)->d->next = NULL;
		}
		if (strcmp((*a)->d->info->name, nume) > 0) {
			c = (dirlist *) malloc(sizeof(dirlist));
			c->info = (Directory *) malloc(sizeof(Directory));
			c->info->name = (char *) malloc(sizeof(char) * 10);
			strcpy(c->info->name, nume);
			c->info->d = NULL;
			c->info->l = NULL;
			c->info->parentDir = *a;
			c->next = (*a)->d;
			(*a)->d = c;
		}
	} else {
		q = (*a)->d;
		c = (dirlist *) malloc(sizeof(dirlist));
		c->info = (Directory *) malloc(sizeof(Directory));
		c->info->name = (char *) malloc(sizeof(char) * 10);
		strcpy(c->info->name, nume);
		c->info->d = NULL;
		c->info->l = NULL;
		c->info->parentDir = *a;
		while (q->next != NULL
&& strcmp(q->next->info->name, c->info->name) < 0)
			q = q->next;
		aux = q->next;
		q->next = c;
		c->next = aux;
	}
}
Directory *cd(Directory *a)
{
	dirlist *b = a->d;
	char c[10];

	Directory *x;

	scanf("%s", c);
	int contor = 0;

	if (strcmp(c, "..") == 0) {
		if (strcmp(a->name, "/") == 0)
			return a;
		a = a->parentDir;
		return a;
	}
	if (b == NULL) {
		printf("Cannot move to '%s': No such directory!\n", c);
		return a;
	}
	if (b->next == NULL) {
		if (strcmp(b->info->name, c) == 0) {
			x = a;
			a = b->info;
			a->parentDir = x;
			return a;
		}
		printf("Cannot move to '%s': No such directory!\n", c);
		return a;
	}
	while (b != NULL) {
		if (strcmp(b->info->name, c) == 0) {
			contor++;
			break;
		}
		b = b->next;
	}
	if (contor != 0) {
		x = a;
		a = b->info;
		a->parentDir = x;
		return a;
	}
	printf("Cannot move to '%s': No such directory!\n", c);
	return a;
}
void tree(Directory *a)
{
	dirlist *b = a->d;
	filelist *c = a->l;
	static int contor = 1;
	int i;

	while (c != NULL) {
		for (i = 0; i < contor; i++)
			printf("    ");
		printf("%s\n", c->info->name);
		c = c->next;
	}
	while (b != NULL) {
		if (b->info->d != NULL || b->info->l != NULL) {
			for (i = 0; i < contor; i++)
				printf("    ");
			printf("%s\n", b->info->name);
			contor++;
			tree(b->info);
			contor--;
		} else {
			for (i = 0; i < contor; i++)
				printf("    ");
			printf("%s\n", b->info->name);
		}
		b = b->next;
	}
}
void pwd(Directory *a)
{
	if (a->parentDir != NULL) {
		pwd(a->parentDir);
		printf("/");
		printf("%s", a->name);
	} else {
		return;
	}
}
void ls(Directory *a)
{
	filelist *c = a->l;
	dirlist *d = a->d;

	while (c != NULL) {
		printf("%s ", c->info->name);
		c = c->next;
	}
	while (d != NULL) {
		printf("%s ", d->info->name);
		d = d->next;
	}
	printf("\n");
}
void rm(Directory **a)
{
	char dir_to_remove[10];

	scanf("%s", dir_to_remove);
	filelist *c = (*a)->l;

	if (c == NULL) {
		printf("Cannot remove '%s': No such file!\n",
dir_to_remove);
	} else {
		if (strcmp(c->info->name, dir_to_remove) == 0) {
			(*a)->l = c->next;
			c->next = NULL;
			free(c->info->name);
			free(c->info->data);
			free(c->info);
			free(c);
		} else {
			filelist *prev;

			while (c != NULL
&& strcmp(c->info->name, dir_to_remove) != 0) {
				prev = c;
				c = c->next;
			}
			if (c != NULL) {
				free(c->info->name);
				free(c->info->data);
				free(c->info);
				prev->next = c->next;
				c->next = NULL;
				free(c);
			} else {
				printf("Cannot remove '%s': No such file!\n",
dir_to_remove);
			}
		}
	}
}
void rm_for_rmdir(Directory *a)
{
	filelist *c;

	while (a->l != NULL) {
		c = a->l;
		a->l = c->next;
		c->next = NULL;
		free(c->info->name);
		free(c->info->data);
		free(c->info);
		free(c);
	}
}
void rm_directoare(Directory *a)
{
	dirlist *q = a->d;

	a->d = q->next;
	q->next = NULL;
	free(q->info->name);
	free(q->info);
	free(q);
}
void rm_ultimuldir(Directory *a, dirlist *c, char *dir)
{
	dirlist *t;

	if (strcmp(dir, c->info->name) == 0) {
		a->d = c->next;
		c->next = NULL;
		free(c->info->name);
		free(c->info);
		free(c);
	} else {
		while (strcmp(dir, c->info->name) != 0) {
			t = c;
			c = c->next;
		}
		t->next = c->next;
		c->next = NULL;
		free(c->info->name);
		free(c->info);
		free(c);
	}
}
void recursive(Directory *a)
{
	dirlist *stersdir = a->d;
	filelist *stersfile = a->l;

	while (stersfile != NULL) {
		rm_for_rmdir(a);
		stersfile = a->l;
	}
	while (stersdir != NULL) {
		if (stersdir->info->l != NULL || stersdir->info->d != NULL) {
			recursive(stersdir->info);
			rm_directoare(a);
			stersdir = a->d;

		} else {
			rm_directoare(a);
			stersdir = a->d;
		}
	}

}
void rmdir(Directory *a)
{
	char dir_to_remove[10];

	scanf("%s", dir_to_remove);
	dirlist *c = a->d;

	filelist *stersfile;

	dirlist *stersdir;

	if (c == NULL)
		printf("Cannot remove '%s': No such directory!\n",
dir_to_remove);
	else {
		while (c != NULL && strcmp(c->info->name, dir_to_remove) != 0)
			c = c->next;
		if (c != NULL) {
			a = c->info;
			stersfile = a->l;
			stersdir = a->d;
			if (stersfile != NULL || stersdir != NULL) {
				recursive(a);
				a = a->parentDir;
				rm_ultimuldir(a, a->d, dir_to_remove);

			} else {
				a = a->parentDir;
				rm_ultimuldir(a, a->d, dir_to_remove);
			}
		} else {
			printf("Cannot remove '%s': No such directory!\n",
dir_to_remove);
		}
	}
}
void recursive_find(Directory *a, int depth, int min, int max, char *c)
{
	filelist *file = a->l;

	dirlist *dir = a->d;

	static int contor;

	while (file != NULL) {
		if (strlen(file->info->data) >= min
&& strlen(file->info->data) <= max && strstr(file->info->data, c))
			printf("%s ", file->info->name);
		file = file->next;
	}
	while (dir != NULL && contor < depth) {
		if (dir->info->l != NULL
|| (dir->info->d != NULL && contor < depth)) {
			contor++;
			recursive_find(dir->info, depth, min, max, c);
			contor--;
			dir = dir->next;
		} else {
			contor--;
		}
	}
}
void find(Directory *a)
{
	int depth, min, max;
	char c[10];

	filelist *file = a->l;

	scanf("%d", &depth);
	scanf("%d", &min);
	scanf("%d", &max);
	scanf("%s", c);
	if (depth != 0)
		recursive_find(a, depth, min, max, c);
	else {
		while (file != NULL) {
			if (strlen(file->info->data) >= min
&& strlen(file->info->data) <= max && strstr(file->info->data, c))
				printf("%s ", file->info->name);
			file = file->next;
		}
	}
}
int main(void)
{
	Directory *a;
	char buffer[100];

	while (scanf("%s", buffer) != EOF) {
		if (strcmp(buffer, "delete") == 0) {
			char c[4];

			scanf("%s", c);
			if (strcmp(c, "fs") == 0) {
				while (strcmp(a->name, "/") != 0)
					a = a->parentDir;
				delete_fs(&a);
				delete_fs2(&a);
			}
			break;
		}
		if (strcmp(buffer, "create") == 0)
			create_fs(&a);
		if (strcmp(buffer, "touch") == 0)
			touch(&a);
		if (strcmp(buffer, "mkdir") == 0)
			mkdir(&a);
		if (strcmp(buffer, "ls") == 0)
			ls(a);
		if (strcmp(buffer, "cd") == 0)
			a = cd(a);
		if (strcmp(buffer, "pwd") == 0) {
			pwd(a);
			if (a->parentDir == NULL)
				printf("/");
			printf("\n");
		}
		if (strcmp(buffer, "rm") == 0)
			rm(&a);
		if (strcmp(buffer, "tree") == 0) {
			printf("%s\n", a->name);
			tree(a);
		}
		if (strcmp(buffer, "rmdir") == 0)
			rmdir(a);
		if (strcmp(buffer, "find") == 0) {
			find(a);
			printf("\n");
		}
	}
	return 0;
}

#include "../include/apue.h" 
#include <errno.h>
#include <fcntl.h>
#include <stropts.h>

int ptym_open(char *pts_name, int pts_namesz) {
	char *ptr;
	int fdm;

	strncpy(pts_name, "/dev/ptmx", pts_namesz);
	pts_name[pts_namesz - 1] = '\0';
	if ((fdm = open(pts_name, O_RDWR)) < 0)
		return (-1);
	if (grantpt(fdm) < 0){ /* grant access to slave */
		close(fdm);
		return (-2);
	}
	if (unblock(fdm) < 0) {
		close(fdm);
		return (-3);
	}
	if ((ptr = ptsname(fdm)) == NULL) {
		close(fdm);
		return (-4);
	}
	strncpy(pts_name, ptr, pts_namesz);
	pts_name[pts_namesz - 1] = '\0';
	return (fdm);
}

int ptys_open(char *pts_name) {
	int fds, setup;

	/* The following open should allocate a controlling terminal */
	if ((fds = open(pts_name, O_RDWR)) < 0)
		return (-5);
	
	/* check if stream is already set up by autopush facility */
	if ((setup = ioctl(fds, I_FIND, "ldterm")) < 0) {
		close(fds);
		return (-6);
	}
	
	if (setup == 0) { 
		if (ioctl(fds, I_PUSH, "ptem") < 0) {
			close(fds);
			return (-7);
		}
		if (ioctl(fds, I_PUSH, "idterm") < 0) {
			close(fds);
			return (-8);
		}
		if (ioctl(fds, I_PUSH, "ttcompat") < 0) {
			clsoe(fds);
			return (-9);
		} 
	}
	return (fds);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>

// definitions from pwd.h and grp.h from bionic
struct passwd {
  char* pw_name;
  char* pw_passwd;
  uid_t pw_uid;
  gid_t pw_gid;
#ifdef __LP64__
  char* pw_gecos;
#else
  /* Note: On LP32, we define pw_gecos to pw_passwd since they're both NULL. */
# define pw_gecos pw_passwd
#endif
  char* pw_dir;
  char* pw_shell;
};

struct group {
  char* gr_name; /* group name */
  char* gr_passwd; /* group password */
  gid_t gr_gid; /* group id */
  char** gr_mem; /* group members */
};



static gid_t termux_gid = -1;
static uid_t termux_uid = -1;
static struct passwd *(*__getpwuid)(uid_t uid) = NULL;

struct passwd *getpwuid(uid_t uid) {
  if (__getpwuid == NULL) {
    __getpwuid = dlsym(RTLD_NEXT, "getpwuid");
    if (dlerror() != NULL) {
      errno = EIO;
      return NULL;
    }
  }
  if (termux_uid == -1) {
    struct stat s;
    if (stat("/data/data/com.termux",&s) == 0) {
      termux_uid = s.st_uid;
      termux_gid = s.st_gid;
    }
  }
  struct passwd* p = __getpwuid(uid);
  if (p == NULL) return NULL;
  if (uid == termux_uid) {
    p->pw_name = "termux";
  }
  return p;
}

static struct group *(*__getgrgid)(gid_t gid) = NULL;

struct group *getgrgid(gid_t gid) {
  if (__getgrgid == NULL) {
    __getgrgid = dlsym(RTLD_NEXT, "getgrgid");
    if (dlerror() != NULL) {
      errno = EIO;
      return NULL;
    }
  }
  if (termux_gid == -1) {
    struct stat s;
    if (stat("/data/data/com.termux",&s) == 0) {
      termux_uid = s.st_uid;
      termux_gid = s.st_gid;
    }
  }
  struct group* g = __getgrgid(gid);
  if (g == NULL) return NULL;
  if (gid == termux_gid) {
    g->gr_name = "termux";
  }
  return g;
}



